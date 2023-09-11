#ifndef ENTITY_H
#define ENTITY_H

#include <raylib.h>

#include <stdint.h>
#include <stddef.h>

typedef enum {
	ENTITY_CIRCLE,
	ENTITY_RECTANGLE
} EntityType;

typedef struct {
	Vector2 center;
	float radius;
} Circle;

typedef struct {
	uint32_t id;
	EntityType type;

	union {
		Circle c;
		Rectangle r;
	};

	Color color;
} Entity;

Entity *entity_create_circle(float x, float y, float radius);
Entity *entity_create_rect(float x, float y, float width, float height);

void entity_render(Entity *entity);

void entity_destroy(Entity *entity);

#endif // ENTITY_H
