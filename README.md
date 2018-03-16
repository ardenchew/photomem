# photomem
Version of photo shop using c memory allocation

Compiling done by Makefile
$make project
$make clean

Converts ppm wise
$./project input.ppm output.ppm contrast 0.5 
$./project input.ppm output.ppm crop 50 50 100 100 //crops to (50,50) to (100,100)
$./project input.ppm output.ppm swap //swaps pixelation channels
$./project input.ppm output.ppm greyscale
$./project input.ppm output.ppm blackout
