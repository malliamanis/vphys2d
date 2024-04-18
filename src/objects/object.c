#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <raylib.h>

#include "vphys2d.h"
#include "util/mathutil.h"
#include "objects/object.h"

Object *object_create_rect(Vector2 position, Vector2 size, Vector2 acceleration, Vector2 velocity, float rotation, float mass, bool gravity, bool bounded, List *objects)
{
	Object *o = malloc(sizeof(Object));

	o->entity = entity_create_rect(position.x, position.y, size.x, size.y, rotation);

	o->acc = acceleration;
	if (gravity)
		o->acc.y += G;
	o->vel = velocity;
	o->pos = position;

	o->a_acc = 0.0f;
	o->a_vel = 0.0f;

	o->mass = mass;
	o->charge = 0.0f; // It has to be set by the user manually

	o->bounded = bounded;

	o->objects = objects;

	return o;
}

Object *object_create_circle(Vector2 position, float radius, Vector2 acceleration, Vector2 velocity, float mass, bool gravity, bool bounded, List *objects)
{
	Object *o = malloc(sizeof(Object));

	o->entity = entity_create_circle(position.x, position.y, radius);

	o->acc = acceleration;
	if (gravity)
		o->acc.y += G;
	o->vel = velocity;
	// o->pos = (Vector2){o->entity->c.center.x, o->entity->c.center.y};
	o->pos = position;

	o->mass = mass;
	o->charge = 0.0f;

	o->bounded = bounded;

	o->objects = objects;

	return o;
}

void object_tick(Object *o)
{
	for (Node *temp = o->objects->head; temp != NULL; temp = temp->next) {
		if (o->entity->type == ENTITY_RECTANGLE)
			break;

		Object *o2 = temp->data;
		if (o2->entity->type == ENTITY_RECTANGLE)
			continue;

		if (o->entity->id == o2->entity->id)
			continue;

		if (CheckCollisionCircles(o->pos, o->entity->c.radius, o2->pos, o2->entity->c.radius)) {
			if (math_vec2_length(o->vel) == 0)
				o->vel = math_vec2_add(o->vel, (Vector2){0.000001f, 0.000001f});
			if (math_vec2_length(o2->vel) == 0)
				o2->vel = math_vec2_add(o2->vel, (Vector2){0.000001f, 0.000001f});

			const Vector2 v1 = o->vel;
			const Vector2 v2 = o2->vel;

			const float m1 = o->mass;
			const float m2 = o2->mass;

			float v1_length = math_vec2_length(v1);
			float v2_length = math_vec2_length(v2);

			const Vector2 diacenter_intersecting = math_vec2_sub(o2->pos, o->pos); // pointing towards o2

			float diacenter_length = o->entity->c.radius + o2->entity->c.radius;
			const Vector2 diacenter = math_vec2_scale(math_vec2_norm(diacenter_intersecting), diacenter_length);

			o->pos = math_vec2_sub(o->pos, math_vec2_sub(diacenter, diacenter_intersecting));
			o2->pos = math_vec2_add(o2->pos, math_vec2_sub(diacenter, diacenter_intersecting));

			const float cosangle1 = math_vec2_dot(diacenter, v1) / (diacenter_length * v1_length);
			const float cosangle2 = math_vec2_dot(math_vec2_scale(diacenter, -1.0f), v2) / (diacenter_length * v2_length);

			const Vector2 v1x = math_vec2_scale(math_vec2_norm(diacenter), v1_length * cosangle1);
			const Vector2 v2x = math_vec2_scale(math_vec2_norm(math_vec2_scale(diacenter, -1.0f)), v2_length * cosangle2);

			// from m1 * v1 + m2 * v2 = m1 * v1n + m2 * v2n
			const Vector2 v1nx = math_vec2_scale(math_vec2_add(math_vec2_scale(v2x, 2 * m2), math_vec2_scale(v1x, (m1 - m2))), 1.0f / (m1 + m2));
			const Vector2 v2nx = math_vec2_scale(math_vec2_add(math_vec2_scale(v1x, 2 * m1), math_vec2_scale(v2x, (m2 - m1))), 1.0f / (m1 + m2));

			// from v = vx + vy
			const Vector2 v1ny = math_vec2_sub(v1, v1x);
			const Vector2 v2ny = math_vec2_sub(v2, v2x);

			o->vel = math_vec2_add(v1nx, v1ny);
			o2->vel = math_vec2_add(v2nx, v2ny);
		}
	}

	for (Node *temp = o->objects->head; temp != NULL; temp = temp->next) {
		if (o->entity->type == ENTITY_CIRCLE)
			break;

		Object *o2 = temp->data;
		if (o2->entity->type == ENTITY_CIRCLE)
			continue;

		if (CheckCollisionRecs(o->entity->r, o2->entity->r)) {
			
		}
	}

	o->vel.x += o->acc.x * DELTA_TIME;
	o->vel.y += o->acc.y * DELTA_TIME;

	o->pos.x += o->vel.x * DELTA_TIME;
	o->pos.y += o->vel.y * DELTA_TIME;

	o->a_vel += o->a_acc * DELTA_TIME;
	o->entity->rotation += o->a_vel * DELTA_TIME;

	if (!o->bounded) {
		return;
	}

	if (o->entity->type == ENTITY_CIRCLE) {
		o->entity->c.center = o->pos;

		if (o->pos.y + o->entity->c.radius >= HEIGHT) {
			o->pos.y = HEIGHT - o->entity->c.radius;
			o->vel.y *= -1;
		}
		else if (o->pos.y - o->entity->c.radius <= 0) {
			o->pos.y = o->entity->c.radius;
			o->vel.y *= -1;
		}

		if (o->pos.x + o->entity->c.radius >= WIDTH) {
			o->pos.x = WIDTH - o->entity->c.radius;
			o->vel.x *= -1;
		}
		else if (o->pos.x - o->entity->c.radius <= 0) {
			o->pos.x = o->entity->c.radius;
			o->vel.x *= -1;
		}
	}
	else if (o->entity->type == ENTITY_RECTANGLE) {
		o->entity->r.x = o->pos.x;
		o->entity->r.y = o->pos.y;

		if (o->pos.y + o->entity->r.height / 2.0f >= HEIGHT) {
			o->pos.y = HEIGHT - o->entity->r.height / 2.0f;
			o->vel.y *= -1;
		}
		else if (o->pos.y - o->entity->r.height / 2.0f <= 0) {
			o->pos.y = o->entity->r.height / 2.0f;
			o->vel.y *= -1;
		}

		if (o->pos.x + o->entity->r.width / 2.0f >= WIDTH) {
			o->pos.x = WIDTH - o->entity->r.width / 2.0f;
			o->vel.x *= -1;
		}
		else if (o->pos.x - o->entity->r.width / 2.0f <= 0) {
			o->pos.x = o->entity->r.width / 2.0f;
			o->vel.x *= -1;
		}
	}
}

void object_render(Object *o)
{
	entity_render(o->entity);
}

void object_destroy(Object *o)
{
	entity_destroy(o->entity);
}
