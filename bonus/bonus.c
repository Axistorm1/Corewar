#include "bonus.h"
#include "op.h"
#include "structures.h"
#include "my_stdlib.h"
#include <alloca.h>
#include <ctype.h>
#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

windows_jungle_t *jungle = NULL;
bool light_mode = false;

static int wgetch_l(WINDOW *window)
{
    return tolower(wgetch(window));
}

// make memory arena wrap around itself
static void update_arena_window(arena_t *arena)
{
    WINDOW *wd = jungle->arena;

    int cols = getmaxx(wd) / 2;
    int lines = getmaxy(wd) - 2;

    int start_pos = (jungle->arena_mem_line * cols) % MEM_SIZE;
    if (start_pos < 0)
        start_pos = 0;
    if (start_pos >= MEM_SIZE)
        start_pos = MEM_SIZE - 1;

    // cursors
    byte1_t cursors[MEM_SIZE];
    memset(cursors, 0, MEM_SIZE);
    if (jungle->cursors)
        for (byte4_t i = 0; i < arena->process_count; i++)
            cursors[arena->processes[i]->pc] = arena->processes[i]->robot->prog_num % TOTAL_COLORS;

    werase(wd);
    wmove(wd, 0, 0);
    for (int y = 0; y < lines; y++) {
        for (int x = 0; x < cols; x++) {
            int pos = (start_pos + y * cols + x) % MEM_SIZE;
            if (pos < MEM_SIZE) {
                int color_pair = cursors[pos] * TOTAL_COLORS + arena->ownership_map[pos] % TOTAL_COLORS;
                wattron(wd, COLOR_PAIR(color_pair));
                mvwprintw(wd, y + 1, (x << 1) + 1, "%02X", arena->memory[pos]);
                wattroff(wd, COLOR_PAIR(color_pair));
            }
        }
    }
}

static void update_champions_info_window(arena_t *arena, corewar_data_t *data)
{
    WINDOW *wd = jungle->champions_info;
    robot_info_t *robot = data->robots[jungle->current_robot_info];

    werase(wd);

    wattron(wd, A_UNDERLINE);
    mvwprintw(wd, 1, 2, "%s -> #%d", robot->header->prog_name, robot->prog_num);
    wattroff(wd, A_UNDERLINE);

    wmove(wd, 3, 1);

    // print comment
    byte4_t max_width = (byte4_t)getmaxx(wd) - 4;
    sbyte4_t max_height = (sbyte4_t)(getmaxy(wd) - 4);
    byte4_t pos = 0;
    byte4_t len = (byte4_t)strlen(robot->header->comment);
    for (byte1_t i = 0; i < max_height - 3; i++) {
        byte4_t line_len = (len - pos > max_width) ? max_width : len - pos;
        mvwprintw(wd, getcury(wd) + (pos > 0 ? 1 : 0), 2, "%.*s", line_len, robot->header->comment + pos);
        pos += line_len;
    }
    if (len > max_width * (byte4_t)(max_height - 3))
        mvwprintw(wd, max_height - 1, (sbyte4_t)max_width - 1, "...");

    // status
    mvwprintw(wd, max_height + 1, 2, "Status: ");
    if (robot->alive) {
        wattron(wd, COLOR_PAIR(2));
        mvwprintw(wd, max_height + 1, 10, "Alive");
        wattroff(wd, COLOR_PAIR(2));
    } else {
        wattron(wd, COLOR_PAIR(1));
        mvwprintw(wd, max_height + 1, 10, "Dead");
        wattroff(wd, COLOR_PAIR(1));
    }

    mvwprintw(wd, max_height + 2, 2, "Process count: %d  ->  %.1f%%     ", robot->process_count, (float)robot->process_count / (float)arena->process_count * 100);
    wprintw(wd, "Starting adress: %d", robot->mem_adr);
}

