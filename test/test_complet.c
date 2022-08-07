#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lecture_ecriture.h"
#include "op_booleennes.h"
#include "op_morphologiques.h"
#include "seuillage.h"
#include "application_cellules.h"

int main(int argc, char** argv)
{
  grid_img img;
  char* new_img_path=NULL;
  char* img_path=NULL;
  char test_path[]="test_beta_";
  unsigned char* new_hist=NULL;
  double threshold;

  /* Lecture de la ligne de commande */
  if (argc != 2) { // On a besoin de l'image
    fprintf(stderr, "Erreur, il manque un argument. Préciser le chemin de l'image. \n");
    exit(EXIT_FAILURE);
  }
  img_path = argv[1];

  /* Création des chemins */
  new_img_path = calloc(256, sizeof(*new_img_path));
  strcat(new_img_path, test_path);
  strcat(new_img_path, img_path);

  /* Création de l'image */
  img = read_pgm_img(img_path);

  /* Seuillage de l'image */
  new_hist = calc_histogram(img); // Calcul de l'histogramme
  threshold = opti_otsu_thresholding(new_hist); // Calcul du seuil par la méthode d'Otsu
  manual_thresholding(img, threshold); // Seuillage de l'image
  free(new_hist); // Libération de la mémoire de l'histogramme

  // Bouchage de trous 
  img = seal_hole(img);

  // Suppression des cellules bords 
  img = delete_edge_cell(img);

  // Erosion 
  img = last_erosion(img); 

  // Dilatation pour avoir assez de pixels voisins lors du comptage de cellules 
  img = expansion(img);

  // Suppression des cellules bords 
  img = delete_edge_cell(img);

  // Comptage du nombre de cellules 
  img.cells = 0;
  for (int i=0; i<img.height; i++){
    for (int j=0; j<img.width; j++){
      if (img.data[i][j]==255){
        dfs(img, i, j);
        img.cells++;
      }
    }}
  printf("Nombre de cellules: %d \n", img.cells);

  /* Ecriture de la nouvelle image */
  write_img_file(img, new_img_path); 

  /* Libération de la mémoire */
  free(new_img_path);
  free_memory(img.data);
  exit(EXIT_SUCCESS);
}
