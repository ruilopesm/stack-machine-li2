int get_index(char operator);

void dispatch_table(STACK *s, char operator);
typedef void (*table)(STACK *s);

void sum(STACK *s);
void sub(STACK *s);
