#include <stdio.h>
#include <stdlib.h>

#include "stack.h"

STACK *create_stack() {
    STACK *s = malloc(sizeof(STACK));
    s->sp = 0;

    return s;
}

void push(STACK *s, int elem) {
    s->arr[s->sp] = elem;
    s->sp++;
}

int pop(STACK *s) {
    s->sp--;
    return s->arr[s->sp];
}
