#include <stdlib.h>
#include <string.h>

#include "canvas.h"

#include "colours.h"

canvas *canvas_create(int width, int height) {
	canvas *c = malloc(sizeof(canvas));

	int i;

	if (c == NULL)
		return NULL;

	c->width = width;
	c->height = height;

	/* allocate contiguously & set to zero */
	c->pixels = calloc(width, sizeof(colour*));
	c->pixels[0] = calloc(width*height, sizeof(colour));
	for (i = 1; i < width; i++)
		c->pixels[i] = c->pixels[0] + i * height;

	return c;
}

void canvas_set_pixel(canvas *c, int x, int y, colour a) {
	c->pixels[x][y] = a;
}

colour canvas_get_pixel(canvas *c, int x, int y) {
	return c->pixels[x][y];
}

void canvas_destroy(canvas *c) {
	free(c->pixels);

	c->width = 0;
	c->height = 0;
	c->pixels = NULL;
}

