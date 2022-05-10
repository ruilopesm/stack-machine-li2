#include "stack.h"
#include "operations.h"
#include "conversions.h"

#include <stdio.h>
#include <stdlib.h>

void convert_to_int(STACK *s, STACK_ELEM x, STACK_ELEM *result) {
    if (x.t == DOUBLE) {
        result->t = LONG;
        result->data.l = x.data.d;
        push(s, *result);
    }
    else if (x.t == CHAR) {
        result->t = LONG;
        result->data.l = x.data.c;
        push(s, *result);
    }
    else if (x.t == STRING) {
        result->t = LONG;
        sscanf(x.data.s, "%ld", &result->data.l);
        push(s, *result);
    }
    // Conversão redundante
    else {
        push(s, x);
    } 
}

void convert_to_double(STACK *s, STACK_ELEM x, STACK_ELEM *result) {
    if (x.t == LONG) {
        result->t = DOUBLE;
        result->data.d = x.data.l;
        push(s, *result);
    } 
    else if (x.t == CHAR) {
        result->t = DOUBLE;
        result->data.d = x.data.c;
        push(s, *result);
    } 
    else if (x.t == STRING) {
        result->t = DOUBLE;
        sscanf(x.data.s, "%lg", &result->data.d);
        push(s, *result);
    }
    // Conversão redundante
    else {
        push(s, x);
    }
}

void convert_to_char(STACK *s, STACK_ELEM x, STACK_ELEM *result) {
    if (x.t == LONG) {
        result->t = CHAR;
        result->data.c = x.data.l % 256;
        push(s, *result);
    } 
    else if (x.t == STRING) {
        result->t = CHAR;
        result->data.c = x.data.s[0];
        push(s, *result);
    } 
    else {
        push(s, x);
    }
}

void convert_to_string(STACK *s, STACK_ELEM x, STACK_ELEM *result) {
     if (x.t == LONG) {
        result->t = STRING;
        snprintf(result->data.s, BUFSIZ, "%ld", x.data.l);
        push(s, *result);
    } 
    else if (x.t == DOUBLE) {
        result->t = STRING;
        snprintf(result->data.s, BUFSIZ, "%lg", x.data.d);
        push(s, *result);
    } 
    else if (x.t == CHAR) {
        result->t = STRING;
        result->data.s[0] = x.data.c;
        result->data.s[1] = '\0';
        push(s, *result);
    } 
    else {
        push(s, x);
    }
}

