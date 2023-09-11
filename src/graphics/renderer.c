#include <raylib.h>

#include "graphics/renderer.h"

void renderer_clear(Color color)
{
	ClearBackground(color);
}

void renderer_render_entity(Entity *entity)
{
	if (entity->type == ENTITY_CIRCLE)
		DrawCircleV(entity->c.center, entity->c.radius, entity->color);
	else
		DrawRectangleRec(entity->r, entity->color);
}
