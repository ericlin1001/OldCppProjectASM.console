#include<iostream.h>
#include"LinkStack.h"
int main()
{
	SeqStack *stack=SeqStack_Init();
	SeqStack_Push(stack,2);
	SeqStack_Push(stack,3);
	SeqStack_Push(stack,4);
	SeqStack_Push(stack,5);
	SeqStack_Push(stack,6);
	SeqStack_Push(stack,7);
	SeqStack_Push(stack,8);
	SeqStack_Push(stack,9);
	SeqStack_Push(stack,10);
	//
	int temp;
	while(SeqStack_Pop(stack,temp))
	cout<<temp<<endl;
	SeqStack_Free(stack);
	return 0;
}
/*
SeqStack *SeqStack_Init();
void SeqStack_Free(SeqStack *stack);
bool SeqStack_IsEmpty(SeqStack *stack);
SeqStack *SeqStack_Push(SeqStack *stack,int newData);
bool SeqStack_Pop(SeqStack *stack,int &userData);

*/