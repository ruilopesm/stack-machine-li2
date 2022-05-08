#include "stack.h"

#include <stdio.h>
#include <stdlib.h>

STACK *create_stack() {
    STACK *s = malloc(sizeof(STACK));
    s->sp = 0;
    s->size = 15000; //É criada uma stack com 15000 posições
    s->stc = calloc(sizeof(STACK_ELEM), s->size); // É alocada a memória necessária para todas esssas posições

    return s;
}

GLOBALS *init_globals() { //São inicializadas as globais com os valores predefinidos
    GLOBALS *g = malloc(sizeof(GLOBALS));

    for (int i = 0; i < 6; i++) {
        g->globals[i].t = LONG;
        g->globals[i].data.l = i + 10; //São inicializados os valores de A a F (10 a 15)
    }
    
    g->globals[13].t = CHAR;
    g->globals[13].data.c = '\n';
    g->globals[18].t = CHAR;
    g->globals[18].data.c = ' ';// São inicializados os valores de S e N (' ' e '\n', respetivamente)
    
    for (int i = 0; i < 3; i++) {
        g->globals[i + 23].t = LONG;
        g->globals[i + 23].data.l = i;//São inicializados os valores de X a Z (0 a 2)
    }

    return g;
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
    print_elems(s); // É necessária para não imprimir /n quando lê um array
    putchar('\n');
}

void print_elems(STACK *s) { //São imprimidos os valores da stack um a um
    for (int i = 0; i < s->sp; i++) {
        STACK_ELEM current = s->stc[i];

        if (current.t == LONG) {
            printf("%ld", current.data.l);
        }
        else if (current.t == CHAR) {
            printf("%c", current.data.c);
        }
        else if (current.t == DOUBLE) {
            printf("%lg", current.data.d);
        }
        else if (current.t == STRING) {
            printf("%s", current.data.s);
        }
        else if (current.t == ARRAY) {
            print_elems(current.data.a);// Se for encontrado um array, a função é chamada recursivamente de modo a imprimir os conteúdos no interior do mesmo
        }
        else if (current.t == BLOCK) {
            printf("{ %s }", current.data.b);
        }
    }
}

void free_stack(STACK *s) {
    // Procura por arrays para libertar
    for (int i = 0; i < s->sp; i++) {
        if (s->stc[i].t == ARRAY) {
            free_stack(s->stc[i].data.a);
        }
    }
    
    // De seguida liberta-se o outro conteúdo da stack
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
    s->stc[s->sp] = elem;//O elemento é colocado no topo da stack
    s->sp++; // O indicador do número de elementos atualmente na stack é aumentado por um

    return 0;
}

int pop(STACK *s, STACK_ELEM *elem) {
    // Se a stack estiver vazia: retorna 1 (ERRO)
    if (s->sp == 0) {
        return 1; 
    }
    s->sp--;// O indicador do número de elementos atualmente na stack é reduzido por um

    STACK_ELEM current = s->stc[s->sp];//O elemento do topo da stack é extraído para o endereço pretendido
    
    *elem = current;
    
    return 0;
}

int peek(STACK *s, STACK_ELEM *elem) {
    // Se a stack estiver vazia: retorna 1 (ERRO)
    if (s->sp == 0) {
        return 1;
    }
    *elem = s->stc[s->sp - 1];//O elemento do topo da stack é extraído para o endereço pretendido, sem alterar o mesmo

    return 0;
}

int nth_element(STACK *s, STACK_ELEM *elem, int n) { // Cria uma cópia do elemento localizado em determinada posição, sendo a posição 0 o topo da stack
    if (s->sp == 0) {
        return 1;
    }
    *elem = s->stc[s->sp - n - 1];//O elemento na posição indicada é extraído para o endereço pretendido, sem alterar o mesmo

    return 0;
}
