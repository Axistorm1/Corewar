#include "bonus.h"
#include "arena.h"
#include "game_info.h"
#include "op.h"
#include "structures.h"
#include "my_stdlib.h"
#include "my_string.h"
#include <alloca.h>
#include <ctype.h>
#include <ncurses.h>
#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static windows_jungle_t *jungle = NULL;
static bool light_mode = false;

static int wgetch_l(WINDOW *window)
{
    return tolower(wgetch(window));
}

static void dump_ownership_to_file(arena_t *arena)
{
    char *filename = NULL;

    asprintf(&filename, "own_dump_cycle_%d.txt", arena->total_cycles);
    FILE *stream = fopen(filename, "w");
    for (byte2_t i = 0; i < MEM_SIZE; i += 32) {
        for (byte1_t j = 0; j < 32; j++)
            fprintf(stream, "%08X", arena->ownership_map[i + j]);
        fprintf(stream, "\n");
    }
    fclose(stream);
}

static void dump_memory_to_file(arena_t *arena)
{
    char *filename = NULL;

    asprintf(&filename, "mem_dump_cycle_%d.txt", arena->total_cycles);
    FILE *stream = fopen(filename, "w");
    for (byte2_t i = 0; i < MEM_SIZE; i += 32) {
        for (byte1_t j = 0; j < 32; j++)
            fprintf(stream, "%02X", arena->memory[i + j]);
        fprintf(stream, "\n");
    }
    fclose(stream);
}

static void dump_decompiled_to_file(
    char *filename,
    header_t *header,
    char **lines)
{
    char *new_filename = NULL;

    char *ptr = strrchr(filename, '.');
    if (ptr)
        ptr[0] = 0;

    asprintf(&new_filename, "decompiled_%s.s", filename);

    FILE *stream = fopen(new_filename, "w");

    fprintf(stream, ".name \"%s\"\n", header->prog_name);
    fprintf(stream, ".comment \"%s\"\n\n", header->comment);

    for (size_t i = 0; lines[i]; i++)
        fprintf(stream, "%s\n", lines[i]);
    fclose(stream);
    if (ptr)
        ptr[0] = '.';
}

static char *type_to_str(param_type_t type)
{
    if (type == PARAM_NOTHING)
        return "Nothing";
    if (type == PARAM_DIR)
        return "Direct";
    if (type == PARAM_INDEX)
        return "Index";
    if (type == PARAM_DIRDEX)
        return "Dirdex";
    if (type == PARAM_IND)
        return "Indirect";
    if (type == PARAM_REG)
        return "Register";
    return "Nothing";
}

// add fullscreen toggle
static void update_arena_window(arena_t *arena)
{
    WINDOW *wd = jungle->arena;

    if (jungle->fullscreen_arena)
        wd = newwin(LINES, COLS, 0, 0);

    int cols = (getmaxx(wd) >> 1) - 1;
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
            cursors[arena->processes[i]->pc] = (byte1_t)arena->processes[i]->robot->prog_num % TOTAL_COLORS;

    // draw the memory arena
    for (int y = 0; y < lines; y++) {
        for (int x = 0; x < cols; x++) {
            int pos = (start_pos + y * cols + x) % MEM_SIZE;
            byte4_t color_pair = arena->ownership_map[pos] & COLORS_MODULO;
            if (color_pair != 0)
                color_pair -= cursors[pos];
            color_pair += (byte4_t)cursors[pos] << COLORS_BS;
            if (light_mode && color_pair < TOTAL_COLORS)
                color_pair += COLOR_WHITE << COLORS_BS;
            wattron(wd, COLOR_PAIR(color_pair));
            mvwprintw(wd, y + 1, (x << 1) + 1, "%02X", arena->memory[pos]);
            wattroff(wd, COLOR_PAIR(color_pair));
        }
    }

    if (jungle->fullscreen_arena) {
        box(wd, 0, 0);
        mvwprintw(wd, 0, 4, "Arena - Fullscreen");
        wnoutrefresh(wd);
        delwin(wd);
    }
}

static void update_champions_info_window(arena_t *arena, corewar_data_t *data)
{
    WINDOW *wd = jungle->champions;
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
        wattron(wd, COLOR_PAIR(COLOR_GREEN + light_mode * LIGHT_MODE_OFFSET));
        mvwprintw(wd, max_height + 1, 10, "Alive");
        wattroff(wd, COLOR_PAIR(COLOR_GREEN + light_mode * LIGHT_MODE_OFFSET));
    } else {
        wattron(wd, COLOR_PAIR(COLOR_RED + light_mode * LIGHT_MODE_OFFSET));
        mvwprintw(wd, max_height + 1, 10, "Dead");
        wattroff(wd, COLOR_PAIR(COLOR_RED + light_mode * LIGHT_MODE_OFFSET));
    }

    mvwprintw(wd, max_height + 2, 2, "Process count: %d  ->  %.1f%%     ", robot->process_count, (float)robot->process_count / (float)arena->process_count * 100);
    wprintw(wd, "Starting adress: %d", robot->mem_adr);
}

