#include "stack.h"
#include "operations.h"
#include "conversions.h"

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <math.h>

void convert_to_int(STACK *s, STACK_ELEM x, STACK_ELEM *result) {
    if (x.t == DOUBLE) {
        result->t = LONG;
        result->data.l = x.data.d;

        /*if(x.data.d != result->data.l){
            result->data.l=LONG_MAX;
        }*/

        push(s, *result);
    }
    else if (x.t == CHAR) {
        result->t = LONG;
        result->data.l = x.data.c;
        
        push(s, *result);
    }
    else if (x.t == STRING) {
        result->t = LONG;
        
        char *end_ptr;
        errno = 0;

        long value = strtol(x.data.s, &end_ptr, 0);
        
        if (errno == 0 && *end_ptr == '\0') {
            result->data.l = value;
        }
        
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
        
        char *end_ptr;
        errno = 0;

        double value = strtod(x.data.s, &end_ptr);
        
        if (errno == 0 && *end_ptr == '\0') {
            result->data.d = value;
        }
        
        push(s, *result);
    }
    // Conversão redundante
    else {
        push(s, x);
    }
}

void convert_to_char(STACK *s, STACK_ELEM x, STACK_ELEM *result) {
    if (x.t == DOUBLE){
        result->t=CHAR;
        result->data.c= (long)(x.data.d) % 256;
        push(s, *result);
    }
    else if (x.t == LONG) {
        result->t = CHAR;
        result->data.c = x.data.l % 256;
        
        push(s, *result);
    } 
    else if (x.t == STRING) {
        result->t = CHAR;
        result->data.c = x.data.s[0];
        
        push(s, *result);
    }
    // Conversão redundante
    else {
        push(s, x);
    }
}

void convert_to_string(STACK *s, STACK_ELEM x, STACK_ELEM *result) {
     if (x.t == LONG) {
        result->t = STRING;
        snprintf(result->data.s, MAX_BUFFER_SIZE, "%ld", x.data.l);
        
        push(s, *result);
    } 
    else if (x.t == DOUBLE) {
        result->t = STRING;
        snprintf(result->data.s, MAX_BUFFER_SIZE, "%lg", x.data.d);
        
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
