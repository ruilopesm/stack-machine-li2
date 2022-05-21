#ifndef CONVERSIONS_H
#define CONVERSIONS_H

/**
 * @brief Função que converte os argumentos para ints
 * 
 * @param s  Apontador para a STACK
 * @param x argumento
 * @param result STACK_ELEM onde irá ser guardado o resultado 
 */
void convert_to_int(STACK *s, STACK_ELEM x, STACK_ELEM *result);

/**
 * @brief Função que converte os argumentos para doubles
 * 
 * @param s  Apontador para a STACK
 * @param x argumento
 * @param result STACK_ELEM onde irá ser guardado o resultado 
 */
void convert_to_double(STACK *s, STACK_ELEM x, STACK_ELEM *result);

/**
 * @brief Função que converte os argumentos para chars
 * 
 * @param s  Apontador para a STACK
 * @param x argumento
 * @param result STACK_ELEM onde irá ser guardado o resultado 
 */
void convert_to_char(STACK *s, STACK_ELEM x, STACK_ELEM *result);

/**
 * @brief Função que converte os argumentos para strings
 * 
 * @param s  Apontador para a STACK
 * @param x argumento
 * @param result STACK_ELEM onde irá ser guardado o resultado 
 */
void convert_to_string(STACK *s, STACK_ELEM x, STACK_ELEM *result);

/**
 * @brief Função que converte os argumentos para array
 * 
 * @param x argumento
 * @param result STACK_ELEM onde irá ser guardado o resultado
 */
void convert_to_array(STACK_ELEM x, STACK_ELEM *result);

/**
 * @brief Função que converte o argumento para string
 * 
 * @param x argumento
 * @param result STACK_ELEM onde irá ser guardado o resultado 
 */
void convert_array_to_string(STACK_ELEM x, STACK_ELEM *result);

#endif