// replace registers by something more... fancy?
static void update_processes_info_window(arena_t *arena)
{
    WINDOW *wd = jungle->processes;
    byte4_t max_height = (byte4_t)getmaxy(wd) - 2;

    werase(wd);

    for (byte4_t i = 0; i + (byte4_t)jungle->shown_process < arena->process_count && i < max_height; i++) {
        process_data_t *data = arena->processes[i + (byte4_t)jungle->shown_process];
        wattron(wd, COLOR_PAIR((data->robot->prog_num & COLORS_MODULO) + light_mode * LIGHT_MODE_OFFSET));
        mvwprintw(wd, (sbyte4_t)i + 1, 2, "Process #%-3d", i + 1 + (byte4_t)jungle->shown_process);
        wprintw(wd,  "%5s -> %5d cycles", op_tab[data->instruction->op_code].mnemonique, data->wait_cycles);
        if (data->alive)
            wprintw(wd, "\tAlive");
        else
            wprintw(wd, "\tDead");
        wprintw(wd, "\tCarry: ");
        if (data->carry)
            wprintw(wd, "1");
        else
        wprintw(wd, "0");
        wattroff(wd, COLOR_PAIR((data->robot->prog_num & COLORS_MODULO) + light_mode * LIGHT_MODE_OFFSET));
    }
}

static int compare(const void* a, const void* b)
{
    byte4_t x = *(byte4_t*)a;
    byte4_t y = *(byte4_t*)b;
    return (x > y) - (x < y);
}

static void update_game_info(arena_t *arena, corewar_data_t *data)
{
    WINDOW *wd = jungle->game_info;

    werase(wd);

    mvwprintw(wd, 1, 2, "Cycle: %d/%d", arena->current_cycle, arena->cycle_to_die);
    mvwprintw(wd, 1, 25, "Total: %d", arena->total_cycles);
    mvwprintw(wd, 1, 40, "+%d/s", jungle->cycling_speed);

    // process count color
    int color = COLOR_GREEN + light_mode * LIGHT_MODE_OFFSET;

    if (arena->process_count > 1000)
        color = COLOR_YELLOW + light_mode * LIGHT_MODE_OFFSET;
    if (arena->process_count > 10000)
        color = COLOR_ORANGE + light_mode * LIGHT_MODE_OFFSET;
    if (arena->process_count > 100000)
        color = COLOR_RED + light_mode * LIGHT_MODE_OFFSET;
    if (arena->process_count == 999999)
        color = COLOR_BLACK + TOTAL_COLORS;

    mvwprintw(wd, 3, 2, "Process count: ");
    wattron(wd, COLOR_PAIR(color));
    mvwprintw(wd, 3, 17, "%d", arena->process_count);
    wattroff(wd, COLOR_PAIR(color));
    mvwprintw(wd, 3, 25, "Live count: ");
    // color for the live count
    if (arena->nbr_live == NBR_LIVE) {
        wattron(wd, COLOR_PAIR(COLOR_GREEN + light_mode * LIGHT_MODE_OFFSET));
        mvwprintw(wd, 3, 37, "%d/%d\n", NBR_LIVE, NBR_LIVE);
        wattroff(wd, COLOR_PAIR(COLOR_GREEN + light_mode * LIGHT_MODE_OFFSET));
    } else {
        wattron(wd, COLOR_PAIR(COLOR_RED + light_mode * LIGHT_MODE_OFFSET));
        mvwprintw(wd, 3, 37, "%d/%d\n", arena->nbr_live, NBR_LIVE);
        wattroff(wd, COLOR_PAIR(COLOR_RED + light_mode * LIGHT_MODE_OFFSET));
    }

    mvwprintw(wd, 4, 2, "Dead processes: %d", arena->dead_process_count);
    mvwprintw(wd, 4, 25, "Robots alive: %d", arena->robots_alive);

    mvwprintw(wd, 5, 2, "Dump cycle: ");
    if (data->dump_cycle == (byte4_t)-1) {
        wattron(wd, COLOR_PAIR(COLOR_RED  + light_mode * LIGHT_MODE_OFFSET));
        mvwprintw(wd, 5, 14, "Never");
        wattroff(wd, COLOR_PAIR(COLOR_RED  + light_mode * LIGHT_MODE_OFFSET));
    } else
        mvwprintw(wd, 5, 14, "%d", data->dump_cycle);

    // Decided to only do this every x cycles
    static int call_counter = 199;
    if (++call_counter % 200 != 0)
        goto draw_chart;

    // this is the math to get the % of ownership
    byte4_t *copy = alloca(MEM_SIZE * sizeof(byte4_t));
    memcpy(copy, arena->ownership_map, MEM_SIZE * sizeof(byte4_t));

    qsort(copy, MEM_SIZE, 4, compare);

    byte4_t current = copy[0];
    byte4_t count = 1;
    byte2_t current_robot = 0;
    static float *percentages = NULL;
    percentages = calloc(data->robot_count + 1, sizeof(float));
    static byte4_t *values = NULL;
    values = calloc(data->robot_count + 1, sizeof(byte4_t));

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
    draw_chart:
    wattron(wd, A_UNDERLINE);
    mvwprintw(wd, getmaxy(wd) - 3, (getmaxx(wd) >> 1) - 6, "Arena share:\n");
    wattroff(wd, A_UNDERLINE);

    int max_width = getmaxx(wd) - 4;
    int current_x = 2;

    for (byte2_t i = 0; i < data->robot_count + 1; i++) {
        int segment_width = (int)((float)max_width * percentages[i]);
        if (segment_width <= 0)
            continue;

        wmove(wd, getcury(wd), current_x);
        if (values[i] == 0) {
            wattron(wd, COLOR_PAIR(LIGHT_MODE_OFFSET - light_mode * LIGHT_MODE_OFFSET + 1));
            whline(wd, ' ', segment_width);
            wattroff(wd, COLOR_PAIR(LIGHT_MODE_OFFSET - light_mode * LIGHT_MODE_OFFSET + 1));
        } else {
            wattron(wd, COLOR_PAIR(((values[i] & COLORS_MODULO) << COLORS_BS) + 1));
            whline(wd, ' ', segment_width);
            wattroff(wd, COLOR_PAIR(((values[i] & COLORS_MODULO) << COLORS_BS) + 1));
        }

        current_x += segment_width;
        if (current_x >= max_width)
            break;
    }
}

