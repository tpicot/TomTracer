#pragma once

#include "colour.h"

typedef struct canvas {
	int width;
	int height;

	colour **pixels; /* pixels[width][height]*/
} canvas;

canvas *canvas_create(int width, int height);

void canvas_set_pixel(canvas *c, int x, int y, colour a);
colour canvas_get_pixel(canvas *c, int x, int y); 

void canvas_destroy(canvas *c);