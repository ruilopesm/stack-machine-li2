#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "stack.h"
#include "parser.h"

int main() {
    STACK *s = create_stack();

    parse_line(s);

    print_stack(s);
    
    free_stack(s);

    return 0;
}
