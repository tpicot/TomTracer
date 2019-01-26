#ifndef TUPLE_H
#define TUPLE_H

#define VECTOR 0
#define POINT 1

typedef struct tuple {
	float x;
	float y;
	float z;
	int w;
} tuple;

void tuple_set_value(tuple *t, float x, float y, float z);
void tuple_set_type(tuple *t, int type);

tuple tuple_create_vector(float x, float y, float z);
tuple tuple_create_point(float x, float y, float z);

int tuple_is_point(tuple *t);
int tuple_is_vector(tuple *t);

tuple tuple_add(tuple a, tuple b);
tuple tuple_subtract(tuple a, tuple b);


#endif