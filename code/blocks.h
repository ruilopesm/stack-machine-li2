#ifndef BLOCKS_H
#define BLOCKS_H

/**
 * @brief Função que determina o tipo do argumento, e dependedendo deste aplica as funções de map
 * 
 * @param x 
 * @param y 
 * @param result 
 * @param g 
 */
void map(STACK_ELEM x, STACK_ELEM y, STACK_ELEM *result, GLOBALS *g);

/**
 * @brief Função que aplica um bloco a todos os elementos de um array
 * 
 * @param x 
 * @param y 
 * @param result 
 * @param g 
 */
void map_array(STACK_ELEM x, STACK_ELEM y, STACK_ELEM *result, GLOBALS *g);

/**
 * @brief Função que aplica um bloco a todos os elementos de uma string 
 * 
 * @param x 
 * @param y 
 * @param result 
 * @param g 
 */
void map_string(STACK_ELEM x, STACK_ELEM y, STACK_ELEM *result, GLOBALS *g);

/**
 * @brief Função que aplica um fold sobre um array usando um bloco
 * 
 * @param x 
 * @param y 
 * @param result 
 * @param g 
 */
void fold(STACK_ELEM x, STACK_ELEM y, STACK_ELEM *result, GLOBALS *g);

/**
 * @brief Função que determina o tipo do argumento, e dependedendo deste aplica as funções de filtro 
 * 
 * @param x 
 * @param y 
 * @param result 
 * @param g 
 */
void filter(STACK_ELEM x, STACK_ELEM y, STACK_ELEM *result, GLOBALS *g);

/**
 * @brief Função que filtra um array conforme uma condição
 * 
 * @param x 
 * @param y 
 * @param result 
 * @param g 
 */
void filter_array(STACK_ELEM x, STACK_ELEM y, STACK_ELEM *result, GLOBALS *g);

/**
 * @brief Função que filtra uma string conforme uma condição
 * 
 * @param x 
 * @param y 
 * @param result 
 * @param g 
 */
void filter_string(STACK_ELEM x, STACK_ELEM y, STACK_ELEM *result, GLOBALS *g);

/**
 * @brief Função que compara dois arrays e retorna 0 se x for menor ou igual a y, 1 se o contrário se verificar
 * 
 * @param x 
 * @param y 
 * @param temp 
 * @param block 
 * @param g 
 * @return int 
 */
int compare_on(STACK_ELEM x,STACK_ELEM y,STACK *temp, char *block,GLOBALS *g);

/**
 * @brief Função que compara dois arrays
 * 
 * @param x 
 * @param y 
 * @return int 
 */
int compare_arrays(STACK *x, STACK *y);

/**
 * @brief Função que ordena um array segundo a condição dada por um bloco
 * 
 * @param block 
 * @param array 
 * @param g 
 */
void sort_on(STACK_ELEM block,STACK_ELEM *array,GLOBALS *g);

/**
 * @brief Função que realiza um loop while para percorrer um bloco
 * 
 * @param s 
 * @param x 
 * @param g 
 */
void while_operation(STACK *s, STACK_ELEM x, GLOBALS *g);

/**
 * @brief Função que verifica se o elemento é verdadeiro
 * 
 * @param x Elemento a verificar
 * @return int 
 */
int truthy_value(STACK_ELEM x);

/**
 * @brief Função que verifica se um elemento é argumento, se o elemento é um char/long/double
 * 
 * @param x Elemento a verificar
 * @return int 
 */
int is_arg(STACK_ELEM x);

int all_char(STACK_ELEM x);

#endif
