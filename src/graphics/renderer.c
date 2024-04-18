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
		DrawRectanglePro(e->r, (Vector2){e->r.width / 2.0f, e->r.height / 2.0f}, RAD2DEG * e->rotation, e->color);
}
