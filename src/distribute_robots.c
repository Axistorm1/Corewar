/*
** EPITECH PROJECT, 2025
** corewar
** File description:
** distribute_robots.c
*/

#include "op.h"
#include "structures.h"
#include "my_string.h"
#include "corewar.h"

static int count_placed_robots(
    robot_info_t **robots,
    byte2_t robot_count)
{
    byte2_t count = 0;

    for (byte2_t i = 0; i < robot_count; i++)
        if (robots[i]->mem_adr != (byte2_t)-1)
            count++;
    return count;
}

static int find_next_robot(
    byte2_t robot_count,
    int placements[robot_count],
    int current_end)
{
    int next_placement = -1;
    int min_distance = MEM_SIZE;
    int distance = 0;

    for (byte2_t i = 0; i < robot_count; i++) {
        if (placements[i] == -1)
            continue;
        distance = 0;
        if (placements[i] > current_end)
            distance = placements[i] - current_end;
        else
            distance = (6144 - current_end) + placements[i] + 1;
        if (distance < min_distance) {
            min_distance = distance;
            next_placement = placements[i];
        }
    }
    return next_placement;
}

static void compute_gaps(
    byte2_t robot_count,
    int gaps[][2],
    int placements[robot_count],
    int sizes[robot_count])
{
    byte2_t current_gap = 0;

    for (byte2_t i = 0; i < robot_count; i++)
        if (placements[i] != (byte2_t)-1) {
            gaps[current_gap][0] = placements[i] + sizes[i];
            gaps[current_gap][1] = find_next_robot(
                robot_count, placements, gaps[current_gap][0]);
            current_gap++;
        }
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
void distribute_robots(robot_info_t **robots, byte2_t robot_count)
{
    int placement_list[robot_count];
    int robots_sizes[robot_count];
    int placed_robots = count_placed_robots(robots, robot_count);
    int gaps[placed_robots][2];

    for (byte2_t i = 0; i < robot_count; i++) {
        placement_list[i] = robots[i]->mem_adr;
        robots_sizes[i] = robots[i]->header->prog_size;
    }
    compute_gaps(robot_count, gaps, placement_list, robots_sizes);
    return;
}
