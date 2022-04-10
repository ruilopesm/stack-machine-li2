int get_index(char operator);

void dispatch_table(STACK *s, char operator);
typedef void (*table)(STACK *s);

void soma(STACK *s);
void sub(STACK *s);
