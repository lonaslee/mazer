/**
 * @file maze.h
 * @brief All maze generation algorithm implementations and maze object creators are here.
 */
#pragma once

#include "grid.h"

/* Maze generator implementations */
#include "aldous_broder.h"
#include "binary_tree.h"
#include "ellers.h"
#include "hunt_and_kill.h"
#include "sidewinder.h"
#include "wilsons.h"

void gen_maze(Grid *grid, MazeGenOptions *options, enum MazeType type) {
    switch (type) {
        case ALDOUS_BRODER: gen_aldous_broder(grid, options); break;
        case BINARY_TREE:   gen_binary_tree(grid, options);   break;
        case ELLERS:        gen_ellers(grid, options);        break;
        case HUNT_AND_KILL: gen_hunt_and_kill(grid, options); break;
        case SIDEWINDER:    gen_sidewinder(grid, options);    break;
        case WILSONS:       gen_wilsons(grid, options);       break;
        default:
            break;
    }
}