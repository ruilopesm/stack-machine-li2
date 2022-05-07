#include "stack.h"
#include "operations.h"
#include "parser.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include <float.h>

char *get_operator(int i) {
    static char *operators[N_OPERATORS] = {
        "+",
        "-",
        "*",
        "/",
        "%",
        "#",
        "^",
        "&",
        "|",
        ")",
        "(",
        "~",
        "i",
        "f",
        "c",
        "s",
        "_",
        ";",
        "\\",
        "@",
        "$",
        "l",
        "=",
        "<",
        ">",
        "!",
        "e&",
        "e|",
        "e<",
        "e>",
        "?",
        ",",
        "S/",
        "N/",
        "t"
    };

    return operators[i];
}

int is_operator(char *token) {
    for (int i = 0; i < N_OPERATORS; i++) {
        if (strcmp(token, get_operator(i)) == 0) {
            return 1;
        }
    }

    return 0;
}

int get_index(char *operator) {
    for (int i = 0; i < N_OPERATORS; i++) {
        if (strcmp(operator, get_operator(i)) == 0) {
            return i;
        }
    }

    // Caso o operador não tenha sido encontrado: retorna -1 (ERRO)
    return -1;
}

void dispatch_table(STACK *s, char *operator) {
    static function table[] = {
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
        not,
        conv_int,
        conv_double,
        conv_char,
        conv_str,
        duplicate,
        other_pop,
        swap,
        rotate,
        copy_nth,
        read_line,
        igual,
        menor,
        maior,
        negacao,
        e_shortcut,
        ou_shortcut,
        e_menor,
        e_maior,
        if_then_else,
        range,
        split_string_by_whitespace,
        split_string_by_slashn,
        convert_lines_to_string
    }; // As funções até agora implementadas são colocadas em posições análogas às referenciadas na função 'get_operator'.

    int index = get_index(operator);
    assert(index != -1);

    // Chama o function pointer
    table[index](s);
}

double get_double_arg(STACK_ELEM x) {
    if (x.t == DOUBLE) {
        return x.data.d;
    } 
    else if (x.t == LONG) {
        return x.data.l;
    } 
    else {
        return x.data.c;
    }
}

long get_long_arg(STACK_ELEM x) {
    if (x.t == LONG) {
        return x.data.l;
    } 
    else {
        return x.data.c;
    }
}

void sum(STACK *s) {
    STACK_ELEM x, y;

    assert(pop(s, &x) == 0);
    assert(pop(s, &y) == 0);

    STACK_ELEM result;

    if (y.t == ARRAY){
        sum_array(y, x, &result, 1);
    }
    else if (x.t == ARRAY){
        sum_array(x, y, &result, 0);
    }
    else if (y.t == STRING || x.t == STRING) {
        append_string(y, x, &result);
    }    
    else if (x.t == DOUBLE || y.t == DOUBLE) {
        result.t = DOUBLE;
        result.data.d = get_double_arg(x) + get_double_arg(y);
    } 
    else if (x.t == LONG || y.t == LONG) {
        result.t = LONG;
        result.data.l = get_long_arg(x) + get_long_arg(y);
    }
    else {
        result.t = CHAR;
        result.data.c = x.data.c + y.data.c;
    }

    push(s, result);
}

void sum_array(STACK_ELEM y, STACK_ELEM x, STACK_ELEM *result, int order) {
    if (x.t == ARRAY) {
        for (int i = 0 ; i < x.data.a->sp; i++) {
            assert(push(y.data.a, x.data.a->stc[i]) == 0);
        }

        *result = y;
    }
    else if (order) {
        assert(push(y.data.a, x) == 0);
        *result = y;
    }
    else {
        STACK *s = create_stack();
        assert(push(s, x) == 0);
        
        for(int i = 0; i < y.data.a->sp; i++) {
            assert(push(s, y.data.a->stc[i]) == 0);
        }
        
        result->t = ARRAY;
        result->data.a = s;

    }
}

void append_string(STACK_ELEM y, STACK_ELEM x, STACK_ELEM *result) {
    if (y.t == STRING) {
        append_string_aux(y, x, result, 1);
    }
    else {
        append_string_aux(x, y, result, 0);
    }
}

