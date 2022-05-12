#include "stack.h"
#include "parser.h"
#include "operations.h"
#include "blocks.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void map_array(STACK_ELEM x, STACK_ELEM y, STACK_ELEM *result, GLOBALS *g) {
    result->t = ARRAY;

    STACK *array_map = create_stack();

    for (int i = 0; i < x.data.a->sp; i++) {
        push(array_map, x.data.a->stc[i]);
        parse_line(array_map, y.data.b, g);
    }

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
