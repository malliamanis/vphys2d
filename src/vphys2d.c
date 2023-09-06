#include <raylib.h>

#include <stdio.h>
#include <stdlib.h>

#include "entities/entity.h"
#include "vphys2d.h"
#include "physics/object.h"
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

	list_add(v->objects, object_create(entity_create(0, 100, 25, 25), (Vector2){0}, (Vector2){100.0f * 1.5f, 0.0f}, 5.0f, v->objects));
	list_add(v->objects, object_create(entity_create(500, 600, 25, 25), (Vector2){0}, (Vector2){-50.0f * 1.5f, -150.0f * 1.5f}, 10.0f, v->objects));

	return v;
}

void vphys2d_run(void)
{
	Vphys2d *v = init();

    const double delta_time = DELTA_TIME;

    double currentTime = GetTime();
	double newTime;
    double accumulator = 0.0;

    while (!window_should_close())
    {
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
}

static void tick(Vphys2d *v)
{
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
	list_destroy(v->objects);
	free(v);
}
