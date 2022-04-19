#include "operations.h"
#include "stack.h"

#include <assert.h>
#include <math.h>

char get_operator(int i) {
    static char const operators[N_OPERATORS] = {
        '+',
        '-',
        '*',
        '/',
        '%',
        '#',
        '^',
        '&',
        '|',
        ')',
        '(',
        '~'
        'i',
        'f',
        'c',
        's'
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
        sub,
        mult,
        divi,
        rem,
        power,
        bw_xor,
        bw_and,
        bw_or,
        increment,
        decrement,
        bw_not
        convI,
        convD,
        convC,
        convS
    }; // As funções até agora implementadas são colocadas em posições análogas às referenciadas na função 'get_operator'.

    int index = get_index(operator);

    // Chama o function pointer
    table[index](s);
}

double get_double_arg(STACK_ELEM x){
    if (x.t == DOUBLE) {
        return x.data.d;
    }
    else if (x.t == LONG) {
        return x.data.l;
    }
    else {
        return x.data.c;
    }
}

long get_long_arg(STACK_ELEM x){
    if (x.t == LONG){
        return x.data.l;
    }
    else {
        return x.data.c;
    }
}

void sum(STACK *s) {
    STACK_ELEM x, y;

    assert(pop(s, &x) == 0);
    assert(pop(s, &y) == 0);

    STACK_ELEM result;
    
    if (x.t == DOUBLE || y.t == DOUBLE) {
        result.t = DOUBLE;
        result.data.d = get_double_arg(x) + get_double_arg(y);
    }
    else if (x.t == LONG || y.t == LONG) {
        result.t = LONG;
        result.data.l = get_long_arg(x) + get_long_arg(y);
    }
    else {
        result.t = CHAR;
        result.data.c = x.data.c + y.data.c;
    }

    push(s, result);
}

void sub(STACK *s) {
    STACK_ELEM x, y;
    
    assert(pop(s, &y) == 0);
    assert(pop(s, &x) == 0);

    STACK_ELEM result;

    if (x.t == DOUBLE || y.t == DOUBLE) {
        result.t = DOUBLE;
        result.data.d = get_double_arg(x) - get_double_arg(y);
    }
    else if (x.t == LONG || y.t == LONG) {
        result.t = LONG;
        result.data.l = get_long_arg(x) - get_long_arg(y);
    }
    else {
        result.t = CHAR;
        result.data.c = x.data.c - y.data.c;
    }

    push(s, result);
}

void mult(STACK *s) {
    STACK_ELEM x, y;
    
    assert(pop(s, &x) == 0);
    assert(pop(s, &y) == 0);

    STACK_ELEM result;
    
    if (x.t == DOUBLE || y.t == DOUBLE) {
        result.t = DOUBLE;
        result.data.d = get_double_arg(x) * get_double_arg(y);
    }
    else if (x.t == LONG || y.t == LONG) {
        result.t = LONG;
        result.data.l = get_long_arg(x) * get_long_arg(y);
    }
    else {
        result.t = CHAR;
        result.data.c = x.data.c * y.data.c;
    }

    push(s, result);
}

void divi(STACK *s) {
    STACK_ELEM x, y;
    
    assert(pop(s, &y) == 0);
    assert(pop(s, &x) == 0);

    STACK_ELEM result;

    if (x.t == DOUBLE || y.t == DOUBLE) {
        result.t = DOUBLE;
        result.data.d = get_double_arg(x) / get_double_arg(y);
    }
    else if (x.t == LONG || y.t == LONG) {
        result.t = LONG;
        result.data.l = get_long_arg(x) / get_long_arg(y);
    }
    else {
        result.t = CHAR;
        result.data.c = x.data.c / y.data.c;
    }

    push(s, result);
}

void rem(STACK *s) {
    STACK_ELEM x, y;
    
    assert(pop(s, &y) == 0);
    assert(pop(s, &x) == 0);

    STACK_ELEM result;

    if (x.t == LONG || y.t == LONG) {
        result.t = LONG;
        result.data.l = get_long_arg(x) % get_long_arg(y);
    }
    else {
        result.t = CHAR;
        result.data.c = x.data.c % y.data.c;
    }

    push(s, result);
}

void power(STACK *s) {
    STACK_ELEM x, y;
    
    assert(pop(s, &y) == 0);
    assert(pop(s, &x) == 0);

    STACK_ELEM result;

    if (x.t == DOUBLE || y.t == DOUBLE) {
        result.t = DOUBLE;
        result.data.d = pow(get_double_arg(x), get_double_arg(y));
    }
    else if (x.t == LONG || y.t == LONG) {
        result.t = LONG;
        result.data.l = (int) pow(get_long_arg(x), get_long_arg(y));
    }
    else {
        result.t = CHAR;
        result.data.c = (char) pow(x.data.c, y.data.c);
    }

    push(s, result);
}

void bw_xor(STACK *s) {
    STACK_ELEM x, y;
    
    assert(pop(s, &x) == 0);
    assert(pop(s, &y) == 0);

    STACK_ELEM result;

    if (x.t == LONG || y.t == LONG) {
        result.t = LONG;
        result.data.l = get_long_arg(x) ^ get_long_arg(y);
    }
    else {
        result.t = CHAR;
        result.data.c = x.data.c ^ y.data.c;
    }

    push(s, result);
}

void bw_and(STACK *s) {
    STACK_ELEM x, y;
    
    assert(pop(s, &x) == 0);
    assert(pop(s, &y) == 0);

    STACK_ELEM result;

    if (x.t == LONG || y.t == LONG) {
        result.t = LONG;
        result.data.l = get_long_arg(x) & get_long_arg(y);
    }
    else {
        result.t = CHAR;
        result.data.c = x.data.c & y.data.c;
    }

    push(s, result);
}

void bw_or(STACK *s) {
    STACK_ELEM x, y;
    
    assert(pop(s, &x) == 0);
    assert(pop(s, &y) == 0);

    STACK_ELEM result;

    if (x.t == LONG || y.t == LONG) {
        result.t = LONG;
        result.data.l = get_long_arg(x) | get_long_arg(y);
    }
    else {
        result.t = CHAR;
        result.data.c = x.data.c | y.data.c;
    }

    push(s, result);
}

void increment(STACK *s) {
    STACK_ELEM x;
    
    assert(pop(s, &x) == 0);
    
    STACK_ELEM result;

    if (x.t == DOUBLE) {
        result.t = DOUBLE;
        result.data.d = ++x.data.d;
    }
    else if (x.t == LONG) {
        result.t = LONG;
        result.data.l = ++x.data.l;
    }
    else {
        result.t = CHAR;
        result.data.c = ++x.data.c;
    }

    push(s, result);
}

void decrement(STACK *s) {
    STACK_ELEM x;
    
    assert(pop(s, &x) == 0);
    
    STACK_ELEM result;

    if (x.t == DOUBLE) {
        result.t = DOUBLE;
        result.data.d = --x.data.d;
    }
    else if (x.t == LONG) {
        result.t = LONG;
        result.data.l = --x.data.l;
    }
    else {
        result.t = CHAR;
        result.data.c = --x.data.c;
    }

    push(s, result);
}

void bw_not(STACK *s) {
    STACK_ELEM x;
    
    assert(pop(s, &x) == 0);
    
    STACK_ELEM result;

    if (x.t == LONG) {
        result.t = LONG;
        result.data.l = ~x.data.l;
    }
    else {
        result.t = CHAR;
        result.data.c = ~x.data.c;
    }

    push(s, result);
}
