#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "ppmIO.h"
#include "imageManip.h"
#include "commandUtil.h"
//TODO include header files

int main(int argc, const char* argv[]) {

  int check = run_alg(argc, argv);
  switch(check) {
  case 0:
    return 0;
  case 1:
    printf("Failed to supply input filename or output filename, or both\n");
    return check;
  case 2:
    printf("Specified input file could not be found\n");
    return check;
  case 3:
    printf("Specified input file is not a properly-formatted PPM file, or reading input somehow fails\n");
    return check;
  case 4:
    printf("Specified output file could not be opened for writing, or writing output somehow fails\n");
    return check;
  case 5:
    printf("No operation name was specified, or operation name specified was invalid\n");
    return check;
  case 6:
    printf("Incorrect number of arguments or kind of arguments specified for the specified operation\n");
    return check;
  case 7:
    printf("Arguments for crop operation were out of range for the given input image\n");
    return check;
  case 8:
    printf("Other error\n");
    return check;
  default:
    return -1;
  }
}