void append_string_aux(STACK_ELEM y, STACK_ELEM x, STACK_ELEM *result, int order) {
    if (x.t == STRING) {
        char *new = malloc(strlen(y.data.s) + strlen(x.data.s) + 1);
        
        if (order) {
            strcpy(new, y.data.s);
            strcat(new, x.data.s);
        }
        else {
            strcpy(new, x.data.s);
            strcat(new, y.data.s);
        }
        
        result->t = STRING;
        result->data.s = new;
        
        free(y.data.s);
        free(x.data.s);
    }
    else if (x.t == CHAR) {
        int len = strlen(y.data.s);
        char *new = malloc(len + 2);
        
        if (order) {
            strcpy(new, y.data.s);
            new[len] = x.data.c;
        }
        else {
            new[0] = x.data.c;
            new[1] = '\0';
            
            strcat(new,y.data.s);
        }
       
        new[len + 1 ] = '\0';
        result->t = STRING;
        result->data.s = new;
        
        free(y.data.s);
    }
    else {
        char *temp = malloc(sizeof(char) * BUFSIZ);
        char *new = malloc(sizeof(char) * BUFSIZ + strlen(y.data.s) + 1);
        
        snprintf(temp, BUFSIZ, "%g", get_double_arg(x));
        
        if (order) {
            strcpy(new, y.data.s);
            strcat(new, temp);
        }
        else {
            strcpy(new, temp);
            strcat(new, y.data.s);
        }

        result->t = STRING;
        result->data.s = new;
        
        free(y.data.s);
        free(temp);
    }
}

void sub(STACK *s) {
    STACK_ELEM x, y;

    assert(pop(s, &y) == 0);
    assert(pop(s, &x) == 0);

    STACK_ELEM result;

    if (x.t == DOUBLE || y.t == DOUBLE) {
        result.t = DOUBLE;
        result.data.d = get_double_arg(x) - get_double_arg(y);
    } 
    else if (x.t == LONG || y.t == LONG) {
        result.t = LONG;
        result.data.l = get_long_arg(x) - get_long_arg(y);
    } 
    else {
        result.t = CHAR;
        result.data.c = x.data.c - y.data.c;
    }

    push(s, result);
}

void mult(STACK *s) {
    STACK_ELEM x, y;

    assert(pop(s, &x) == 0);
    assert(pop(s, &y) == 0);

    STACK_ELEM result;

    if (y.t == STRING || y.t == ARRAY) {
        mult_structure(x, y, &result);
    }
    else if (x.t == DOUBLE || y.t == DOUBLE) {
        result.t = DOUBLE;
        result.data.d = get_double_arg(x) * get_double_arg(y);
    } 
    else if (x.t == LONG || y.t == LONG) {
        result.t = LONG;
        result.data.l = get_long_arg(x) * get_long_arg(y);
    } 
    else if (x.t == CHAR && y.t == CHAR) {
        result.t = CHAR;
        result.data.c = x.data.c * y.data.c;
    }

    push(s, result);
}

void mult_structure(STACK_ELEM x, STACK_ELEM y, STACK_ELEM *result) {
    if (y.t == STRING) {
        int len = strlen(y.data.s) + 1;

        char *new = malloc(len * x.data.l * sizeof(char));
        strcpy(new, y.data.s);

        for (int i = 0; i < x.data.l - 1; i++) {
            strcat(new, y.data.s);
        }

        result->t = STRING;
        result->data.s = new;

        free(y.data.s);
    }
    else if (y.t == ARRAY) {
        int len = y.data.a->sp;

        for (int i = len; i < len * x.data.l; i++) {
            push(y.data.a, y.data.a->stc[i % len]);
        }

        result->t = ARRAY;
        result->data.a = y.data.a;
    }
}

void divi(STACK *s) {
    STACK_ELEM x, y;

    assert(pop(s, &y) == 0);
    assert(pop(s, &x) == 0);

    STACK_ELEM result;

    if (x.t == STRING && y.t == STRING) {
        result.t = ARRAY;
        STACK *new = create_stack();
        
        split_by_substring(&x, &y, new);
        
        result.data.a = new;
        
        free(x.data.s);
        free(y.data.s);
    }
    else if (x.t == DOUBLE || y.t == DOUBLE) {
        result.t = DOUBLE;
        result.data.d = get_double_arg(x) / get_double_arg(y);
    } 
    else if (x.t == LONG || y.t == LONG) {
        result.t = LONG;
        result.data.l = get_long_arg(x) / get_long_arg(y);
    } 
    else {
        result.t = CHAR;
        result.data.c = x.data.c / y.data.c;
    }

    push(s, result);

}

