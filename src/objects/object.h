#ifndef OBJECT_H
#define OBJECT_H

#include <stdbool.h>

#include <raylib.h>

#include "util/list.h"
#include "entities/entity.h"

#define METER ((float)(50.0f)) // 100px = 1m

#define G ((float)(9.81f) * METER)

typedef struct {
	Entity *entity;

	Vector2 acc, vel, pos;

	float mass; // in Kg
	float charge; // in Coulombs

	bool bounded; // determines whether or not it reacts with the screen walls

	List *objects;

} Object;

Object *object_create_rect(Vector2 position, Vector2 size, Vector2 acceleration, Vector2 velocity, float rotation, float mass, bool gravity, bool bounded, List *objects);
Object *object_create_circle(Vector2 position, float radius, Vector2 acceleration, Vector2 velocity, float mass, bool gravity, bool bounded, List *objects);

void object_tick(Object *object);
void object_render(Object *object);

void object_destroy(Object *object);

#endif
