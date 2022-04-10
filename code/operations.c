#include "stack.h"
#include "operations.h"

#include <math.h>
#include <assert.h>

int get_index(char operator) {
    int index;
    char operators[2] = {
        '+',
        '-'
    };

    for (int i = 0; i < 2; i++) {
        if (operator == operators[i]) {
            index = i;
        }
    }

    return index;
}

void dispatch_table(STACK *s, char operator) {
    table functions[] = {
        soma, 
        sub
    };

    int index = get_index(operator);

    functions[index](s);
}

void soma(STACK *s) {
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
