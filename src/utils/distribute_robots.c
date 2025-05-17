#include "corewar.h"
#include "errors.h"
#include "op.h"
#include "structures.h"
#include "utils.h"
#include <stdlib.h>
#include <string.h>

static byte2_t count_placed_robots(robot_info_t **robots, byte2_t robot_count)
{
    byte2_t count = 0;

    for (byte2_t i = 0; i < robot_count; i++)
        if (robots[i]->mem_adr != (byte2_t)-1)
            count++;
    return count;
}

static int find_next_robot(byte2_t robot_count, int placements[robot_count],
                           int current_end)
{
    int next_placement = -1;
    int min_distance   = MEM_SIZE;
    int distance       = 0;

    for (byte2_t i = 0; i < robot_count; i++)
    {
        if (placements[i] == -1)
            continue;
        distance = 0;
        if (placements[i] > current_end)
            distance = placements[i] - current_end;
        else
            distance = (MEM_SIZE - current_end) + placements[i] + 1;
        if (distance < min_distance)
        {
            min_distance   = distance;
            next_placement = placements[i];
        }
    }
    return next_placement;
}

static void compute_gaps(byte2_t robot_count, int gaps[][3],
                         int placements[robot_count], int sizes[robot_count])
{
    byte2_t current_gap = 0;

    for (byte2_t i = 0; i < robot_count; i++)
    {
        if (placements[i] == (byte2_t)-1)
            continue;
        gaps[current_gap][0] = placements[i] + sizes[i];
        gaps[current_gap][1] =
            find_next_robot(robot_count, placements, gaps[current_gap][0]);
        gaps[current_gap][2] = gaps[current_gap][1] - gaps[current_gap][0];
        if (gaps[current_gap][2] < 0)
            gaps[current_gap][2] = MEM_SIZE - abs(gaps[current_gap][2]);
        current_gap++;
    }
}

static byte2_t find_highest_gap(byte2_t gap_count, int gaps[gap_count][3],
                                int position_count[gap_count])
{
    int     highest = 0;
    byte2_t index   = 0;

    for (byte2_t i = 0; i < gap_count; i++)
        if (gaps[i][2] / (position_count[i] + 1) > highest)
        {
            index   = i;
            highest = gaps[i][2] / (position_count[i] + 1);
        }
    return index;
}

static void place_robots_in_gap(gap_placement_info_t *gap_info)
{
    int adress = 0;

    if (gap_info->positions_count <= 0)
        return;
    for (byte2_t i = 0; i < gap_info->positions_count; i++)
    {
        adress =
            (gap_info->gap_size / (gap_info->positions_count + 1) * (i + 1) -
             (gap_info->robots_in_gap[i]->header->prog_size / 2) +
             gap_info->gap_start) %
            MEM_SIZE;
        if (adress < 0)
            adress = MEM_SIZE - abs(adress);
        gap_info->robots_in_gap[i]->mem_adr = (byte2_t)adress;
    }
}

static robot_info_t **place_in_gaps(byte2_t        placed_count,
                                    byte2_t        to_place_count,
                                    int            gaps[placed_count][3],
                                    robot_info_t **robots)
{
    robot_info_t *pos[placed_count][to_place_count];
    int           pos_count[placed_count];
    int           highest_index = 0;
    int           gaps_copy[placed_count][3];

    memset(pos_count, 0, sizeof(int) * placed_count);
    memcpy(gaps_copy, gaps, sizeof(int) * placed_count * 3);
    for (byte2_t i = 0; i < to_place_count; i++)
    {
        highest_index = find_highest_gap(placed_count, gaps, pos_count);
        if (gaps[highest_index][2] > robots[i]->header->prog_size)
        {
            gaps[highest_index][2] -= robots[i]->header->prog_size;
            pos[highest_index][pos_count[highest_index]] = robots[i];
            pos_count[highest_index]++;
        }
        else
            return write_error(PLACING_ERROR, NULL, -1);
    }
    for (byte2_t gap_idx = 0; gap_idx < placed_count; gap_idx++)
        place_robots_in_gap(
            &(gap_placement_info_t){pos[gap_idx], gaps_copy[gap_idx][0],
                                    gaps_copy[gap_idx][2], pos_count[gap_idx]});
    return robots;
}

static robot_info_t **place_default(robot_info_t **robots, byte2_t robot_count)
{
    float   memory_adress = (float)MEM_SIZE / robot_count;
    byte2_t new_adress    = 0;

    for (byte2_t i = 0; i < robot_count; i++)
    {
        new_adress =
            update_program_counter((byte2_t)(memory_adress * i),
                                   -(sbyte2_t)robots[i]->header->prog_size / 2);
        robots[i]->mem_adr = new_adress;
    }
    return robots;
}

static robot_info_t **create_new_robot_list(robot_info_t **robots,
                                            byte2_t        robot_count)
{
    byte2_t        count    = 0;
    robot_info_t **new_list = calloc(robot_count, sizeof(robot_info_t *));

    for (byte2_t i = 0; i < robot_count; i++)
        if (robots[i]->mem_adr == (byte2_t)-1)
        {
            new_list[count] = robots[i];
            count++;
        }
    return new_list;
}

// The algorithm works as follows:
// - Find the current gaps and their sizes
// - For each robot, we add it to the gap with the most remaining space
// - Repeat
//
// - Once all robots are pseudo-placed, actually place them by dividing
// the original gap size by the amount of robots that fit in said gap
//
// Easier said than done!
//
// In case a robot doesn't fit in current biggest gap,
// either restart with another robot or just display a warning about it
//
// There are as many initial gaps as there are robots
// - 1 robot = 1 gap [the rest of the arena]
// - 2 robots = 2 gaps [the one between the robots and the one after]
robot_info_t **distribute_robots(robot_info_t **robots, byte2_t robot_count)
{
    int     placement_list[robot_count];
    int     robots_sizes[robot_count];
    byte2_t placed_robots = count_placed_robots(robots, robot_count);
    int     gaps[placed_robots][3];

    if (placed_robots == 0)
        return place_default(robots, robot_count);
    if (robot_count - placed_robots == 0)
        return robots;
    for (byte2_t i = 0; i < robot_count; i++)
    {
        placement_list[i] = robots[i]->mem_adr;
        robots_sizes[i]   = robots[i]->header->prog_size;
    }
    compute_gaps(robot_count, gaps, placement_list, robots_sizes);
    robots = create_new_robot_list(robots, robot_count);
    place_in_gaps(placed_robots, robot_count - placed_robots, gaps, robots);
    free(robots);
    return (robot_info_t **)1;
}
