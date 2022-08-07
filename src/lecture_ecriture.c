#include <stdio.h>
#include <stdlib.h>
#include <errno.h> // pour utiliser perror
#include <string.h>
#include "lecture_ecriture.h"

/*
Fonction récupérant les dimensions de l'image en lisant le fichier pgm et rangeant les valeurs des pixels dans un tableau 2D
*param char img_path[]
*return img Structure contenant la taille et le contenu de l'image pgm lue
*/
grid_img read_pgm_img(char img_path[]){
  grid_img img;
  char magic_nb[20];
  int l_nb, c_nb, deep_nb;
  FILE* fpgm;
  fpgm = fopen(img_path, "rb");

  fscanf(fpgm, "%s \n%d %d \n%d", magic_nb, &c_nb, &l_nb, &deep_nb); // Récupération de l'en tête

  img.width = c_nb;
  img.height = l_nb;

  img.data = allocate_memory(img.width, img.height); // allouer la mémoire de img.data

  // Remplissage de la matrice avec la valeur des pixels
  for (int i = 0; i<img.height; i++) fread(img.data[i],sizeof(unsigned char),img.width,fpgm);

  fclose(fpgm);
  return img;
}

/*
Fonction allouant la mémoire de manière contigüe pour un tableau 2D
*param width Nombre de colonnes
*param height Nombre de lignes

*return Tableau d'entiers alloué
*/
unsigned char ** allocate_memory(int width, int height){
  unsigned char** img_array = malloc(height*sizeof(unsigned char*));
  img_array[0]= malloc(height * width * sizeof(unsigned char));
  for (int i=1; i< height; i++) img_array[i]= img_array[0] + i * width;

  return img_array;
}

/*
Fonction détruisant la mémoire allouée dynamiquement de manière contigüe
*param img_array
return void
*/
void free_memory(unsigned char ** img_array){
  free(img_array[0]);
  free(img_array);
}


/* Fonction écrivant les caractéristiques d'une image .pgm dans un fichier
*param img  Structure contenant la taille et le contenu de l'image pgm lue auparavant
return void*/
void write_img_file(grid_img img, char new_img_path[]){
  FILE * f_test;
  f_test = fopen(new_img_path, "wb"); // Ouvrir nouveau fichier en mode écriture binaire

  fprintf(f_test, "P5\n%d %d\n255\n", img.width, img.height); // Ecrire l'en tête

  for(int k = 0; k<img.height; k++) fwrite(img.data[k], sizeof(unsigned char), img.width, f_test);   // Ecrire valeur des pixels

  fclose(f_test);

}
/*
Fonction initialisant une nouvelle image à partir des dimensions d'une autre Image
*param new_img Structure de la nouvelle image à initialiser
*model_img Structure de l'image servant de modèlegal

*return new_img Image dont la mémoire et les dimensions sont initialisées
*/
grid_img init_img(grid_img new_img, grid_img model_img){
  new_img.width = model_img.width;
  new_img.height = model_img.height;
  new_img.data = allocate_memory(new_img.width, new_img.height);

  return new_img;
}
