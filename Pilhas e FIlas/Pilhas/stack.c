#include "stack.h"
#include "vector.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct Stack
{
    Vector *v;
} Stack;

Stack *stack_construct()
{
    Stack *s = (Stack *)calloc(1, sizeof(Stack));
    s->v = vector_construct();
    return s;
}

void stack_push(Stack *s, data_type val)
{
    vector_push_back(s->v, val);
}

data_type stack_pop(Stack *s)
{
    return vector_pop_back(s->v);
}

int stack_empty(Stack *s)
{
    return vector_size(s->v) == 0;
}

void stack_destroy(Stack *s)
{
    vector_destroy(s->v);
    free(s);
}