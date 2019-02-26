#include "circularList.h"
#include <stdio.h>

int main()
{	
	struct CircularList* deque = circularListCreate(); 
	circularListAddBack(deque, (TYPE)1);
	circularListAddBack(deque, (TYPE)2);
	circularListAddBack(deque, (TYPE)3);
	circularListAddFront(deque, (TYPE)4);
	circularListAddFront(deque, (TYPE)5);
	circularListAddFront(deque, (TYPE)6);
	printf("First Print\n");
	circularListPrint(deque);
	
	printf("First\n");
	printf("%g\n", circularListFront(deque));
	
	printf("Last\n");
	
	printf("%g\n", circularListBack(deque));
	
	
	circularListRemoveFront(deque);
	circularListRemoveBack(deque);
	printf("Second Print\n");
	circularListPrint(deque);
	
	
	circularListReverse(deque);
	printf("Reverse Print\n");
	circularListPrint(deque);
	
	
	circularListDestroy(deque);
	
	return 0;
}
