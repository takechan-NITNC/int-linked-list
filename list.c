#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include <list.h>
struct list *list_init(void)
{
	struct list *ret = malloc(sizeof(struct list));
	*ret = (struct list){NULL, NULL, 0};
	return ret;
}
struct list *list_init_from_array(int *array, int count)
{
	struct list *ret = list_init();
	for (int i = 0; i < count; i++) {
		list_add(ret, array[i]);
	}
	return ret;
}
struct node *get_node(struct list *source, int i)
{
	struct node *head;
	if (i <= list_get_count(source) - 1 - i) {
		head = source->first;
		for (int j = 0; j < i; j++) {
			head = head->next;
		}
	} else {
		head = source->last;
		for (int j = list_get_count(source) - 1; j > i; j--) {
			head = head->previous;
		}
	}
	return head;
}
int list_get(struct list *source, int i)
{
	if (i < 0 || i >= list_get_count(source)) {
		fprintf(stderr, "%sの%d行目：Index %d out of bounds %d.\n", __FILE__, __LINE__, i, list_get_count(source) - 1);
		exit(1);
	}
	return get_node(source, i)->element;
}
void list_set(struct list *target, int i, int element)
{
	if (i < 0 || i >= list_get_count(target)) {
		fprintf(stderr, "%sの%d行目：Index %d out of bounds %d.\n", __FILE__, __LINE__, i, list_get_count(target) - 1);
		exit(1);
	}
	get_node(target, i)->element = element;
}
void list_add(struct list *target, int element)
{
	if (list_get_count(target) == INT_MAX) {
		fprintf(stderr, "%sの%d行目：要素数が上限%dに達しました。\n", __FILE__, __LINE__, INT_MAX);
		exit(1);
	}
	struct node *new = malloc(sizeof(struct node));
	*new = (struct node){target->last, NULL, element};
	target->last = new;
	if (list_get_count(target)) {
		target->last->next = new;
	} else {
		target->first = new;
	}
	target->count++;
}
void list_insert(struct list *target, int i, int element)
{
	if (list_get_count(target) == INT_MAX) {
		fprintf(stderr, "%sの%d行目：要素数が上限%dに達しました。\n", __FILE__, __LINE__, INT_MAX);
		exit(1);
	}
	if (i < 0 || i > list_get_count(target)) {
		fprintf(stderr, "%sの%d行目：Index %d out of bounds %d.\n", __FILE__, __LINE__, i, list_get_count(target));
		exit(1);
	}
	if (i == list_get_count(target)) {
		list_add(target, element);
		return;
	}
	struct node *head = get_node(target, i);
	struct node *new = malloc(sizeof(struct node));
	*new = (struct node){head->previous, head, element};
	if (i) {
		new->previous->next = new;
	} else {
		target->first = new;
	}
	head->previous = new;
	target->count++;
}
void list_remove(struct list *target, int i)
{
	if (i < 0 || i >= list_get_count(target)) {
		fprintf(stderr, "%sの%d行目：Index %d out of bounds %d.\n", __FILE__, __LINE__, i, list_get_count(target) - 1);
		exit(1);
	}
	struct node *removed = get_node(target, i);
	if (i) {
		removed->previous->next = removed->next;
	} else {
		target->first = removed->next;
	}
	if (i == list_get_count(target) - 1) {
		target->last = removed->previous;
	} else {
		removed->next->previous = removed->previous;
	}
	free(removed);
	target->count--;
}
int list_get_count(struct list *source)
{
	return source->count;
}
struct list *list_copy(struct list *source)
{
	int *array = list_to_array(source);
	struct list *ret = list_init_from_array(array, list_get_count(source));
	free(array);
	return ret;
}
struct list *list_to_array(struct list *source)
{
	int *ret = malloc(sizeof(int) * list_get_count(source));
	struct node *head = source->first;
	for (int i = 0; i < list_get_count(source); i++) {
		ret[i] = head->element;
		head = head->next;
	}
	return ret;
}
void list_free(struct list *target)
{
	for (struct node *head = source->first; head != NULL;) {
		head = head->next;
		free(head);
	}
	free(target);
}