void update_console_window(
    char *str,
    byte2_t prog_num,
    byte4_t cycle)
{
    WINDOW *wd = jungle->console;
    int max_messages = getmaxy(wd) - 2;

    if (!str)
        goto draw;

    static char *messages[100];
    static byte2_t prog_nums[100];
    static byte4_t cycle_sent[100];
    static byte1_t current_messages = 0;

    // handle messages
    if (current_messages >= max_messages) {
        free(messages[0]);
        for (byte1_t i = 0; i < current_messages - 1; i++) {
            messages[i] = messages[i + 1];
            prog_nums[i] = prog_nums[i + 1];
            cycle_sent[i] = cycle_sent[i + 1];
        }
        current_messages--;
    }
    messages[current_messages] = strdup(str);
    prog_nums[current_messages] = prog_num & COLORS_MODULO;
    cycle_sent[current_messages] = cycle;
    current_messages++;

    draw:
    werase(wd);

    for (byte1_t i = 0; i < current_messages; i++) {
        mvwprintw(wd, i + 1 + max_messages - current_messages, 2, "%d: ", cycle_sent[i]);
        wattron(wd, COLOR_PAIR(prog_nums[i] + light_mode * LIGHT_MODE_OFFSET));
        wprintw(wd, "%s\n", messages[i]);
        wattroff(wd, COLOR_PAIR(prog_nums[i] + light_mode * LIGHT_MODE_OFFSET));
    }
}

static void quit_ncurses(void)
{
    exit_ncurses();
    free_garbage();
    exit(0);
}

static void display_corewar_ascii_logo(void)
{
    WINDOW *wd = newwin(5, 60, 0, (COLS - 60) >> 1);

    werase(wd);

    byte1_t logo_array[] =
    " ######  ######  ######  ####### ##     ##  #####  ######  \n"
    "##      ##    ## ##   ## ##      ##     ## ##   ## ##   ## \n"
    "##      ##    ## ######  #####   ##  #  ## ####### ######  \n"
    "##      ##    ## ##   ## ##      ## ### ## ##   ## ##   ## \n"
    " ######  ######  ##   ## #######  ### ###  ##   ## ##   ## \n";

    if (light_mode)
        wbkgd(wd, COLOR_PAIR(LIGHT_MODE_OFFSET));

    for (int i = 0; logo_array[i]; i++)
        if (logo_array[i] == 35) {
            wattron(wd, COLOR_PAIR(TOTAL_COLORS * COLOR_DARK_RED));
            waddch(wd, ' ');
            wattroff(wd, COLOR_PAIR(TOTAL_COLORS * COLOR_DARK_RED));
        } else if (logo_array[i] == '\n')
            waddch(wd, '\n');
        else
            waddch(wd, logo_array[i]);

    wnoutrefresh(wd);
    doupdate();
    delwin(wd);
}

