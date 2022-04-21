#include "types.h"

/**
 * @brief Inicializa uma stack com 100 posições
 * 
 * @return STACK* 
 */
STACK *create_stack();

/**
 * @brief Aumenta o tamanho da stack (para o dobro), se possível
 * 
 * @param s Apontador para a stack
 * @return int 
 */
int increase_stack(STACK *s);

/**
 * @brief Imprime todos os elementos da stack, começando pelo elemento do fundo e acabando no do topo
 * 
 * @param s Apontador para a stack
 */
void print_stack(STACK *s);

/**
 * @brief Liberta a memória alocada, na heap, pela stack
 * 
 * @param s Apontador para a stack
 */
void free_stack(STACK *s);

/**
 * @brief Adiciona um elemento à stack, se possível
 * 
 * @param s Apontador para a stack
 * @param elem Elemento a ser adicionado à stack
 * @return int 
 */
int push(STACK *s, STACK_ELEM elem);

/**
 * @brief Retira o elemento que está no topo da stack
 * 
 * @param s Apontador para a stack
 * @param elem Apontador para o elemento que será retirado
 * @return int 
 */
int pop(STACK *s, STACK_ELEM *elem);

/**
 * @brief Encontra o elemento no topo da stack, mas não o retiro (ao contrário da 'pop')
 * 
 * @param s Apontador para a stack
 * @param elem Apontador para o elemento que receberá o conteúdo do topo da stack
 * @return int 
 */
int peek(STACK *s, STACK_ELEM *elem);

int nth_element(STACK *s, STACK_ELEM *elem, int n);
