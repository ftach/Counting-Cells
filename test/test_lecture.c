#include <stdio.h>
#include <stdlib.h>

#include "lecture_ecriture.h"
#include "op_booleennes.h"
#include "op_morphologiques.h"
#include "seuillage.h"
#include "application_cellules.h"

void test_read_pgm_img(){
  grid_img img;
  // Test avec disques.pgm
  puts("***** Testing get_img_dim function with disques.pgm *****");
  img = read_pgm_img("disques.pgm");
  write_img_file(img, "test_lecture_disques.pgm");
  puts("height=150 and width=150 should be.");
  printf("Function read_pgm_img got: height= %d  width= %d \n \n", img.height, img.width);
  free_memory(img.data);

// Test avec cellules_geant.pgm
  puts("***** Testing get_img_dim function with cellules_geant.pgm *****");
  img = read_pgm_img("cellules_geant.pgm");
  write_img_file(img, "test_lecture_cellules_geant.pgm");
  puts("height=1288 and width=1904 should be.");
  printf("Function read_pgm_img got: height= %d  width= %d \n", img.height, img.width);
  free_memory(img.data);

}

//int main(int argc, char** argv)
int main(void)
{
  test_read_pgm_img();
  exit(EXIT_SUCCESS);
}
