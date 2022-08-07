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
  char test_path[]="test_erosion_";
  unsigned char* new_hist=NULL;
  double threshold, nb_erosion;

  // Vérification de la ligne de commande
  if (argc != 3) { // On a besoin de l'image
    fprintf(stderr, "Erreur, il manque des arguments. Préciser le chemin de l'image ET le nombre d'érosions voulus. \n");
    exit(EXIT_FAILURE);
  }

  // Création des chemins 
  img_path = argv[1];
  nb_erosion = atof(argv[2]);
  new_img_path = calloc(256, sizeof(*new_img_path));
  strcat(new_img_path, test_path);
  strcat(new_img_path, img_path);

  img = read_pgm_img(img_path); // Lecture et création de la structure image

  // Seuillage
  new_hist = calc_histogram(img);
  threshold = opti_otsu_thresholding(new_hist);
  manual_thresholding(img, threshold);
  free(new_hist);

  for (int i = 0; i < nb_erosion; i++) img = erosion(img);   // Erosion 

  write_img_file(img, new_img_path); // Ecriture de l'image pour vérifier que tous les pixels blancs ont été parcourus

  // Libération de la mémoire
  free(new_img_path);
  free_memory(img.data);

  exit(EXIT_SUCCESS);
}
