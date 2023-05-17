#include "queue.h"
#include "list.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct Queue
{
    List *list;
} Queue;

Queue *queue_construct()
{
    Queue *queue = malloc(sizeof(Queue));
    queue->list = list_construct();
    return queue;
}

void queue_enqueue(Queue *queue, data_type value)
{
    list_push_back(queue->list, value);
}

data_type queue_dequeue(Queue *queue)
{
    return list_pop_front(queue->list);
}

int queue_empty(Queue *queue)
{
    return list_size(queue->list) == 0;
}

void queue_destroy(Queue *queue)
{
    list_destroy(queue->list);
    free(queue);
}
