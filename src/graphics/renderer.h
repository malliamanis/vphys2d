#ifndef RENDERER_H
#define RENDERER_H

#include <raylib.h>

#include "entities/entity.h"

void renderer_clear(Color color);
void renderer_render_entity(Entity *entity);
void renderer_render_textured_entity(Entity *entity, Texture2D *texture);

#endif // RENDERER_H
