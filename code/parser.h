int is_double(char *token);
int is_long(char *token);
void remove_char(char *s, size_t p);

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
