#ifndef PLAYER_H
#define PLAYER_H

#include <stdbool.h>

#include "objects/object.h"

typedef struct {
	Object *obj;
} Player;

Player *player_create(Object *object);

void player_update(Player *player);
void player_tick(Player *player);

void player_destroy(Player *player);

#endif // PLAYER_H
