#include <stdio.h>
#include <stdlib.h>
#include <errno.h> // pour utiliser perror
#include <string.h>
#include "op_morphologiques.h"
#include "op_booleennes.h"
#include "lecture_ecriture.h"

/*
Fonction permettant de reconstruire une partie d'une image à partir d'une graine que l'on fait croître
Il ne faut pas utiliser la reconstruction sur cellules_mini.pgm sans faire d'érosion avant!
*param original_img Image que l'on va reconstruire (partiellement)
*param seed_img Image graine à faire croître

*return reconstructed_img Image reconstruite
*/
grid_img reconstruction(grid_img original_img, grid_img seed_img){
  /* Initialisation des images */
  grid_img expanded_seed, reconstructed_img, last_reconstructed_img, last_expanded_seed;
  expanded_seed = init_img(expanded_seed, original_img);
  reconstructed_img = init_img(reconstructed_img, original_img);
  last_reconstructed_img = init_img(last_reconstructed_img, original_img);
  last_expanded_seed = init_img(last_expanded_seed, original_img);
  expanded_seed = expansion(seed_img);

  /* Reconstruction de l'image tant que la graine croît */
  do {
    last_reconstructed_img = reconstructed_img;
    reconstructed_img = intersection(original_img, expanded_seed);
    last_expanded_seed = reconstructed_img;
    expanded_seed = expansion(last_expanded_seed);
  } while(memcmp(*(reconstructed_img.data), *(last_reconstructed_img.data), sizeof(unsigned char)*(reconstructed_img.height)*(reconstructed_img.width))!=0);

  reconstructed_img = intersection(original_img, expanded_seed);

  /*free_memory(expanded_seed.data);
  free_memory(last_reconstructed_img.data);
  free_memory(last_expanded_seed.data);*/

  return reconstructed_img;
}

/*
Fonction réalisant l'opération morphologique de dilatation de l'image graine
*param seed_img Image graine à dilater

*return expanded_seed Image graine dilatée
*/
grid_img expansion(grid_img seed_img){
grid_img expanded_seed;
expanded_seed = init_img(expanded_seed, seed_img);
  for (int i=0; i<seed_img.height-2; i++){
    for (int j=0; j<seed_img.width-2; j++){
    /* Si un des 9 px est blanc */
    if (seed_img.data[i][j]==255||seed_img.data[i][j+1]==255||seed_img.data[i][j+2]==255||
      seed_img.data[i+1][j]==255||seed_img.data[i+1][j+1]==255||seed_img.data[i+1][j+2]==255||
      seed_img.data[i+2][j]==255||seed_img.data[i+2][j+1]==255||seed_img.data[i+2][j+2]==255){
        /* Alors mettre TOUS les px en blanc */
        expanded_seed.data[i][j]=255;
        expanded_seed.data[i][j+1]=255;
        expanded_seed.data[i][j+2]=255;
        expanded_seed.data[i+1][j]=255;
        expanded_seed.data[i+1][j+1]=255;
        expanded_seed.data[i+1][j+2]=255;
        expanded_seed.data[i+2][j]=255;
        expanded_seed.data[i+2][j+1]=255;
        expanded_seed.data[i+2][j+2]=255;
      }
  }}

  return expanded_seed;
}

/*
Fonction réalisant l'opération morphologique d'érosion sur une image
*param original_img Image à éroder

*return eroded_img Image érodée
*/
grid_img erosion(grid_img original_img){
  grid_img eroded_img;
  eroded_img = init_img(eroded_img, original_img);

  for (int i=0; i<original_img.height-2; i++){
    for (int j=0; j<original_img.width-2; j++){
      /* Si un dex px est noir */
    if (original_img.data[i][j]==0||original_img.data[i][j+1]==0||original_img.data[i][j+2]==0||
      original_img.data[i+1][j]==0||original_img.data[i+1][j+1]==0||original_img.data[i+1][j+2]==0||
      original_img.data[i+2][j]==0||original_img.data[i+2][j+1]==0||original_img.data[i+2][j+2]==0){
        /* Alors mettre TOUS les pixels en noir */
        eroded_img.data[i][j]=0;
        eroded_img.data[i][j+1]=0;
        eroded_img.data[i][j+2]=0;
        eroded_img.data[i+1][j]=0;
        eroded_img.data[i+1][j+1]=0;
        eroded_img.data[i+1][j+2]=0;
        eroded_img.data[i+2][j]=0;
        eroded_img.data[i+2][j+1]=0;
        eroded_img.data[i+2][j+2]=0;
      }
    else if (original_img.data[i][j]==255&&original_img.data[i][j+1]==255&&original_img.data[i][j+2]==255&&
      original_img.data[i+1][j]==255&&original_img.data[i+1][j+1]==255&&original_img.data[i+1][j+2]==255&&
      original_img.data[i+2][j]==255&&original_img.data[i+2][j+1]==255&&original_img.data[i+2][j+2]==255){ //Sinon mettre tous les px en blanc
      eroded_img.data[i][j]=255;
      eroded_img.data[i][j+1]=255;
      eroded_img.data[i][j+2]=255;
      eroded_img.data[i+1][j]=255;
      eroded_img.data[i+1][j+1]=255;
      eroded_img.data[i+1][j+2]=255;
      eroded_img.data[i+2][j]=255;
      eroded_img.data[i+2][j+1]=255;
      eroded_img.data[i+2][j+2]=255;
      }

  }}

  return eroded_img;
}

/* Fonction inversant la valeur des pixels d'une image seuillée.
Les pixels blancs deviennent noirs et vice versa.
*param original_img Image dont on veut inverser la valeur des pixels

return inversed_img Image dont la valeur des pixels a été inversée
*/
grid_img inversion(grid_img original_img){
  grid_img inversed_img;
  inversed_img = init_img(inversed_img, original_img);

  for (int i = 0; i<original_img.height; i++){
    for (int j = 0; j<original_img.width; j++){
      if(original_img.data[i][j]==0) inversed_img.data[i][j] = 255;
      else if(original_img.data[i][j]==255) inversed_img.data[i][j] = 0;
    }}
  return inversed_img;
}

/*
Fonction qui permet d'échanger le contenu de deux images
*param img1 adresse de l'image à échanger
*param img2 adresse de l'image à échanger
*return void
*/
void swap_img(grid_img *img1, grid_img *img2){
  grid_img tmp;
  tmp = *img1;  // On copie l'image 1 dans une temporaire
  *img1 = *img2; // On copie l'image 2 dans l'image 1
  *img2 = tmp; // On copie l'image temporaire dans l'image 2

  /*free_memory(tmp.data);*/
}

/* 
Fonction qui permet de créer une image vide (noire) à partir de l'image d'origine. 
On utilise l'image d'origine afin d'avoir la bonne taille de l'image.
*param original_img Image d'origine
*return empty_img Image vide
*/
grid_img create_empty_img(grid_img original_img){
  grid_img empty_img;
  empty_img = init_img(empty_img, original_img);
  for(int i = 0; i<empty_img.height; i++){
    for (int j = 0; j<empty_img.width; j++){
      if (empty_img.data[i][j]==255) empty_img.data[i][j]=0; // Mettre le reste des px blancs en noir
    }
  }
  return empty_img;
}