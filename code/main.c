#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "stack.h"

int main() {
    STACK *s = create_stack();

    assert(push(s, 3) == 0);
    assert(push(s, 2) == 0);

    int x, y;
    assert(pop(s, &x) == 0);
    assert(pop(s, &y) == 0);

    printf("%d\n", x + y);

    free_stack(s);

    return 0;
}