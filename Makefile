CC = gcc
CFLAGS = -Wall -Werror `pkg-config --cflags gtk+-3.0` `pkg-config --libs gtk+-3.0`
LIBS = -lm -lexpat

OBJ =\
	main.c \
	display.c \
	parsing.c \
	calculations.c \
	draw.c

all: main

clean:
		rm -f *.o statystyki-trasy

.c.o:
		$(CC) -c $(INCLUDES) $(CFLAGS) $<

main: $(OBJ)
		$(CC) $(OBJ) $(LIBS) $(CFLAGS) -o statystyki-trasy