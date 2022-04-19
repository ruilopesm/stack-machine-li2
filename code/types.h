#include <stdio.h>

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
} STACK;
