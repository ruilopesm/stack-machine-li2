/**
 * @brief Macro que define o número de operadores implementados na stack
 *
 */
#define N_OPERATORS 33

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
void dispatch_table(STACK *s, char *operator);

/**
 * @brief Definição do tipo de cada elemento da tabela de despacho
 *
 */
typedef void (*function)(STACK *s);

/**
 * @brief Retira os dois elementos do topo da stack e coloca no topo a soma dos mesmos
 *
 * @param s Apontador para a stack
 */
void sum(STACK *s);

/**
 * @brief Funçao que concatena uma string e um elemento 
 * 
 * @param y array
 * @param x elemento a adicionar
 * @param result array final
 */
void sum_array(STACK_ELEM y, STACK_ELEM x, STACK_ELEM *result, int order);

/**
 * @brief Funçao que invoca a funçao append_string_aux com os argumentos corretos
 * 
 * @param y string ou argumento
 * @param x string ou argumento
 * @param result string final
 */
void append_string(STACK_ELEM y, STACK_ELEM x, STACK_ELEM *result);

/**
 * @brief Funçao que concatena os argumentos
 * 
 * @param y string
 * @param x argumento
 * @param result resltado final
 */
void append_string_aux(STACK_ELEM y, STACK_ELEM x, STACK_ELEM *result, int order);

/**
 * @brief Retira os dois elementos do topo da stack e coloca no topo a subtração do penúltimo pelo último
 *
 * @param s Apontador para a stack
 */
void sub(STACK *s);

/**
 * @brief Retira os dois elementos do topo da stack e coloca no topo a multiplicação dos mesmos
 *
 * @param s Apontador para a stack
 */
void mult(STACK *s);

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
void divi(STACK *s);

char *create_string(int size);

void split_by_substring(STACK_ELEM *main, STACK_ELEM *sub, STACK *new);

/**
 * @brief Retira os dois elementos do topo da stack e coloca no topo o resto da divisão do penúltimo pelo último
 *
 * @param s Apontador para a stack
 */
void rem(STACK *s);

/**
 * @brief Função que calcula a exponenciação de dois elementos da stack
 *
 * @param s Apontador para a stack
 */
void power(STACK *s);

/**
 * @brief Funçao que calcula em que indice ocorre uma substring numa string maior
 * 
 * @param x string
 * @param y substring que se procura
 * @param result indice
 */
void find_substring_index(STACK_ELEM x, STACK_ELEM y, STACK_ELEM *result);

/**
 * @brief Retira os dois elementos do topo da stack e retorna o resultado da operação XOR ("ou exclusivo" ao nível dos bits)
 *
 * @param s Apontador para a stack
 */
void bw_xor(STACK *s);

/**
 * @brief Retira os dois elementos do topo da stack e retorna o resultado da operação AND ("e" ao nível dos bits)
 *
 * @param s Apontador para a stack
 */
void bw_and(STACK *s);

/**
 * @brief Retira os dois elementos do topo da stack e retorna o resultado da operação OR ("ou" ao nível dos bits)
 *
 * @param s Apontador para a stack
 */
void bw_or(STACK *s);

/**
 * @brief Retira um elemento da stack, incrementa o seu valor, e de seguida coloca-o de volta na stack
 *
 * @param s Apontador para a stack
 */
void increment(STACK *s);

/**
 * @brief Retira um elemento da stack, decrementa o seu valor, e de seguida coloca-o de volta na stack
 *
 * @param s Apontador para a stack
 */
void decrement(STACK *s);

/**
 * @brief Retira os um elementos do topo da stack e retorna o resultado da operação NOT ("negação" ao nível dos bits)
 *
 * @param s Apontador para a stack
 */
void not(STACK *s);

/**
 * @brief Converte o elemento no topo da stack para o tipo "int"
 * 
 * @param s Apontador para a stack
 */
void conv_int(STACK *s);

/**
 * @brief Converte o elemento no topo da stack para o tipo "double"
 * 
 * @param s Apontador para a stack
 */
void conv_double(STACK *s);

/**
 * @brief Converte o elemento no topo da stack para o tipo "char"
 * 
 * 
 * @param s Apontador para a stack
 */        
void conv_char(STACK *s);

/**
 * @brief Converte o elemento no topo da stack para o tipo "string"
 * 
 * @param s Apontador para a stack
 */
void conv_str(STACK *s);

/**
 * @brief Duplica o elemento no topo da stack
 * 
 * @param s Apontador para a stack
 */
void duplicate(STACK *s);

/**
 * @brief Dá pop do elemento no topo da stack
 * 
 * @param s Apontador para a stack
 */
void other_pop(STACK *s);

/**
 * @brief Troca a ordem dos dois elementos no topo da stack
 * 
 * @param s Apontador para a stack
 */
void swap(STACK *s);

/**
 * @brief Coloca o terceiro elemento no topo da stack
 * 
 * @param s Apontador para a stack
 */
void rotate(STACK *s);

/**
 * @brief Copia o n-ésimo elemento para o topo da stack
 * 
 * @param s Apontador para a stack
 */
void copy_nth(STACK *s);

/**
 * @brief Lê a linha seguinte e adiciona-a à stack
 * 
 * @param s Apontador para a stack
 */
void read_line(STACK *s, GLOBALS *g);

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
void igual(STACK *s);

/**
 * @brief Função que compara se o elemento do topo da stack é menor do que o segundo elemento da stack
 * 
 * @param s Apontador para a stack
 */
void menor(STACK *s);

/**
 * @brief Função que compara se o elemento do topo da stack é maoir do que o segundo elemento da stack
 * 
 * @param s Apontador para a stack
 */
void maior(STACK *s);

/**
 * @brief Função que devolve a negação de um argumento
 * 
 * @param s Apontador para a stack
 */
void negacao(STACK *s);

/**
 * @brief operador lógico "e". Recebe dois argumentos, se ambos forem verdadeiros devolve verdadeiro
 * 
 * @param s Apontador para a stack
 */
void e_shortcut(STACK *s);

/**
 * @brief operador lógico "ou". Recebe dois argumentos, caso um deles seja verdadeiro devolve verdadeiro
 * 
 * @param s Apontador para a stack
 */
void ou_shortcut(STACK *s);

/**
 * @brief Funçao que coloca o menor de dois números no topo da stack
 * 
 * @param s Apontador para a stack
 */
void e_menor(STACK *s);

/**
 * @brief Funçao que coloca o maior de dois números no topo da stack
 * 
 * @param s Apontador para a stack
 */
void e_maior(STACK *s);

/**
 * @brief Função que recebe tres argumentos. Caso o primeiro seja verdadeiro devolve o segundo elemento, caso contrario devolve o terceiro
 * 
 * @param s Apontador para a stack
 */
void if_then_else(STACK *s);

/**
 * @brief Funçao que calcula o comprimento/range de um argumento.
 * 
 * @param s Apontador para a stack
 */
void range(STACK *s);

void split_string_by_whitespace(STACK *s);

void split_string_by_slashn(STACK *s);
