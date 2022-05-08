#include "stack.h"
#include "operations.h"
#include "parser.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <errno.h>

int get_line(STACK *s, GLOBALS *g) {
    char *line = malloc(sizeof(char) * BUFSIZ);
    
    if (fgets(line, BUFSIZ, stdin) != NULL) {//O input é lido
        line[strlen(line) - 1] = '\0';

        parse_line(s, line, g);//O input é interpretado pelo parser
    }
    
    free(line);
    return 0;
}
    
void parse_line(STACK *s, char *line, GLOBALS *g) {
    char *token = malloc(sizeof(char) * BUFSIZ);
    int parsed = 0;
    
    while ((int) strlen(line) != parsed) {
        while (line[parsed] == ' ') { // A função elimina possíveis espaços residuaisS
            parsed++;
        }
        
        if (line[parsed] == '\"') {
            copy(token, line, find_char(line, '\"', parsed) + 1, parsed);//Se encontrar uma aspa, irá procurar a próxima aspa e ler todo esse input como uma string
        }
        else if (line[parsed] == '[') {
            copy(token, line, get_array_length(line, parsed) + 1, parsed);//Se encontrar um [, irá procurar até o array terminar (ignorando arrays dentro dele mesmo) e ler todo esse input como um array
        }
        else if (line[parsed] == '{') {
            copy(token, line, find_char(line, '}', parsed) + 1, parsed);//Se encontrar uma chaveta, irá procurar a próxima chaveta e ler todo esse input como um bloco
        }
        else {
            copy(token, line, find_char(line, ' ', parsed), parsed);//Caso contrário, irá ler como um input normal e só ler até ao próximo espaço
        }
        
        parsed += (int) strlen(token); //O que já lemos irá ser ignorado em futuros ciclos
        handle_token(s, token, g); // O que foi lido é interpretado
    }

    free(token);
}

void handle_token(STACK *s, char *token, GLOBALS *g) {
    if (is_long(token)) { //  Se o input for um long, irá adicioná-lo à stack
        long value;
        sscanf(token, "%ld", &value);
        
        STACK_ELEM new = {
            .t = LONG, 
            .data = { .l = value }
        };

        assert(push(s, new) == 0);
    } 
    else if (is_double(token)) {//  Se o input for um double, irá adicioná-lo à stack
        double value;
        sscanf(token, "%lg", &value);

        STACK_ELEM new = {
            .t = DOUBLE, 
            .data = { .d = value }
        };

        assert(push(s, new) == 0);
    }
    else if (is_string(token)) {//  Se o input for uma string, irá adicioná-la à stack após remover as aspas

        STACK_ELEM new = *(handle_string_token(token));
        assert(push(s, new) == 0);
    }
    else if (is_array(token)) {//  Se o input for um array, irá adicioná-lo à stack após remover os parênteses

        STACK_ELEM new = *(handle_array_token(token));
        assert(push(s, new) == 0);
    }
    else if (is_block(token)) {//  Se o input for um bloco, irá adicioná-lo à stack após remover os parênteses

        STACK_ELEM new = *(handle_block_token(token));
        assert(push(s, new) == 0);
    }
    else if (is_global(token)) {//  Se o input for uma global, irá adicionar uma cópia da mesma à stack
        char value;
        sscanf(token, "%c", &value);
        
        STACK_ELEM new = get_global(value, g);
        
        assert(push(s, new) == 0);
    }
    else if (is_readress_global(token)) {//  Se o input for a mudança de uma global, irá alterar o valor da mesma para o valor no topo da stack
        STACK_ELEM new = *(handle_readress_global_token(token));

        char value = token[1];
        g->globals[value - 65] = new;
    }
    else if (is_operator(token)) {
        dispatch_table(s, token);
    }
}

STACK_ELEM *handle_array_token(char *token){
    int len = strlen(token);

    // Remove os [] do array (e espaços entre esses e os elementos do array)
    remove_char(token, len - 2);
    remove_char(token, len - 2);
    remove_char(token, 0);
    remove_char(token, 0);
        
    STACK *array = create_stack();
    parse_line(array, token, g);
        
    STACK_ELEM new = {
        .t = ARRAY,
        .data= { .a = array }
    };
    return &new;
        
}