char *create_string(int size) {
    char *section = malloc(sizeof(char) * size);
    
    return section;
}
void split_by_substring(STACK_ELEM *main, STACK_ELEM *sub, STACK *new) {
    char *init = main->data.s, *current, *section;
    
    STACK_ELEM temp;
    temp.t = STRING;
    
    int len = strlen(sub->data.s);
    
    while ((current = strstr(init, sub->data.s)) != NULL) {
        section = create_string(current - init + 1);
        
        strncpy(section, init, current - init);
        section[current - init] = '\0';
        temp.data.s = section;
        
        assert(push(new, temp) == 0);
        
        init = current + len;
    }

    if (strlen(init) >= 2 || (strlen(init) == 1 && init[0] != '\n')) {
        section = create_string(strlen(init) + 1);
        strcpy(section, init);
        temp.data.s = section;
        
        assert(push(new,temp) == 0);
    }
}

void rem(STACK *s) {
    STACK_ELEM x, y;

    assert(pop(s, &y) == 0);
    assert(pop(s, &x) == 0);

    STACK_ELEM result;

    if (x.t == LONG || y.t == LONG) {
        result.t = LONG;
        result.data.l = get_long_arg(x) % get_long_arg(y);
    } 
    else {
        result.t = CHAR;
        result.data.c = x.data.c % y.data.c;
    }

    push(s, result);
}


void power(STACK *s) {
    STACK_ELEM x, y;

    assert(pop(s, &y) == 0);
    assert(pop(s, &x) == 0);

    STACK_ELEM result;

    if (x.t == STRING && y.t == STRING){
        find_substring_index(x,y,&result);
    }
    else if (x.t == DOUBLE || y.t == DOUBLE) {
        result.t = DOUBLE;
        result.data.d = pow(get_double_arg(x), get_double_arg(y));
    } 
    else if (x.t == LONG || y.t == LONG) {
        result.t = LONG;
        result.data.l = (long int) pow(get_long_arg(x), get_long_arg(y));
    } 
    else {
        result.t = CHAR;
        result.data.c = (char) pow(x.data.c, y.data.c);
    }

    push(s, result);
}

void find_substring_index(STACK_ELEM x, STACK_ELEM y, STACK_ELEM *result) {
    result->t = LONG;
    char *temp;
    
    if (strlen(x.data.s) > strlen(y.data.s)) {
        if ((temp = (strstr(x.data.s, y.data.s))) == NULL) {
            result->data.l = -1;
        }
        else {
            result->data.l = temp - x.data.s;
        }
    }
    else {
        if ((temp = (strstr(y.data.s, x.data.s))) == NULL) {
            result->data.l = -1;
        }
        else {
            result->data.l = temp - y.data.s;
        }
    }
}

void bw_xor(STACK *s) {
    STACK_ELEM x, y;

    assert(pop(s, &x) == 0);
    assert(pop(s, &y) == 0);

    STACK_ELEM result;

    if (x.t == LONG || y.t == LONG) {
        result.t = LONG;
        result.data.l = get_long_arg(x) ^ get_long_arg(y);
    } 
    else {
        result.t = CHAR;
        result.data.c = x.data.c ^ y.data.c;
    }

    push(s, result);
}

void bw_and(STACK *s) {
    STACK_ELEM x, y;

    assert(pop(s, &x) == 0);
    assert(pop(s, &y) == 0);

    STACK_ELEM result;

    if (x.t == LONG || y.t == LONG) {
        result.t = LONG;
        result.data.l = get_long_arg(x) & get_long_arg(y);
    } 
    else {
        result.t = CHAR;
        result.data.c = x.data.c & y.data.c;
    }

    push(s, result);
}

void bw_or(STACK *s) {
    STACK_ELEM x, y;

    assert(pop(s, &x) == 0);
    assert(pop(s, &y) == 0);

    STACK_ELEM result;

    if (x.t == LONG || y.t == LONG) {
        result.t = LONG;
        result.data.l = get_long_arg(x) | get_long_arg(y);
    } 
    else {
        result.t = CHAR;
        result.data.c = x.data.c | y.data.c;
    }

    push(s, result);
}

