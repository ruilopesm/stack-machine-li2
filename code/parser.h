#include <stddef.h>

int get_line(STACK *s);

/**
 * @brief Lê o input do utilizador e realiza as operações pretendidas pelo mesmo
 * 
 * @param s Um apontador para a stack
 * @return int 
 */
void parse_line(STACK *s,char *line);

/**
 * @brief Realiza a operação pretendida pelo utilizador conforme o símbolo lido
 * 
 * @param s Um apontador para a stack
 * @param token Símbolo lido
 */
void handle_token(STACK *s, char *token);

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

int is_array(char *token);

/**
 * @brief Verifica se o token é uma "vaiável global"
 * 
 * @param token 
 * @return int 
 */
int is_global(char *token);

int is_readress_global(char *token);

int find_char(char *line, char c, int parsed);

int get_array_length(char *line, int parsed);

void copy(char *token, char *line, int len, int parsed);

int remove_slashn (char *token);

/**
 * @brief Remove o caracter na posição indicada por 'p'
 * 
 * @param s 
 * @param p 
 */
void remove_char(char *s, int p);
