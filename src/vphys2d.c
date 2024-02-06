#include <raylib.h>

#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#include "vphys2d.h"
#include "objects/object.h"
#include "objects/player.h"
#include "graphics/renderer.h"

static Vphys2d *init(void);

static void update(Vphys2d *v);
static void tick(Vphys2d *v);
static void render(Vphys2d *v);

static void terminate(Vphys2d *v);

static Vphys2d *init(void)
{
	Vphys2d *v = malloc(sizeof(Vphys2d));

	v->window = window_init(WIDTH, HEIGHT, TITLE);

	v->objects = list_create((destructor)object_destroy, sizeof(Object));

	// v->player = player_create(object_create_rect((Vector2){200, HEIGHT - 200}, (Vector2){100, 100}, (Vector2){0}, (Vector2){0}, 10.0f, true, v->objects));
	v->player = player_create(object_create_circle((Vector2){200, HEIGHT - 200}, 50.0f, (Vector2){0}, (Vector2){0}, 10.0f, false, v->objects));

	// list_add(v->objects, v->player->obj);

	// for (int i = 0; i < 100; ++i) {
	// 	list_add(v->objects, object_create((Vector2){GetRandomValue(100, (WIDTH * 10) - 100) / 10.0f, GetRandomValue(100, (HEIGHT * 10) - 100) / 10.0f}, 10.0f, (Vector2){0}, (Vector2){100.0f * GetRandomValue(-1, 1), 0.0f}, 0.2f, v->objects));
	// }

	return v;
}

void vphys2d_run(void)
{
	SetRandomSeed(time(NULL));

	Vphys2d *v = init();

	const double delta_time = DELTA_TIME;

	double currentTime = GetTime();
	double newTime;
	double accumulator = 0.0;

	while (!window_should_close()) {
		update(v);

		newTime = GetTime();

		accumulator += newTime - currentTime;
		currentTime = newTime;

		while (accumulator >= delta_time)
		{
			tick(v);
			accumulator -= delta_time;
		}

		render(v);
	}

	terminate(v);
}

static void update(Vphys2d *v)
{
	window_update(v->window);

	player_update(v->player);
}

static void tick(Vphys2d *v)
{
	player_tick(v->player);

	for (Node *temp = v->objects->head; temp != NULL; temp = temp->next)
		object_tick(temp->data);
}

static void render(Vphys2d *v)
{
	BeginDrawing();
	ClearBackground(v->window->background);
	
	for (Node *temp = v->objects->head; temp != NULL; temp = temp->next)
		object_render(temp->data);

	EndDrawing();
}

static void terminate(Vphys2d *v)
{
	window_destroy(v->window);

	player_destroy(v->player); // doesn't free the object
	list_destroy(v->objects);

	free(v);
}
