#include <raylib.h>

#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#include "vphys2d.h"
#include "objects/object.h"
#include "objects/player.h"

#undef M_PI
#define M_PI ((double)3.14159265)

static void init(void);

static void update(void);
static void tick(void);
static void render(void);

static void terminate(void);

static Vphys2d *v;

static void init(void)
{
	v = malloc(sizeof(Vphys2d));

	v->window = window_init(WIDTH, HEIGHT, TITLE);
	v->objects = list_create((destructor)object_destroy, sizeof(Object));

	v->player = player_create(object_create_rect((Vector2){200, HEIGHT - 300}, (Vector2){100, 100}, (Vector2){0}, (Vector2){0}, 0.0f, 10.0f, false, true, v->objects));
	// v->player = player_create(object_create_circle((Vector2){200, HEIGHT / 2.0f}, METER / 2.0f, (Vector2){0}, (Vector2){0}, 10.0f, false, true, v->objects));
	// v->player->obj->charge = 10.0f;
	// list_add(v->objects, v->player->obj);

	// Object *obj = object_create_rect((Vector2){WIDTH / 2.0f, HEIGHT / 2.0f}, (Vector2){5 * METER, 5 * METER}, (Vector2){0}, (Vector2){0}, 0.0f, 5.0f, false, true, v->objects);
	// list_add(v->objects, obj);

	v->field = homefield_create((Vector2){WIDTH / 2.0f, HEIGHT / 2.0f}, 10 * METER, 13 * METER, 0.0f, 200.0f, v->objects);

	for (int i = 0; i < 50; ++i) {
		Object *o = object_create_circle((Vector2){GetRandomValue(100, (WIDTH * 10) - 100) / 10.0f, GetRandomValue(100, (HEIGHT * 10) - 100) / 10.0f}, 10.0f, (Vector2){0}, (Vector2){10.0f * GetRandomValue(-1 * METER, 1 * METER), 0.0f}, 0.01f, false, true, v->objects);
		o->charge = GetRandomValue(-100, 100) / 100.0f;
		list_add(v->objects, o);
	}
	
	SetRandomSeed(time(NULL));
}

void vphys2d_run(void)
{
	init();

	double currentTime = GetTime();
	double newTime;
	double accumulator = 0.0;

	while (!window_should_close()) {
		update();

		newTime = GetTime();

		accumulator += newTime - currentTime;
		currentTime = newTime;

		while (accumulator >= DELTA_TIME)
		{
			tick();
			accumulator -= DELTA_TIME;
		}

		render();
	}

	terminate();
}

static void update(void)
{
	window_update(v->window);

	player_update(v->player);
}

static void tick(void)
{
	player_tick(v->player);
	// homefield_tick(v->field);

	for (Node *temp = v->objects->head; temp != NULL; temp = temp->next)
		object_tick(temp->data);

}

static void render(void)
{
	BeginDrawing();
	ClearBackground(v->window->background);

	for (Node *temp = v->objects->head; temp != NULL; temp = temp->next)
		object_render(temp->data);

	DrawFPS(0, 0);

	EndDrawing();
}

static void terminate(void)
{
	window_destroy(v->window);

	player_destroy(v->player); // doesn't free the object
	// homefield_destroy(v->field);
	list_destroy(v->objects);

	free(v);
}
