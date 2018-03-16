//ppmIO.c
//601.220, Spring 2018
//Starter code for midterm project - feel free to edit/add to this file

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "ppmIO.h"

/* read PPM formatted image from a file (assumes fp != NULL) */
Image* readPPM(FILE *fp) {

  Image* im = malloc(sizeof(Image));
  
  //fp should already be opened
  if (!fp) return NULL;
  
  char str[255]; //for reading file lines
  if (fgets(str,255,fp) == NULL) {
    free(im);
    im = NULL;
    return im; //header
  }
  if (fgets(str,255,fp) == NULL) {
    free(im);
    im = NULL;
    return im; //next
  }
  while (str[0] == '#') {
    if (fgets(str,255,fp) == NULL) {
      free(im);
      im = NULL;
      return im;
    }
  }
  sscanf(str,"%d %d", &im->cols, &im->rows);
  int colors;
  if (fscanf(fp,"%d ",&colors) != 1) {
    free(im);
    im = NULL;
    return im;
  }
  if (colors != 255) {
    free(im);
    im = NULL;
    return im;
  }
   
  im->data = malloc(sizeof(Pixel)*im->cols*im->rows);
  if ((int) fread(im->data, sizeof(Pixel), (im->cols*im->rows), fp) != (im->cols*im->rows)) {
    free(im->data);
    free(im);
    im = NULL;
    return im;
  }

  return im;
}

/* write PPM formatted image to a file (assumes fp != NULL and img != NULL) */
int writePPM(FILE *fp, const Image* im) {

  /* abort if either file pointer is dead or image pointer is null; indicate failure with -1 */
  if (!fp || !im) {
    return -1;
  }

  /* write tag and dimensions; colors is always 255 */
  fprintf(fp, "P6\n%d %d\n%d\n", im->cols, im->rows, 255);

  /* write pixels */
  int num_pixels_written = (int) fwrite(im->data, sizeof(Pixel), (im->rows) * (im->cols), fp);

  /* check if write was successful or not; indicate failure with -1 */
  if (num_pixels_written != (im->rows) * (im->cols)) {
    return -1;
  }

  /* success, so return number of pixels written */
  return num_pixels_written;
}



