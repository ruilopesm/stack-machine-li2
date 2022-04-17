#include "stack.h"

#include <stdio.h>
#include <stdlib.h>

STACK *create_stack() {
    STACK *s = malloc(sizeof(STACK));
    s->sp = 0;
    s->size = 100;
    s->stc = calloc(sizeof(STACK_ELEM), s->size);

    return s;
}

int increase_stack(STACK *s) {
    // Se a realocação da stack falhar: retorna 1 (ERRO)
    if ((s->stc = realloc(s->stc, sizeof(s->stc) * 2)) == NULL) {
        return 1;
    }
    s->size *= 2;

    return 0;
}

void print_stack(STACK *s) {
    for (int i = 0; i < s->sp; i++) {
        STACK_ELEM current = s->stc[i];

        if (current.t == LONG) {
            printf("%ld", current.data.l);
            // Testing purposes
            printf("The result is a long!\n");
        }
        else if (current.t == CHAR) {
            printf("%c", current.data.c);
        }
        else if (current.t == DOUBLE) {
            printf("%lg", current.data.d);
            // Testing purposes
            printf("\nThe result is a double!\n");
        }
    }
    putchar('\n');
}

void free_stack(STACK *s) {
    // Inicialmente liberta-se o conteúdo da stack
    free(s->stc);
    
    // Finalmente liberta-se a estrutura da stack
    free(s);
}

int push(STACK *s, STACK_ELEM elem) {
    if (s->sp == s->size) { 
        // Se não for possível duplicar o tamanho da stack: retorna 1 (ERRO)
        if (increase_stack(s)) { 
            return 1; 
        }
    }
    s->stc[s->sp] = elem;
    s->sp++;

    return 0;
}

int pop(STACK *s, STACK_ELEM *elem) {
    // Se a stack estiver vazia: retorna 1 (ERRO)
    if (s->sp == 0) {
        return 1; 
    }
    s->sp--;
    *elem = s->stc[s->sp];

    return 0;
}

int peek(STACK *s, STACK_ELEM *elem) {
    // Se a stack estiver vazia: retorna 1 (ERRO)
    if (s->sp == 0) {
        return 1;
    }
    *elem = s->stc[s->sp];

    return 0;
}
