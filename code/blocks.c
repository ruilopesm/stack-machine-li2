#include "stack.h"
#include "parser.h"
#include "operations.h"
#include "blocks.h"
#include "conversions.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

void map_array(STACK_ELEM x, STACK_ELEM y, STACK_ELEM *result, GLOBALS *g) {

    STACK *array_map = create_stack();

    for (int i = 0; i < x.data.a->sp; i++) {
        push(array_map, x.data.a->stc[i]);
        parse_line(array_map, y.data.b, g);
    }

    result->t = ARRAY;
    result->data.a = array_map;
}

void map_string(STACK_ELEM x, STACK_ELEM y, STACK_ELEM *result, GLOBALS *g) {
    char *str = malloc((strlen(x.data.s) + 1) * sizeof(char)), *start = str;
    strcpy(str, x.data.s);

    STACK *string_map = create_stack();
    STACK_ELEM aux;
    aux.t = CHAR;

    for (char c = *str; c != '\0'; c = *++str) {
        aux.data.c = c;
        push(string_map, aux);
        parse_line(string_map, y.data.b, g);
    }

    str = start;

    for (int i = 0; i < string_map->sp; i++) {
        aux = string_map->stc[i];
        *str++ = aux.data.c;
    }

    *str = '\0';

    result->t = STRING;
    result->data.s = start;
    free_stack(string_map);
}

void fold(STACK_ELEM x, STACK_ELEM y, STACK_ELEM *result, GLOBALS *g) {

    STACK *array_fold = create_stack();
    STACK_ELEM acc = x.data.a->stc[0];
    push(array_fold, acc);

    for (int i = 1; i < x.data.a->sp; i++) {
        push(array_fold, x.data.a->stc[i]);
        parse_line(array_fold, y.data.b, g);
    }

    assert(pop(array_fold, &acc) == 0);

    *result = acc;
}

void filter(STACK_ELEM x, STACK_ELEM y, STACK_ELEM *result, GLOBALS *g) {
    if (x.t == ARRAY)
        filter_array(x, y, result, g);
    else
        filter_string(x, y, result, g);
}

void filter_array(STACK_ELEM x, STACK_ELEM y, STACK_ELEM *result, GLOBALS *g) {

    STACK *array_filter = create_stack();
    STACK_ELEM aux;

    for (int i = 0; i < x.data.a->sp; i++) {
        push(array_filter, x.data.a->stc[i]);
        parse_line(array_filter, y.data.b, g);
        assert(pop(array_filter, &aux) == 0);
        if (aux.data.l || aux.data.d) {
            push(array_filter, x.data.a->stc[i]);
        }
    }

    result->t = ARRAY;
    result->data.a = array_filter;
}

void filter_string(STACK_ELEM x, STACK_ELEM y, STACK_ELEM *result, GLOBALS *g) {
    char *str = malloc((strlen(x.data.s) + 1) * sizeof(char)), *start = str;
    strcpy(str, x.data.s);

    STACK *string_filter = create_stack();
    STACK_ELEM aux;
    aux.t = CHAR;

    for (char c = *str; c != '\0'; c = *++str) {
        aux.data.c = c;
        push(string_filter, aux);
        parse_line(string_filter, y.data.b, g);
        assert(pop(string_filter, &aux) == 0);
        if (aux.data.c) {
            push(string_filter, aux);
        }
    }

    str = start;

    for (int i = 0; i < string_filter->sp; i++) {
        aux = string_filter->stc[i];
        *str++ = aux.data.c;
    }

    *str = '\0';

    result->t = STRING;
    result->data.s = start;
    free_stack(string_filter);
}
