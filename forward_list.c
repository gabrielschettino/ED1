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
    while(aux!= NULL){
        print_fn(aux->value);
        aux = aux->next;
    }
    printf("]\n");
}


void forward_list_destroy(ForwardList *l){
    while(l->head!= NULL){
        Node *aux = l->head;
        l->head = l->head->next;
        free(aux);
    }
    free(l);
}