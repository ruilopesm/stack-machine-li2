#include <stdio.h>
#include <stdlib.h>

#include "stack.h"

int main() {
    STACK *s = create_stack();

    if (push(s, 3)){}
    if (push(s, 2)){}
    int x,y;
    if(pop(s,&x)){}
    if(pop(s,&y)){}
    int soma = x + y;

    printf("%d\n", soma);
    return 0;
}
