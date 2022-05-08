#include "stack.h"
#include "parser.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/**
 * @brief Função principal do programa
 * 
 * @return int 
 */
int main() {
    STACK *s = create_stack(); //É inicializada a stack vazia, com espaço para 1000 posições
    GLOBALS *g = init_globals(); //São inicializadas as variáveis globais com os valores predefinidos

    get_line(s, g);//Os comandos da stack são lidos e as operações pedidas são realizadas

    print_stack(s); // Os conteúdos no estado final da stack são impressos
    
    free_stack(s); // A memória ocupada pela stack é libertada

    return 0;
}
