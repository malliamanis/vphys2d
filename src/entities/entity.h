#ifndef ENTITY_H
#define ENTITY_H

#include <raylib.h>

#include <stdint.h>
#include <stddef.h>

typedef struct {
	Rectangle rect;
	Color color;
} Entity;

Entity *entity_create(float x, float y, float width, float height);

void entity_render(Entity *entity);

void entity_destroy(Entity *entity);

#endif // ENTITY_H
