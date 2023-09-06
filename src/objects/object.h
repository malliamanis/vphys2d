#ifndef OBJECT_H
#define OBJECT_H

#include <raylib.h>

#include "util/list.h"
#include "entities/entity.h"

#define METER ((float)(100.0f)) // 100px = 1m

#define G ((float)(9.81f) * METER)

typedef struct {
	Entity *entity;

	Vector2 acc, vel, pos;

	float mass;
	// float rotation;

	List *objects;
} Object;

Object *object_create(Entity *entity, Vector2 acceleration, Vector2 velocity, float mass, List *objects);

void object_tick(Object *object);
void object_render(Object *object);

void object_destroy(Object *object);

#endif