static void update_processes_info_window(arena_t *arena)
{
    WINDOW *wd = jungle->processes_info;
    byte4_t max_height = (byte4_t)getmaxy(wd) - 2;

    werase(wd);

    for (byte4_t i = 0; i + (byte4_t)jungle->shown_process < arena->process_count && i < max_height; i++) {
        process_data_t *data = arena->processes[i + (byte4_t)jungle->shown_process];
        wattron(wd, COLOR_PAIR(data->robot->prog_num % TOTAL_COLORS));
        mvwprintw(wd, (sbyte4_t)i + 1, 1, "Process #%-3d", i + 1 + (byte4_t)jungle->shown_process);
        wprintw(wd,  "%5s -> {", op_tab[data->instruction->op_code].mnemonique);
        for (byte1_t i = 0; i < REG_NUMBER - 1; i++)
            wprintw(wd, "%d,", data->registers[i]);
        wprintw(wd, "%d}", data->registers[15]);
        wattroff(wd, COLOR_PAIR(data->robot->prog_num % TOTAL_COLORS));
    }
}

static int compare(const void* a, const void* b)
{
    byte4_t x = *(byte4_t*)a;
    byte4_t y = *(byte4_t*)b;
    return (x > y) - (x < y);
}

static void update_game_info(arena_t *arena)
{
    WINDOW *wd = jungle->game_info;

    werase(wd);

    mvwprintw(wd, 1, 2, "Cycle: %d/%d", arena->current_cycle, arena->cycle_to_die);
    mvwprintw(wd, 1, 25, "Total: %d", arena->total_cycles);
    mvwprintw(wd, 1, 40, "+%d/s", jungle->cycling_speed);

    // process count color
    int color = COLOR_GREEN;

    if (arena->process_count > 1000)
        color = COLOR_YELLOW;
    if (arena->process_count > 10000)
        color = COLOR_ORANGE;
    if (arena->process_count > 100000)
        color = COLOR_RED;
    if (arena->process_count == 999999)
        color = COLOR_BLACK + TOTAL_COLORS;

    mvwprintw(wd, 3, 2, "Process count: ");
    wattron(wd, COLOR_PAIR(color));
    mvwprintw(wd, 3, 17, "%d", arena->process_count);
    wattroff(wd, COLOR_PAIR(color));
    mvwprintw(wd, 3, 25, "Live count: ");
    // color for the live count
    if (arena->nbr_live == NBR_LIVE) {
        wattron(wd, COLOR_PAIR(2));
        mvwprintw(wd, 3, 37, "%d/%d\n", NBR_LIVE, NBR_LIVE);
        wattroff(wd, COLOR_PAIR(2));
    } else {
        wattron(wd, COLOR_PAIR(1));
        mvwprintw(wd, 3, 37, "%d/%d\n", arena->nbr_live, NBR_LIVE);
        wattroff(wd, COLOR_PAIR(1));
    }

    mvwprintw(wd, 4, 2, "Dead processes: %d", arena->dead_process_count);

    // this is the math to get the % of ownership
    byte4_t *copy = alloca(MEM_SIZE * sizeof(byte4_t));
    memcpy(copy, arena->ownership_map, MEM_SIZE * sizeof(byte4_t));

    qsort(copy, MEM_SIZE, 4, compare);

    byte4_t current = copy[0];
    byte4_t count = 1;
    byte2_t current_robot = 0;
    float percentages[arena->robots_alive + 1];
    byte4_t values[arena->robots_alive + 1];

    for (byte2_t i = 1; i < MEM_SIZE; i++) {
        if (copy[i] == current)
            count++;
        else {
            percentages[current_robot] = (float)count / (float)MEM_SIZE;
            values[current_robot] = current;
            current_robot++;
            current = copy[i];
            count = 1;
        }
    }
    percentages[current_robot] = (float)count / (float)MEM_SIZE;
    values[current_robot] = current;

    // draw the line
    wattron(wd, A_UNDERLINE);
    mvwprintw(wd, getmaxy(wd) - 3, getmaxx(wd) / 2 - 6, "Arena share:\n");
    wattroff(wd, A_UNDERLINE);

    int max_width = getmaxx(wd) - 4;
    int current_x = 2;

    for (byte2_t i = 0; i < arena->robots_alive + 1; i++) {
        int segment_width = (int)((float)max_width * percentages[i]);
        if (segment_width <= 0)
            continue;

        wmove(wd, getcury(wd), current_x);
        if (values[i] == 0) {
            wattron(wd, COLOR_PAIR(TOTAL_COLORS * (COLOR_WHITE)));
            whline(wd, ' ', segment_width);
            wattroff(wd, COLOR_PAIR(TOTAL_COLORS * (COLOR_WHITE)));
        } else {
            wattron(wd, COLOR_PAIR(values[i] % TOTAL_COLORS * TOTAL_COLORS + 1));
            whline(wd, ' ', segment_width);
            wattroff(wd, COLOR_PAIR(values[i] % TOTAL_COLORS * TOTAL_COLORS + 1));
        }

        current_x += segment_width;
        if (current_x >= max_width)
            break;
    }
}

