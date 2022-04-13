static char const operators[] = {
    '+',
    '-'
};
static int const len = sizeof(operators);

int is_operator(char *token);
int get_index(char operator);

void dispatch_table(STACK *s, char operator);
typedef void (*binary)(STACK *s);

void sum(STACK *s);
void sub(STACK *s);
