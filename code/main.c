#include <stdio.h>
#include <stdlib.h>

#include "stack.h"
#include "operations.h"

int main() {
    STACK *s = create_stack();

    push(s, 2);
    push(s, 3); 

    dispatch_table(s, '+'); 

    // Print stack content
    for (int i = 0; i < s->sp; i++) {
        printf("%d\n", s->stc[i]);
    }
    
    free_stack(s);

    return 0;
}
