#include "tuple.h"

void tuple_set_value(tuple *t, float x, float y, float z) {
	t->x = x;
	t->y = y;
	t->z = z;
}

void tuple_set_type(tuple *t, int type) {
	t->w = type;
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

int tuple_is_point(tuple *t) {
	return(t->w == POINT);
}

int tuple_is_vector(tuple *t) {
	return(t->w == VECTOR);
}

tuple tuple_add(tuple a, tuple b) {
	tuple c = { a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w };
	return c;
}

tuple tuple_subtract(tuple a, tuple b) {
	tuple c = { a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w };
	return c;
}

