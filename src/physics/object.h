#ifndef OBJECT_H
#define OBJECT_H

#include <raylib.h>

#include "util/list.h"
#include "entities/entity.h"

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
