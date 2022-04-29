#include "stack.h"
#include "operations.h"
#include "parser.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>
#include <regex.h>
    
int find_char(char *line,char c,int parsed){
    int i;
    for (i=1+parsed;line[i]!=c && line[i]!= '\0' && line[i]!= '\n' ;i++){}
    return i-parsed;
}

void copy (char *token, char *line,int len,int parsed){
    int i;
    for(i=0;i<len;i++){
        token[i] = line[i+parsed];
    }
    token[i]='\0';
}

int get_line (STACK *s){
    char line[BUFSIZ];
    if (fgets(line, BUFSIZ, stdin) != NULL) {
        parse_line (s,line);
    }
    return 0;
}

int parse_line(STACK *s, char *line) {
    char token[BUFSIZ];
    int parsed = 0;

    while ((int)(strlen(line)) != parsed) {
        if (line[parsed]==' ') parsed++;
        if (line[parsed]=='\"'){
            copy(token, line, find_char(line,'\"',parsed)+1,parsed);
        }
        else if (line[parsed]=='['){
            copy(token, line, find_char(line,'[',parsed)+1,parsed);
        }
        else {
            copy(token, line, find_char(line,' ',parsed),parsed);
        }
        handle_token(s, token);
        parsed += strlen(token);
    }
    return 0;
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
    else if (is_string(token)) {
        char *heap_token = strdup(token);
        size_t len = strlen(token);

        // Remove as aspas da string
        remove_char(heap_token, 0);
        remove_char(heap_token, len - 2);

        STACK_ELEM new = {
            .t = STRING, 
            .data = { .s = heap_token }
        };
        assert(push(s, new) == 0);
    }
    else if (is_array(token)) {
        size_t len = strlen(token);
        //Remove os [] da string
        /*remove_char(token, len - 2);
        remove_char(token, len - 2);
        remove_char(token, 0);
        remove_char(token, 0);*/
        printf("%s",token);
        /*STACK *array = create_stack();
        parse_line(array,token);
        STACK_ELEM new ={
            .t = ARRAY,
            .data= { .a = array }
        };
        assert(push(s, new) == 0);*/
    }
    else if (is_global(token)) {
        char value;
        sscanf(token, "%c", &value);
        
        STACK_ELEM new = get_global(s, value);
        assert(push(s, new) == 0);
    }
    else if (is_readress_global(token)){
        STACK_ELEM top;
        assert (peek(s,&top) == 0);
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
   static bool flag = false;
    static regex_t regex;
    printf("a");
    if (!flag) {
        assert(regcomp(&regex, "^\\[.*\\]$", REG_EXTENDED) == 0);
    }

    return regexec(&regex, token, 0, NULL, 0) == 0;
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

// Remove o caracter na posição indicada por 'p'
void remove_char(char *s, size_t p) {
    for (size_t i = p; s[i] != '\0'; i++) {
        s[i] = s[i + 1];
    }
}
