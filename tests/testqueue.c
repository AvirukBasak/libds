#include "../include/tlib/queue.h"

QUEUE_DECLARE(int);
QUEUE_DEFINE(int);

int main() {
    Queue(int) qu = QueueFn(int, new)();
    qu->push(qu, 56);
    qu->push(qu, 38);
    qu->push(qu, 90);
    qu->push(qu, 23);
    qu->push(qu, 14);
    printf("len = %zu\n", qu->length(qu));
    while (!qu->isempty(qu)) {
        printf("qu = { ");
        QUEUE_FOREACH(qu, printf("%d ", *value));
        printf("}; ");
        printf("pop = %d\n", qu->pop(qu));
    }
    return 0;
}
