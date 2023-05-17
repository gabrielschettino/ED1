#include <stdlib.h>
#include <stdio.h>

#include "queue.h"

int main()
{
    int n, i, val;
    Queue *s = queue_construct();

    scanf("%d", &n);

    for (i = 0; i < n; i++)
    {
        scanf("%d", &val);
        queue_enqueue(s, val);
    }

    while (!queue_empty(s))
        printf("%d\n", queue_dequeue(s));

    queue_destroy(s);
    return 0;
}