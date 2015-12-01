#include <assert.h>
#include <string.h>
#include "linked_list.h"

void test_linked_list_empty_data_size()
{
    struct linked_list l;
    linked_list_init(&l);
    assert(linked_list_data_size(l) == 0);
    linked_list_free(&l);
}

void test_linked_list_unitialized_data()
{
    struct linked_list l;
    assert(linked_list_data_size(l) == 0);
    linked_list_free(&l);
}

void test_linked_list_data_size_one_buffer()
{
    struct linked_list l;
    linked_list_init(&l);
    const char* data="hello, world";
    ssize_t size = strlen(data);
    linked_list_add(&l, data);
    assert(linked_list_data_size(l) == size);
    linked_list_free(&l);
}

void test_linked_list_data_size_two_same_buffers()
{
    struct linked_list l;
    linked_list_init(&l);
    const char* data="hello, world";
    ssize_t size = strlen(data) * 2;
    linked_list_add(&l, data);
    linked_list_add(&l, data);
    assert(linked_list_data_size(l) == size);
    linked_list_free(&l);
}

void test_linked_list_data_size_two_different_buffers()
{
    struct linked_list l;
    linked_list_init(&l);
    const char* data_first="hello, world";
    ssize_t size_first = strlen(data_first);
    linked_list_add(&l, data_first);
    const char* data_second="goodbye, world";
    ssize_t size_second = strlen(data_second);
    linked_list_add(&l, data_second);
    assert(linked_list_data_size(l) == (size_first+size_second));
    linked_list_free(&l);
}

int main(int argc, char *argv[])
{
    test_linked_list_empty_data_size();
    test_linked_list_unitialized_data();
    test_linked_list_data_size_one_buffer();
    test_linked_list_data_size_two_same_buffers();
    test_linked_list_data_size_two_different_buffers();
    return 0;
}

