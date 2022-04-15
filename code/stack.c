#include "stack.h"

#include <stdio.h>
#include <stdlib.h>

/**
 * @brief Inicializa uma stack de tamanho 100
 * 
 * @return STACK* 
 */
STACK *create_stack() {
    STACK *s = malloc(sizeof(STACK));
    s->sp = 0;
    s->size = 100;
    s->stc = calloc(sizeof(int), s->size);

    return s;
}

/**
 * @brief Aumenta o tamanho da stack, se possível
 * 
 * @param s Stack que é necessário aumentar
 * @return int 
 */
int increase_stack(STACK *s) {
    if ((s->stc = realloc(s->stc, sizeof(s->stc) * 2)) == NULL) {
        return 1; // Se a alocação do dobro da memória atual da stack falhar, retorna 1 (erro)
    }
    s->size *= 2; //Se a duplicação de memória for bem sucedida, duplica o indicador do tamanho máximo de objetos na stack

    return 0; // Se a duplicação for bem sucedida, a função retorna 0.
}
/**
 * @brief Imprime todos os elementos da stack, começando pelo elemento do fundo e acabando no do topo
 * 
 * @param s Stack cujos elementos serão apresentados
 */
void print_stack(STACK *s) {
    for (int i = 0; i < s->sp; i++) {
        printf("%d", s->stc[i]); // Desde o início do array (fundo da stack) até ao valor de sp (topo da stack), os elementos vão sendo imprimidos um a um
    }
    putchar('\n'); //A linha é terminada
}

/**
 * @brief Libertar a stack de memória
 * 
 * @param s Stack a ser eliminada
 */
void free_stack(STACK *s) {
    free(s->stc); //Inicialmente é libertada toda a memória dos conteúdos da stack
    free(s); //De seguida são eliminadas as outras informações da stack (tamanho atual, tamanho max)
}

/**
 * @brief Adiciona um elemento à stack, se possível
 * 
 * @param s Stack onde o elemento será adicionado
 * @param elem Elemento a ser adicionado à stack
 * @return int 
 */
int push(STACK *s, int elem) {
    if (s->sp == s->size) { 
        if (increase_stack(s)) { //Se a stack atingir o seu limite máximo, tenta-se duplicar o seu tamanho
            return 1; //Se não for possível duplicar o tamanho da stack, a função retorna 1 (erro)
        }
    }
    s->stc[s->sp] = elem; //O elemento é adicionado ao topo da stack
    s->sp++;//O tamanho atual da stack é aumentado

    return 0;
}

/**
 * @brief Retira o elemento mais acima na stack (mais recente)
 * 
 * @param s Stack de onde o elemento é retirado
 * @param elem Pointer para o elemento que será retirado
 * @return int 
 */
int pop(STACK *s, int *elem) {
    if (s->sp == 0) {
        return 1; //Se a stack for vazia, a função irá retornar 1 (erro)
    }
    s->sp--; // O tamanho da stack é reduzido por 1
    *elem = s->stc[s->sp];// O pointer introduzido como argumento passará a apontar para o elemento que foi retirado

    return 0;
}

/**
 * @brief Encontra o elemento mais acima na stack, sem o retirar
 * 
 * @param s 
 * @param elem 
 * @return int 
 */
int peek(STACK *s, int *elem) {
    if (s->sp == 0) {
        return 1;//Se a stack for vazia, a função irá retornar 1 (erro)
    }
    *elem = s->stc[s->sp];// O pointer introduzido como argumento passará a apontar para o elemento no topo da stack

    return 0;
}
