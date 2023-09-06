#include <stdlib.h>

#include "entities/entity.h"
#include "graphics/renderer.h"

Entity *entity_create(float x, float y, float width, float height)
{
	Entity *e = calloc(1, sizeof(Entity));

	e->rect.x = x;
	e->rect.y = y;
	e->rect.width = width;
	e->rect.height = height;
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
