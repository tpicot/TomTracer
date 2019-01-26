#include <math.h>

#include "tuple.h"
#include "util.h"

void tuple_set_value(tuple *t, float x, float y, float z) {
	t->x = x;
	t->y = y;
	t->z = z;
}

void tuple_set_type(tuple *t, float type) {
	t->w = type;
}

int tuple_is_point(tuple *t) {
	return(equal(t->w,POINT));
}

int tuple_is_vector(tuple *t) {
	return(equal(t->w,VECTOR));
}

int tuple_compare(tuple *a, tuple *b) {
	if (equal(a->x, b->x) == 0)
		return 0;	
	if (equal(a->y, b->y) == 0)
		return 0;
	if (equal(a->z, b->z) == 0)
		return 0;
	if (equal(a->w, b->w) == 0)
		return 0;

	return 1;
}

tuple tuple_create_point(float x, float y, float z) {
	tuple a;
	tuple_set_value(&a, x, y, z);
	tuple_set_type(&a, POINT);
	return a;
}

tuple tuple_create_vector(float x, float y, float z) {
	tuple a;
	tuple_set_value(&a, x, y, z);
	tuple_set_type(&a, VECTOR);
	return a;
}

tuple tuple_add(tuple a, tuple b) {
	tuple c = { a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w };
	return c;
}

tuple tuple_subtract(tuple a, tuple b) {
	tuple c = { a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w };
	return c;
}

tuple tuple_scale(tuple a, float scalar) {
	a.x = a.x * scalar;
	a.y = a.y * scalar;
	a.z = a.z * scalar;
	a.w = a.w * scalar;
	return a;
}

tuple tuple_negate(tuple a) {
	return tuple_scale(a, -1);
};

tuple tuple_divide(tuple a, float divisor) {
	return tuple_scale(a, 1/divisor);
};

float tuple_magnitude(tuple *a) {
	return (float)sqrt((a->x * a->x + a->y * a->y + a->z * a->z + a->w * a->w));
}

float tuple_dot_product(tuple *a, tuple *b) {
	return a->x * b->x + a->y * b->y + a->z * b->z + a->w * b->w;
}

tuple tuple_normalize(tuple a) {
	tuple b;

	float magnitude = tuple_magnitude(&a);

	b.x = a.x / magnitude;
	b.y = a.y / magnitude;
	b.z = a.z / magnitude;
	b.w = a.w / magnitude;

	return b;
}

tuple tuple_cross_product(tuple a, tuple b) {
	return tuple_create_vector(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x);
}