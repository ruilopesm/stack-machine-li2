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

