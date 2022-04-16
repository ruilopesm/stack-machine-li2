#include "stack.h"
#include "operations.h"
#include "parser.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

/**
 * @brief Realiza a operação pretendida pelo utilizador conforme o símbolo lido
 * 
 * @param s Stack onde os elementos serão lidos e colocados
 * @param token Símbolo lido
 */
void handle_token(STACK *s, char *token) {
    if (is_operator(token)) { 
        dispatch_table(s, token[0]);// Se o símbolo for um operador, irá procurar a operação pretendida e realizá-la
    }
    else {
        int value;
        sscanf(token, "%d", &value); 
        assert(push(s, value) == 0);// Caso contrário, irá ler esse elemento e de seguida adicioná-lo à stack, se possível
    }
}

/**
 * @brief Lê o input do utilizador e realiza as operações pretendidas pelo mesmo
 * 
 * @param s Stack para onde os elementos serão colocados
 * @return int 
 */
int parse_line(STACK *s) { 
    char line[BUFSIZ];
    char token[BUFSIZ];

    if (fgets(line, BUFSIZ, stdin) != NULL) {
        while (sscanf(line, "%s%[^\n]", token, line) == 2) { //Se o input não for vazio, irá ler o mesmo até acabarem os elementos
            handle_token(s, token); // A cada elemento lido irá realizar a operação relacionada com esse símbolo
        }
        handle_token(s, token);
    }

    return 0;
}
