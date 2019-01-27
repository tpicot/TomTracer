#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL.h>

#include "tuple.h"
#include "canvas.h"

#define WIDTH 900
#define HEIGHT 550

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

/* pixel manipulation */

int pixel_position(int x, int y) {
	return (int)(y * WIDTH + x);
}

int plot(Uint32* pixels, int x, int y, int r, int g, int b) {
	int position = pixel_position(x, y);

	if (position < (WIDTH * HEIGHT))
		pixels[position] = (255 << 16) | (0 << 8) | 0;
}

void plot_canvas(canvas c, Uint32* pixels) {


}

int main(int argc, char ** argv)
{
	int leftMouseButtonDown = 0;
	int quit = 0;
	SDL_Event event;
	Uint32 *pixels;
	canvas *c;

	/* SDL init */
	SDL_Init(SDL_INIT_VIDEO);
	SDL_Window *window = SDL_CreateWindow("TomTracer",SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, 0);
	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);
	SDL_Texture *texture = SDL_CreateTexture(renderer,SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, WIDTH, HEIGHT);

	/* Tracer init */
	// c = canvas_create(WIDTH, HEIGHT);

	pixels = malloc(WIDTH * HEIGHT * sizeof(Uint32));
	memset(pixels, 255, WIDTH * HEIGHT * sizeof(Uint32));
	
	projectile p;
	environment e;
	int pixel_location;
	int x, y;

	p.position = tuple_create_point(0, 1, 0);
	p.velocity = tuple_scale(tuple_normalize(tuple_create_vector(1, 1.8, 0)), (float)11.25);
	e.gravity = tuple_create_vector(0, (float)-0.2, 0);
	e.wind = tuple_create_vector((float)-0.01, 0, 0);

	while (p.position.y > 0) {
		p = tick(e, p);

		int y = (int)(HEIGHT - p.position.y);
		int x = (int)p.position.x;

		printf("x: %f, y: %f, z: %f, w: %f \n", p.position.x, p.position.y, p.position.z, p.position.w);
		plot(pixels, x, y, 0, 0, 0);
	}

	// display
	SDL_UpdateTexture(texture, NULL, pixels, WIDTH * sizeof(Uint32));
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

	return 0;
}




