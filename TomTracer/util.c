#include <math.h>

#include "util.h"

int equal(float a, float b) {
	return (fabsf(a - b) < (float)EPSILON);
}