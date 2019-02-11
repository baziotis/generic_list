#ifndef GENERIC_LIST
#define GENERIC_LIST

typedef struct list_node {
    struct list_node *prev;
    struct list_node *next;
    void *data;
} list_node_t;

typedef struct list {
    list_node_t *head;
	size_t data_size;
    int (*data_cmp)(void *, void *);
    void (*data_print)(FILE *, void *);
} list_t;

void __list_initialize(list_t *, size_t, int (*)(void *, void *), void (*)(FILE *, void *));
list_node_t *list_sorted_insert(list_t *, void *);
list_node_t *list_insert(list_t *, void *);
void list_delete_list(list_t *);
void list_delete_node(list_t *, list_node_t *);
void list_print(list_t *, FILE *out);
list_node_t *list_search(list_t *, void *);

#define list_initialize(l, t, dc, dp) __list_initialize(l, sizeof(t), dc, dp)

#endif
