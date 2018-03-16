#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "ppmIO.h"
#include "imageManip.h"

int select_alg(int argc, const char* argv[], Image* im) {
  const char* oper = argv[3];

  //selecting an algorithm
  if (strcmp(oper, "swap") == 0) {
    if (argc != 4) return 6;
    return swap(im);
  } else if (strcmp(oper, "blackout") == 0) {
    if (argc != 4) return 6;
    return blackout(im);
  } else if (strcmp(oper, "crop") == 0) {
    if (argc != 8) return 6;
    return crop(im, argv);
  } else if (strcmp(oper, "grayscale") == 0) {
    if (argc != 4) return 6;
    return grayscale(im);
  } else if (strcmp(oper, "contrast") == 0) {
    if (argc != 5) return 6;
    return contrast(im, argv);
  } else {
    return 5;
  }
}

//swap function
int swap(Image* im) {
  unsigned char r, g, b;
  Pixel temp;
  for (int i = 0; i < ((im->cols)*(im->rows)); i++) {
    temp = im->data[i];
    r = temp.r;
    g = temp.g;
    b = temp.b;
    temp = (Pixel) {g,b,r};
    im->data[i] = temp;
  }
  return 0;
}

//blackout top right corner
int blackout(Image* im) {
  int col_bound = (im->cols & 1) ? 1 + (im->cols/2) : im->cols/2;
  int row_bound = (im->rows & 1) ? 1 + (im->rows/2) : im->rows/2;
  int col_cur, row_cur;
  Pixel black = (Pixel) {0,0,0};
  for (int i = 0; i < ((im->cols)*(im->rows)); i++) {
    col_cur = i % im->cols;
    row_cur = i / im->cols;
    if (col_cur >= col_bound && row_cur < row_bound) im->data[i] = black;    
  }
  return 0;
}


//crop coordinates
int crop(Image* im, const char* argv[]) {
  int col_left, row_top, col_right, row_bottom;

  //checks for valid input
  if (sscanf(argv[4], "%d", &col_left) != 1) return 6;
  if (sscanf(argv[5], "%d", &row_top) != 1) return 6;
  if (sscanf(argv[6], "%d", &col_right) != 1) return 6;
  if (sscanf(argv[7], "%d", &row_bottom) != 1) return 6;
  if (col_left < 0 || col_left >= im->cols) return 7;
  if (row_top < 0 || row_top >= im->rows) return 7;
  if (col_right <= col_left || col_right > im->cols) return 7;
  if (row_bottom <= row_top || row_bottom > im->rows) return 7;
  
  int rows_new = row_bottom - row_top;
  int cols_new = col_right - col_left;
  //Pixel *temp_data = malloc(sizeof(Pixel)*rows_new*cols_new);
  int counter = 0;
  int col_cur, row_cur;
  for (int i = 0; i < ((im->cols)*(im->rows)); i++) {
    col_cur = i % im->cols;
    row_cur = i / im->cols;
    if (col_cur >= col_left && col_cur < col_right && row_cur >= row_top && row_cur < row_bottom) {
      im->data[counter] = im->data[i];
      counter++;
    }
  }
  
  im->data = realloc(im->data, sizeof(Pixel)*rows_new*cols_new);
  im->rows = rows_new;
  im->cols = cols_new;

  return 0;
}

//grayscale
int grayscale(Image* im) {
  unsigned char intensity;
  Pixel temp;
  for (int i = 0; i < ((im->cols)*(im->rows)); i++) {
    temp = im->data[i];
    intensity = (0.30*temp.r) + (0.59*temp.g) + (0.11*temp.b);
    temp = (Pixel) {intensity,intensity,intensity};
    im->data[i] = temp;
  }
  return 0;
}

//contrast image
int contrast(Image* im, const char* argv[]) {
  double adj;
  if (sscanf(argv[4], "%lf", &adj) != 1) return 6;
  // if (adj < 0.0) return 6;
  // will work if negative
  
  unsigned char r, g, b;
  Pixel temp;
  for (int i = 0; i < ((im->cols)*(im->rows)); i++) {
    temp = im->data[i];
    r = contrast_helper(temp.r,adj);
    g = contrast_helper(temp.g,adj);
    b = contrast_helper(temp.b,adj);
    temp = (Pixel) {r,g,b};
    im->data[i] = temp;
  }
  return 0;
}

//contrast helper function for channeling 
unsigned char contrast_helper(unsigned char ch, double adj) {
  double d = (double) ch;
  d = d - (255.0/2.0);
  d = d * adj;
  d = d + (255.0/2.0);
  if (d > 255.0) d = 255.0;
  if (d < 0.0) d = 0.0;
  ch = (unsigned char) d;
  return ch;
}