static void display_secret_menu(WINDOW *wd)
{
    char *secret_ascii_top[] = {"",
        "                   _ |\\_",
        "                   \\` ..\\",
        "              __,.-\" =__Y=",
        "            .\"        )",
        "      _    /   ,    \\/\\_",
        "     ((____|    )_-\\ \\_-`",
        "     `-----'`-----` `--`",
        NULL};
    for (byte1_t i = 0; secret_ascii_top[i]; i++)
        mvwprintw(wd, 1 + i, 1, "%s", secret_ascii_top[i]);

    wattron(wd, A_UNDERLINE);
    mvwprintw(wd, getmaxy(wd) / 2, getmaxx(wd) / 2 - 4, "The game");
    wattroff(wd, A_UNDERLINE);

    char *secret_ascii_bottom[] = {"",
        "      |\\      _,,,---,,_",
        "ZZZzz /,`.-'`'    -.  ;-;;,_",
        "     |,4-  ) )-,_. ,\\ (  `'-'",
        "    '---''(_/--'  `-'\\_)",
        NULL};

    for (byte1_t i = 0; secret_ascii_bottom[i]; i++)
        mvwprintw(wd, getmaxy(wd) - 7 + i, 3, "%s", secret_ascii_bottom[i]);
}

// maybe add a big COREWAR ascii? like btop (UwU btop my beloved)
static void update_help_menu(void)
{
    WINDOW *wd = newwin(LINES - 6, 40, 5, (COLS >> 1) - 20);

    keypad(wd, true);

    help_start:
    werase(wd);

    display_corewar_ascii_logo();

    if (light_mode)
        wbkgd(wd, COLOR_PAIR(LIGHT_MODE_OFFSET));

    wattron(wd, COLOR_PAIR(COLOR_RED + light_mode * LIGHT_MODE_OFFSET));
    box(wd, 0, 0);
    wattroff(wd, COLOR_PAIR(COLOR_RED + light_mode * LIGHT_MODE_OFFSET));


    if (jungle->help_menu_page == 3) {
        mvwprintw(wd, 0, 4, "Cute cats");
        mvwprintw(wd, 0, getmaxx(wd) - 10, "page ?/2");
        display_secret_menu(wd);
        goto events;
    }

    mvwprintw(wd, 0, 4, "Help");

    mvwprintw(wd, 0, getmaxx(wd) - 10, "page %d/2", jungle->help_menu_page);
    if (jungle->help_menu_page == 1)
        mvwprintw(wd, 1, getmaxx(wd) - 7, "->");
    if (jungle->help_menu_page == 2)
        mvwprintw(wd, 1, getmaxx(wd) - 7, "<-");

    wattron(wd, A_UNDERLINE);
    mvwprintw(wd, 2, 2, "Key:");
    mvwprintw(wd, 2, 8, "Description:");
    wattroff(wd, A_UNDERLINE);

    if (jungle->help_menu_page == 1)
        goto page_1;
    if (jungle->help_menu_page == 2)
        goto page_2;

    page_1:
    mvwprintw(wd, 3, 2, "H\tOpen the help window");
    mvwprintw(wd, 4, 2, "P\tOpen processes menu");
    mvwprintw(wd, 5, 2, "SPACE\tPause game");
    mvwprintw(wd, 6, 2, "ESC\tPause for one second");
    mvwprintw(wd, 7, 2, "C\tEnable/Disable cursors");
    mvwprintw(wd, 8, 2, "B\tSwitch between light/dark mode");
    mvwprintw(wd, 10, 2, "+\tIncrease speed to maximum");
    mvwprintw(wd, 11, 2, "-\tDecrease speed to minimum");
    mvwprintw(wd, 12, 2, ">\tIncrease cycles to die");
    mvwprintw(wd, 13, 2, "<\tDecrease cycles to die");
    mvwprintw(wd, 14, 2, "S\tFinish cycles round");
    mvwprintw(wd, 16, 2, "L\tDump memory to file");
    mvwprintw(wd, 17, 2, "X\tDump ownership to file");
    mvwprintw(wd, 18, 2, "Q\tQuit the game");
    goto events;

    //arena help
    page_2:
    mvwprintw(wd, 3, 2, "TAB\tSwitch active window");

    wattron(wd, A_UNDERLINE);
    mvwprintw(wd, 5, 2, "Arena:");
    wattroff(wd, A_UNDERLINE);
    mvwprintw(wd, 6, 2, "LEFT\tDecrease speed");
    mvwprintw(wd, 7, 2, "RIGHT\tIncrease speed");
    mvwprintw(wd, 8, 2, "UP\tMove up in arena");
    mvwprintw(wd, 9, 2, "DOWN\tMove down in arena");
    mvwprintw(wd, 10, 2, "F\tToggle Fullscreen");

    // champions help
    int champions_offset = 12;
    wattron(wd, A_UNDERLINE);
    mvwprintw(wd, champions_offset, 2, "Champions:");
    wattroff(wd, A_UNDERLINE);
    mvwprintw(wd, champions_offset + 1, 2, "LEFT\tCycle left through champions");
    mvwprintw(wd, champions_offset + 2, 2, "RIGHT\tCycle right through champions");
    mvwprintw(wd, champions_offset + 3, 2, "M\tShow decompiled code");

    // processes help
    int processes_offset = champions_offset + 5;
    wattron(wd, A_UNDERLINE);
    mvwprintw(wd, processes_offset, 2, "Processes:");
    wattroff(wd, A_UNDERLINE);
    mvwprintw(wd, processes_offset + 1, 2, "DOWN\tMove down in processes");
    mvwprintw(wd, processes_offset + 2, 2, "UP\tMove up in processes");

    // decompiled menu
    int decompiled_offset = processes_offset + 4;
    wattron(wd, A_UNDERLINE);
    mvwprintw(wd, decompiled_offset, 2, "Decompiled menu:");
    wattroff(wd, A_UNDERLINE);
    mvwprintw(wd, decompiled_offset + 1, 2, "DOWN\tMove down in decompiled code");
    mvwprintw(wd, decompiled_offset + 2, 2, "UP\tMove up in decompiled code");
    mvwprintw(wd, decompiled_offset + 3, 2, "D\tWrite decompiled code to file");

    events:

    mvwprintw(wd, getmaxy(wd) - 2, (getmaxx(wd) - 12) >> 1, "Made with <3");
    mvwprintw(wd, getmaxy(wd) - 1, (getmaxx(wd) - 24) >> 1, "by Axistorm and Arkcadia");

    wnoutrefresh(wd);
    doupdate();

    wtimeout(wd, 1000);
    int key = wgetch_l(wd);

    if (key == 'q')
        quit_ncurses();

    if (key == 'p')
        jungle->process_menu = true;

    if ((key == KEY_DOWN || key == KEY_RIGHT) && jungle->help_menu_page < 2)
        jungle->help_menu_page++;
    if ((key == KEY_UP || key == KEY_LEFT) && jungle->help_menu_page > 1)
        jungle->help_menu_page--;

    if (key == 'g')
        jungle->help_menu_page = 3;

    if (key != 'h' && key != 'p')
        goto help_start;

    delwin(wd);
}

