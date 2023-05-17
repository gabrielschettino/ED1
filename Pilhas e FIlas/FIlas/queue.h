
#ifndef _QUEUE_H_
#define _QUEUE_H_

typedef int data_type;
typedef struct Queue Queue;

Queue *queue_construct();
void queue_enqueue(Queue *queue, data_type value);
data_type queue_dequeue(Queue *queue);
int queue_empty(Queue *queue);
void queue_destroy(Queue *queue);

#endif