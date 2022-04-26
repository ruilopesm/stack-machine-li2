/**
 * @brief Enum que guarda os tipos implementados na stack
 * 
 */
typedef enum {
    LONG,
    CHAR,
    DOUBLE,
    STRING
} TYPE;

/**
 * @brief Estrutura que guarda o tipo e o conteúdo de um elemento da stack
 * 
 */
typedef struct {
    TYPE t; /**< Tipo do elemento (vindo do enum 'TYPE') */
    union {
        long l;
        char c;
        double d;
        char *s;
    } data; /**< Conteúdo do elemento */
} STACK_ELEM;

/**
 * @brief A estrutura onde constam os parâmetros da stack
 * 
 */
typedef struct {
    int sp; /**< O stack pointer */
    int size; /**< O tamanho total da stack */
    STACK_ELEM *stc; /**< O conteúdo da stack */
    STACK_ELEM globals[26]; /**< Variáveis "globais" */
} STACK;

/**
 * @brief Inicializa uma stack com 100 posições
 * 
 * @return STACK* 
 */
STACK *create_stack();

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
