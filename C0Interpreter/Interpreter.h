#include "Parser.h"
#define MAX_SIZEOF_MEMORY 20
#define MAX_SIZEOF_INPUT 50
#define MAX_SIZEOF_OUTPUT 50
typedef struct{
	char *name;
	int value;
}Memory[MAX_SIZEOF_MEMORY];
extern Memory g_memory;
extern int g_pMemory;
int fetch(char *name);
void store(char *name,int value);
//
void Interpreter();