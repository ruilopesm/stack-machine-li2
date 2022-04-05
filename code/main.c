#include <stdio.h>
#include <stdlib.h>

#include "stack.h"

int main() {
    STACK *s = create_stack();

    push(s, 3);
    push(s, 2);

    int soma = pop(s) + pop(s);

    printf("%d\n", soma);
    return 0;
}
