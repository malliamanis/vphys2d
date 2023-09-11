#include <stdlib.h>

#include "entities/entity.h"
#include "graphics/renderer.h"

uint32_t id_count = 0;

Entity *entity_create_circle(float x, float y, float radius)
{
	Entity *e = malloc(sizeof(Entity));

	e->id = id_count++;
	e->type = ENTITY_CIRCLE;

	e->c.center = (Vector2){x, y};
	e->c.radius = radius;

	e->color = WHITE;

	return e;
}

Entity *entity_create_rect(float x, float y, float width, float height)
{
	Entity *e = malloc(sizeof(Entity));

	e->id = id_count++;
	e->type = ENTITY_RECTANGLE;

	e->r.x = x;
	e->r.y = y;
	e->r.width = width;
	e->r.height = height;

	e->color = WHITE;

	return e;
}

void entity_render(Entity *e)
{
	renderer_render_entity(e);
}

void entity_destroy(Entity *e)
{
	free(e);
}
