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

	// v->player = player_create(object_create_rect((Vector2){200, HEIGHT - 200}, (Vector2){100, 100}, (Vector2){0}, (Vector2){0}, 0.0f, 10.0f, true, true, v->objects));
	v->player = player_create(object_create_circle((Vector2){200, HEIGHT / 2.0f}, METER / 2.0f, (Vector2){0}, (Vector2){0}, 10.0f, false, true, v->objects));
	list_add(v->objects, v->player->obj);

	v->field = homefield_create((Vector2){WIDTH / 2.0f, HEIGHT / 2.0f}, 10 * METER, 13 * METER, 90.0f, 200.0f, v->objects);

	for (int i = 0; i < 200; ++i) {
		Object *o = object_create_circle((Vector2){GetRandomValue(100, (WIDTH * 10) - 100) / 10.0f, GetRandomValue(100, (HEIGHT * 10) - 100) / 10.0f}, 10.0f, (Vector2){0}, (Vector2){10.0f * GetRandomValue(-1 * METER, 1 * METER), 0.0f}, 0.01f, false, true, v->objects);
		o->charge = GetRandomValue(-100, 100) / 1000.0f;
		list_add(v->objects, o);
	}

	Object *particle = object_create_circle((Vector2){METER / 5.0f, HEIGHT / 2.0f - 2.5 *METER}, METER / 5.0f, (Vector2){0}, (Vector2){METER * 10, 0.0f}, 0.01f, false, true, v->objects);
	particle->charge = 0.02f;
	list_add(v->objects, particle);

	return v;
}

void vphys2d_run(void)
{
	SetRandomSeed(time(NULL));

	Vphys2d *v = init();

	double currentTime = GetTime();
	double newTime;
	double accumulator = 0.0;

	while (!window_should_close()) {
		update(v);

		newTime = GetTime();

		accumulator += newTime - currentTime;
		currentTime = newTime;

		while (accumulator >= DELTA_TIME)
		{
			tick(v);
			accumulator -= DELTA_TIME;
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
	homefield_tick(v->field);

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
	homefield_destroy(v->field);
	list_destroy(v->objects);

	free(v);
}
