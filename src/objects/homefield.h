#ifndef HOMFIELD_H
#define HOMFIELD_H

#include "objects/object.h"

typedef struct {
	Object *p_plate;
	Object *n_plate;

	Vector2 pos;
	float distance;
	float width;
	float orientation;

	float voltage;

	List *objects;
} HomEField; // Homogenous elecric field

// orientation in radians with 0 radians being horizontal and positive plate up
HomEField *homefield_create(Vector2 position, float distance, float width, float orientation, float voltage, List *objects);

void homefield_tick(HomEField *homefield);

void homefield_destroy(HomEField *homefield);

#endif
