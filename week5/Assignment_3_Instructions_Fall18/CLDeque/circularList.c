#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "circularList.h"

// Double link
struct Link
{
	TYPE value;
	struct Link * next;
	struct Link * prev;
};

struct CircularList
{
	int size;
	struct Link* sentinel;
};

/**
 * Allocates the list's sentinel and sets the size to 0.
 * The sentinel's next and prev should point to the sentinel itself.
 */
static void init(struct CircularList* list)
{
	struct Link * sent = malloc(sizeof(struct Link));
	list->size=0;
	sent->next = sent;
	sent->prev = sent;
	list->sentinel = sent;
}

/**
 * Creates a link with the given value and NULL next and prev pointers.
 */
static struct Link* createLink(TYPE value)
{
	struct Link * newLink = malloc(sizeof(struct Link));
	newLink->next = NULL;
	newLink->prev = NULL;
	newLink->value = value;
	return newLink;
}

/**
 * Adds a new link with the given value after the given link and
 * increments the list's size.
 */
static void addLinkAfter(struct CircularList* list, struct Link* link, TYPE value)
{
	struct Link* newLink = createLink(value);
	newLink->next = link->next;
	link->next = newLink;
	newLink->prev = link;
	struct Link* secondFront = newLink->next;
	secondFront->prev = newLink;
	list->size += 1;
}

/**
 * Removes the given link from the list and
 * decrements the list's size.
 */
static void removeLink(struct CircularList* list, struct Link* link)
{
	struct Link* p = link->prev;
	struct Link* n = link->next;
	n->prev = p;
	p->next = n;
	list->size -= 1;
	free(link);
}

/**
 * Allocates and initializes a list.
 */
struct CircularList* circularListCreate()
{
	struct CircularList* list = malloc(sizeof(struct CircularList));
	init(list);
	return list;
}

/**
 * Deallocates every link in the list and frees the list pointer.
 */
void circularListDestroy(struct CircularList* list)
{
	struct Link * sent = list->sentinel;
	struct Link * current = sent->next;
	struct Link * n = current->next;
	
	while (sent!=current){
		removeLink(list, current);
		current = n;
		n = current->next;
	}
	free(sent);
	free(list);
}

/**
 * Adds a new link with the given value to the front of the deque.
 */
void circularListAddFront(struct CircularList* list, TYPE value)
{
	struct Link * sent = list->sentinel;
	addLinkAfter(list, sent, value);
}

/**
 * Adds a new link with the given value to the back of the deque.
 */
void circularListAddBack(struct CircularList* list, TYPE value)
{
	struct Link * sent = list->sentinel;
	struct Link * currentBack = sent->prev;
	addLinkAfter(list,currentBack,value);
}

/**
 * Returns the value of the link at the front of the deque.
 */
TYPE circularListFront(struct CircularList* list)
{
	struct Link * sent = list->sentinel;
	struct Link * front = sent->next;
	return front->value;
}

/**
 * Returns the value of the link at the back of the deque.
 */
TYPE circularListBack(struct CircularList* list)
{
	struct Link * sent = list->sentinel;
	struct Link * back = sent->prev;
	return back->value;
}

/**
 * Removes the link at the front of the deque.
 */
void circularListRemoveFront(struct CircularList* list)
{
	struct Link* front = list->sentinel;
	front = front->next;
	removeLink(list,front);
}

/**
 * Removes the link at the back of the deque.
 */
void circularListRemoveBack(struct CircularList* list)
{
	struct Link* back = list->sentinel;
	back = back->prev;
	removeLink(list,back);
}

/**
 * Returns 1 if the deque is empty and 0 otherwise.
 */
int circularListIsEmpty(struct CircularList* list)
{
	if(list->size>0){
		return 0;
	} else {
		return 1;
	}
}

/**
 * Prints the values of the links in the deque from front to back.
 */
void circularListPrint(struct CircularList* list)
{
	struct Link * sent = list->sentinel;
	struct Link * current = sent->next;
	for(int a=0; a<list->size;a++){
		double printVal = current->value;
		printf("%f\n",printVal);
		current = current->next;
	}
}

/**
 * Reverses the deque.
 */
void circularListReverse(struct CircularList* list)
{
	struct Link * sent = list->sentinel;
	struct Link * current = sent->prev;
	int count = list->size;
	for(int a=0;a<count;a++){
		circularListAddBack(list,current->value);
		current = current->prev;
	}
	for (int b=0;b<count;b++){
		current = sent->next;
		removeLink(list,current);
	}
}
