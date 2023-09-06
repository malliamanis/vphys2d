#ifndef LIST_H
#define LIST_H

#include <stdint.h>
#include <stddef.h>

typedef struct node {
	uint32_t id;
	void *data;

	struct node *next;
} Node;

typedef void (*destructor)(void *);

typedef struct {
	size_t data_size;
	
	Node *head;
	uint32_t id_counter;

	Node **marked_for_removal;
	size_t marked_size;
	uint32_t marked_iterator;

	destructor data_destructor;
} List;

List *list_create(destructor data_destructor, size_t data_size);

Node *list_get(List *list, const void *data);
Node *list_add(List *list, void *data);
void  list_remove(List *list, void *data);

void list_mark_for_removal(List *list, Node *node);
void list_remove_marked(List *list);

void list_destroy(List *list);

void list_print(List *list);

#endif // LIST_H
