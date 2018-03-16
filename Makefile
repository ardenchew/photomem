CC = gcc
CONSERVATIVE_FLAGS = -std=c99 -Wall -Wextra -pedantic
DEBUGGING_FLAGS = -g -O0
CFLAGS = $(CONSERVATIVE_FLAGS) $(DEBUGGING_FLAGS)

project: project.o commandUtil.o ppmIO.o imageManip.o
	$(CC) -o project project.o commandUtil.o ppmIO.o imageManip.o

imageManip.o: imageManip.c ppmIO.h imageManip.h
	$(CC) $(CFLAGS) -c imageManip.c

ppmIO.o: ppmIO.c ppmIO.h
	$(CC) $(CFLAGS) -c ppmIO.c

commandUtil.o: commandUtil.c commandUtil.h ppmIO.h imageManip.h
	$(CC) $(CFLAGS) -c commandUtil.c

project.o: project.c commandUtil.h ppmIO.h imageManip.h
	$(CC) $(CFLAGS) -c project.c

clean:
	rm -f *.o project *.gcov
