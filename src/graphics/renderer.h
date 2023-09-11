#ifndef RENDERER_H
#define RENDERER_H

#include <raylib.h>

#include "entities/entity.h"

void renderer_clear(Color color);
void renderer_render_entity(Entity *entity);

#endif // RENDERER_H
