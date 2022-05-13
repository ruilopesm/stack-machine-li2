#include "stack.h"
#include "parser.h"
#include "operations.h"
#include "blocks.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

void map_array(STACK_ELEM x, STACK_ELEM y, STACK_ELEM *result, GLOBALS *g) {
    result->t = ARRAY;

    STACK *array_map = create_stack();

    for (int i = 0; i < x.data.a->sp; i++) {
        push(array_map, x.data.a->stc[i]);
        parse_line(array_map, y.data.b, g);
    }

    result->data.a = array_map;
}

void map_string(STACK_ELEM x, STACK_ELEM y, STACK_ELEM *result, GLOBALS *g) {
    char *str = malloc((strlen(x.data.s) + 1) * sizeof(char)), *start = str;
    strcpy(str, x.data.s);

    STACK *string_map = create_stack();

    STACK_ELEM aux;
    aux.t = CHAR;

    for (char c = *str; c != '\0'; c = *++str) {
        aux.data.c = c;
        push(string_map, aux);
        parse_line(string_map, y.data.b, g);
    }

    str = start;

    for (int i = 0; i < string_map->sp; i++) {
        aux = string_map->stc[i];
        *str++ = aux.data.c;
    }

    *str = '\0';

    result->t = STRING;
    result->data.s = start;
    free_stack(string_map);
}

//Retorna 0 se x for menor ou igual a y, 1 se o contrário se verificar
int cmpOn(STACK_ELEM x,STACK_ELEM y,STACK *temp, char *block,GLOBALS *g){
    STACK_ELEM xp,yp;
    assert(push(temp,x) == 0);
    parse_line(temp,block,g);
    assert(push(temp,y) == 0);
    parse_line(temp,block,g);
    assert(pop(temp,&yp) == 0);
    assert(pop(temp,&xp) == 0);
    if(xp.t == STRING && yp.t == STRING){
        if(strcmp(xp.data.s,yp.data.s) <= 0){
            return 0;
        }
        else{
            return 1;
        }
        
    }
    else if(xp.t == ARRAY && yp.t == ARRAY){
        return cmp_arrays(xp.data.a,yp.data.a);
    }
    else {
        double xc =get_double_arg(xp),yc = get_double_arg(yp);
        if(xc<=yc){
            return 0;
        }
        else{
            return 1;
        }
    }
    temp->sp = 0; //Esvaziar a stack temporária, caso tenha elementos anteriores de modo a não causar erros (provavelmente não necessário, mas existe como segurança extra)
}

int cmp_arrays(STACK *x, STACK *y){
    int result;
    for(int i=0;i>=0;i++){
        if(x->stc[i].t==STRING && y->stc[i].t == STRING){
            result = (strcmp(x->stc[i].data.s,y->stc[i].data.s));
            if (result < 0){
                return 0;
            }
            if (result > 0){
                return 1;
            }
        }
        if(x->stc[i].t==ARRAY && y->stc[i].t == ARRAY){
            result = cmp_arrays(x->stc[i].data.a,y->stc[i].data.a);
            if (result < 0){
                return 0;
            }
            if (result > 0){
                return 1;
            }
        }
        else{
            double xc = get_double_arg(x->stc[i]),yc = get_double_arg(y->stc[i]);
            if(xc < yc){
                return 0;
            }
            if(xc > yc){
                return 1;
            }

        }
        //Se chegar ao fim de qualquer um dos arrays termina a comparação
        if(i==x->sp-1){
            return 0;
        }
        if(i==y->sp-1){
            return 1;
        }
    }
}

//Ordena um array segundo dada condição por um bloco
void sortOn(STACK_ELEM block,STACK_ELEM *array,GLOBALS *g){
    STACK *temp=create_stack();
    int i,j;
    for(i=1;i<array->data.a->sp;i++){ 
        for(j=0;j<i && cmpOn(array->data.a->stc[i],array->data.a->stc[j],temp,block.data.s,g);j++){
        }
        for(;j<i;j++){
            swap(array->data.a,j,i);
        }
    }
}