// add colors
// add a drawing based on remaining side based on each line
void update_console_window(char *str, byte2_t prog_num)
{
    WINDOW *wd = jungle->console;
    int max_messages = getmaxy(wd) - 5;

    if (!str)
        goto draw;

    static char *messages[100];
    static byte2_t prog_nums[100];
    static byte1_t current_messages = 0;
    static byte4_t total_messages = 0;

    // handle messages
    if (current_messages >= max_messages) {
        free(messages[0]);
        for (byte1_t i = 0; i < current_messages - 1; i++) {
            messages[i] = messages[i + 1];
            prog_nums[i] = prog_nums[i + 1];
        }
        current_messages--;
    }
    messages[current_messages] = strdup(str);
    prog_nums[current_messages] = prog_num % TOTAL_COLORS;
    current_messages++;
    total_messages++;

    draw:
    werase(wd);

    wattron(wd, A_UNDERLINE);
    mvwprintw(wd, 1, getmaxx(wd) / 2 - 5, "CONSOLE:\n");
    wattroff(wd, A_UNDERLINE);

    for (byte1_t i = 0; i < current_messages; i++) {
        mvwprintw(wd, i + 3 + max_messages - current_messages, 2, "%2d: ", total_messages - current_messages + i + 1);
        wattron(wd, COLOR_PAIR(prog_nums[i]));
        wprintw(wd, "%s\n", messages[i]);
        wattroff(wd, COLOR_PAIR(prog_nums[i]));
    }
}

static void quit_ncurses(void)
{
    exit_ncurses();
    free_garbage();
    exit(0);
}

void update_help_menu(void)
{
    WINDOW *wd = newwin(LINES - 5, COLS / 3, 2, COLS / 3);

    wattron(wd, COLOR_PAIR(1));
    box(wd, 0, 0);
    wattroff(wd, COLOR_PAIR(1));

    wattron(wd, A_UNDERLINE);
    mvwprintw(wd, 1, 2, "HELP MENU");
    wattroff(wd, A_UNDERLINE);

    mvwprintw(wd, 3, 2, "H\tOpen this help menu");
    mvwprintw(wd, 4, 2, "TAB\tSwitch active window");
    mvwprintw(wd, 5, 2, "SPACE\tPause game");
    mvwprintw(wd, 6, 2, "C\tEnable/Disable cursors");
    mvwprintw(wd, 7, 2, "+\tIncrease speed to maximum");
    mvwprintw(wd, 8, 2, "-\tDecrease speed to minimum");

    int arena_offset = 10;
    //arena help
    mvwprintw(wd, arena_offset, 2, "Arena:");
    mvwprintw(wd, arena_offset + 1, 2, "LEFT\tDecrease speed");
    mvwprintw(wd, arena_offset + 2, 2, "RIGHT\tIncrease speed");
    mvwprintw(wd, arena_offset + 3, 2, "UP\tMove up in arena");
    mvwprintw(wd, arena_offset + 4, 2, "DOWN\tMove down in arena");

    int champions_offset = arena_offset + 6;
    // champions info help
    mvwprintw(wd, champions_offset, 2, "Champions info:");
    mvwprintw(wd, champions_offset + 1, 2, "LEFT\tCycle left through champions");
    mvwprintw(wd, champions_offset + 2, 2, "RIGHT\tCycle right through champions");

    wnoutrefresh(wd);
    doupdate();

    // stay in help loop
    wtimeout(wd, 1000);
    int key = wgetch_l(wd);
    while (key != 'h') {
        if (key == 'q')
            quit_ncurses();
        key = wgetch_l(wd);
    }

    // remove artefacts
    werase(wd);
    wnoutrefresh(wd);
    doupdate();
}

