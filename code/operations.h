/**
 * @brief Macro que define o número de operadores implementados na stack
 *
 */
#define N_OPERATORS 35

/**
 * @brief Função que retorna o operador associado ao índice dado
 *
 * @param i O índice
 * @return char
 */
char *get_operator(int i);

/**
 * @brief Função que verifica se um dado char é um operador
 *
 * @param token Uma string cujo primeiro elemento é o char a ser verificado
 * @return int
 */
int is_operator(char *token);

/**
 * @brief Função que retorna o índice associado a um operador
 *
 * @param operator O operador
 * @return int
 */
int get_index(char *operator);

/**
 * @brief Funçao que obtem um argumento e converte para o tipo "double"
 * 
 * @param x 
 * @return double 
 */
double get_double_arg(STACK_ELEM x);

/**
 * @brief Funçao que obtem um argumento e converte para o tipo "long"
 * 
 * @param x 
 * @return long 
 */
long get_long_arg(STACK_ELEM x);
/**
 * @brief Uma tabela de despacho responsável por invocar a função correspondente ao operador dado
 *
 * @param s Apontador para a stack
 * @param operator O operador
 */
void dispatch_table(STACK *s, char *operator, GLOBALS *g);

/**
 * @brief Definição do tipo de cada elemento da tabela de despacho
 *
 */
typedef void (*function_pointer)(STACK *s, GLOBALS *g);

/**
 * @brief Retira os dois elementos do topo da stack e coloca no topo a soma dos mesmos
 *
 * @param s Apontador para a stack
 */
void plus_operator(STACK *s,GLOBALS *g);

/**
 * @brief Retira os dois elementos do topo da stack e coloca no topo a subtração do penúltimo pelo último
 *
 * @param s Apontador para a stack
 */
void minus_operator(STACK *s, GLOBALS *g);

/**
 * @brief Retira os dois elementos do topo da stack e coloca no topo a multiplicação dos mesmos
 *
 * @param s Apontador para a stack
 */
void asterisk_operator(STACK *s, GLOBALS *g);

/**
 * @brief Funçao que concatena multiplas vezes um array ou uma string
 * 
 * @param x número de vezes que se concatena a string ou o array
 * @param y array ou string
 * @param result 
 */
void mult_structure(STACK_ELEM x, STACK_ELEM y, STACK_ELEM *result);

/**
 * @brief Retira os dois elementos do topo da stack e coloca no topo a divisão do penúltimo pelo último
 *
 * @param s Apontador para a stack
 */
void slash_operator(STACK *s, GLOBALS *g);

/**
 * @brief Retira os dois elementos do topo da stack e coloca no topo o resto da divisão do penúltimo pelo último
 *
 * @param s Apontador para a stack
 */
void percentage_operator(STACK *s, GLOBALS *g);

/**
 * @brief Função que calcula a exponenciação de dois elementos da stack
 *
 * @param s Apontador para a stack
 */
void hashtag_operator(STACK *s, GLOBALS *g);

/**
 * @brief Retira os dois elementos do topo da stack e retorna o resultado da operação XOR ("ou exclusivo" ao nível dos bits)
 *
 * @param s Apontador para a stack
 */
void circumflex_operator(STACK *s, GLOBALS *g);

/**
 * @brief Retira os dois elementos do topo da stack e retorna o resultado da operação AND ("e" ao nível dos bits)
 *
 * @param s Apontador para a stack
 */
void and_operator(STACK *s, GLOBALS *g);

/**
 * @brief Retira os dois elementos do topo da stack e retorna o resultado da operação OR ("ou" ao nível dos bits)
 *
 * @param s Apontador para a stack
 */
void or_operator(STACK *s, GLOBALS *g);

/**
 * @brief Retira um elemento da stack, incrementa o seu valor, e de seguida coloca-o de volta na stack
 *
 * @param s Apontador para a stack
 */
void left_parenthesis_operator(STACK *s, GLOBALS *g);

/**
 * @brief Retira um elemento da stack, decrementa o seu valor, e de seguida coloca-o de volta na stack
 *
 * @param s Apontador para a stack
 */
void right_parenthesis_operator(STACK *s, GLOBALS *g);

/**
 * @brief Retira os um elementos do topo da stack e retorna o resultado da operação NOT ("negação" ao nível dos bits)
 *
 * @param s Apontador para a stack
 */
void tilde_operator(STACK *s, GLOBALS *g);

