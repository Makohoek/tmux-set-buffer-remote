#include "linked_list.h"
#include <string.h>
#include <stdlib.h>

void linked_list_init(struct linked_list* l) {
  l->first_node = NULL;
}

void linked_list_add(struct linked_list* l, const char* data) {
  struct node* new_node = malloc(sizeof(struct node));
  new_node->next = NULL;
  strncpy(new_node->buf, data, LIST_BUFSZ);

  if (l->first_node == NULL) {
    l->first_node = new_node;
    return;
  }

  struct node* current_node = l->first_node;
  while (current_node->next != NULL) {
    current_node = current_node->next;
  }

  current_node->next = new_node;
}

ssize_t linked_list_data_size(const struct linked_list l) {
  size_t size = 0;
  linked_list_for_each(l, node) size += strnlen(node->buf, LIST_BUFSZ);
  return size;
}

void linked_list_free(struct linked_list* l) {
  struct node* next_node;
  while (l->first_node != NULL) {
    next_node = l->first_node->next;
    free(l->first_node);
    l->first_node = next_node;
  }
}