static WINDOW *get_active(void)
{
    if (jungle->active_window == CHAMPIONS_INFO)
        return jungle->champions_info;
    if (jungle->active_window == PROCESSES_INFO)
        return jungle->processes_info;
    if (jungle->active_window == ARENA)
        return jungle->arena;
    if (jungle->active_window == GAME_INFO)
        return jungle->game_info;
    if (jungle->active_window == CONSOLE)
        return jungle->console;
    return 0;
}

static void draw_borders(void)
{
    WINDOW *active = get_active();

    box(jungle->champions_info, 0, 0);
    box(jungle->processes_info, 0, 0);
    box(jungle->arena, 0, 0);
    box(jungle->game_info, 0, 0);
    box(jungle->console, 0, 0);

    wattron(active, COLOR_PAIR(2));
    box(active, 0, 0);
    wattroff(active, COLOR_PAIR(2));

    wnoutrefresh(jungle->champions_info);
    wnoutrefresh(jungle->processes_info);
    wnoutrefresh(jungle->arena);
    wnoutrefresh(jungle->game_info);
    wnoutrefresh(jungle->console);

    doupdate();
}

static void handle_cycling_speed(int key)
{
    if (key == KEY_LEFT && jungle->cycling_speed > 1)
        jungle->cycling_speed--;
    if (key == KEY_RIGHT && jungle->cycling_speed < 1000)
        jungle->cycling_speed++;
    if (key == '+')
        jungle->cycling_speed = 1000;
    if (key == '-')
        jungle->cycling_speed = 1;
}

static void handle_events(corewar_data_t *data, arena_t *arena)
{
    WINDOW *wd = get_active();

    wtimeout(wd, 1000 / jungle->cycling_speed);;
    keypad(wd, TRUE);

    int key = wgetch_l(wd);

    if (key == 'q')
        quit_ncurses();

    if (key == KEY_STAB || key == '\t')
        jungle->active_window++;
    if (jungle->active_window > CONSOLE)
        jungle->active_window = CHAMPIONS_INFO;

    if (key == ' ') {
        werase(jungle->arena);
        box(jungle->arena, 0, 0);
        mvwprintw(jungle->arena, getmaxy(jungle->arena) / 2 - 1, getmaxx(jungle->arena) / 2 - 7,"GAME PAUSED");
        wnoutrefresh(jungle->arena);
        doupdate();

        key = wgetch_l(wd);
        while (key != ' ') {
            if (key == 'q')
                quit_ncurses();
            key = wgetch_l(wd);
        }
    }

    if (key == 'h')
        update_help_menu();

    if (key == 'c')
        jungle->cursors = !jungle->cursors;

    if (jungle->active_window == ARENA)
        goto arena;
    if (jungle->active_window == CHAMPIONS_INFO)
        goto robot_info;
    if (jungle->active_window == GAME_INFO)
        goto game_info;
    if (jungle->active_window == PROCESSES_INFO)
        goto processes_info;
    if (jungle->active_window == CONSOLE)
        goto console;
    return;

    arena:
    if (key == KEY_UP)
        jungle->arena_mem_line--;
    if (key == KEY_DOWN)
        jungle->arena_mem_line++;
    handle_cycling_speed(key);
    return;

    processes_info:
    if (key == KEY_DOWN && jungle->shown_process + getmaxy(jungle->processes_info) - 2 < (sbyte4_t)arena->process_count)
        jungle->shown_process++;
    if (key == KEY_UP && jungle->shown_process > 0)
        jungle->shown_process--;
    handle_cycling_speed(key);
    return;

    robot_info:
    if (key == KEY_LEFT)
        jungle->current_robot_info--;
    if (jungle->current_robot_info < 0)
        jungle->current_robot_info = data->robot_count - 1;
    if (key == KEY_RIGHT)
        jungle->current_robot_info++;
    if (jungle->current_robot_info >= data->robot_count)
        jungle->current_robot_info = 0;
    if (key == '+')
        jungle->cycling_speed = 1000;
    if (key == '-')
        jungle->cycling_speed = 1;
    if (key == 'k')
        data->robots[jungle->current_robot_info]->alive = false;
    return;

    game_info:
    handle_cycling_speed(key);
    return;

    console:
    handle_cycling_speed(key);
    return;

}

