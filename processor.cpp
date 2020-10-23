#include "compiler.h"

int Processor(char* argv){
	Proc cpu;
	StackCreate(&cpu.tack);
	char* buffer = nullptr;
	int n_sym = 0;
	CreateBuffer(&buffer, argv, &n_sym);

	char* ptr = buffer;
	int command = *buffer;

	while(ptr < (buffer + sizeof(char) * n_sym)){
		command = *ptr;
		switch(command){
			case PUSH:	{ptr += sizeof(char);
						StackPush(&cpu.tack, *(element*)ptr);
						ptr += sizeof(element) - 1;
						break;}

			case ADD:	{element tmp1 = 0; 
						element tmp2 = 0;
						tmp1 = StackPop(&cpu.tack);
						tmp2 = StackPop(&cpu.tack);
						tmp1 += tmp2;
						StackPush(&cpu.tack, tmp1);
						break;}

			case SUB:	{element tmp1, tmp2 = 0;
						tmp1 = StackPop(&cpu.tack);
						tmp2 = StackPop(&cpu.tack);
						tmp1 -= tmp2;
						StackPush(&cpu.tack, tmp1);
						break;}

			case MUL:	{element tmp1, tmp2 = 0;
						tmp1 = StackPop(&cpu.tack);
						tmp2 = StackPop(&cpu.tack);
						tmp1 *= tmp2;
						StackPush(&cpu.tack, tmp1);
						break;}

			case DIV:	{element tmp1, tmp2 = 0;
						tmp1 = StackPop(&cpu.tack);
						tmp2 = StackPop(&cpu.tack);
						tmp1 /= tmp2;
						StackPush(&cpu.tack, tmp1);
						break;}

			case SIN:	{element tmp1, tmp2 = 0;
						tmp1 = StackPop(&cpu.tack);
						tmp1 = sin(tmp1);
						StackPush(&cpu.tack, tmp1);
						break;}

			case COS:	{element tmp1, tmp2 = 0;
						tmp1 = StackPop(&cpu.tack);
						tmp1 = cos(tmp1);
						StackPush(&cpu.tack, tmp1);
						break;}

			case SQRT:	{element tmp1 = 0;
						tmp1 = StackPop(&cpu.tack);
						tmp1 = sqrt(tmp1);
						StackPush(&cpu.tack, tmp1);
						break;}

			case NEG:	{element tmp1, tmp2 = 0;
						tmp1 = StackPop(&cpu.tack);
						tmp1 = (-1) * (tmp1);
						StackPush(&cpu.tack, tmp1);
					  	break;}

			case OUT:	{element tmp1 = 0;
						printf("Poped number %lg\n", StackPop(&cpu.tack));
					  	break;}

			case IN:	{element tmp1 = 0;
						scanf("%lg", &tmp1);
						StackPush(&cpu.tack, tmp1);
					 	break;}

			case DUMP:	{StackDump(&cpu.tack, 0);
					   	break;}

			case HALT:	{abort();
					   	break;}

			default:	printf("AND WHAT DID YOU EXPECT???\n");
						break;
		}
		ptr += sizeof(char);
	}
	return 0;
}