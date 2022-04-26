#include <stddef.h>

int is_long(char *token);
int is_double(char *token);
int is_string(char *token);
int is_global(char *token);


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
 * @brief Remove o caracter na posição indicada por 'p'
 * 
 * @param s 
 * @param p 
 */
void remove_char(char *s, size_t p);

/**
 * @brief Verifica se o token é uma string
 * 
 * @param token 
 * @return int 
 */
int is_string(char *token);

/**
 * @brief Verifica se o token é uma "vaiável global"
 * 
 * @param token 
 * @return int 
 */
int is_global(char *token);

/**
 * @brief Realiza a operação pretendida pelo utilizador conforme o símbolo lido
 * 
 * @param s Um apontador para a stack
 * @param token Símbolo lido
 */
void handle_token(STACK *s, char *token);

/**
 * @brief Lê o input do utilizador e realiza as operações pretendidas pelo mesmo
 * 
 * @param s Um apontador para a stack
 * @return int 
 */
int parse_line(STACK *s);
