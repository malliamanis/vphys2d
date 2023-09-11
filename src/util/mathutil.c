#include <math.h>

#include "util/mathutil.h"

// non-ptr

float math_vec2_dot(Vector2 v1, Vector2 v2)
{
	return v1.x * v2.x + v1.y * v2.y;
}

float math_vec2_length(Vector2 v)
{
	return sqrtf(v.x * v.x + v.y * v.y);
}

Vector2 math_vec2_scale(Vector2 v, float a)
{
	return (Vector2){v.x * a, v.y * a};
}

Vector2 math_vec2_norm(Vector2 v)
{
	float temp = sqrtf(v.x * v.x + v.y * v.y);

	if (temp == 0)
		return v;
	else
		temp = 1.0f / temp;

	return (Vector2){v.x * temp, v.y * temp};
}

Vector2 math_vec2_add(Vector2 v1, Vector2 v2)
{
	return (Vector2){v1.x + v2.x, v1.y + v2.y};
}


Vector2 math_vec2_sub(Vector2 v1, Vector2 v2)
{
	return (Vector2){v1.x - v2.x, v1.y - v2.y};
}

// ptr

void math_ptr_vec2_scale(Vector2 *v, float a)
{
	v->x *= a;
	v->y *= a;
}

void math_ptr_vec2_norm(Vector2 *v)
{
	float ilength = 1 / sqrt(v->x * v->x + v->y * v->y);
	v->x *= ilength;
	v->y *= ilength;
}
