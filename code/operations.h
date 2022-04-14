#define N_OPERATORS 12

/**
 * @brief Função que retorna o operador associado ao índice dado.
 * 
 * @param i O índice.
 * @return char 
 */
char get_operator(int i);

/**
 * @brief Função que verifica se um dado char é um operador.
 * 
 * @param token Uma string cujo primeiro elemento é o char a ser verificado.
 * @return int 
 */
int is_operator(char *token);

/**
 * @brief Função que retorna o índice associado a um operador.
 * 
 * @param operator O operador.
 * @return int 
 */
int get_index(char operator);

/**
 * @brief Uma tabela de despacho responsável por invocar a função correspondente ao operador dado.
 * 
 * @param s Um apontador para a stack.
 * @param operator O operador.
 */
void dispatch_table(STACK *s, char operator);

/**
 * @brief Definição do tipo de cada elemento da tabela de despacho.
 * 
 */
typedef void (*function)(STACK *s);

/**
 * @brief Função que soma dois elementos da stack.
 * 
 * @param s Um apontador para a stack.
 */
void sum(STACK *s);

/**
 * @brief Função que subtrai dois elementos da stack.
 * 
 * @param s Um apontador para a stack.
 */
void sub(STACK *s);

/**
 * @brief Função que multiplica dois elementos da stack.
 * 
 * @param s Um apontador para a stack.
 */
void mult(STACK *s);

/**
 * @brief Função que divide dois elementos da stack.
 * 
 * @param s Um apontador para a stack.
 */
void divi(STACK *s);

/**
 * @brief Função que calcula o resto da divisão inteiros de dois elementos da stack.
 * 
 * @param s Um apontador para a stack.
 */
void rem(STACK *s);

/**
 * @brief Função que calcula a exponenciação de dois elementos da stack.
 * 
 * @param s 
 */
void power(STACK *s);

/**
 * @brief Função que calcula, ao nível dos bits, o "ou exclusivo" entre dois elementos da stack.
 * 
 * @param s Um apontador para a stack.
 */
void bw_xor(STACK *s);

/**
 * @brief Função que calcula, ao nível dos bits, o "e" entre dois elementos da stack.
 * 
 * @param s Um apontador para a stack.
 */
void bw_and(STACK *s);

/**
 * @brief Função que calcula, ao nível dos bits, o "ou" entre dois elementos da stack.
 * 
 * @param s Um apontador para a stack.
 */
void bw_or(STACK *s);

/**
 * @brief Função que incrementa um elemento da stack.
 * 
 * @param s Um apontador para a stack.
 */
void increment(STACK *s);

/**
 * @brief Função que decrementa um elemento da stack.
 * 
 * @param s Um apontador para a stack.
 */
void decrement(STACK *s);

/**
 * @brief Função que calcula, ao nível dos bits, o "not" de um elemento da stack.
 * 
 * @param s Um apontador para a stack.
 */
void bw_not(STACK *s);
