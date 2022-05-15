#ifndef PARSER_H
#define PARSER_H

#include <stddef.h>

/**
 * @brief Função que obtem o objeto da linha
 * 
 * @param s 
 * @param g 
 * @return int 
 */
int get_line(STACK *s, GLOBALS *g);

/**
 * @brief Lê o input do utilizador e realiza as operações pretendidas pelo mesmo
 * 
 * @param s Um apontador para a stack
 * @return int 
 */
void parse_line(STACK *s, char *line, GLOBALS *g);

/**
 * @brief Realiza a operação pretendida pelo utilizador conforme o símbolo lido
 * 
 * @param s Um apontador para a stack
 * @param token Símbolo lido
 */
void handle_token(STACK *s, char *token, GLOBALS *g);

/**
 * @brief Verifica se a string contém apenas algarismos
 * 
 * @param token 
 * @return int 
 */
int is_long(char *token);

/**
 * @brief Verifica se a string contém apenas algarismos e um ponto (.)
 * 
 * @param token 
 * @return int 
 */
int is_double(char *token);

/**
 * @brief Verifica se o token é uma string
 * 
 * @param token 
 * @return int 
 */
int is_string(char *token);

/**
 * @brief Verifica se o token é um array
 * 
 * @param token 
 * @return int 
 */
int is_array(char *token);

/**
 * @brief Verifica se o token é um bloco
 * 
 * @param token 
 * @return int 
 */
int is_block(char *token);

/**
 * @brief Verifica se o token é uma "vaiável global"
 * 
 * @param token 
 */
int is_global(char *token);

/**
 * @brief Funçao que altera o valor da variável global
 * 
 * @param token 
 * @return int 
 */
int is_readress_global(char *token);

/**
 * @brief Função resposável pelo token caso este seja do tipo long
 * 
 * @param s 
 * @param token 
 */
void handle_long(STACK *s, char *token);

/**
 * @brief Função resposável pelo token caso este seja do tipo double
 * 
 * @param s 
 * @param token 
 */
void handle_double(STACK *s, char *token);

/**
 * @brief Função resposável pelo token caso este seja do tipo string
 * 
 * @param s 
 * @param token 
 */
void handle_string(STACK *s, char *token);

/**
 * @brief Função resposável pelo token caso este seja do tipo array
 * 
 * @param s 
 * @param token 
 * @param g 
 */
void handle_array(STACK *s, char *token, GLOBALS *g);

/**
 * @brief Função resposável pelo token caso este seja do tipo bloco
 * 
 * @param s 
 * @param token 
 */
void handle_block(STACK *s, char *token);

/**
 * @brief Função resposável pelo token caso este seja uma variavel global
 * 
 * @param s 
 * @param token 
 * @param g 
 */
void handle_global(STACK *s, char *token, GLOBALS *g);

/**
 * @brief Função resposável pelo token caso este seja uma variavel global, e tenha falhado as outras verificações
 * 
 * @param s 
 * @param token 
 * @param g 
 */
void handle_readress_global(STACK *s, char *token, GLOBALS *g);

/**
 * @brief Funçao que encontra o indice do char c
 * 
 * @param line array
 * @param c char que se quer encontar
 * @param parsed indice onde se começa a procura
 */
int find_char(char *line, char c, int parsed);

/**
 * @brief Funçao que encontra o tamanho total do aray
 * 
 * @param line array
 * @param parsed indice do incio do array
 */
int get_array_length(char *line, int parsed);

/**
 * @brief Funçao que encontra o tamanho total do bloco
 * 
 * @param line 
 * @param parsed 
 * @return int 
 */
int get_block_length(char *line, int parsed);

/**
 * @brief Funçao que copia o line para o token a partir da posição parsed até que tenha um tamanho de len
 * 
 * @param token 
 * @param line 
 * @param len tamanho do token
 * @param parsed posiçao de inicío do token
 */
void copy(char *token, char *line, int len, int parsed);

/**
 * @brief Remove o caracter na posição indicada por 'p'
 * 
 * @param s Apontador para a stack
 * @param p 
 */
void remove_char(char *s, int p);

#endif
