#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "ppmIO.h"
#include "imageManip.h"
#include "commandUtil.h"

int run_alg(int argc, const char* argv[]) {
  //check 1
  if (argc < 3) return 1;

  //check 2
  FILE* input = fopen(argv[1], "r");
  if (input == NULL) return 2;

  //check 3 & generate input image
  Image* im = readPPM(input);
  if (im == NULL) {
    fclose(input);
    return 3;
  }
  fclose(input);

  //check 4
  FILE* output = fopen(argv[2], "w");
  if (output == NULL) {
    free(im->data);
    free(im);
    return 4;
  }
  //check 5,6,7 call to function
  if (argc < 4) {
    fclose(output);
    free(im->data);
    free(im);
    return 5;
  }
  int sa = select_alg(argc, argv, im);
  if (sa != 0) {
    fclose(output);
    free(im->data);
    free(im);
    return sa;
  }
  //return to check 4
  if (writePPM(output, im) == -1) {
    fclose(output);
    free(im);
    free(im->data);
    return 4;
  }
  fclose(output);

  free(im->data);
  free(im);

  return 0;

}


