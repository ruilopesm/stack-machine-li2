/**
 * @brief Função que executa a adiçao de dois números
 * 
 * @param x 1º numero a ser somado
 * @param y 2º numero  ser somado
 * @param result STACK_ELEMENT onde irá ser guardado o resultado
 */
void sum_two_numbers(STACK_ELEM x, STACK_ELEM y, STACK_ELEM *result);

/**
 * @brief Função que executa a subtração de dois números
 * 
 * @param x diminuendo
 * @param y diminuidor
 * @param result STACK_ELEMENT onde irá ser guardado o resultado
 */
void subtract_two_numbers(STACK_ELEM x, STACK_ELEM y, STACK_ELEM *result);


/**
 * @brief Função que executa a multiplicação de dois números
 * 
 * @param x 1º numero a ser multiplicado
 * @param y 2º numero  ser multiplicado
 * @param result STACK_ELEMENT onde irá ser guardado o resultado
 */
void multiply_two_numbers(STACK_ELEM x, STACK_ELEM y, STACK_ELEM *result);

void divide_two_numbers(STACK_ELEM x, STACK_ELEM y, STACK_ELEM *result);

void remainder_two_numbers(STACK_ELEM x, STACK_ELEM y, STACK_ELEM *result);

void power_two_numbers(STACK_ELEM x, STACK_ELEM y, STACK_ELEM *result);

void bitwise_xor_two_numbers(STACK_ELEM x, STACK_ELEM y, STACK_ELEM *result);

void bitwise_or_two_numbers(STACK_ELEM x, STACK_ELEM y, STACK_ELEM *result);

void bitwise_and_two_numbers(STACK_ELEM x, STACK_ELEM y, STACK_ELEM *result);

void increment_number(STACK_ELEM x, STACK_ELEM *result);

void decrement_number(STACK_ELEM x, STACK_ELEM *result);

void bitwise_not_one_number(STACK *s, STACK_ELEM x, STACK_ELEM *result);

void compare_two_numbers_equality(STACK *s, STACK_ELEM x, STACK_ELEM y, long to_push, STACK_ELEM *result);

void compare_two_numbers_less(STACK *s, STACK_ELEM x, STACK_ELEM y, long to_push, STACK_ELEM *result);

void compare_two_numbers_more(STACK *s, STACK_ELEM x, STACK_ELEM y, long to_push, STACK_ELEM *result);
