#ifndef OBJECT_H
#define OBJECT_H

#include <stdbool.h>

#include <raylib.h>

#include "util/list.h"
#include "entities/entity.h"

#define METER ((float)(100.0f)) // 100px = 1m

#define G ((float)(9.81f) * METER)

typedef struct {
	Entity *entity;

	Vector2 acc, vel, pos;

	float mass; // in Kg
	// float rotation;
	float charge; // in Coulombs

	List *objects;
} Object;

Object *object_create_rect(Vector2 position, Vector2 size, Vector2 acceleration, Vector2 velocity, float mass, bool gravity, List *objects);
Object *object_create_circle(Vector2 position, float radius, Vector2 acceleration, Vector2 velocity, float mass, bool gravity, List *objects);

void object_tick(Object *object);
void object_render(Object *object);

void object_destroy(Object *object);

#endif
