#include <stdio.h>
#include <stdlib.h>
#include <errno.h> // pour utiliser perror
#include <string.h>

#include "application_cellules.h"
#include "lecture_ecriture.h"
#include "op_booleennes.h"
#include "op_morphologiques.h"

/*
Fonction créant une image graine à partir d'une image source.
Ici, seul un rectangle de 1px de largeur de l'image source est conservé, le reste devenant noir.
*param original_img Image source
*param seed_img Image graine déjà initialisée mais vide

*return seed_img Image graine créée
*/
grid_img create_seed(grid_img original_img, grid_img seed_img){

  /* Mettre tout les px en noir sauf la ligne 0, la dernière ligne, la colonne 0 et la dernière colonne */
  for (int i = 0; i<original_img.height; i++){
    for (int j = 0; j<original_img.width; j++){
      if (i>0 && i<original_img.height-1 && j>0 && j<original_img.width-1) seed_img.data[i][j] = 0;
      else seed_img.data[i][j] = original_img.data[i][j];
    }
  }

  return seed_img;
}

/*
Fonction permettant de boucher les trous à l'intérieur des cellules causés par le seuillage de l'image.
*param thresholded_img Image avec cellules contenant des trous

return no_hole_img Image ne contenant plus de trou
*/
grid_img seal_hole(grid_img thresholded_img){
  // Initialiser images
  grid_img inversed_img, seed_img, no_hole_img;
  inversed_img = init_img(inversed_img, thresholded_img);
  seed_img = init_img(seed_img, thresholded_img);
  no_hole_img = init_img(no_hole_img, thresholded_img);

  inversed_img = inversion(thresholded_img); // Inverser image originale
  seed_img = create_seed(thresholded_img, seed_img); // Créer image graine
  no_hole_img = reconstruction(inversed_img, seed_img); // Reconstruire l'image avec les cellules bords uniquement
  no_hole_img = inversion(no_hole_img);// inverser à nouveau l'image

  /*free_memory(inversed_img.data);
  free_memory(seed_img.data);*/

  return no_hole_img;
}

/*
Fonction supprimant les cellules situées au bord de l'Image
*param original_img Image dont on veut supprimer les cellules bords

return no_edge_img Image sans cellules bords
*/
grid_img delete_edge_cell(grid_img original_img){
  grid_img seed_img, reconstructed_seed, no_edge_img;

  seed_img = init_img(seed_img, original_img); // Initialiser image graine
  reconstructed_seed = init_img(reconstructed_seed, original_img); // Initialiser image graine reconstruite
  no_edge_img = init_img(no_edge_img, original_img); // Initialiser image sans cellules bords

  seed_img = create_seed(original_img, seed_img); // Créer image graine
  reconstructed_seed = reconstruction(original_img, seed_img); // Reconstruire l'image avec les cellules bords uniquement
  no_edge_img = xor(original_img, reconstructed_seed); // Obtenir l'image sans cellules bord avec un ou exclusif

  /*free_memory(seed_img.data);
  free_memory(reconstructed_seed.data);*/

  return no_edge_img;
}

/*
Fonction réalisant l'algorithme de parcours en profondeur (Deep First Search).
Cet algorithme permet notamment de compter le nombre de cellules situé sur l'image (seuillée, sans cellule bord et érodée)
Il est basé sur la 4-connectivité.

*param original_img Image à parcourir
*param x Abscisse du px à explorer
*param y Ordonée du x à explorer

*return void
 */
void dfs(grid_img original_img, int x, int y){
  /* Si le px exploré n'a jamais été visité et est blanc */
    if (original_img.data[x][y]==255) {
        original_img.data[x][y] = 150; // Marquer le px comme visité
        /* Puis on explore ses 4 voisins */
        dfs(original_img, x, y-1);
        dfs(original_img, x, y+1);
        dfs(original_img, x+1, y);
        dfs(original_img, x-1, y);}
}

/* Fonction qui consiste créer une image des érodés ultimes, c’est-à-dire, pour chaque cellule, sa
dernière version érodée avant qu’elle ne disparaisse.
L'image retournée nécessite 1 ou 2 dilatations avant comptage du nombre de cellules.
*param original_img Image dont on veut déterminer les érodés ultimes
*return last_eroded_img Image contenant les érodés ultimes
*/
grid_img last_erosion(grid_img original_img){
  grid_img last_erosion_img, eroded_img, residues, reconstructed_img, current_img, empty_img;
  last_erosion_img = init_img(last_erosion_img, original_img);
  eroded_img = init_img(eroded_img, original_img);
  residues = init_img(residues, original_img);
  reconstructed_img = init_img(reconstructed_img, original_img);
  current_img = init_img(current_img, original_img);

  empty_img = create_empty_img(original_img);
  current_img = original_img;

  do {
    eroded_img = erosion(current_img);
    reconstructed_img = init_img(reconstructed_img, original_img);     // Réinitialiser image reconstruite
    reconstructed_img = reconstruction(current_img, eroded_img);
    residues = xor(reconstructed_img, current_img); //les px différents deviennent blancs
    last_erosion_img = make_union(residues, last_erosion_img); 
    swap_img(&current_img, &eroded_img);
  } while(memcmp(*(current_img.data), *(empty_img.data), sizeof(unsigned char)*(current_img.height)*(current_img.width))!=0); 

  // Libération de la mémoire
  /*free_memory(eroded_img.data);
  free_memory(residues.data);
  free_memory(reconstructed_img.data);
  free_memory(empty_img.data);
  free_memory(current_img.data);*/

  return last_erosion_img;
}