// top -> process number and robot
// some stats/info
// what to change (with numbers to use) [signals]
void update_process_menu_window(arena_t *arena, bool paused)
{
    if (paused) {
        WINDOW *wd = newwin(LINES >> 1, COLS >> 1, LINES >> 2, COLS >> 2);
        werase(wd);
        wnoutrefresh(wd);
    }
    if (!jungle->process_menu)
        return;

    WINDOW *wd = newwin(LINES >> 1, COLS >> 1, LINES >> 2, COLS >> 2);

    werase(wd);

    keypad(wd, TRUE);

    if (light_mode)
        wbkgd(wd, COLOR_PAIR(LIGHT_MODE_OFFSET));

    box(wd, 0, 0);
    mvwprintw(wd, 0, 4, "Processes menu");

    if (jungle->current_process > arena->process_count)
        goto refresh;
    process_data_t *process = arena->processes[jungle->current_process];
    if (!process)
        goto refresh;

    mvwprintw(wd, 1, 2, "Process #%-4d Robot: %s", jungle->current_process + 1, process->robot->header->prog_name);
    // status
    mvwprintw(wd, 3, 2, "Status: ");
    if (process->alive) {
        wattron(wd, COLOR_PAIR(COLOR_GREEN + light_mode * LIGHT_MODE_OFFSET));
        mvwprintw(wd, 3, 10, "Alive");
        wattroff(wd, COLOR_PAIR(COLOR_GREEN + light_mode * LIGHT_MODE_OFFSET));
    } else {
        wattron(wd, COLOR_PAIR(COLOR_RED + light_mode * LIGHT_MODE_OFFSET));
        mvwprintw(wd, 3, 10, "Dead");
        wattroff(wd, COLOR_PAIR(COLOR_RED + light_mode * LIGHT_MODE_OFFSET));
    }
    // carry
    mvwprintw(wd, 3, 25, "Carry: ");
    if (process->carry) {
        wattron(wd, COLOR_PAIR(COLOR_GREEN + light_mode * LIGHT_MODE_OFFSET));
        mvwprintw(wd, 3, 32, "True");
        wattroff(wd, COLOR_PAIR(COLOR_GREEN + light_mode * LIGHT_MODE_OFFSET));
    } else {
        wattron(wd, COLOR_PAIR(COLOR_RED + light_mode * LIGHT_MODE_OFFSET));
        mvwprintw(wd, 3, 32, "False");
        wattroff(wd, COLOR_PAIR(COLOR_RED + light_mode * LIGHT_MODE_OFFSET));
    }

    mvwprintw(wd, 4, 2, "Program counter: %-5d Wait cycles: %-5d Lifetime: %d", process->pc, process->wait_cycles, arena->total_cycles - process->cycle_born);

    // instruction
    instruction_t *instruction = process->instruction;
    mvwprintw(wd, 5, 2, "Instruction: %-9s Coding byte: %-3d   Size: %d", op_tab[instruction->op_code].mnemonique, instruction->coding_byte, instruction->size);

    mvwprintw(wd, 6, 2, "%s: %d %s: %d %s: %d",
        type_to_str(instruction->types[0]), (int)get_data_in_param(&(type_and_param_t){instruction->types[0], instruction->params[0]}, instruction->types[0], arena, process),
        type_to_str(instruction->types[1]), (int)get_data_in_param(&(type_and_param_t){instruction->types[1], instruction->params[1]}, instruction->types[1], arena, process),
        type_to_str(instruction->types[2]), (int)get_data_in_param(&(type_and_param_t){instruction->types[2], instruction->params[2]}, instruction->types[2], arena, process));

    // registers
    wattron(wd, A_UNDERLINE);
    mvwprintw(wd, 8, 17, "Registers");
    wattroff(wd, A_UNDERLINE);
    for (byte1_t i = 0; i < REG_NUMBER >> 2; i++)
        mvwprintw(wd, 9 + i, 2, "%-10d| %-10d| %-10d| %-10d", process->registers[i * 4], process->registers[i * 4 + 1], process->registers[i * 4 + 2], process->registers[i * 4 + 3]);

    // signals
    wattron(wd, A_UNDERLINE);
    mvwprintw(wd, 14, 2, "Signals");
    wattroff(wd, A_UNDERLINE);
    mvwprintw(wd, 15, 2, "1: Finish instruction  2: Kill process  3: Change carry  4: Revive");

    if (jungle->signal == SKIP)
        process->wait_cycles = 0;
    if (jungle->signal == KILL) {
        kill_audio();
        process->alive = false;
        process->wait_cycles = (byte4_t)-1;
    }
    if (jungle->signal == CARRY)
        process->carry = !process->carry;
    if (jungle->signal == REVIVE) {
        revive_audio();
        process->alive = true;
        process->wait_cycles = (byte4_t)op_tab[instruction->op_code].nbr_cycles;
    }

    refresh:
    wnoutrefresh(wd);
    delwin(wd);
}

