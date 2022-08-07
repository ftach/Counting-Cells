#ifndef _APPLICATION_CELLULES_H
#define _APPLICATION_CELLULES_H

#include "lecture_ecriture.h"

void dfs(grid_img, int x, int y);
grid_img last_erosion(grid_img original_img);
grid_img seal_hole(grid_img original_img);
grid_img delete_edge_cell(grid_img original_img);
grid_img create_seed(grid_img original_img, grid_img seed_img);

#endif
