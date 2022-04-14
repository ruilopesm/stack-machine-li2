#define N_OPERATORS 5

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
