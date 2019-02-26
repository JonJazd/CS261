#include "linkedList.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

// Double link
struct Link
{
	TYPE value;
	struct Link* next;
	struct Link* prev;
};

// Double linked list with front and back sentinels
struct LinkedList
{
	int size;
	struct Link* frontSentinel;
	struct Link* backSentinel;
};

/**
 * Allocates the list's sentinel and sets the size to 0.
 * The sentinels' next and prev should point to eachother or NULL
 * as appropriate.
 */
static void init(struct LinkedList* list) {
	struct Link * frontSent = malloc(sizeof(struct Link));
	struct Link * backSent = malloc(sizeof(struct Link));
	list->size = 0;
	frontSent->next = backSent;
	frontSent->prev = NULL;
	backSent->next = NULL;
	backSent->prev = frontSent;
	list->frontSentinel = frontSent;
	list->backSentinel = backSent;
}

/**
 * Adds a new link with the given value before the given link and
 * increments the list's size.
 */
static void addLinkBefore(struct LinkedList* list, struct Link* link, TYPE value)
{
	if (link==list->frontSentinel){
		printf("Cannot add before front sentinel");
	} else {
		list->size += 1;
		struct Link * newLink = malloc(sizeof(struct Link));
		struct Link * oldPrev = link->prev;
		newLink->prev = oldPrev;
		oldPrev->next = newLink;
		link->prev = newLink;
		newLink->next = link;
		newLink->value = value;
	}
}

/**
 * Removes the given link from the list and
 * decrements the list's size.
 */
static void removeLink(struct LinkedList* list, struct Link* link)
{
	list->size -= 1;
	struct Link * oldNext = link->next;
	struct Link * oldPrev = link->prev;
	link->prev->next = oldNext;
	link->next->prev = oldPrev;
	free(link);
}

/**
 * Allocates and initializes a list.
 */
struct LinkedList* linkedListCreate()
{
	struct LinkedList* newDeque = malloc(sizeof(struct LinkedList));
	init(newDeque);
	return newDeque;
}

/**
 * Deallocates every link in the list including the sentinels,
 * and frees the list itself.
 */
void linkedListDestroy(struct LinkedList* list)
{
	while (!linkedListIsEmpty(list))
	{
		linkedListRemoveFront(list);
	}
	free(list->frontSentinel);
	free(list->backSentinel);
	free(list);
}

/**
 * Adds a new link with the given value to the front of the deque.
 */
void linkedListAddFront(struct LinkedList* list, TYPE value)
{
	struct Link * sent = list->frontSentinel;
	struct Link * front = sent->next;
	addLinkBefore(list,front,value);
}

/**
 * Adds a new link with the given value to the back of the deque.
 */
void linkedListAddBack(struct LinkedList* list, TYPE value)
{
	addLinkBefore(list,list->backSentinel,value);
}

/**
 * Returns the value of the link at the front of the deque.
 */
TYPE linkedListFront(struct LinkedList* list)
{
	struct Link * frontS = list->frontSentinel;
	struct Link * front = frontS->next;
	return front->value;
}

/**
 * Returns the value of the link at the back of the deque.
 */
TYPE linkedListBack(struct LinkedList* list)
{
	struct Link * backS = list->backSentinel;
	struct Link * back = backS->prev;
	return back->value;
}

/**
 * Removes the link at the front of the deque.
 */
void linkedListRemoveFront(struct LinkedList* list)
{
	struct Link * fSent = list->frontSentinel;
	struct Link * front = fSent->next;
	removeLink(list,front);
}

/**
 * Removes the link at the back of the deque.
 */
void linkedListRemoveBack(struct LinkedList* list)
{
	struct Link * bSent = list->backSentinel;
	struct Link * back = bSent->prev;
	removeLink(list,back);
}

/**
 * Returns 1 if the deque is empty and 0 otherwise.
 */
int linkedListIsEmpty(struct LinkedList* list)
{
	if (list->size<1){
		return 1;
	} else {
		return 0;
	}
}

/**
 * Prints the values of the links in the deque from front to back.
 */
void linkedListPrint(struct LinkedList* list)
{
	struct Link * current = list->frontSentinel;
	current = current->next;
	while (current!=list->backSentinel){
		printf("%d\n",current->value);
		current = current->next;
	}
}

/**
 * Adds a link with the given value to the bag.
 */
void linkedListAdd(struct LinkedList* list, TYPE value)
{
	struct Link * sent = list->backSentinel;
	addLinkBefore(list,sent,value);
}

/**
 * Returns 1 if a link with the value is in the bag and 0 otherwise.
 */
int linkedListContains(struct LinkedList* list, TYPE value)
{
	struct Link * current = list->frontSentinel;
	current = current->next;
	while (current!=list->backSentinel){
		if (current->value == value){
			return 1;
		}
		current = current->next;
	}
	return 0;
}

/**
 * Removes the first occurrence of a link with the given value.
 */
void linkedListRemove(struct LinkedList* list, TYPE value)
{
	struct Link * current = list->frontSentinel;
	current = current->next;
	while (current->value!=value && current!=list->backSentinel){
		current = current->next;
	}
	if (current!=list->backSentinel){
		removeLink(list, current);
	}
}
