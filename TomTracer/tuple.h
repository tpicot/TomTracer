#ifndef TUPLE_H
#define TUPLE_H

#define VECTOR 0
#define POINT 1

typedef struct tuple {
	float x;
	float y;
	float z;
	float w;
} tuple;

void tuple_set_value(tuple *t, float x, float y, float z);
void tuple_set_type(tuple *t, float type);

tuple tuple_create_vector(float x, float y, float z);
tuple tuple_create_point(float x, float y, float z);

int tuple_is_point(tuple *t);
int tuple_is_vector(tuple *t);
int tuple_compare(tuple *a, tuple *b);
float tuple_magnitude(tuple *a);
float tuple_dot_product(tuple *a, tuple *b);

tuple tuple_add(tuple a, tuple b);
tuple tuple_subtract(tuple a, tuple b);
tuple tuple_negate(tuple a);
tuple tuple_scale(tuple a, float scalar);
tuple tuple_divide(tuple a, float divisor);
tuple tuple_normalize(tuple a);
tuple tuple_cross_product(tuple a, tuple b);

#endif