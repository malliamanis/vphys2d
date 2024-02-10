#ifndef VPHYS2D_H
#define VPHYS2D_H

#include <raylib.h>

#include <stdint.h>

#include "util/list.h"
#include "objects/player.h"
#include "graphics/window.h"
#include "entities/entity.h"
#include "objects/homefield.h"

#define WIDTH 1600
#define HEIGHT ((int)(WIDTH / 16 * 9))
#define TITLE "VPhys2D"

#define DELTA_TIME ((double)(1 / 1000.0))

typedef struct {
	Window *window;

	List *objects;
	Player *player;
	HomEField *field;
} Vphys2d;

void vphys2d_run(void);

#endif
