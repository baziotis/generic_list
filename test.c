#include <stdio.h>

#include "generic_list.h"

int cmp(void *a, void *b) {
	int v = *((int *) a);
	int w = *((int *) b);
	return v - w;
}

void print(FILE *out, void *v) {
	fprintf(out, "%d\n", *((int *)v));
}

int main(void) {

	int temp;
	list_t l;
	// Give it the type that it will hold, how to compare data and
	// how to print data.
	list_initialize(&l, int, cmp, print);
	// Do a bunch of random insertions.
	temp = 5;
	list_sorted_insert(&l, &temp);
	temp = 3;
	list_sorted_insert(&l, &temp);
	temp = 7;
	list_sorted_insert(&l, &temp);
	// Print the thing
	list_print(&l, stdout);
	temp = 5;
	// Get a node back.
	list_node_t *ln = list_search(&l, &temp);
	// Delete the node
	list_delete_node(&l, ln);
	printf("\n");
	list_print(&l, stdout);
	list_delete_list(&l);

	return 0;
}
