#include <stdlib.h>

#include "vphys2d.h"
#include "physics/object.h"

Object *object_create(Entity *entity, Vector2 acceleration, Vector2 velocity, float mass, List *objects)
{
	Object *o = malloc(sizeof(Object));

	o->entity = entity;

	o->acc = acceleration;
	o->vel = velocity;
	o->pos = (Vector2){entity->rect.x, entity->rect.y};

	o->objects = objects;

	return o;
}

void object_tick(Object *o)
{
	for (Node *temp = o->objects->head; temp->next != NULL; temp = temp->next) {
		Object *o2 = temp->data;

		if (CheckCollisionRecs(o->entity->rect, o2->entity->rect)) {
			Vector2 v1 = o->vel;
			Vector2 v2 = o2->vel;

			float m1 = o->mass;
			float m2 = o2->mass;

			o->vel.x = ((2 * m2 * v2.x) + ((m1 - m2) * v1.x)) / (m1 + m2);
			o->vel.y = ((2 * m2 * v2.y) + ((m1 - m2) * v1.y)) / (m1 + m2);

			o2->vel.x = ((2 * m1 * v1.x) + ((m2 - m1) * v2.x)) / (m1 + m2);
			o2->vel.y = ((2 * m1 * v1.y) + ((m2 - m1) * v2.y)) / (m1 + m2);
		}
	}

	o->vel.x += o->acc.x * DELTA_TIME;
	o->vel.y += o->acc.y * DELTA_TIME;

	o->pos.x += o->vel.x * DELTA_TIME;
	o->pos.y += o->vel.y * DELTA_TIME;

	o->entity->rect.x = o->pos.x;
	o->entity->rect.y = o->pos.y;
}

void object_render(Object *o)
{
	entity_render(o->entity);
}

void object_destroy(Object *o)
{
	entity_destroy(o->entity);
}
