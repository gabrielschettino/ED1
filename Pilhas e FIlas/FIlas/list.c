#include "list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

List *list_construct()
{
    List *l = (List *)malloc(sizeof(List));
    l->head = NULL;
    l->last = NULL;
    l->size = 0;
    return l;
}

void list_push_front(List *l, data_type data)
{
    Node *n = node_construct(data, NULL, NULL);
    if (l->head == NULL)
    {
        l->head = n;
        l->last = n;
    }
    else
    {
        n->next = l->head;
        l->head->prev = n;
        l->head = n;
    }
    l->size++;
}

int list_size(List *l)
{
    return l->size;
}

void list_print(List *l, void (*print_fn)(data_type))
{
    Node *n = l->head;
    printf("[");
    while (n != NULL)
    {
        print_fn(n->value);
        n = n->next;
        if (n != NULL)
        {
            printf(", ");
        }
    }
    printf("]");
}

void list_destroy(List *l)
{
    Node *n = l->head;
    while (n != NULL)
    {
        Node *tmp = n;
        n = n->next;
        node_destroy(tmp);
    }
    free(l);
}

void list_print_reverse(List *l, void (*print_fn)(data_type))
{
    Node *n = l->last;
    printf("[");
    while (n != NULL)
    {
        print_fn(n->value);
        n = n->prev;
        if (n != NULL)
        {
            printf(", ");
        }
    }
    printf("]");
}

data_type list_pop_front(List *l)
{
    Node *n = l->head;
    data_type data = n->value;
    l->head = n->next;
    if (l->head != NULL)
    {
        l->head->prev = NULL;
    }
    node_destroy(n);
    l->size--;
    return data;
}

/**
 * @brief Pushes a new node to the back of the double linked list.
 *
 * @param l
 * Pointer to the double linked list.
 * @param data
 * data to be stored in the new node.
 */
void list_push_back(List *l, data_type data)
{
    Node *n = node_construct(data, NULL, NULL);
    if (l->head == NULL)
    {
        l->head = n;
        l->last = n;
    }
    else
    {
        n->prev = l->last;
        l->last->next = n;
        l->last = n;
    }
    l->size++;
}

/**
 * @brief Remove the last node of the double linked list and returns its data.
 * @param l
 * Pointer to the double linked list.
 * @return data_type
 * Data stored in the last node of the double linked list that was removed.
 */
data_type list_pop_back(List *l)
{
    Node *n = l->last;
    data_type data = n->value;
    l->last = n->prev;
    if (l->last != NULL)
    {
        l->last->next = NULL;
    }
    node_destroy(n);
    l->size--;
    return data;
}

ListIterator *list_front_iterator(List *l)
{
    ListIterator *it = (ListIterator *)malloc(sizeof(ListIterator));
    it->current = l->head;
    return it;
}

ListIterator *list_back_iterator(List *l)
{
    ListIterator *it = (ListIterator *)malloc(sizeof(ListIterator));
    it->current = l->last;
    return it;
}

data_type *list_iterator_next(ListIterator *it)
{
    data_type *data = &(it->current->value);
    it->current = it->current->next;
    return data;
}

data_type *list_iterator_previous(ListIterator *it)
{
    data_type *data = &(it->current->value);
    it->current = it->current->prev;
    return data;
}

data_type *list_iterator_get(ListIterator *it)
{
    return &(it->current->value);
}

bool list_iterator_is_over(ListIterator *it)
{
    return it->current == NULL;
}

void list_iterator_destroy(ListIterator *it)
{
    free(it);
}

data_type list_get(List *l, int i)
{
    Node *n = l->head;
    while (i > 0)
    {
        n = n->next;
        i--;
    }
    return n->value;
}

/**
 * @brief Removes all nodes with the given value from the double linked list.
 * Removes all nodes with the given value from the double linked list and frees the memory allocated for them.
 * @param l
 * Pointer to the double linked list.
 * @param val
 * Value to be removed from the double linked list.
 */
void list_remove(List *l, data_type val)
{
    Node *n = l->head;
    while (n != NULL)
    {
        if (n->value == val)
        {
            if (n->prev != NULL)
            {
                n->prev->next = n->next;
            }
            else
            {
                l->head = n->next;
            }
            if (n->next != NULL)
            {
                n->next->prev = n->prev;
            }
            else
            {
                l->last = n->prev;
            }
            Node *tmp = n;
            n = n->next;
            node_destroy(tmp);
            l->size--;
        }
        else
        {
            n = n->next;
        }
    }
}