#include "llrec.h"



void llpivot(Node *&head, Node *&smaller, Node *&larger, int pivot)
{
	// set pointers to NULL to establish an empty list 
	smaller = NULL;
	larger = NULL; 

	// base case, returns if head/current item in list does not 
	// exist 
	if (!head) {
		return;
	}

	// recursive call 
	llpivot(head->next, smaller, larger, pivot);

	// deterines whether element at hand is less than/equal to 
	// pivot number and if so, adds element to "smaller" list 
	if (head->val <= pivot) {
		head->next = smaller;
		smaller = head;
		head = NULL;
	}
	
	// if element is greater than pivot number, adds element 
	// to "larger" list 
	else {
		head->next = larger;
		larger = head;
		head = NULL;
	}
}