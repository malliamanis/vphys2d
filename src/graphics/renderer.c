#include <raylib.h>

#include "graphics/renderer.h"

void renderer_clear(Color color)
{
	ClearBackground(color);
}

void renderer_render_entity(Entity *e)
{
	if (e->type == ENTITY_CIRCLE)
		DrawCircleV(e->c.center, e->c.radius, e->color);
	else if (e->type == ENTITY_RECTANGLE)
		DrawRectangleRec(e->r, e->color);
}
