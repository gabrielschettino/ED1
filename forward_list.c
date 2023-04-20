#include <stdio.h>
#include <stdlib.h>
#include "forward_list.h"

ForwardList *forward_list_construct(){
    ForwardList *l = (ForwardList*)malloc(sizeof(ForwardList));
    l->head = NULL;
    l->size = 0;
    return l;
}

void forward_list_push_front(ForwardList *l, data_type value){
    Node *n = (Node*)malloc(sizeof(Node));
    n->value = value;
    n->next = l->head;
    l->head = n;
    l->size++;
}

int forward_list_size(ForwardList *l){
    return l->size;
}

void forward_list_print(ForwardList *l, void (*print_fn)(data_type)){
    Node *aux = l->head;
    printf("[");
    for(int i = 0; i < l->size; i++){
        print_fn(aux->value);
        if(i == l->size-1){
            
        }else{
            printf(", ");
        }
        aux = aux->next;
    }
    printf("]");
}


void forward_list_destroy(ForwardList *l){
    while(l->head!= NULL){
        Node *aux = l->head;
        l->head = l->head->next;
        free(aux);
    }
    free(l);
}



/**
 * @brief Removes all nodes with the given value from the linked list.
 * Removes all nodes with the given value from the linked list and frees the memory allocated for them.
 * @param l
 * Pointer to the linked list.
 * @param val
 * Value to be removed from the linked list.
 */
void forward_list_remove(ForwardList *l, data_type val){
    while(l->head!= NULL){
        if(l->head->value == val){
            Node *aux = l->head;
            l->head = l->head->next;
            free(aux);
        }else{
            l->head = l->head->next;
        }
    }
}


void forward_list_cat(ForwardList *l, ForwardList *m){
    while(m->head!= NULL){
        forward_list_push_front(l, m->head->value);
        m->head = m->head->next;
    }
}