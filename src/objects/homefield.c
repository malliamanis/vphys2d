#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>

#include "objects/object.h"
#include "util/mathutil.h"
#include "objects/homefield.h"

#define THICKNESS ((float)METER / 2.0f)

HomEField *homefield_create(Vector2 position, float distance, float width, float orientation, float voltage, List *objects)
{
	HomEField *h = malloc(sizeof(HomEField));

	h->p_plate = object_create_rect((Vector2){position.x - width / 2.0f, position.y - (distance / 2.0f - THICKNESS)}, (Vector2){width, THICKNESS}, (Vector2){0}, (Vector2){0}, orientation, 0.0f, false, false, objects);
	h->n_plate = object_create_rect((Vector2){position.x - width / 2.0f, position.y + distance / 2.0f}, (Vector2){width, THICKNESS}, (Vector2){0}, (Vector2){0}, orientation, 0.0f, false, false, objects);
	
	list_add(objects, h->p_plate);
	list_add(objects, h->n_plate);

	h->pos = position;

	h->distance = distance;
	h->width = width;
	h->orientation = orientation;
	h->voltage = voltage;

	h->objects = objects;

	return h;
}

void homefield_tick(HomEField *h)
{
	for (Node *temp = h->objects->head; temp != NULL; temp = temp->next) {
		Object *o = temp->data;
		if (o->charge == 0.0f)
			continue;

		if (o->entity->type == ENTITY_RECTANGLE) {
			if (CheckCollisionRecs(h->p_plate->entity->r, o->entity->r) || CheckCollisionRecs(h->n_plate->entity->r, o->entity->r)) 
				o->vel.y = 0;
		}
		else if (o->entity->type == ENTITY_CIRCLE) {
			// Do something
		}

		if (o->pos.x >= h->p_plate->pos.x && o->pos.x <= h->p_plate->pos.x + h->p_plate->entity->r.width) {
			if (o->pos.y >= h->p_plate->pos.y + h->p_plate->entity->r.height && o->pos.y <= h->n_plate->pos.y) {
				Vector2 acc = {0, (h->voltage * o->charge) / h->distance / o->mass};
				o->vel = math_vec2_add(o->vel, acc);
			}
		}
	}
}

void homefield_destroy(HomEField *homefield)
{
	free(homefield);
}
