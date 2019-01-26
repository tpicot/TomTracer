#include "pch.h"

extern "C" {

#include "../TomTracer/tuple.h"
#include "../TomTracer/util.h"

}

/* tuple.h */

TEST(Tuple, create_point) {
	tuple t = tuple_create_point((float)4.3, (float)-4.2, (float)3.1);
	EXPECT_FLOAT_EQ(t.y,-4.2);
	EXPECT_FLOAT_EQ(t.z,3.1);
	EXPECT_FLOAT_EQ(t.w,1);
	EXPECT_EQ(tuple_is_point(&t),1);
	EXPECT_EQ(tuple_is_vector(&t), 0);
}

TEST(Tuple, create_vector) {
	tuple t = tuple_create_vector((float)4.3, (float)-4.2, (float)3.1);
	EXPECT_FLOAT_EQ(t.y, -4.2);
	EXPECT_FLOAT_EQ(t.z, 3.1);
	EXPECT_FLOAT_EQ(t.w, 0);
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

/* util.h */

TEST(Util, equal) {
	EXPECT_EQ(equal((float)1.0, (float)3.0), 0);
	EXPECT_EQ(equal((float)1.0, (float)1.0001), 0);
	EXPECT_EQ(equal((float)1.0, (float)1.000001), 1);
}