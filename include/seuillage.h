#ifndef _SEUILLAGE_H
#define _SEUILLAGE_H

#include "lecture_ecriture.h"

unsigned char * calc_histogram(grid_img img);
void manual_thresholding(grid_img img, double thresholding);
double otsu_thresholding(unsigned char * histogram);
double opti_otsu_thresholding(unsigned char * histogram);

#endif
