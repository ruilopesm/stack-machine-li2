#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "stack.h"
#include "operations.h"

int main() {
    STACK *s = create_stack();

    assert(push(s, 2) == 0);
    assert(push(s, 3) == 0); 

    dispatch_table(s, '+'); 

    // Print stack content
    for (int i = 0; i < s->sp; i++) {
        printf("%d\n", s->stc[i]);
    }
    
    free_stack(s);

    return 0;
}
