#include <stdlib.h>

#include "vphys2d.h"
#include "objects/player.h"

#define JUMP ((float)(5.0f) * METER)

#define ACC ((float)(7.0f) * METER)
#define SPEED_MAX ((float)(2.5f) * METER)

Player *player_create(Object *object)
{
	Player *p = malloc(sizeof(Player));

	p->obj = object;

	return p;
}

void player_update(Player *p)
{
}

void player_tick(Player *p)
{
	bool key_a = IsKeyDown(KEY_A);
	bool key_d = IsKeyDown(KEY_D);

	if (key_a && p->obj->vel.x > -SPEED_MAX)
		p->obj->acc.x = -ACC;
	if (key_d && p->obj->vel.x < SPEED_MAX)
		p->obj->acc.x = ACC;

	if (!key_a && !key_d)
		p->obj->acc.x = 0.0f;
}

void player_destroy(Player *p)
{
	free(p);
}
