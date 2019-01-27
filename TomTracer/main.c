#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL.h>

#include "tuple.h"
#include "canvas.h"
#include "colours.h"

/* projectile toy */

typedef struct projectile {
	tuple position;
	tuple velocity;
} projectile;

typedef struct environment {
	tuple gravity;
	tuple wind;
} environment;

projectile tick(environment e, projectile p) {
	tuple position;
	tuple velocity;
	projectile new_p;

	position = tuple_add(p.position, p.velocity);
	velocity = tuple_add(tuple_add(p.velocity, e.gravity), e.wind);

	new_p.position = position;
	new_p.velocity = velocity;

	return new_p;
}

void plot_projectile(canvas *c) {
	projectile p;
	environment e;
	int x, y;
	colour col = { 255,0,0 };

	p.position = tuple_create_point(0, 1, 0);
	p.velocity = tuple_scale(tuple_normalize(tuple_create_vector((float)1, (float)1.8, (float)0)), (float)11.25);
	e.gravity = tuple_create_vector(0, (float)-0.1, 0);
	e.wind = tuple_create_vector((float)-0.01, 0, 0);

	while (p.position.y > 0) {
		p = tick(e, p);

		y = (int)(c->height - p.position.y); /* move (0,0) from bottom left to top left */
		x = (int)p.position.x;

		printf("x: %f, y: %f, z: %f, w: %f \n", p.position.x, p.position.y, p.position.z, p.position.w);	
		canvas_set_pixel(c, x, y, col);
	}
}

/* pixel manipulation */

int get_pixel_position(int x, int y, int width) {
	return (int)(y * width + x);
}

void plot_pixel(Uint32* pixels, int x, int y, int r, int g, int b, int width, int height) {
	int position = get_pixel_position(x, y, width);

	if (position < (width * height)) /* bounds check */
		pixels[position] = (r << 16) | (g << 8) | b;
}

void canvas_to_pixels(canvas *c, Uint32* pixels) {
	// copy each pixel in canvas to SDL pixel area
	int i, j;
	colour col;
	
	for(i = 0; i < c->width; i++)
		for (j = 0; j < c->height; j++) {
			col = canvas_get_pixel(c, i, j);
				plot_pixel(pixels, i, j, col.r, col.g, col.b, c->width, c->height);
		}
}

int main(int argc, char ** argv)
{
	int quit = 0;
	SDL_Event event;
	Uint32 *pixels;

	/* Tracer init */
	int width = 900;
	int height = 550;
	canvas *c;

	/* SDL init */
	SDL_Init(SDL_INIT_VIDEO);
	SDL_Window *window = SDL_CreateWindow("TomTracer",SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, 0);
	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);
	SDL_Texture *texture = SDL_CreateTexture(renderer,SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, width, height);

	pixels = malloc(width * height * sizeof(Uint32));
	
	c = canvas_create(width, height);
	plot_projectile(c);
	canvas_to_pixels(c, pixels);
	   	
	// display
	SDL_UpdateTexture(texture, NULL, pixels, width * sizeof(Uint32));
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, texture, NULL, NULL);
	SDL_RenderPresent(renderer);

	// handle exit
	while (!quit)
	{
		SDL_PollEvent(&event);
		switch (event.type)
		{
		case SDL_QUIT:
			quit = 1;
			break;
		}
	}

	SDL_DestroyTexture(texture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	free(c);

	return 0;
}