void increment(STACK *s) {
    STACK_ELEM x;

    assert(pop(s, &x) == 0);

    STACK_ELEM result;

    if (x.t == STRING) {
        result.t = STRING;

        int len = strlen(x.data.s);

        STACK_ELEM to_push = {
            .t = CHAR,
            .data.c = x.data.s[len - 1]
        };

        x.data.s[len - 1] = '\0';

        char *token = x.data.s;

        result.data.s = strdup(token);

        push(s, result);
        push(s, to_push);

        free(token);

        return;
    }
    else if (x.t == ARRAY) {
        result.t = ARRAY;

        assert(pop(x.data.a, &result) == 0);

        push(s, x);
        push(s, result);

        return;
    }
    else if (x.t == DOUBLE) {
        result.t = DOUBLE;
        result.data.d = ++x.data.d;
    } 
    else if (x.t == LONG) {
        result.t = LONG;
        result.data.l = ++x.data.l;
    } 
    else {
        result.t = CHAR;
        result.data.c = ++x.data.c;
    }
    push(s, result);
    
}   

void decrement(STACK *s) {
    STACK_ELEM x;

    assert(pop(s, &x) == 0);

    STACK_ELEM result;

    if (x.t == STRING) {
        result.t = STRING;

        STACK_ELEM to_push = {
            .t = CHAR,
            .data.c = x.data.s[0]
        };

        char *token = x.data.s + 1;
        
        result.data.s = strdup(token);

        push(s, result);
        push(s, to_push);

        free(x.data.s);

        return;
    }
    else if (x.t == ARRAY) {
        STACK *new = create_stack();

        STACK_ELEM to_push = x.data.a->stc[0];

        for (int i = 1; i < x.data.a->sp; i++) {
            push(new, x.data.a->stc[i]);
        }

        result.t = ARRAY;
        result.data.a = new;

        push(s, result);
        push(s, to_push);

        return;
    }
    else if (x.t == DOUBLE) {
        result.t = DOUBLE;
        result.data.d = --x.data.d;
    } 
    else if (x.t == LONG) {
        result.t = LONG;
        result.data.l = --x.data.l;
    } 
    else {
        result.t = CHAR;
        result.data.c = --x.data.c;
    }

    push(s, result);
}

void not(STACK *s) {
    
    STACK_ELEM x;

    assert(pop(s, &x) == 0);

    if (x.t == ARRAY) {
        for (int i = x.data.a->sp - 1; i >= 0; i--) {
            STACK_ELEM new;
            
            assert(nth_element(x.data.a, &new, i) == 0);
            assert(push(s, new) == 0);
        }

        free(x.data.a);
    }
    else {
        STACK_ELEM result;
    
        if (x.t == LONG) {
            result.t = LONG;
            result.data.l = ~x.data.l;
        } 
        else {
            result.t = CHAR;
            result.data.c = ~x.data.c;
        }
        
        push(s, result);
    }
}

void conv_int(STACK *s) {
    STACK_ELEM x;
    
    assert(pop(s, &x) == 0);
    
    STACK_ELEM result;

    if (x.t == DOUBLE) {
        result.t = LONG;
        result.data.l = x.data.d;
        push(s, result);
    }
    else if (x.t == CHAR) {
        result.t = LONG;
        result.data.l = x.data.c;
        push(s, result);
    }
    else if (x.t == STRING) {
        result.t = LONG;
        sscanf(x.data.s, "%ld", &result.data.l);
        push(s, result);
    }
    // Conversão redundante
    else {
        push(s, x);
    }
}

void conv_double(STACK *s) {
    STACK_ELEM x;
    
    assert(pop(s, &x) == 0);
    
    STACK_ELEM result;

    if (x.t == LONG) {
        result.t = DOUBLE;
        result.data.d = x.data.l;
        push(s, result);
    } 
    else if (x.t == CHAR) {
        result.t = DOUBLE;
        result.data.d = x.data.c;
        push(s, result);
    } 
    else if (x.t == STRING) {
        result.t = DOUBLE;
        sscanf(x.data.s, "%lg", &result.data.d);
        push(s, result);
    }
    // Conversão redundante
    else {
        push(s, x);
    }
}

void conv_char(STACK *s) {
    STACK_ELEM x;
    
    assert(pop(s, &x) == 0);
    
    STACK_ELEM result;

    if (x.t == LONG) {
        result.t = CHAR;
        result.data.c = x.data.l % 256;
        push(s, result);
    } 
    else if (x.t == STRING) {
        result.t = CHAR;
        result.data.c = x.data.s[0];
        push(s, result);
    } 
    else {
        push(s, x);
    }
}

