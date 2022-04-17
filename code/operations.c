#include "stack.h"
#include "operations.h"

#include <assert.h>
#include <math.h>

char get_operator(int i) {
    static char const operators[N_OPERATORS] = {
        '+',
        // '-',
        // '*',
        // '/',
        // '%',
        // '#',
        // '^',
        // '&',
        // '|',
        // ')',
        // '(',
        // '~'
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
    int index = -1;

    for (int i = 0; i < N_OPERATORS; i++) {
        if (operator == get_operator(i)) {
            index = i;
        }
    }

    // Caso o operador não tenha sido encontrado: retorna -1 (ERRO)
    return index;
}

void dispatch_table(STACK *s, char operator) {
    function table[] = {
        sum, 
        // sub,
        // mult,
        // divi,
        // rem,
        // power,
        // bw_xor,
        // bw_and,
        // bw_or,
        // increment,
        // decrement,
        // bw_not
    }; // As funções até agora implementadas são colocadas em posições análogas às referenciadas na função 'get_operator'.

    int index = get_index(operator);

    table[index](s);
}

void sum(STACK *s) {
    STACK_ELEM x, y;
    
    assert(pop(s, &x) == 0);
    assert(pop(s, &y) == 0);

    STACK_ELEM result;
    
    if (x.t == LONG) {
        if (y.t == DOUBLE) {
            result.t = DOUBLE;
            result.data.d = x.data.l + y.data.d;
        }
        else if (y.t == LONG) {
            result.t = LONG;
            result.data.l = x.data.l + y.data.l;
        }
    } 
    else if (x.t == DOUBLE) {
        if (y.t == LONG) {
            result.t = DOUBLE;
            result.data.d = x.data.d + y.data.l;
        }
        else if (y.t == DOUBLE) {
            result.t = DOUBLE;
            result.data.d = x.data.d + y.data.d;
        }  
    }
    push(s, result);
}

// void sub(STACK *s) {
//     int x, y;
    
//     assert(pop(s, &y) == 0);
//     assert(pop(s, &x) == 0);

//     push(s, x - y);
// }

// void mult(STACK *s) {
//     int x, y;
    
//     assert(pop(s, &x) == 0);
//     assert(pop(s, &y) == 0); 

//     push(s, x * y);
// }

// void divi(STACK *s) {
//     int x, y;
    
//     assert(pop(s, &y) == 0);
//     assert(pop(s, &x) == 0);

//     push(s, x / y);
// }

// void rem(STACK *s) {
//     int x, y;
    
//     assert(pop(s, &y) == 0);
//     assert(pop(s, &x) == 0);

//     push(s, x % y);
// }

// void power(STACK *s) {
//     int x, y;
    
//     assert(pop(s, &y) == 0);
//     assert(pop(s, &x) == 0);

//     push(s, pow(x, y));
// }

// void bw_xor(STACK *s) {
//     int x, y;
    
//     assert(pop(s, &x) == 0);
//     assert(pop(s, &y) == 0);

//     push(s, x ^ y);
// }

// void bw_and(STACK *s) {
//     int x, y;
    
//     assert(pop(s, &x) == 0);
//     assert(pop(s, &y) == 0);

//     push(s, x & y);
// }

// void bw_or(STACK *s) {
//     int x, y;
    
//     assert(pop(s, &x) == 0);
//     assert(pop(s, &y) == 0);

//     push(s, x | y);
// }

// void increment(STACK *s) {
//     int x;
    
//     assert(pop(s, &x) == 0);

//     push(s, ++x);
// }

// void decrement(STACK *s) {
//     int x;
    
//     assert(pop(s, &x) == 0);

//     push(s, --x);
// }

// void bw_not(STACK *s) {
//     int x;
    
//     assert(pop(s, &x) == 0);

//     push(s, ~x);
// }
