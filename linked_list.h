#ifndef TMUX_LINKED_LIST_INCLUDED
#define TMUX_LINKED_LIST_INCLUDED

#include <stdlib.h>

#define LIST_BUFSZ 4048
struct node
{
    char buf[LIST_BUFSZ];
    struct node *next;
};

struct linked_list
{
    struct node *first_node;
};

#define linked_list_for_each(l, __element_name) \
    struct node* __element_name; \
for (__element_name = l.first_node; __element_name != NULL; __element_name = __element_name->next) \

void linked_list_init(struct linked_list *l);
void linked_list_add(struct linked_list *l, const char *data);
ssize_t linked_list_data_size(struct linked_list l);
void linked_list_free(struct linked_list *l);

#endif
