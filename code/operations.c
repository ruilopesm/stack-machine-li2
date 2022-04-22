#include "stack.h"
#include "operations.h"
#include "parser.h"

#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>

char const *get_operator(int i) {
    static char const* const operators[N_OPERATORS] = {
        "+",
        "-",
        "*",
        "/",
        "%",
        "#",
        "^",
        "&",
        "|",
        ")",
        "(",
        "~",
        "i",
        "f",
        "c",
        "s",
        "_",
        ";",
        "\\",
        "@",
        "$",
        "l"
    };

    return operators[i];
}

int is_operator(char *token) {
    for (int i = 0; i < N_OPERATORS; i++) {
        if (strcmp(token, get_operator(i)) == 0) {
            return 1;
        }
    }

    return 0;
}

int get_index(char const *operator) {
    int index = -1;

    for (int i = 0; i < N_OPERATORS; i++) {
        if (strcmp(operator, get_operator(i)) == 0) {
            index = i;
        }
    }

    // Caso o operador não tenha sido encontrado: retorna -1 (ERRO)
    return index;
}

void dispatch_table(STACK *s, char const *operator) {
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
        bw_not,
        conv_int,
        conv_double,
        conv_char,
        conv_str,
        duplicate,
        other_pop,
        swap,
        rotate,
        copy_nth,
        read_line
    }; // As funções até agora implementadas são colocadas em posições análogas às referenciadas na função 'get_operator'.

    int index = get_index(operator);

    // Chama o function pointer
    table[index](s);
}

double get_double_arg(STACK_ELEM x) {
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

long get_long_arg(STACK_ELEM x) {
    if (x.t == LONG) {
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
        result.data.l = (int)pow(get_long_arg(x), get_long_arg(y));
    } 
    else {
        result.t = CHAR;
        result.data.c = (char)pow(x.data.c, y.data.c);
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

void conv_int(STACK *s) {
    STACK_ELEM x;
    
    assert(pop(s, &x) == 0);
    
    STACK_ELEM result;

    if (x.t == DOUBLE) {
        result.t = LONG;
        result.data.l = x.data.d;
        push(s, result);
    } 
    else if (x.t == CHAR) {
        result.t = LONG;
        result.data.l = x.data.c;
        push(s, result);
    } 
    else if (x.t == STRING) {
        result.t = LONG;
        sscanf(x.data.s, "%ld", &result.data.l);
    }
    // Conversão redundante
    else {
        push(s, x);
    }
}

void conv_double(STACK *s) {
    STACK_ELEM x;
    
    assert(pop(s, &x) == 0);
    
    STACK_ELEM result;

    if (x.t == LONG) {
        result.t = DOUBLE;
        result.data.d = x.data.l;
        push(s, result);
    } 
    else if (x.t == CHAR) {
        result.t = DOUBLE;
        result.data.d = x.data.c;
        push(s, result);
    } 
    else if (x.t == STRING) {
        result.t = DOUBLE;
        sscanf(x.data.s, "%lg", &result.data.d);
    }
    // Conversão redundante
    else {
        push(s, x);
    }
}

void conv_char(STACK *s) {
    STACK_ELEM x;
    
    assert(pop(s, &x) == 0);
    
    STACK_ELEM result;

    if (x.t == LONG) {
        result.t = CHAR;
        result.data.c = x.data.l % 256;
        push(s, result);
    } 
    else if (x.t == STRING) {
        result.t = CHAR;
        result.data.c = x.data.s[0];
        push(s, result);
    } 
    else {
        push(s, x);
    }
}

void conv_str(STACK *s) {
    STACK_ELEM x;
    
    assert(pop(s, &x) == 0);
    
    STACK_ELEM result;
    result.data.s = NULL;

    if (x.t == LONG) {
        result.t = STRING;
        snprintf(result.data.s, BUFSIZ, "%ld", x.data.l);
        push(s, result);
    } 
    else if (x.t == DOUBLE) {
        result.t = STRING;
        snprintf(result.data.s, BUFSIZ, "%lg", x.data.d);
        push(s, result);
    } 
    else if (x.t == CHAR) {
        result.t = STRING;
        result.data.s[0] = x.data.c;
        result.data.s[1] = '\0';
        push(s, result);
    } 
    else {
        push(s, x);
    }
}

void duplicate(STACK *s) {
    STACK_ELEM x;
    
    assert(pop(s, &x) == 0);
    
    assert(push(s, x) == 0);
    assert(push(s, x) == 0);
}

void other_pop(STACK *s) {
    STACK_ELEM x;
    
    assert(pop(s, &x) == 0);
}

void swap(STACK *s) {
    STACK_ELEM x, y;

    assert(pop(s, &x) == 0);
    assert(pop(s, &y) == 0);

    assert(push(s, x) == 0);
    assert(push(s, y) == 0);
}

void rotate(STACK *s) {
    STACK_ELEM x, y, z;

    assert(pop(s, &x) == 0);
    assert(pop(s, &y) == 0);
    assert(pop(s, &z) == 0);

    assert(push(s, y) == 0);
    assert(push(s, x) == 0);
    assert(push(s, z) == 0);   
}

void copy_nth(STACK *s) {
    STACK_ELEM x;

    assert(pop(s, &x) == 0);

    int n = x.data.l;
    STACK_ELEM result;
    assert(nth_element(s, &result, n) == 0);

    assert(push(s, result) == 0);
}

void read_line(STACK *s) {
    parse_line(s);
}
