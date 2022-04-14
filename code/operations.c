#include "stack.h"
#include "operations.h"

#include <math.h>
#include <assert.h>

int get_index(char operator) {
    int index;
    char operators[5] = {
        '+',
        '-',
        '*',
        '/',
        '%'
    };

    for (int i = 0; i < 5; i++) {
        if (operator == operators[i]) {
            index = i;
        }
    }

    return index;
}

void dispatch_table(STACK *s, char operator) {
    table functions[] = {
        sum, 
        sub,
        mul,
        divi,
        resto
    };

    int index = get_index(operator);

    functions[index](s);
}

void sum(STACK *s) {
    int x, y;
    assert(pop(s, &x) == 0);
    assert(pop(s, &y) == 0);

    push(s, x + y);
}

void sub(STACK *s) { 
    int x, y;
    assert(pop(s, &y) == 0);
    assert(pop(s, &x) == 0);

    push(s, x - y);
}

void mul(STACK *s) {
    int x, y;
    assert(pop(s, &x) == 0);
    assert(pop(s, &y) == 0);

    push(s, x * y);
}

void divi(STACK *s) {
    int x, y;
    assert(pop(s, &x) == 0);
    assert(pop(s, &y) == 0);                              
    assert(y != 0);

    push(s, y / x);
}


void resto(STACK *s) {
    int x, y;
    assert(pop(s, &x) == 0);
    assert(pop(s, &y) == 0);                              
    assert(y != 0);

    push(s, (int) y-(y / x));
}