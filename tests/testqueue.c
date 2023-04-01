#include "ctl/queue.h"

QUEUE_DECLARE(int);
QUEUE_DEFINE(int);

void testqueue() {
    Queue(int) qu = QueueFn(int, new)();
    qu->push(qu, 56)
      ->push(qu, 38)
      ->push(qu, 90)
      ->push(qu, 23)
      ->push(qu, 14);
    while (!qu->isempty(qu)) {
        printf("qu:%zu = { ", len(qu));
        QUEUE_FOREACH(qu, printf("%d ", *value));
        printf("}; ");
        printf("pop = %d\n", qu->pop(qu));
    }
    printf("qu:%zu = {}\n", len(qu));
    qu->push(qu, 690)
      ->push(qu, 155)
      ->push(qu, 644)
      ->push(qu, 647)
      ->push(qu, 226);
    printf("qu:%zu = { ", len(qu));
    QUEUE_FOREACH(qu, printf("%d ", *value));
    printf("}\n");
    qu->free(&qu);
}