STACK_ELEM *handle_string_token(char *token){
    char *heap_token = strdup(token);
    int len = strlen(token);

    // Remove as aspas da string
    remove_char(heap_token, 0);
    remove_char(heap_token, len - 2);

    STACK_ELEM new = {
        .t = STRING, 
        .data = { .s = heap_token }
    };
    return &new;
}

STACK_ELEM *handle_block_token(char *token){
    char *heap_token = strdup(token);
    int len = strlen(token);

    // Remove as {} do array (e espaços entre esses e os elementos do bloco)
    remove_char(heap_token, len - 2);
    remove_char(heap_token, len - 2);
    remove_char(heap_token, 0);
    remove_char(heap_token, 0);
        
    STACK_ELEM new = {
        .t = BLOCK,
        .data= { .b = heap_token }
    };
}

STACK_ELEM *handle_readress_global_token(char *token){
    STACK_ELEM top, new, temp;
        
    assert(peek(s, &top) == 0);
    new = top;
        
     if (top.t == STRING) {
        int len = strlen(top.data.s);
            
        char *copy = malloc(sizeof(char) * len + 1);
        strcpy(copy, top.data.s); // É criada uma cópia da string para colocar na global
        copy[len] = '\0';

        new.t = STRING;
        new.data.s = copy;
    }
    else if (top.t == ARRAY) {
        STACK *cpy_array = create_stack();
            
        for (int i = top.data.a->sp - 1; i >= 0; i--) {
            nth_element(top.data.a, &temp, i);// É criada uma cópia do array para colocar na global
            assert(push(cpy_array, temp) == 0);
        }

        new.t = ARRAY;
        new.data.a = cpy_array;
    }
    return &new;
}

int is_long(char *token) {
    char *end_ptr;
    errno = 0;

    strtol(token, &end_ptr, 0);
    
    return errno == 0 && *end_ptr == '\0';
}

int is_double(char *token) {
    char *end_ptr;
    errno = 0;

    strtod(token, &end_ptr);

    return errno == 0 && *end_ptr == '\0';
}

int is_string(char *token) {
    return token[0] == '"' && token[strlen(token) - 1] == '"';
}

int is_array(char *token) {
    return token[0] == '[' && token[strlen(token) - 1] == ']';
}

int is_block(char *token) {
    return token[0] == '{' && token[strlen(token) - 1] == '}';
}

int is_global(char *token) {
    return token[0] >= 'A' && token[0] <= 'Z' && strlen(token) == 1;
}

int is_readress_global(char *token) {
    return token[0] == ':' && token[1] >= 'A' && token[1] <= 'Z' && strlen(token) == 2;
}

int find_char(char *line, char c, int parsed) {
    int i;
    
    for (i = 1 + parsed; line[i] != c && line[i] != '\0' && line[i] != '\n'; i++);
    
    return i - parsed;
}

int get_array_length(char *line, int parsed) {
    int i, array_number = 0;
    
    for (i = 1 + parsed; line[i] != '\0' && line[i] != '\n'; i++) {
        // Se encontrar um array dentro do mesmo, irá ignorar o próximo ']' que encontrar, visto que esse pertencerá ao array dentro desse mesmo
        if (line[i] == '['){ 
            array_number++;
        }
        else if (line[i] == ']'){
            if (array_number == 0){
                return i - parsed;
            }
            else {
                array_number--;
            }
        }
    }

    return i - parsed;
}

void copy(char *token, char *line, int len, int parsed) {
    int i;
    
    for (i = 0; i < len; i++){
        token[i] = line[i + parsed];
    }
    token[i] = '\0';
}

// Remove o caracter na posição indicada por 'p'
void remove_char(char *s, int p) {
    for (int i = p; s[i] != '\0'; i++) {
        s[i] = s[i + 1];
    }
}
