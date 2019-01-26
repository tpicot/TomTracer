#include <stdio.h>
#include <string.h>
#include <SDL.h>

#include "tuple.h"

/* https://dzone.com/articles/sdl2-pixel-drawing */

/*int main(int argc, char ** argv)
{
	int leftMouseButtonDown = 0;
	int quit = 0;
	SDL_Event event;

	SDL_Init(SDL_INIT_VIDEO);

	SDL_Window *window = SDL_CreateWindow("TomTracer",SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, 0);
	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);
	SDL_Texture *texture = SDL_CreateTexture(renderer,SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC, 640, 480);
	Uint32 * pixels = malloc(640 * 480 * sizeof(Uint32));

	memset(pixels, 255, 640 * 480 * sizeof(Uint32));

	tuple_create_point(1, 2, 3);

	while (!quit)
	{
		SDL_UpdateTexture(texture, NULL, pixels, 640 * sizeof(Uint32));
		SDL_PollEvent(&event);

		switch (event.type)
		{
		case SDL_QUIT:
			quit = 1;
			break;
		case SDL_MOUSEBUTTONUP:
			if (event.button.button == SDL_BUTTON_LEFT)
				leftMouseButtonDown = 0;
			break;
		case SDL_MOUSEBUTTONDOWN:
			if (event.button.button == SDL_BUTTON_LEFT)
				leftMouseButtonDown = 1;
		case SDL_MOUSEMOTION:
			if (leftMouseButtonDown)
			{
				int mouseX = event.motion.x;
				int mouseY = event.motion.y;
				pixels[mouseY * 640 + mouseX] = 0;
			}
			break;
		}

		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, texture, NULL, NULL);
		SDL_RenderPresent(renderer);
	}

	free(pixels);

	SDL_DestroyTexture(texture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}*/

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

int main(int argc, char ** argv) {
	projectile p;
	environment e;

	p.position = tuple_create_point(0, 1, 0);
	p.velocity = tuple_create_vector(1, 1, 0);
	e.gravity = tuple_create_vector(0, (float)-0.1, 0);
	e.wind = tuple_create_vector((float)-0.01, 0, 0);

	
	while (p.position.y > 0) {
		p = tick(e, p);
		printf("x: %f, y: %f, z: %f, w: %f \n", p.position.x, p.position.y, p.position.z, p.position.w);
	}

	return 0;
}
