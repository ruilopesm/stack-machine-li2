#include "stack.h"
#include "operations.h"
#include "parser.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>
#include <regex.h>

int get_line(STACK *s){
    char line[BUFSIZ];
    
    if (fgets(line, BUFSIZ, stdin) != NULL) {
        parse_line(s, line);
    }
    
    return 0;
}
    
void parse_line(STACK *s, char *line) {
    char token[BUFSIZ];
    int parsed = 0;
    
    while ((int) strlen(line) != parsed) {
        while (line[parsed] == ' ') {
            parsed++;
        }
        
        if (line[parsed] == '\"'){
            copy(token, line, find_char(line, '\"', parsed) + 1, parsed);
        }
        else if (line[parsed] == '['){
            copy(token, line, get_array_length(line, parsed) + 1, parsed);
        }
        else {
            copy(token, line, find_char(line, ' ', parsed), parsed);
        }
        
        if (remove_slashn(token)) {
            parsed++;
        }
        
        parsed += (int) strlen(token);
        handle_token(s, token);
    }
}

void handle_token(STACK *s, char *token) {
    if (is_long(token)) {
        long value;
        sscanf(token, "%ld", &value);
        
        STACK_ELEM new = {
            .t = LONG, 
            .data = { .l = value }
        };

        assert(push(s, new) == 0);
    } 
    else if (is_double(token)) {
        double value;
        sscanf(token, "%lg", &value);

        STACK_ELEM new = {
            .t = DOUBLE, 
            .data = { .d = value }
        };

        assert(push(s, new) == 0);
    }
    else if (is_array(token)) {
        int len = strlen(token);

        // Remove os [] do array (e espaços entre esses e os elementos do array)
        remove_char(token, len - 2);
        remove_char(token, len - 2);
        remove_char(token, 0);
        remove_char(token, 0);
        
        STACK *array = create_stack();
        parse_line(array,token);
        
        STACK_ELEM new = {
            .t = ARRAY,
            .data= { .a = array }
        };
        
        assert(push(s, new) == 0);
    }
    else if (is_string(token)) {
        char *heap_token = strdup(token);
        int len = strlen(token);

        // Remove as aspas da string
        remove_char(heap_token, 0);
        remove_char(heap_token, len - 2);

        STACK_ELEM new = {
            .t = STRING, 
            .data = { .s = heap_token }
        };

        assert(push(s, new) == 0);
    }
    else if (is_global(token)) {
        char value;
        sscanf(token, "%c", &value);
        
        STACK_ELEM new = get_global(s, value);
        
        assert(push(s, new) == 0);
    }
    else if (is_readress_global(token)){
        STACK_ELEM top;
        
        assert(peek(s, &top) == 0);
        
        char value = token[1];
        s->globals[value - 65] = top;
    }
    else if (is_operator(token)) {
        dispatch_table(s, token);
    }
}

// Verifica se a string contém apenas algarismos
int is_long(char *token) {
    static bool flag = false;
    static regex_t regex;

    if (!flag) {
        assert(regcomp(&regex, "^-?[0-9]+$", REG_EXTENDED) == 0);
        flag = true;
    }

    return regexec(&regex, token, 0, NULL, 0) == 0;
}

// Verifica se a string contém apenas algarismos e um ponto (.)
int is_double(char *token) {
    static bool flag = false;
    static regex_t regex;

    if (!flag) {
        assert(regcomp(&regex, "^-?[0-9]+\\.[0-9]+$", REG_EXTENDED) == 0);
        flag = true;
    }

    return regexec(&regex, token, 0, NULL, 0) == 0;
}

int is_string(char *token) {
    static bool flag = false;
    static regex_t regex;

    if (!flag) {
        assert(regcomp(&regex, "^\".*\"$", REG_EXTENDED) == 0);
    }

    return regexec(&regex, token, 0, NULL, 0) == 0;
}

int is_array(char *token) {
    return token[0] == '[' && token[strlen(token) - 1] == ']';
}

int is_global(char *token) {
    static bool flag = false;
    static regex_t regex;

    if (!flag) {
        assert(regcomp(&regex, "^[A-Z]$", REG_EXTENDED) == 0);
    }
    
    return regexec(&regex, token, 0, NULL, 0) == 0;
}

int is_readress_global(char *token) {
    static bool flag = false;
    static regex_t regex;

    if (!flag) {
        assert(regcomp(&regex, "^:[A-Z]$", REG_EXTENDED) == 0);
    }
    
    return regexec(&regex, token, 0, NULL, 0) == 0;
}

int find_char(char *line, char c, int parsed) {
    int i;
    
    for (i = 1 + parsed; line[i] != c && line[i] != '\0' && line[i] != '\n'; i++);
    
    return i - parsed;
}

// Encontra o tamanho total do array
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

// Remove o '\n' da string (retorna ainda se o \n existia na string ou não)
int remove_slashn(char *token){
    int len = strlen(token);
    
    if (token[len - 1] == '\n'){
        remove_char(token, len - 1);
        return 1;
    }
    
    return 0;
}

// Remove o caracter na posição indicada por 'p'
void remove_char(char *s, int p) {
    for (int i = p; s[i] != '\0'; i++) {
        s[i] = s[i + 1];
    }
}