/**
 * @brief Converte o elemento no topo da stack para o tipo "int"
 * 
 * @param s Apontador para a stack
 */
void lowercase_i_operator(STACK *s, GLOBALS *g);

/**
 * @brief Converte o elemento no topo da stack para o tipo "double"
 * 
 * @param s Apontador para a stack
 */
void lowercase_f_operator(STACK *s, GLOBALS *g);

/**
 * @brief Converte o elemento no topo da stack para o tipo "char"
 * 
 * 
 * @param s Apontador para a stack
 */        
void lowercase_c_operator(STACK *s, GLOBALS *g);

/**
 * @brief Converte o elemento no topo da stack para o tipo "string"
 * 
 * @param s Apontador para a stack
 */
void lowercase_s_operator(STACK *s, GLOBALS *g);

/**
 * @brief Duplica o elemento no topo da stack
 * 
 * @param s Apontador para a stack
 */
void underscore_operator(STACK *s, GLOBALS *g);

/**
 * @brief Dá pop do elemento no topo da stack
 * 
 * @param s Apontador para a stack
 */
void semicolon_operator(STACK *s, GLOBALS *g);

/**
 * @brief Troca a ordem dos dois elementos no topo da stack
 * 
 * @param s Apontador para a stack
 */
void inverted_slash_operator(STACK *s, GLOBALS *g);

/**
 * @brief Coloca o terceiro elemento no topo da stack
 * 
 * @param s Apontador para a stack
 */
void arroba_operator(STACK *s, GLOBALS *g);

/**
 * @brief Copia o n-ésimo elemento para o topo da stack
 * 
 * @param s Apontador para a stack
 */
void dollar_operator(STACK *s, GLOBALS *g);

/**
 * @brief Lê a linha seguinte e adiciona-a à stack
 * 
 * @param s Apontador para a stack
 */
void lowercase_l_operator(STACK *s, GLOBALS *g);

/**
 * @brief Coloca o valor atual da variável global na stack
 * 
 * @param s Apontador para a stack
 * @param value letra que se encontra na variável global
 * @return STACK_ELEM 
 */
STACK_ELEM get_global(char value, GLOBALS *g);

/**
 * @brief Função que compara se os dois elementos do topo da stack são iguais
 * 
 * @param s Apontador para a stack
 */
void equal_sign_operator(STACK *s, GLOBALS *g);

/**
 * @brief Função que compara se o elemento do topo da stack é menor do que o segundo elemento da stack
 * 
 * @param s Apontador para a stack
 */
void less_sign_operator(STACK *s, GLOBALS *g);

/**
 * @brief Função que compara se o elemento do topo da stack é maoir do que o segundo elemento da stack
 * 
 * @param s Apontador para a stack
 */
void more_sign_operator(STACK *s, GLOBALS *g);

/**
 * @brief Função que devolve a negação de um argumento
 * 
 * @param s Apontador para a stack
 */
void exclamation_mark_operator(STACK *s, GLOBALS *g);

/**
 * @brief operador lógico "e". Recebe dois argumentos, se ambos forem verdadeiros devolve verdadeiro
 * 
 * @param s Apontador para a stack
 */
void and_with_and_operator(STACK *s, GLOBALS *g);

/**
 * @brief operador lógico "ou". Recebe dois argumentos, caso um deles seja verdadeiro devolve verdadeiro
 * 
 * @param s Apontador para a stack
 */
void and_with_or_operator(STACK *s, GLOBALS *g);

/**
 * @brief Funçao que coloca o menor de dois números no topo da stack
 * 
 * @param s Apontador para a stack
 */
void and_with_less_operator(STACK *s, GLOBALS *g);

/**
 * @brief Funçao que coloca o maior de dois números no topo da stack
 * 
 * @param s Apontador para a stack
 */
void and_with_more_operator(STACK *s, GLOBALS *g);

/**
 * @brief Função que recebe tres argumentos. Caso o primeiro seja verdadeiro devolve o segundo elemento, caso contrario devolve o terceiro
 * 
 * @param s Apontador para a stack
 */
void question_mark_operator(STACK *s, GLOBALS *g);

/**
 * @brief Funçao que calcula o comprimento/range de um argumento.
 * 
 * @param s Apontador para a stack
 */
void comma_operator(STACK *s, GLOBALS *g);

void uppercase_s_and_slash_operator(STACK *s, GLOBALS *g);

void uppercase_n_and_slash_operator(STACK *s, GLOBALS *g);

void lowercase_t_operator(STACK *s, GLOBALS *g);
