#ifndef IMAGEMANIP_H
#define IMAGEMANIP_H

int select_alg(int argc, const char* argv[], Image* im);

int swap(Image* im);
int blackout(Image* im);
int crop(Image* im, const char*argv[]);
int grayscale(Image* im);
int contrast(Image* im, const char* argv[]);
unsigned char contrast_helper(unsigned char ch, double adj);

#endif
