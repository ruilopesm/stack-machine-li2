#include "stack.h"
#include "operations.h"

#include <assert.h>
#include <math.h>

char get_operator(int i) {
    static char const operators[N_OPERATORS] = {
        '+',
        '-'
    };

    return operators[i];
}

int is_operator(char *token) {
    for (int i = 0; i < N_OPERATORS; i++) {
        if (token[0] == get_operator(i)) {
            return 1;
        }
    }
    
    return 0;
}

int get_index(char operator) {
    int index;

    for (int i = 0; i < N_OPERATORS; i++) {
        if (operator == get_operator(i)) {
            index = i;
        }
    }

    return index;
}

void dispatch_table(STACK *s, char operator) {
    binary functions[] = {
        sum, 
        sub,
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
