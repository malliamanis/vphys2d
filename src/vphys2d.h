#ifndef VPHYS2D_H
#define VPHYS2D_H

#include <raylib.h>

#include <stdint.h>

#include "util/list.h"
#include "objects/player.h"
#include "graphics/window.h"
#include "entities/entity.h"

#define WIDTH 1280
#define HEIGHT 720
#define TITLE "VPhys2D"

#define DELTA_TIME ((double)(1 / 100.0))

typedef struct {
	Window *window;

	List *objects;
	Player *player;
} Vphys2d;

void vphys2d_run(void);

#endif
