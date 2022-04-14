#define N_OPERATORS 12

char get_operator(int i);
int is_operator(char *token);
int get_index(char operator);

void dispatch_table(STACK *s, char operator);
typedef void (*function)(STACK *s);

// Binary operators
void sum(STACK *s);
void sub(STACK *s);
void mult(STACK *s);
void divi(STACK *s);
void rem(STACK *s);
void power(STACK *s);
void bw_xor(STACK *s);
void bw_and(STACK *s);
void bw_or(STACK *s);

// Unary operators
void increment(STACK *s);
void decrement(STACK *s);
void bw_not(STACK *s);