void run_ncurses(arena_t *arena, corewar_data_t *data)
{
    erase();
    update_champions_info_window(arena, data);
    update_arena_window(arena);
    update_game_info(arena);
    update_console_window(NULL, 0);
    update_processes_info_window(arena);
    draw_borders();
    handle_events(data, arena);
}

void launch_ncurses(void)
{
    jungle = calloc(1, sizeof(windows_jungle_t));

    initscr();
    cbreak();
    noecho();
    curs_set(0);

    start_color();
    init_color(8, 255 * 4 - 20, 165 * 4 - 18, 0);
    init_color(9, 139 * 4 - 10, 0, 0);
    for (byte1_t i = 0; i < TOTAL_COLORS; i++) {
        // dark mode
        init_pair(i, i, COLOR_BLACK);
        // all colors (for the arena share)
        init_pair(i + TOTAL_COLORS * 1, i, COLOR_RED);
        init_pair(i + TOTAL_COLORS * 2, i, COLOR_GREEN);
        init_pair(i + TOTAL_COLORS * 3, i, COLOR_YELLOW);
        init_pair(i + TOTAL_COLORS * 4, i, COLOR_BLUE);
        init_pair(i + TOTAL_COLORS * 5, i, COLOR_MAGENTA);
        init_pair(i + TOTAL_COLORS * 6, i, COLOR_CYAN);
        // light mode
        init_pair(i + TOTAL_COLORS * 7, i, COLOR_WHITE);
        // non standard colors
        init_pair(i + TOTAL_COLORS * 8, i, COLOR_ORANGE);
        init_pair(i + TOTAL_COLORS * 9, i, COLOR_DARK_RED);
    }

    WINDOW *champions_info = subwin(stdscr, LINES / 3, COLS / 2, 0, 0);
    WINDOW *processes_info = subwin(stdscr, LINES / 3, COLS / 2, 0, COLS / 2);
    WINDOW *arena = subwin(stdscr, LINES * 2 / 3, COLS * 2 / 3, LINES / 3, 0);
    WINDOW *game_info = subwin(stdscr, LINES / 3, COLS / 3, LINES / 3, COLS / 3 * 2);
    WINDOW *console = subwin(stdscr, LINES / 3, COLS / 3, LINES / 3 * 2, COLS / 3 * 2);

    jungle->champions_info = champions_info;
    jungle->processes_info = processes_info;
    jungle->arena = arena;
    jungle->game_info = game_info;
    jungle->console = console;

    jungle->arena_mem_line = 10000;
    jungle->active_window = ARENA;
    jungle->arena_window_size = (MEM_SIZE / (COLS / 3)) - (LINES * 2 / 3 - 2);

    jungle->cycling_speed = 100;

    jungle->cursors = true;

    update_console_window(NULL, 0);
}

void exit_ncurses(void)
{
    free(jungle);
    endwin();
}
