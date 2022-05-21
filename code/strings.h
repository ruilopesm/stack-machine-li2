#ifndef STRINGS_H
#define STRINGS_H

/**
 * @brief Função que concatena duas strings
 * 
 * @param y 
 * @param x 
 * @param result 
 */
void concatenate_two_strings(STACK_ELEM y, STACK_ELEM x, STACK_ELEM *result);

/**
 * @brief Função que concatena as duas substrings dependendo da ordem pretendida
 * 
 * @param y 
 * @param x 
 * @param result 
 * @param order 
 */
void concatenate_two_strings_aux(STACK_ELEM y, STACK_ELEM x, STACK_ELEM *result, int order);

/**
 * @brief Função que replica uma string
 * 
 * @param x 
 * @param y 
 * @param result 
 */
void replicate_string(STACK_ELEM x, STACK_ELEM y, STACK_ELEM *result);

/**
 * @brief Função que separa uma string em substrings
 * 
 * @param main 
 * @param sub 
 * @param new 
 */
void split_string_by_substring(STACK_ELEM *main, STACK_ELEM *sub, STACK *new);

/**
 * @brief Função que obtém o indix de uma substring
 * 
 * @param x 
 * @param y 
 * @param result 
 */
void find_substring_index(STACK_ELEM x, STACK_ELEM y, STACK_ELEM *result);

/**
 * @brief Função que remove o char que se encontra no inicio de uma string
 * 
 * @param s 
 * @param x 
 * @param result 
 */
void remove_first_element_from_string(STACK *s, STACK_ELEM x, STACK_ELEM *result);

/**
 * @brief Função que remove o char que se encontra no final de uma string
 * 
 * @param s 
 * @param x 
 * @param result 
 */
void remove_last_element_from_string(STACK *s, STACK_ELEM x, STACK_ELEM *result);

/**
 * @brief Função que obtem o char que se encontra no index dado
 * 
 * @param s 
 * @param x 
 * @param y 
 * @param result 
 */
void get_char_at_index(STACK *s, STACK_ELEM x, STACK_ELEM y, STACK_ELEM *result);

/**
 * @brief Função que verifica a igualdade entre duas strings
 * 
 * @param s 
 * @param x 
 * @param y 
 * @param result 
 */
void check_strings_equality(STACK *s, STACK_ELEM x, STACK_ELEM y, STACK_ELEM *result);

/**
 * @brief Função que verifica se uma string é menor que outra
 * 
 * @param s 
 * @param x 
 * @param y 
 * @param result 
 */
void check_strings_less(STACK *s, STACK_ELEM x, STACK_ELEM y, STACK_ELEM *result);

/**
 * @brief Função que obtem os elemento de uma string
 * 
 * @param s 
 * @param x 
 * @param y 
 * @param result 
 */
void take_from_string(STACK *s, STACK_ELEM x, STACK_ELEM y, STACK_ELEM *result);

/**
 * @brief Função que verifica se uma string é maoir que outra
 * 
 * @param s 
 * @param x 
 * @param y 
 * @param result 
 */
void check_strings_more(STACK *s, STACK_ELEM x, STACK_ELEM y, STACK_ELEM *result);

/**
 * @brief Função que remove um elemento de uma string
 * 
 * @param s 
 * @param x 
 * @param y 
 * @param result 
 */
void drop_from_string(STACK *s, STACK_ELEM x, STACK_ELEM y, STACK_ELEM *result);

#endif
