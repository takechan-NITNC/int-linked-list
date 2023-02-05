#pragma once
struct node {
	struct node *previous;
	struct node *next;
	int element;
};
struct list {
	struct node *first;
	struct node *last;
	int count;
};
struct list *list_init();
struct list *list_init_from_array(int*, int);
int list_get(struct list*, int);
void list_set(struct list*, int, int);
void list_add(struct list*, int);
void list_insert(struct list*, int, int);
void list_remove(struct list*, int);
int list_get_count(struct list*);
struct list *list_copy(struct list*);
int *list_to_array(struct list*);
void list_free(struct list*);