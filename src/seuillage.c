#include <stdio.h>
#include <stdlib.h>
#include <errno.h> // pour utiliser perror
#include <string.h>
#include "seuillage.h"

/*
Fonction réalisant le seuillage d'une image à partir d'une valeur de seuil donnée

*param img Image à seuiller
*param threshold Seuil demandé

*return void
 */
void manual_thresholding(grid_img img, double threshold)
{
  for(int i=0; i<img.height; i++){
    for(int j=0; j<img.width; j++){
      if(img.data[i][j]<threshold) img.data[i][j] = 0;
      else img.data[i][j] = 255;}}

}

/*
Fonction calculant l'histogramme d'une image et le stockant dans un tableau
*param img Image à analyser

*return new_hist Histogramme de l'image analysée
*/
unsigned char * calc_histogram(grid_img img){
  unsigned char* new_hist=NULL;

  new_hist = calloc(255, sizeof(*new_hist)); // penser à détruire mémoire

  for(int i=0; i<img.height; i++){
    for(int j=0; j<img.width; j++){
      new_hist[img.data[i][j]]++;
    }
  }
  return new_hist;
}

/*
Fonction calculant le seuil d'après la méthode d'Otsu
*param histogram Histogramme de l'image analysée

*return thresholding Seuil calculé par la méthode d'Otsu
*/
double otsu_thresholding(unsigned char * histogram){
  double black_proba=0, white_proba=0, black_average=0, white_average=0, variance=0, variance_max=0.0;
  double threshold=0;
  for(int s=0; s<=255; s++){
    for (int i=0; i<=255; i++){
      if(i<s) {
        black_proba+= histogram[i];    // calculer proba noir
        black_average+= i * histogram[i];     // calculer moyenne empirique noir
      }
      else {
        white_proba+= histogram[i];     // calculer proba blanc
        white_average+= i * histogram[i];     // calculer moyenne empirique blanc
      }
    }
    black_average /= black_proba;
    white_average /= white_proba;

    // calculer variance inter-classe
    variance = black_proba*white_proba*(black_average - white_average)*(black_average - white_average);
    if(variance>variance_max) {
      variance_max = variance;
      threshold = (double)s;
    }
    black_proba=0;
    white_proba=0;
    black_average=0;
    white_average=0;
}
  // return s pour lequel variance is max
  return threshold;
}

/*
Fonction calculant le seuil d'après la méthode d'Otsu de manière optimisée.
Les valeurs sont mises à jour au lieu d'être recalculées pour chaque seuil possible
*param histogram Histogramme de l'image analysée

*return thresholding Seuil calculé par la méthode d'Otsu
*/
double opti_otsu_thresholding(unsigned char * histogram){
  double omegaB=0, omegaW=0, ksiB=0, ksiW=0, muB=0, muW=0, sigma=0.0, sigma_max=0.0;
  double threshold=0;
  // Calculer omegaW et ksiW = Sommes complètes, muW = ksiW/omegaW
  for (int i = 0; i<255; i++){
    omegaW += histogram[i];
    ksiW += i*histogram[i];
  }
  muW = ksiW/omegaW;
  // Mise à jour des valeurs
  for(int s=1; s<255; s++){
    omegaB += histogram[s-1];
    ksiB += (s-1)*histogram[s-1];
    muB = ksiB/omegaB;
    omegaW -= histogram[s-1];
    ksiW -= (s-1)*histogram[s-1];
    muW = ksiW/omegaW;
    // calculer variance inter-classe
    sigma = omegaB*omegaW*(muB - muW)*(muB - muW);
    if(sigma>sigma_max) {
      sigma_max = sigma;
      threshold = (double)s;
    }
  }

  return threshold;
}
