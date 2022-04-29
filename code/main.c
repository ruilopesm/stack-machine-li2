#include "stack.h"
#include "parser.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/**
 * @brief Função principal do programa
 * 
 * @return int 
 */
int main() {
    STACK *s = create_stack();

    get_line(s);

    print_stack(s);
    
    free_stack(s);

    return 0;
}
