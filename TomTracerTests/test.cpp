#include <math.h>

#include "pch.h"

extern "C" {

#include "../TomTracer/tuple.h"
#include "../TomTracer/colours.h"
#include "../TomTracer/canvas.h"
#include "../TomTracer/util.h"
}

/* tuple.h */

// ASSERT_FLOAT_EQ(expected, actual);

TEST(Tuple, create_point) {
	tuple t = tuple_create_point((float)4.3, (float)-4.2, (float)3.1);
	EXPECT_FLOAT_EQ(t.y,(float)-4.2);
	EXPECT_FLOAT_EQ(t.z,(float)3.1);
	EXPECT_FLOAT_EQ(t.w,(float)1);
	EXPECT_EQ(tuple_is_point(&t),1);
	EXPECT_EQ(tuple_is_vector(&t), 0);
}

TEST(Tuple, create_vector) {
	tuple t = tuple_create_vector((float)4.3, (float)-4.2, (float)3.1);
	EXPECT_FLOAT_EQ(t.y, (float)-4.2);
	EXPECT_FLOAT_EQ(t.z, (float)3.1);
	EXPECT_FLOAT_EQ(t.w, (float)0);
	EXPECT_EQ(tuple_is_point(&t), 0);
	EXPECT_EQ(tuple_is_vector(&t), 1);
}

TEST(Tuple, add_point_vector) {
	tuple a = tuple_create_point(3, -2, 5);
	tuple b = tuple_create_vector(-2, 3, 1);
	tuple c = tuple_add(a, b);
	EXPECT_EQ(equal(c.x, 1), 1);
	EXPECT_EQ(equal(c.y, 1), 1);
	EXPECT_EQ(equal(c.z, 6), 1);
	EXPECT_EQ(equal(c.w, 1), 1);
}

TEST(Tuple, subtract_point_point) {
	tuple a = tuple_create_point(3, 2, 1);
	tuple b = tuple_create_point(5, 6, 7);
	tuple c = tuple_subtract(a, b);
	EXPECT_EQ(equal(c.x, -2), 1);
	EXPECT_EQ(equal(c.y,-4), 1);
	EXPECT_EQ(equal(c.z, -6), 1);
	EXPECT_EQ(tuple_is_vector(&c), 1);
}

TEST(Tuple, subtract_vector_point) {
	tuple a = tuple_create_point(3, 2, 1);
	tuple b = tuple_create_vector(5, 6, 7);
	tuple c = tuple_subtract(a, b);
	EXPECT_EQ(equal(c.x, -2), 1);
	EXPECT_EQ(equal(c.y, -4), 1);
	EXPECT_EQ(equal(c.z, -6), 1);
	EXPECT_EQ(tuple_is_point(&c), 1);
}

TEST(Tuple, subtract_vector_vector) {
	tuple a = tuple_create_vector(3, 2, 1);
	tuple b = tuple_create_vector(5, 6, 7);
	tuple c = tuple_subtract(a, b);
	EXPECT_EQ(equal(c.x, -2), 1);
	EXPECT_EQ(equal(c.y, -4), 1);
	EXPECT_EQ(equal(c.z, -6), 1);
	EXPECT_EQ(tuple_is_vector(&c), 1);
}

TEST(Tuple, negate) {
	tuple a = { 1,-2, 3,-4 };
	tuple b = { -1, 2, -3, 4 };
	a = tuple_negate(a);
	EXPECT_EQ(tuple_compare(&a, &b), 1);

	a = { 1, -2, 3,-4 };
	b = { 1, 2, -3, 4 };
	a = tuple_negate(a);
	EXPECT_EQ(tuple_compare(&a, &b), 0);
}

TEST(Tuple, divide) {
	tuple a = { 1, -2, 3, -4 };
	tuple b = { 0.5, -1, 1.5, -2 };
	a = tuple_divide(a,2);
	EXPECT_EQ(tuple_compare(&a, &b), 1);
}

TEST(Tuple, magnitude) {
	tuple a = tuple_create_vector(1, 0, 0);
	EXPECT_FLOAT_EQ(tuple_magnitude(&a), 1);

	a = tuple_create_vector(0, 1, 0);
	EXPECT_FLOAT_EQ(tuple_magnitude(&a), 1);

	a = tuple_create_vector(0, 0, 1);
	EXPECT_FLOAT_EQ(tuple_magnitude(&a), 1);

	a = tuple_create_vector(1, 2, 3);
	EXPECT_FLOAT_EQ(tuple_magnitude(&a), (float)sqrt(14));

	a = tuple_create_vector(-1, -2, -3);
	EXPECT_FLOAT_EQ(tuple_magnitude(&a), (float)sqrt(14));
}

