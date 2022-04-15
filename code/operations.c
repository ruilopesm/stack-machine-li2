#include "stack.h"
#include "operations.h"

#include <assert.h>
#include <math.h>

/**
 * @brief Retorna a operação correspondente a certo número predefinido
 * 
 * @param i Número recebido
 * @return char 
 */
char get_operator(int i) {
    static char const operators[N_OPERATORS] = {
        '+',
        '-',
        '*',
        '/',
        '%',
        '#',
        '^',
        '&',
        '|',
        ')',
        '(',
        '~'
    };

    return operators[i]; // Retorna a operação na posição desse número
}

/**
 * @brief Verifica se o elemento é um operador
 * 
 * @param token //Caracter lido
 * @return int 
 */
int is_operator(char *token) {
    for (int i = 0; i < N_OPERATORS; i++) {
        if (token[0] == get_operator(i)) {//A função verificará todos os operadores até encontrar um que seja igual ao caracter lido ou não existam mais operadores
            return 1; // Se o caracter lido for o operador ao qual foi comparado, irá retornar 1 (true)
        }
    }
    
    return 0; // Se o caracter não for o operador, irá retornar 0 (false)
}

/**
 * @brief Procura qual o operador que foi lido
 * 
 * @param operator Operador recebido
 * @return int 
 */
int get_index(char operator) {
    int index = -1;

    for (int i = 0; i < N_OPERATORS; i++) {
        if (operator == get_operator(i)) {
            index = i; // Quando encontrar o operador correto, irá atribuir o valor numérico correspondente a esse (definido em get_operator)
        }
    }

    return index;
}

/**
 * @brief Inicializa a operação correspondente ao número recebido
 * 
 * @param s 
 * @param operator 
 */
void dispatch_table(STACK *s, char operator) {
    function table[] = {
        sum, 
        sub,
        mult,
        divi,
        rem,
        power,
        bw_xor,
        bw_and,
        bw_or,
        increment,
        decrement,
        bw_not
    }; // As funções até agora implementadas são colocadas em posições análogas às referenciadas em get_operator

    int index = get_index(operator); //O índice correspondente a essas operações é encontrado

    table[index](s); // A função correspondente a esse operador é executada
}

/**
 * @brief Retira os dois elementos do topo da stack e coloca no topo a soma dos mesmos
 * 
 * @param s Stack sobre a qual essas operações serão executadas
 */
void sum(STACK *s) {
    int x, y;
    
    assert(pop(s, &x) == 0);
    assert(pop(s, &y) == 0);//Os elementos são retirados da stack

    push(s, x + y);//Os elementos são somados e essa soma é colocada na stack
}

/**
 * @brief Retira os dois elementos do topo da stack e coloca no topo a subtração do penúltimo pelo último
 * 
 * @param s Stack sobre a qual essas operações serão executadas
 */
void sub(STACK *s) {
    int x, y;
    
    assert(pop(s, &y) == 0);
    assert(pop(s, &x) == 0); //Os elementos são retirados da stack

    push(s, x - y);//Os elementos são subtraídos e esse resultado é colocado na stack
}

/**
 * @brief Retira os dois elementos do topo da stack e coloca no topo a multiplicação dos mesmos
 * 
 * @param s Stack sobre a qual essas operações serão executadas
 */
void mult(STACK *s) {
    int x, y;
    assert(pop(s, &x) == 0);
    assert(pop(s, &y) == 0); //Os elementos são retirados da stack

    push(s, x * y);//Os elementos são multiplicados e esse resultado é colocado na stack
}

/**
 * @brief Retira os dois elementos do topo da stack e coloca no topo a divisão do penúltimo pelo último
 * 
 * @param s Stack sobre a qual essas operações serão executadas
 */
void divi(STACK *s) {
    int x, y;
    assert(pop(s, &y) == 0);
    assert(pop(s, &x) == 0);//Os elementos são retirados da stack                          

    push(s, x / y);//Os elementos são divididos e esse resultado é colocado na stack
}
/**
 * @brief Retira os dois elementos do topo da stack e coloca no topo o resto da divisão do penúltimo pelo último
 * 
 * @param s Stack sobre a qual essas operações serão executadas
 */
void rem(STACK *s) {
    int x, y;
    assert(pop(s, &y) == 0);
    assert(pop(s, &x) == 0);//Os elementos são retirados da stack                                

    push(s, x % y);//Os elementos são divididos o resto da mesma é colocado na stack
}

/**
 * @brief Retira os dois elementos do topo da stack e coloca no topo o penúmtimo elevado o último
 * 
 * @param s Stack sobre a qual essas operações serão executadas
 */
void power(STACK *s) {
    int x, y;
    assert(pop(s, &y) == 0);
    assert(pop(s, &x) == 0);//Os elementos são retirados da stack       

    push(s, pow(x, y));//O resultado da operação é colocado na stack
}

/**
 * @brief Retira os dois elementos do topo da stack e retorna o resultado da operação XOR
 * 
 * @param s Stack sobre a qual essas operações serão executadas
 */
void bw_xor(STACK *s) {
    int x, y;
    assert(pop(s, &x) == 0);
    assert(pop(s, &y) == 0);//Os elementos são retirados da stack   

    push(s, x ^ y);//O resultado da operação é colocado na stack
}

/**
 * @brief Retira os dois elementos do topo da stack e retorna o resultado da operação AND
 * 
 * @param s Stack sobre a qual essas operações serão executadas
 */
void bw_and(STACK *s) {
    int x, y;
    assert(pop(s, &x) == 0);
    assert(pop(s, &y) == 0);//Os elementos são retirados da stack

    push(s, x & y);//O resultado da operação é colocado na stack
}

/**
 * @brief Retira os dois elementos do topo da stack e retorna o resultado da operação OR
 * 
 * @param s Stack sobre a qual essas operações serão executadas
 */
void bw_or(STACK *s) {
    int x, y;
    assert(pop(s, &x) == 0);
    assert(pop(s, &y) == 0);//Os elementos são retirados da stack

    push(s, x | y);//O resultado da operação é colocado na stack
}

/**
 * @brief Retira um elemento da stack, aumenta o seu valor por um, e de seguida coloca-o de volta na stack
 * 
 * @param s Stack sobre a qual essas operações serão executadas
 */
void increment(STACK *s) {
    int x;
    assert(pop(s, &x) == 0);//O elemento é retirado da stack

    push(s, ++x);//O resultado da operação é colocado na stack
}

/**
 * @brief Retira um elemento da stack, diminui o seu valor por um, e de seguida coloca-o de volta na stack
 * 
 * @param s Stack sobre a qual essas operações serão executadas
 */
void decrement(STACK *s) {
    int x;
    assert(pop(s, &x) == 0);//O elemento é retirado da stack

    push(s, --x);//O resultado da operação é colocado na stack
}

/**
 * @brief Retira os um elementos do topo da stack e retorna o resultado da operação NOT
 * 
 * @param s Stack sobre a qual essas operações serão executadas
 */
void bw_not(STACK *s) {
    int x;
    assert(pop(s, &x) == 0);//O elemento é retirado da stack

    push(s, ~x);//O resultado da operação é colocado na stack
}
