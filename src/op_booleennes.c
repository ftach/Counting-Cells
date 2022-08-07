#include <stdio.h>
#include <stdlib.h>
#include <errno.h> // pour utiliser perror
#include <string.h>
#include "op_booleennes.h"
#include "lecture_ecriture.h"

/*
Fonction réalisant l'opération de OU-exclusif entre deux images
*param img1 Image numéro 1
*param img2 Image numéro 2

*return xor_img Image issue du OU-exclusif entre img1 et img2
 */
grid_img xor(grid_img img1, grid_img img2){
  grid_img xor_img;
  xor_img = init_img(xor_img, img1);

  for (int i = 0; i<xor_img.height; i++){
    for (int j = 0; j<xor_img.width; j++){
      if(img1.data[i][j]!=img2.data[i][j]) xor_img.data[i][j]=255; // Si pixels != alors mettre blanc
      else xor_img.data[i][j]=0; // Sinon mettre pixel en noir
     }}
  return xor_img;
}

/*
Fonction réalisant l'opération logique d'intersection
*param img1 Image numéro 1
*param img2 Image numéro 2

*return intersection_img Image issue de l'intersection de img1 et img2
*/
grid_img intersection(grid_img img1, grid_img img2){
  grid_img intersection_img;
  intersection_img = init_img(intersection_img, img1);

  for (int i = 0; i<intersection_img.height; i++){
    for (int j = 0; j<intersection_img.width; j++){
      /* Si les px sont de couleurs différentes alors l'intersection est un px noir */
      if(img1.data[i][j]!=img2.data[i][j]) intersection_img.data[i][j]=0;
      /* Sinon, l'intersection est le px originel */
      else intersection_img.data[i][j] = img2.data[i][j];
    }}

  return intersection_img;
}

/*
Fonction réalisant l'opération d'union entre deux images
*param img1 Image numéro 1
*param img2 Image numéro 2

*return union_img Image issue de l'union entre img1 et img2
 */
grid_img make_union(grid_img img1, grid_img img2){
  grid_img union_img;
  union_img = init_img(union_img, img1);

  for (int i = 0; i<union_img.height; i++){
    for (int j = 0; j<union_img.width; j++){
      if(img1.data[i][j]==0 && img2.data[i][j]==0) union_img.data[i][j]=0; // Si pixels != alors mettre blanc
      else union_img.data[i][j]=255; // Sinon le px est blanc
    }}
  return union_img;
}
