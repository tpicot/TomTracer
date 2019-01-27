#ifndef COLOUR_H
#define COLOUR_H

#define VECTOR 0
#define POINT 1

typedef struct colour {
	float r;
	float g;
	float b;
} colour;

void colour_set_value(colour *t, float r, float g, float b);
colour colour_create(float r, float g, float b);

colour colour_add(colour a, colour b);
colour colour_subtract(colour a, colour b);
colour colour_multiply(colour a, colour b);
colour colour_scale(colour a, float scalar);

#endif