void conv_str(STACK *s) {
    STACK_ELEM x;
    
    assert(pop(s, &x) == 0);
    
    STACK_ELEM result;
    result.data.s = malloc(sizeof(char) * BUFSIZ);

    if (x.t == LONG) {
        result.t = STRING;
        snprintf(result.data.s, BUFSIZ, "%ld", x.data.l);
        push(s, result);
    } 
    else if (x.t == DOUBLE) {
        result.t = STRING;
        snprintf(result.data.s, BUFSIZ, "%lg", x.data.d);
        push(s, result);
    } 
    else if (x.t == CHAR) {
        result.t = STRING;
        result.data.s[0] = x.data.c;
        result.data.s[1] = '\0';
        push(s, result);
    } 
    else {
        push(s, x);
    }
}

void duplicate(STACK *s) {
    STACK_ELEM x;
    
    assert(pop(s, &x) == 0);
    
    assert(push(s, x) == 0);
    assert(push(s, x) == 0);
}

void other_pop(STACK *s) {
    STACK_ELEM x;
    
    assert(pop(s, &x) == 0);
}

void swap(STACK *s) {
    STACK_ELEM x, y;

    assert(pop(s, &x) == 0);
    assert(pop(s, &y) == 0);

    assert(push(s, x) == 0);
    assert(push(s, y) == 0);
}

void rotate(STACK *s) {
    STACK_ELEM x, y, z;

    assert(pop(s, &x) == 0);
    assert(pop(s, &y) == 0);
    assert(pop(s, &z) == 0);

    assert(push(s, y) == 0);
    assert(push(s, x) == 0);
    assert(push(s, z) == 0);   
}

void copy_nth(STACK *s) {
    STACK_ELEM x;

    assert(pop(s, &x) == 0);

    STACK_ELEM result;

    assert(nth_element(s, &result, x.data.l) == 0);

    assert(push(s, result) == 0);
}

void read_line(STACK *s) {
    char *line = malloc(sizeof(char) * BUFSIZ);

    if (fgets(line, BUFSIZ, stdin) != NULL) {
        line[strlen(line) - 1] = '\0';

        STACK_ELEM result = {
            .t = STRING,
            .data.s = strdup(line)
        };

        assert(push(s, result) == 0);
    }
}

STACK_ELEM get_global(char value, GLOBALS *g) {
    STACK_ELEM new, current = g->globals[value -  65];
    
    if (current.t == DOUBLE) {
        new.t = DOUBLE;
        new.data.d = current.data.d;
    }
    else if (current.t == LONG) {
        new.t = LONG;
        new.data.l = current.data.l;
    }
    else if (current.t == STRING) {
        int len = strlen(current.data.s); // Vai ser criada cópia da string de modo a não alterar o valor
        char *copy = malloc(sizeof(char) * len + 1);
        strcpy(copy,current.data.s);
        copy[len] = '\0'; // Assegurar que a string é finalizada corretamente
        new.t = STRING;
        new.data.s = copy;
    }
    else if (current.t == ARRAY) {
        STACK_ELEM temp;
        STACK *cpy_array = create_stack();
        for(int i = current.data.a->sp -1;i>=0;i--){
            nth_element(current.data.a,&temp,i);
            assert(push(cpy_array,temp) == 0);
        }
        new.t= ARRAY;
        new.data.a=cpy_array;
    }
    else {
        new.t = CHAR;
        new.data.c = current.data.c;
    }

    return new;
}

void igual(STACK *s) {
    STACK_ELEM x, y;
    long to_push = 0;

    STACK_ELEM result;

    assert(pop(s, &x) == 0);
    assert(pop(s, &y) == 0);

    if (y.t == ARRAY) {
        long pos = get_long_arg(x);
        
        assert(nth_element(y.data.a, &result, (y.data.a->sp) - pos - 1) == 0);
        
        push(s, result);
        
        return;
    }
    else if (x.t != STRING && y.t == STRING) {
        long pos = get_long_arg(x);

        result.t = CHAR;        
        result.data.c = y.data.s[pos];
        
        push(s, result);

        return;
    }
    else if (x.t == STRING && y.t == STRING) {
        result.t = LONG;
        result.data.l = strcmp(x.data.s, y.data.s) == 0 ? 1 : to_push;
        push(s, result);
    }
    else if (get_double_arg(x) == get_double_arg(y)) {
        result.t = LONG;
        to_push = 1;
        result.data.l = to_push;
        push(s, result);
    }
    else {
        result.t = LONG;
        result.data.l = to_push;
        push(s, result);
    }
}

