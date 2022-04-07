typedef struct {
    int sp;
    int size;
    int *stc;
} STACK;

STACK *create_stack();
int increase_stack(STACK *s);
void free_stack(STACK *s);

int push(STACK *s, int elem);
int pop(STACK *s, int *elem);
