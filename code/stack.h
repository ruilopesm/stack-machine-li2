#ifndef STACK_H
#define STACK_H

#define MAX_BUFFER_SIZE 10081/**< tamanho do buffer */

typedef struct STACK STACK;

/**
 * @brief Enum que guarda os tipos implementados na stack
 * 
 */
typedef enum {/**< tipos dos elementos */
    LONG,
    CHAR,
    DOUBLE,
    STRING,
    ARRAY,
    BLOCK
} TYPE;

/**
 * @brief Estrutura que guarda o tipo e o conteúdo de um elemento da stack
 * 
 */
typedef struct {
    TYPE t; /**< Tipo do elemento (vindo do enum 'TYPE') */
    union {
        long l;/**< long */
        char c;/**< char */
        double d;/**< double */
        char *s;/**< string */
        STACK *a;/**< array */
        char *b;/**< bloco */
    } data; /**< Conteúdo do elemento */
} STACK_ELEM;

/**
 * @brief A estrutura onde constam os parâmetros da stack
 * 
 */
typedef struct STACK {
    int sp; /**< O stack pointer */
    int size; /**< O tamanho total da stack */
    STACK_ELEM *stc; /**< O conteúdo da stack */
} STACK;

/**
 * @brief A estrutura onde constam as variáveis "globais" do programa
 * 
 */
typedef struct {
    STACK_ELEM globals[26]; /**< Variáveis "globais" */
} GLOBALS;

/**
 * @brief Inicializa uma stack com 100 posições
 * 
 * @return STACK* 
 */
STACK *create_stack();

/**
 * @brief Inicializa as variáveis "globais"
 * 
 * @return GLOBALS* 
 */
GLOBALS *init_globals();

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
 * @brief Funçao que imprime os elementos na STACK
 * 
 * @param s Apontador para a stack
 */
void print_elems (STACK *s);

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

/**
 * @brief Verifica o conteudo do n-ésimo elemento
 * 
 * @param s 
 * @param elem 
 * @param n 
 * @return int 
 */
int nth_element(STACK *s, STACK_ELEM *elem, int n);

/**
 * @brief Função que troca a posição de dois elementos numa stack (onde a posição 0 é o fundo da stack e sp - 1 o topo)
 * 
 * @param array 
 * @param x 
 * @param y 
 */
void swap(STACK *array, int x, int y);

#endif