TEST(Tuple, normalize) {
	tuple a = tuple_create_vector(4, 0, 0);
	tuple b = tuple_create_vector(1, 0, 0);
	a = tuple_normalize(a);
	EXPECT_EQ(tuple_compare(&a, &b), 1);

	a = tuple_create_vector(1, 2, 3);
	b = tuple_create_vector((float)(1/sqrt(14)), (float)(2/sqrt(14)), (float)(3/sqrt(14)));
	a = tuple_normalize(a);
	EXPECT_EQ(tuple_compare(&a, &b), 1);

	a = tuple_create_vector(1, 2, 3);
	b = tuple_create_vector((float)(1 / sqrt(12)), (float)(2 / sqrt(12)), (float)(3 / sqrt(12)));
	a = tuple_normalize(a);
	EXPECT_EQ(tuple_compare(&a, &b), 0);
}

TEST(Tuple, dot_product) {
	tuple a = tuple_create_vector(1, 2, 3);
	tuple b = tuple_create_vector(2, 3, 4);

	EXPECT_EQ(tuple_dot_product(&a, &b), 20);
}

TEST(Tuple, vector_cross_product) {
	tuple a = tuple_create_vector(1, 2, 3);
	tuple b = tuple_create_vector(2, 3, 4);
	
	tuple c = tuple_cross_product(a, b);
	tuple d = { -1, 2, -1 };

	EXPECT_EQ(tuple_compare(&c, &d), 1);

	c = tuple_cross_product(b, a);
	d = { 1, -2, 1 };

	EXPECT_EQ(tuple_compare(&c, &d), 1);
}

/* colours.h */

TEST(Colour, colour_create) {
	colour c = colour_create((float)-.5, (float)0.4, (float)1.7);
	EXPECT_FLOAT_EQ(c.r, (float)-0.5);
	EXPECT_FLOAT_EQ(c.g, (float)0.4);
	EXPECT_FLOAT_EQ(c.b, (float)1.7);
}

TEST(Colour, colour_add) {
	colour a = colour_create((float)0.9, (float)0.6, (float)0.75);
	colour b = colour_create((float)0.7, (float)0.1, (float)0.25);
	colour c = colour_add(a, b);

	EXPECT_FLOAT_EQ(c.r, (float)1.6);
	EXPECT_FLOAT_EQ(c.g, (float)0.7);
	EXPECT_FLOAT_EQ(c.b, (float)1.0);
}

TEST(Colour, colour_subtract) {
	colour a = colour_create((float)0.9, (float)0.6, (float)0.75);
	colour b = colour_create((float)0.7, (float)0.1, (float)0.25);
	colour c = colour_subtract(a, b);

	EXPECT_FLOAT_EQ(c.r, (float)0.2);
	EXPECT_FLOAT_EQ(c.g, (float)0.5);
	EXPECT_FLOAT_EQ(c.b, (float)0.5);
}

TEST(Colour, colour_scale) {
	colour a = colour_create((float)0.2, (float)0.3, (float)0.4);
	a = colour_scale(a, 2);

	EXPECT_FLOAT_EQ(a.r, (float)0.4);
	EXPECT_FLOAT_EQ(a.g, (float)0.6);
	EXPECT_FLOAT_EQ(a.b, (float)0.8);
}

TEST(Canvas, canvas_create) {
	canvas *c = canvas_create(10, 20);
	colour a = colour_create(0, 0, 0);

	EXPECT_EQ(c->height, 20);
	EXPECT_EQ(c->width, 10);

	for (int i = 0; i < c->width; i++)
		for (int j = 0; j < c->height; j++) {
			EXPECT_EQ(c->pixels[i][j].r, a.r);
			EXPECT_EQ(c->pixels[i][j].g, a.g);
			EXPECT_EQ(c->pixels[i][j].b, a.b);
		}

	canvas_destroy(c);
	free(c);
}

TEST(Canvas, canvas_write_pixel) {
	canvas *c = canvas_create(10, 20);
	colour a = colour_create(1, 0, 0);

	canvas_set_pixel(c, 2, 3, a);

	colour b = canvas_get_pixel(c, 2, 3);

	EXPECT_EQ(a.r, b.r);
	EXPECT_EQ(a.g, b.g);
	EXPECT_EQ(a.b, b.b);

	canvas_destroy(c);
	free(c);
}



/* util.h */

TEST(Util, equal) {
	EXPECT_EQ(equal((float)1.0, (float)3.0), 0);
	EXPECT_EQ(equal((float)1.0, (float)1.0001), 0);
	EXPECT_EQ(equal((float)1.0, (float)1.000001), 1);
}