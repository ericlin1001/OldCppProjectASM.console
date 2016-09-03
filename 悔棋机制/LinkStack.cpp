#include"LinkStack.h"
SeqStack *SeqStack_Init(){
	SeqStack *temp =new SeqStack;
	temp->top=MAXSIZE-1;
	for(int i=0;i<MAXSIZE;i++){
		temp->stakcData[i]=-1;
	}
	return temp;
}
void SeqStack_Free(SeqStack *stack){
	delete stack;
}
bool SeqStack_IsEmpty(SeqStack *stack){
	return (stack->stakcData[stack->top]==-1);
}
SeqStack *SeqStack_Push(SeqStack *stack,int newData){
	stack->top++;
	stack->top%=MAXSIZE;
	stack->stakcData[stack->top]=newData;
	return stack;
}
bool SeqStack_Pop(SeqStack *stack,int &userData){
	if(SeqStack_IsEmpty(stack)){
		return false;
	}
	userData=stack->stakcData[stack->top];
	stack->stakcData[stack->top]=-1;
	//
	//stack->top--;
	stack->top+=MAXSIZE-1;
	stack->top%=MAXSIZE;
	return true;
}