void update_source_code_window(corewar_data_t *data)
{
    if (!jungle->source_code)
        return;

    WINDOW *wd = newwin(LINES - 5, COLS / 3, 2, COLS * 1/3);

    werase(wd);

    if (light_mode)
        wbkgd(wd, COLOR_PAIR(LIGHT_MODE_OFFSET));

    wattron(wd, COLOR_PAIR(COLOR_RED + light_mode * LIGHT_MODE_OFFSET));
    box(wd, 0, 0);
    wattroff(wd, COLOR_PAIR(COLOR_RED + light_mode * LIGHT_MODE_OFFSET));

    robot_info_t *robot = data->robots[jungle->current_robot_info];

    mvwprintw(wd, 0, 4, "Source - %s", robot->filename);

    instruction_t **instructions = parse_champions(robot->header, robot->filename);
    char **lines = transcribe_dot_s(instructions);
    sbyte4_t len = (sbyte4_t)str_array_len(lines);

    if (jungle->source_line > len - getmaxy(wd) + 3)
        jungle->source_line = len - getmaxy(wd) + 3;

    if (jungle->source_line < 0)
        jungle->source_line = 0;

    for (sbyte4_t i = jungle->source_line; i < len && i < getmaxy(wd) - 3 + jungle->source_line && lines[i]; i++)
        mvwprintw(wd, 2 + i - jungle->source_line, 2, "%4d | %s", i + 1, lines[i]);

    if (jungle->dump_decompiled)
        dump_decompiled_to_file(robot->filename, robot->header, lines);

    wnoutrefresh(wd);
    delwin(wd);
}

static WINDOW *get_active(void)
{
    if (jungle->active_window == CHAMPIONS_INFO)
        return jungle->champions;
    if (jungle->active_window == PROCESSES_INFO)
        return jungle->processes;
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

    if (light_mode)
        wbkgd(active, COLOR_PAIR(TOTAL_COLORS * COLOR_WHITE));

    box(jungle->champions, 0, 0);
    box(jungle->processes, 0, 0);
    box(jungle->arena, 0, 0);
    box(jungle->game_info, 0, 0);
    box(jungle->console, 0, 0);

    if (light_mode) {
        wattron(active, COLOR_PAIR(TOTAL_COLORS * COLOR_WHITE + COLOR_DARK_RED));
        box(active, 0, 0);
        wattroff(active, COLOR_PAIR(TOTAL_COLORS * COLOR_WHITE + COLOR_DARK_RED));
    } else {
        wattron(active, COLOR_PAIR(COLOR_RED));
        box(active, 0, 0);
        wattroff(active, COLOR_PAIR(COLOR_RED));
    }

    mvwprintw(jungle->champions, 0, 4, "Champions");
    mvwprintw(jungle->processes, 0, 4, "Processes");
    mvwprintw(jungle->arena, 0, 4, "Arena");
    mvwprintw(jungle->game_info, 0, 4, "Game info");
    mvwprintw(jungle->console, 0, 4, "Console");

    wnoutrefresh(jungle->champions);
    wnoutrefresh(jungle->processes);
    wnoutrefresh(jungle->arena);
    wnoutrefresh(jungle->game_info);
    wnoutrefresh(jungle->console);
}

