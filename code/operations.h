#define N_OPERATORS 9

char get_operator(int i);

int is_operator(char *token);
int get_index(char operator);

void dispatch_table(STACK *s, char operator);
typedef void (*binary)(STACK *s);

void sum(STACK *s);
void sub(STACK *s);
void mult(STACK *s);
void divi(STACK *s);
void rem(STACK *s);
void power(STACK *s);
void bw_xor(STACK *s);
void bw_and(STACK *s);
void bw_or(STACK *s);
