void map_array(STACK_ELEM x, STACK_ELEM y, STACK_ELEM *result, GLOBALS *g);

void map_string(STACK_ELEM x, STACK_ELEM y, STACK_ELEM *result, GLOBALS *g);

void fold(STACK_ELEM x, STACK_ELEM y, STACK_ELEM *result, GLOBALS *g);

void filter(STACK_ELEM x, STACK_ELEM y, STACK_ELEM *result, GLOBALS *g);

void filter_array(STACK_ELEM x, STACK_ELEM y, STACK_ELEM *result, GLOBALS *g);

void filter_string(STACK_ELEM x, STACK_ELEM y, STACK_ELEM *result, GLOBALS *g);

void while_operation(STACK *s, STACK_ELEM x, GLOBALS *g);