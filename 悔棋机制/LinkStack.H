#define MAXSIZE 6
typedef struct {
int stakcData[MAXSIZE];
int top;
} SeqStack;

SeqStack *SeqStack_Init();
void SeqStack_Free(SeqStack *stack);
bool SeqStack_IsEmpty(SeqStack *stack);
SeqStack *SeqStack_Push(SeqStack *stack,int newData);
bool SeqStack_Pop(SeqStack *stack,int &userData);

