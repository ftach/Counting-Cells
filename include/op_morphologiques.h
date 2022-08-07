#ifndef _OP_MORPHOLOGIQUES_H
#define _OP_MORPHOLOGIQUES_H

#include "lecture_ecriture.h"

grid_img expansion(grid_img seed_img);
grid_img erosion(grid_img original_img);
grid_img reconstruction(grid_img original_img, grid_img seed_img);
grid_img inversion(grid_img original_img);
void swap_img(grid_img *img1, grid_img *img2);
grid_img create_empty_img(grid_img original_img);

#endif
