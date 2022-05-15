#ifndef CONVERSIONS_H
#define CONVERSIONS_H

/**
 * @brief Função que converte os argumentos para ints
 * 
 * @param s 
 * @param x 
 * @param result 
 */
void convert_to_int(STACK *s, STACK_ELEM x, STACK_ELEM *result);

/**
 * @brief Função que converte os argumentos para doubles
 * 
 * @param s 
 * @param x 
 * @param result 
 */
void convert_to_double(STACK *s, STACK_ELEM x, STACK_ELEM *result);

/**
 * @brief Função que converte os argumentos para chars
 * 
 * @param s 
 * @param x 
 * @param result 
 */
void convert_to_char(STACK *s, STACK_ELEM x, STACK_ELEM *result);

/**
 * @brief Função que converte os argumentos para strings
 * 
 * @param s 
 * @param x 
 * @param result 
 */
void convert_to_string(STACK *s, STACK_ELEM x, STACK_ELEM *result);

#endif