void menor(STACK *s) {
    STACK_ELEM x, y;
    long to_push = 0;

    STACK_ELEM result;

    assert(pop(s, &y) == 0);
    assert(pop(s, &x) == 0);

    if (x.t == ARRAY) {
        long len = x.data.a->sp,extract = get_long_arg(y);
        
        if (extract > len) {
            extract = len; // Se for pedido para extrair mais elementos do que aqueles que existem no array, será apenas extraído o array todo (é impossivel estrair mais elementos do que aqueles que existem)
        }
        
        for (int i = 0; i < extract; i++) {
            assert(nth_element(x.data.a, &result, (x.data.a->sp) - i - 1) == 0);
            assert(push(s, result) == 0);
        }
        
        return;
    }
    else if (x.t == STRING && y.t == STRING) {
        result.t = LONG;
        result.data.l = strcmp(x.data.s, y.data.s) < 0 ? 1 : to_push;
        push(s, result);
    }
    else if (x.t == STRING) {
        int len = strlen(x.data.s), extract = get_long_arg(y);
        
        if (extract > len) {
            extract = len; // Se for pedido para extrair mais caracteres do que aqueles que existem na string, será apenas extraída a string toda
        }
        
        char *new = malloc(sizeof(char) * (extract + 1));
        
        strncpy(new, x.data.s, extract);
        new[extract] = '\0';
        
        result.t = STRING;
        result.data.s = new;
        
        assert(push(s,result) == 0);
        
        free(x.data.s);
        
        return;
    }
    else if (get_double_arg(x) < get_double_arg(y)) {
        result.t = LONG;
        to_push = 1;
        result.data.l = to_push;
        push(s, result);
    }
    else {
        result.t = LONG;
        result.data.l = to_push;
        push(s, result);
    }
    
}

void maior(STACK *s) {
    STACK_ELEM x, y;
    long to_push = 0;

    STACK_ELEM result;

    assert(pop(s, &y) == 0);
    assert(pop(s, &x) == 0);   

    if (x.t == ARRAY) {
        long len = x.data.a->sp,extract = get_long_arg(y);
        
        if (extract > len) {
            extract = len; // Se for pedido para extrair mais elementos do que aqueles que existem no array, será apenas extraído o array todo (é impossivel estrair mais elementos do que aqueles que existem)
        }
          
        for (int i = extract - 1; i >= 0 ; i--) {
            assert(nth_element(x.data.a, &result, i) == 0);
            assert(push(s, result) == 0);
        }
        
      return;
    }
    else if (x.t == STRING && y.t == STRING) {
        result.t = LONG;
        result.data.l = strcmp(x.data.s, y.data.s) > 0 ? 1 : to_push;
        push(s, result);
    }
    else if (x.t == STRING) {
        int len = strlen(x.data.s), extract = get_long_arg(y);
        
        if (extract > len) {
            extract = len; // Se for pedido para extrair mais caracteres do que aqueles que existem na string, será apenas extraída a string toda
        }
        
        char *new = malloc(sizeof(char) * (extract + 1));
        
        strncpy(new, x.data.s + len - extract, extract);
        new[extract] = '\0';
        
        result.t = STRING;
        result.data.s = new;
        
        assert(push(s,result) == 0);
        
        free(x.data.s);
        
        return;
    }
    else if (get_double_arg(x) > get_double_arg(y)) {
        result.t = LONG;
        to_push = 1;
        result.data.l = to_push;
        push(s, result);
    }
    else {
        result.t = LONG;
        result.data.l = to_push;
        push(s, result);
    }
    
}

void negacao(STACK *s) {
    STACK_ELEM x;
    long to_push = 0;

    STACK_ELEM result;
    result.t = LONG;

    assert(pop(s, &x) == 0);

    if ((x.t == LONG || x.t == CHAR) && x.data.l == 0) {
        to_push = 1;
    }
    else if (x.t == DOUBLE && x.data.d == 0.0) {
        to_push = 1;
    }

    result.data.l = to_push;
    push(s, result);
}