static void handle_cycling_speed(int key)
{
    if (key == KEY_LEFT && jungle->cycling_speed > 1)
        jungle->cycling_speed--;
    if (key == KEY_RIGHT && jungle->cycling_speed < 1000)
        jungle->cycling_speed++;
}

static void handle_process_change(int key, arena_t *arena)
{
    if (key == KEY_LEFT) {
        if (jungle->current_process == 0)
            jungle->current_process = arena->process_count;
        jungle->current_process--;
    }
    if (key == KEY_RIGHT)
        jungle->current_process++;
    if (jungle->current_process >= arena->process_count)
        jungle->current_process = 0;
}

static void handle_events(corewar_data_t *data, arena_t *arena)
{
    WINDOW *wd = get_active();

    wtimeout(wd, 1000 / jungle->cycling_speed);
    keypad(wd, TRUE);

    int key = wgetch_l(wd);

    // quit
    if (key == 'q')
        quit_ncurses();

    // switch active
    if (key == KEY_STAB || key == '\t')
        jungle->active_window++;
    if (jungle->active_window > CONSOLE)
        jungle->active_window = CHAMPIONS_INFO;

    // pause
    // THIS IS THE WORST PAUSE MENU POSSIBLE BUT IT WORKS
    if (key == ' ') {
        werase(jungle->arena);
        box(jungle->arena, 0, 0);
        mvwprintw(wd, 0, 4, "Arena - Paused");
        mvwprintw(jungle->arena, getmaxy(jungle->arena) / 2 - 1, getmaxx(jungle->arena) / 2 - 7, "GAME PAUSED");
        wnoutrefresh(jungle->arena);

        wtimeout(wd, 0);
        key = wgetch_l(wd);
        while (key != ' ') {
            if (key == 'q')
                quit_ncurses();
            if (jungle->process_menu) {
                mvwprintw(jungle->arena, getmaxy(jungle->arena) / 2 - 1, getmaxx(jungle->arena) / 2 - 32, "GAME PAUSED");
                wnoutrefresh(wd);
                handle_process_change(key, arena);
                update_process_menu_window(arena, false);
            }
            if (key == 'p') {
                jungle->process_menu = !jungle->process_menu;
                if (!jungle->process_menu) {
                    update_process_menu_window(arena, true);
                    werase(jungle->arena);
                    draw_borders();
                    mvwprintw(wd, 0, 4, "Arena - Paused");
                    mvwprintw(jungle->arena, getmaxy(jungle->arena) / 2 - 1, getmaxx(jungle->arena) / 2 - 7, "GAME PAUSED");
                    wnoutrefresh(jungle->arena);
                }
            }
            key = wgetch_l(wd);
            doupdate();
        }
    }

    // help menu
    if (key == 'h')
        update_help_menu();

    // processes menu
    if (key == 'p' && !jungle->source_code)
        jungle->process_menu = !jungle->process_menu;

    // cursors toggle
    if (key == 'c')
        jungle->cursors = !jungle->cursors;

    // light/dark mode
    if (key == 'b')
        light_mode = !light_mode;

    if (key == 'l')
        dump_memory_to_file(arena);

    if (key == 'x')
        dump_ownership_to_file(arena);

    // speed modifications
    if (key == '+')
        jungle->cycling_speed = 1000;
    if (key == '-')
        jungle->cycling_speed = 1;
    if (key == 's')
        arena->current_cycle = arena->cycle_to_die;
    if (key == '<')
        arena->cycle_to_die -= 5;
    if (key == '>')
        arena->cycle_to_die += 5;

    if (jungle->source_code)
        goto source_code;
    if (jungle->process_menu)
        goto process_menu;
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
    if (key == 'f')
        jungle->fullscreen_arena = !jungle->fullscreen_arena;
    handle_cycling_speed(key);
    return;

    processes_info:
    if (key == KEY_DOWN && jungle->shown_process + getmaxy(jungle->processes) - 2 < (sbyte4_t)arena->process_count)
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
    if (key == 'm')
        jungle->source_code = !jungle->source_code;
    return;

    game_info:
    handle_cycling_speed(key);
    return;

    console:
    handle_cycling_speed(key);
    return;

    process_menu:
    handle_process_change(key, arena);

    jungle->signal = NO_SIGNAL;
    if (key == '1')
        jungle->signal = SKIP;
    if (key == '2')
        jungle->signal = KILL;
    if (key == '3')
        jungle->signal = CARRY;
    if (key == '4')
        jungle->signal = REVIVE;
    return;

    source_code:
    if (key == KEY_DOWN)
        jungle->source_line++;
    if (key == KEY_UP && jungle->source_line > 0)
        jungle->source_line--;
    jungle->dump_decompiled = false;
    if (key == 'd')
        jungle->dump_decompiled = true;
    goto robot_info;
}

