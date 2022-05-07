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
    char line[BUFSIZ];
    
    if (fgets(line, BUFSIZ, stdin) != NULL) {
        parse_line(s, line, g);
    }
    
    return 0;
}
    
void parse_line(STACK *s, char *line, GLOBALS *g) {
    char token[BUFSIZ];
    int parsed = 0;
    
    while ((int) strlen(line) != parsed) {
        while (line[parsed] == ' ') {
            parsed++;
        }
        
        if (line[parsed] == '\"') {
            copy(token, line, find_char(line, '\"', parsed) + 1, parsed);
        }
        else if (line[parsed] == '[') {
            copy(token, line, get_array_length(line, parsed) + 1, parsed);
        }
        else {
            copy(token, line, find_char(line, ' ', parsed), parsed);
        }
        
        parsed += (int) strlen(token);
        handle_token(s, token, g);
    }
}

void handle_token(STACK *s, char *token, GLOBALS *g) {
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
        parse_line(array, token, g);
        
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
        
        STACK_ELEM new = get_global(value, g);
        
        assert(push(s, new) == 0);
    }
    else if (is_readress_global(token)) {
        STACK_ELEM top;
        
        assert(peek(s, &top) == 0);
        
        char value = token[1];
        g->globals[value - 65] = top;
    }
    else if (strcmp(token, "l") == 0) {
        read_line(s, g);
    }
    else if (is_operator(token)) {
        dispatch_table(s, token);
    }
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
