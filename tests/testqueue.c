#include "ctl/queue.h"

QUEUE_DECLARE(int);
QUEUE_DEFINE(int);

void testqueue() {
    Queue(int) qu = QueueFn(int, new)();
    qu->push(qu, 56);
    qu->push(qu, 38);
    qu->push(qu, 90);
    qu->push(qu, 23);
    qu->push(qu, 14);
    while (!qu->isempty(qu)) {
        printf("qu:%zu = { ", len(qu));
        QUEUE_FOREACH(qu, printf("%d ", *value));
        printf("}; ");
        printf("pop = %d\n", qu->pop(qu));
    }
    printf("qu:%zu = {}\n", len(qu));
    qu->push(qu, 690);
    qu->push(qu, 155);
    qu->push(qu, 644);
    qu->push(qu, 647);
    qu->push(qu, 226);
    printf("qu:%zu = { ", len(qu));
    QUEUE_FOREACH(qu, printf("%d ", *value));
    printf("}\n");
    qu->free(&qu);
}
