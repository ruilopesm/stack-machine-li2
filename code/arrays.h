/**
 * @brief Função que concatena dois arrays 
 * 
 * @param y array
 * @param x array
 * @param result STACK_ELEM onde irá ser guardado o resultado 
 * @param order 
 */
void concatenate_two_arrays(STACK_ELEM y, STACK_ELEM x, STACK_ELEM *result, int order);

/**
 * @brief Função que replica um array
 * 
 * @param x array
 * @param y array
 * @param result STACK_ELEM onde irá ser guardado o resultado 
 */
void replicate_array(STACK_ELEM x, STACK_ELEM y, STACK_ELEM *result);

/**
 * @brief Função que remove o elemento que se encontra no final de um array 
 * 
 * @param s Apontador para a STACK
 * @param x array
 * @param result STACK_ELEM onde irá ser guardado o resultado 
 */
void remove_first_element_from_array(STACK *s, STACK_ELEM x, STACK_ELEM *result);

/**
 * @brief Função que remove o elemento que se encontra no final de um array 
 * 
 * @param s Apontador para a STACK
 * @param x array
 * @param result STACK_ELEM onde irá ser guardado o resultado 
 */
void remove_last_element_from_array(STACK *s, STACK_ELEM x, STACK_ELEM *result);

/**
 * @brief Função que transfere os valores de um array para a STACK
 * 
 * @param s Apontador para a STACK
 * @param x array
 */
void transfer_array_elements_to_stack(STACK *s, STACK_ELEM x);

/**
 * @brief Função que obtem o elemento que se encontra no index dado
 * 
 * @param s Apontador para a STACK
 * @param x index
 * @param y array
 * @param result STACK_ELEM onde irá ser guardado o resultado 
 */
void get_element_at_index(STACK *s, STACK_ELEM x, STACK_ELEM y, STACK_ELEM *result);

/**
 * @brief Função que obtem os elemento de um array
 * 
 * @param s Apontador para a STACK
 * @param x tamanho
 * @param y array
 * @param result STACK_ELEM onde irá ser guardado o resultado 
 */
void take_from_array(STACK_ELEM x, STACK_ELEM y, STACK_ELEM *result);

/**
 * @brief Função que remove um elemento de um array
 * 
 * @param x array
 * @param y tamanho
 * @param result STACK_ELEM onde irá ser guardado o resultado 
 */
void drop_from_array(STACK_ELEM x, STACK_ELEM y, STACK_ELEM *result);

/**
 * @brief Função que cria um array com um determinado alcance
 * 
 * @param x alcance
 * @param result STACK_ELEM onde irá ser guardado o resultado 
 */
void create_array_in_range(STACK_ELEM x, STACK_ELEM *result);