void e_shortcut(STACK *s) {
    STACK_ELEM x, y;
    
    assert(pop(s, &y) == 0);
    assert(pop(s, &x) == 0);

    STACK_ELEM result = x;

    if (x.t == LONG && x.data.l) {
        result = y;
    }

    push(s, result);
}

void ou_shortcut(STACK *s) {
    STACK_ELEM x, y;
    
    assert(pop(s, &y) == 0);
    assert(pop(s, &x) == 0);

    STACK_ELEM result = y;

    if (get_double_arg(x)) {
        result = x;
    }

    push(s, result);
}

void e_menor(STACK *s) {
    STACK_ELEM x, y;

    assert(pop(s, &y) == 0);
    assert(pop(s, &x) == 0);

    STACK_ELEM result = y;

    if (x.t == STRING && y.t == STRING) {
        if (strcmp(x.data.s, y.data.s) < 0) {
            result = x;
        }
    }
    else if (get_double_arg(x) < get_double_arg(y)) {
        result = x;
    }
    
    push(s, result);
}

void e_maior(STACK *s) {
    STACK_ELEM x, y;

    assert(pop(s, &y) == 0);
    assert(pop(s, &x) == 0);

    STACK_ELEM result = y;

    if (x.t == STRING && y.t == STRING) {
        if (strcmp(x.data.s, y.data.s) > 0) {
            result = x;
        }
    }
    else if (get_double_arg(x) > get_double_arg(y)) {
        result = x;
    }
    
    push(s, result);
}

void if_then_else(STACK *s) {
    STACK_ELEM x, y, z;

    assert(pop(s, &z) == 0);
    assert(pop(s, &y) == 0);
    assert(pop(s, &x) == 0);

    STACK_ELEM result = z;

    if (x.t == LONG && x.data.l != 0) {
        result = y;
    }
    else if (x.t == DOUBLE && x.data.d != 0.0) {
        result = y;
    }
    else if (x.t == ARRAY && x.data.a->sp != 0) {
        result = y;
    }
    else if (x.t == STRING && strlen(x.data.s) != 0) {
        result = y;
    }

    push(s, result);
}

void range(STACK *s) {
    STACK_ELEM x;

    assert(pop(s, &x) == 0);

    STACK_ELEM result;
    result.t = LONG;

    if (x.t == STRING) {
        result.data.l = strlen(x.data.s);
    }
    else if (x.t == ARRAY) {
        result.data.l = x.data.a->sp;
    }
    else if (x.t == LONG || x.t == CHAR) {
        STACK *new = create_stack();
        
        for (int i = 0; i < x.data.l; i++) {
            STACK_ELEM to_push = { .t = LONG };
            to_push.data.l = i;
            
            push(new, to_push);
        }

        // t :T N/ , S  T S/ , S T 
        result.t = ARRAY;
        result.data.a = new;
    }

    push(s, result);
}

void split_string_by_whitespace(STACK *s) {
    STACK_ELEM x;
    
    assert(pop(s, &x) == 0);

    STACK_ELEM result = {
        .t = ARRAY,
        .data.a = create_stack()
    };

    if (x.t == STRING) {
        char *token, *rest = x.data.s;

        while ((token = strtok_r(rest, " \t\r\n\v\f", &rest))) {
            STACK_ELEM to_push = {
                .t = STRING,
                .data.s = strdup(token)
            };
            
            push(result.data.a, to_push);
        }
        
        push(s, result);
        
        free(token);
    }
}

void split_string_by_slashn(STACK *s) {
    STACK_ELEM x;
    
    assert(pop(s, &x) == 0);

    STACK_ELEM result = {
        .t = ARRAY,
        .data.a = create_stack()
    };

    if (x.t == STRING) {
        char *token, *rest = x.data.s;

        while ((token = strtok_r(rest, "\n", &rest))) {
            STACK_ELEM to_push = {
                .t = STRING,
                .data.s = strdup(token)
            };
            
            push(result.data.a, to_push);
        }
        
        push(s, result);
        
        free(token);
    }
}

void convert_lines_to_string(STACK *s) {
    char *line = malloc(sizeof(char) * BUFSIZ), *total = line;
    int len = 0;

    while (fgets(line, BUFSIZ, stdin) != NULL) {
        len = strlen(line);
        line += len;
    }

    STACK_ELEM result = {
        .t = STRING,
        .data.s = strdup(total)
    };

    line[strlen(line) - 1] = '\0';

    assert(push(s, result) == 0);
}
