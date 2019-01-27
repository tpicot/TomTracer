#include <math.h>

#include "colours.h"
#include "util.h"

void colour_set_value(colour *c, float r, float g, float b) {
	c->r = r;
	c->g = g;
	c->b = b;
}

colour colour_create(float r, float g, float b) {
	colour a;
	colour_set_value(&a, r, g, b);
	return a;
}

colour colour_add(colour a, colour b) {
	colour c = { a.r + b.r, a.g + b.g, a.b + b.b };
	return c;
}

colour colour_subtract(colour a, colour b) {
	colour c = { a.r - b.r, a.g - b.g, a.b - b.b };
	return c;
}

colour colour_multiply(colour a, colour b) {
	colour c = { a.r * b.r, a.g * b.g, a.b * b.b };
	return c;
}

colour colour_scale(colour a, float scalar) {
	colour b = { scalar, scalar, scalar };
	return colour_multiply(a, b);
}
