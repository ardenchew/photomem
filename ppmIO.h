//ppmIO.h
//601.220, Spring 2018
//Starter code for midterm project - feel free to edit/add to this file


#ifndef PPMIO_H
#define PPMIO_H


/* struct to store an RGB pixel, one byte per channel */
typedef struct _pixel {
  unsigned char r;
  unsigned char g;
  unsigned char b;
} Pixel;


/* struct to store an image: dimensions and pointer to pixel array */
typedef struct _image {
  Pixel *data;
  int rows;
  int cols;
} Image;


/* read PPM formatted image from a file (assumes fp != NULL) */
Image* readPPM(FILE *fp);


/* write PPM formatted image to a file (assumes fp != NULL and img != NULL) */
int writePPM(FILE* fp, const Image* img);

#endif
