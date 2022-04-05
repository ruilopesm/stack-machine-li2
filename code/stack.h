typedef struct {
    int sp;
    int size;
    int *stc;
} STACK;

STACK *create_stack();

int push(STACK *s, int elem);
int pop(STACK *s, int *elem);