void run_ncurses(arena_t *arena, corewar_data_t *data)
{
    if (light_mode && !jungle->fullscreen_arena) {
        wbkgd(stdscr, COLOR_PAIR(TOTAL_COLORS * COLOR_WHITE));
        wnoutrefresh(stdscr);
        wbkgd(jungle->champions, COLOR_PAIR(TOTAL_COLORS * COLOR_WHITE));
        wbkgd(jungle->processes, COLOR_PAIR(TOTAL_COLORS * COLOR_WHITE));
        wbkgd(jungle->arena, COLOR_PAIR(TOTAL_COLORS * COLOR_WHITE));
        wbkgd(jungle->game_info, COLOR_PAIR(TOTAL_COLORS * COLOR_WHITE));
        wbkgd(jungle->console, COLOR_PAIR(TOTAL_COLORS * COLOR_WHITE));
    } else if (!light_mode) {
        wbkgd(stdscr, COLOR_PAIR(0));
        wnoutrefresh(stdscr);
        wbkgd(jungle->champions, COLOR_PAIR(0));
        wbkgd(jungle->processes, COLOR_PAIR(0));
        wbkgd(jungle->arena, COLOR_PAIR(0));
        wbkgd(jungle->game_info, COLOR_PAIR(0));
        wbkgd(jungle->console, COLOR_PAIR(0));
    }

    update_arena_window(arena);
    if (!jungle->fullscreen_arena) {
        update_champions_info_window(arena, data);
        update_game_info(arena, data);
        update_console_window(NULL, 0, 0);
        update_processes_info_window(arena);
        draw_borders();
        update_process_menu_window(arena, false);
        update_source_code_window(data);
    }
    doupdate();
    handle_events(data, arena);
}

static void sigint_handler(int a)
{
    quit_ncurses();
    exit(a);
    abort();
    raise(SIGINT);
    kill(getpid(), SIGINT);
    system("shutdown now");
}

void launch_ncurses(game_info_t *game_data)
{
    jungle = calloc(1, sizeof(windows_jungle_t));

    initscr();
    cbreak();
    noecho();
    curs_set(0);

    ESCDELAY = 1000;

    start_color();
    //make total colors a multiple of 2 to optimize a lot of bottleneck coomputation in arena
    init_color(COLOR_ORANGE, 1000, 640, 0);
    init_color(9, 550, 0, 0);
    init_color(10, 670, 1000, 180);
    init_color(11, 4, 520, 100);
    init_color(12, 280, 0, 120);
    init_color(13, 1000, 0, 750);
    init_color(14, 800, 750, 800);
    init_color(15, 400, 800, 1000);
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
        init_pair(i + TOTAL_COLORS * 10, i, 10);
        init_pair(i + TOTAL_COLORS * 11, i, 11);
        init_pair(i + TOTAL_COLORS * 12, i, 12);
        init_pair(i + TOTAL_COLORS * 13, i, 13);
        init_pair(i + TOTAL_COLORS * 14, i, 14);
        init_pair(i + TOTAL_COLORS * 15, i, 15);
    }

    // need to get actual values instead of rounded approximations
    WINDOW *champions = subwin(stdscr, LINES / 3, COLS >> 1, 0, 0);
    WINDOW *processes = subwin(stdscr, LINES / 3, COLS >> 1, 0, COLS >> 1);
    WINDOW *arena = subwin(stdscr, LINES * 2 / 3, COLS * 2 / 3, LINES / 3, 0);
    WINDOW *game_info = subwin(stdscr, LINES / 3, COLS / 3, LINES / 3, COLS * 2 / 3);
    WINDOW *console = subwin(stdscr, LINES / 3, COLS / 3, LINES * 2 / 3, COLS * 2 / 3);

    jungle->champions = champions;
    jungle->processes = processes;
    jungle->arena = arena;
    jungle->game_info = game_info;
    jungle->console = console;

    jungle->arena_mem_line = 10000 + (sbyte4_t)(arc4random() % 100);
    jungle->active_window = ARENA;
    jungle->arena_window_size = (MEM_SIZE / (COLS / 3)) - (LINES * 2 / 3 - 2);

    jungle->cycling_speed = 50;

    jungle->cursors = true;

    jungle->help_menu_page = 1;

    light_mode = !game_data->light_mode;

    update_console_window(NULL, 0, 0);

    signal(SIGINT, sigint_handler);
}

void exit_ncurses(void)
{
    free(jungle);
    endwin();
}
