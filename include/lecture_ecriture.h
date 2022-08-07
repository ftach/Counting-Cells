#ifndef _LECTURE_ECRITURE_H
#define _LECTURE_ECRITURE_H

struct grid_img {
int width;
int height;
int cells;
unsigned char** data;
};
typedef struct grid_img grid_img;

grid_img read_pgm_img(char img_path[]);
unsigned char ** allocate_memory(int width, int height);
grid_img init_img(grid_img new_img, grid_img model_img);
void write_img_file(grid_img img, char new_img_path[]);
void free_memory(unsigned char ** img_array);

#endif
