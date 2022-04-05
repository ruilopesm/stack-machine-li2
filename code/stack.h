#define MAX 100

typedef struct {
    int sp;
    int arr[MAX];
} STACK;

STACK *create_stack();

void push(STACK *s, int elem);
int pop(STACK *s);
