#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

typedef struct XOR_Linked_List {
	int data;
	struct XOR_Linked_List *neighbor;
} XOR_Linked_List;

void xor_linked_list_push_front(XOR_Linked_List **head, int value)
{
	XOR_Linked_List *new_head = malloc(sizeof(*new_head));
	*new_head = (XOR_Linked_List) {
		.data = value,
		.neighbor = *head,
	};

	if (*head != NULL) {
		(*head)->neighbor = (XOR_Linked_List *) ((uintptr_t) (void *) (*head)->neighbor ^ (uintptr_t) (void *) new_head);
	}

	*head = new_head;
}

void xor_linked_list_traverse(const XOR_Linked_List *head)
{
	const XOR_Linked_List *prev = NULL;
	const XOR_Linked_List *curr = head;

	while (curr != NULL) {
		printf("%d (%p) <-> ", curr->data, curr);

		const XOR_Linked_List *temp = curr;
		curr = (const XOR_Linked_List *) ((uintptr_t) (void *) curr->neighbor ^ (uintptr_t) (void *) prev);
		prev = temp;
	}
	printf("NULL\n");
}

XOR_Linked_List *xor_linked_list_search(XOR_Linked_List *head, const int value)
{
	const XOR_Linked_List *prev = NULL;
	XOR_Linked_List *curr = head;

	while (curr != NULL) {
		if (curr->data == value) {
			break;
		}

		const XOR_Linked_List *temp = curr;
		curr = (XOR_Linked_List *) ((uintptr_t) (void *) curr->neighbor ^ (uintptr_t) (void *) prev);
		prev = temp;
	}

	return curr;
}

void xor_linked_list_delete(XOR_Linked_List **head, const int value)
{
	XOR_Linked_List *prev = NULL;
	XOR_Linked_List *curr = *head;

	if (curr->data == value) {
		*head = (XOR_Linked_List *) ((uintptr_t) (void *) curr->neighbor ^ (uintptr_t) (void *) prev);
		if (*head != NULL) {
			(*head)->neighbor = (XOR_Linked_List *) ((uintptr_t) (void *) (*head)->neighbor ^ (uintptr_t) (void *) curr);
		}

		free(curr);
		
		return;
	}

	while (curr != NULL) {
		if (curr->data == value) {
			break;
		}

		XOR_Linked_List *temp = curr;
		curr = (XOR_Linked_List *) ((uintptr_t) (void *) curr->neighbor ^ (uintptr_t) (void *) prev);
		prev = temp;
	}

	XOR_Linked_List *next = (XOR_Linked_List *) ((uintptr_t) (void *) curr->neighbor ^ (uintptr_t) (void *) prev);

	if (prev != NULL) {
		prev->neighbor = (XOR_Linked_List *) ((uintptr_t) (void *) prev->neighbor ^ (uintptr_t) (void *) curr);
		prev->neighbor = (XOR_Linked_List *) ((uintptr_t) (void *) prev->neighbor ^ (uintptr_t) (void *) next);
	}

	if (next != NULL) {
		next->neighbor = (XOR_Linked_List *) ((uintptr_t) (void *) next->neighbor ^ (uintptr_t) (void *) curr);
		next->neighbor = (XOR_Linked_List *) ((uintptr_t) (void *) next->neighbor ^ (uintptr_t) (void *) prev);
	}

	free(curr);
}

void xor_linked_list_free(XOR_Linked_List *head)
{
	const XOR_Linked_List *prev = NULL;
	XOR_Linked_List *curr = head;

	while (curr != NULL) {
		XOR_Linked_List *temp = curr;
		curr = (XOR_Linked_List *) ((uintptr_t) (void *) curr->neighbor ^ (uintptr_t) (void *) prev);
		prev = temp;

		free(temp);
	}
}

int main()
{
	XOR_Linked_List *xll = NULL;

	xor_linked_list_traverse(xll);
	xor_linked_list_push_front(&xll, 1);
	xor_linked_list_traverse(xll);
	xor_linked_list_push_front(&xll, 2);
	xor_linked_list_traverse(xll);
	xor_linked_list_push_front(&xll, 3);
	xor_linked_list_traverse(xll);

	printf("Found: %p\n", xor_linked_list_search(xll, 2));
	printf("Found: %p\n", xor_linked_list_search(xll, 5));

	xor_linked_list_delete(&xll, 2);
	xor_linked_list_traverse(xll);
	xor_linked_list_delete(&xll, 1);
	xor_linked_list_traverse(xll);
	xor_linked_list_delete(&xll, 3);
	xor_linked_list_traverse(xll);

	return 0;
}
