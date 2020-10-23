#include "compiler.h"
int main(int argc, char* argv[]){
	char* input = nullptr;
	char* code = nullptr;

	if(!strcmp(argv[1], "-assembler")){
		input = argv[2];
		code = argv[3];
		Assembler(input, code);
	}
	if(!strcmp(argv[1], "-disassembler")){
		code = argv[3];
		input = argv[4];
		Disassembler(code, input);
	}
	if(!strcmp(argv[1], "-cpu")){
		code = argv[2];
		Processor(code);
	}
	return 0;
}

void PrintCommand(char com, FILE* file){
	fwrite(&com, sizeof(char), 1, file);
}

void PrintValue(element val, FILE* file){
	fwrite(&val, sizeof(element), 1, file);
}

void Assembler(char* buffer, char* code){

	FILE* output = fopen(code, "w");
	assert(output);

	Text source;
	CreateText(&source, buffer);

	for(size_t i = 0; i < source.lines; ++i){

		if(strstr(source.strings[i].str, "push") != nullptr){

			PrintCommand(PUSH, output);

			element value = 0;
			value = atof(source.strings[i].str + 5);
			PrintValue(value, output);

		}
		if(strstr(source.strings[i].str, "add") != nullptr)
			PrintCommand(ADD, output);
		if(strstr(source.strings[i].str, "sub") != nullptr)
			PrintCommand(SUB, output);
		if(strstr(source.strings[i].str, "mul") != nullptr)
			PrintCommand(MUL, output);
		if(strstr(source.strings[i].str, "div") != nullptr)
			PrintCommand(DIV, output);
		if(strstr(source.strings[i].str, "sin") != nullptr)
			PrintCommand(SIN, output);
		if(strstr(source.strings[i].str, "cos") != nullptr)
			PrintCommand(COS, output);
		if(strstr(source.strings[i].str, "sqrt") != nullptr)
			PrintCommand(SQRT, output);
		if(strstr(source.strings[i].str, "neg") != nullptr)
			PrintCommand(NEG, output);
		if(strstr(source.strings[i].str, "out") != nullptr)
			PrintCommand(OUT, output);
		if(strstr(source.strings[i].str, "in") != nullptr)
			PrintCommand(IN, output);
		if(strstr(source.strings[i].str, "dump") != nullptr)
			PrintCommand(DUMP, output);
		if(strstr(source.strings[i].str, "hack") != nullptr)
			PrintCommand(HACK, output);
		if(strstr(source.strings[i].str, "halt") != nullptr)
			PrintCommand(HALT, output);
	}
}

void Disassembler(char* code, char* text){

	FILE* file = fopen(text, "w");
	assert(file);

	char* buffer = nullptr;
	int n_sym = 0;
	CreateBuffer(&buffer, code, &n_sym);
	char* ptr = buffer;
	int command = 0;

	while(ptr < (buffer + sizeof(char) * n_sym)){
		command = *(ptr);
		switch(command){
			case PUSH: 	ptr += sizeof(char);
						fprintf(file, "push %lg\n", *(element*)ptr);
						ptr += sizeof(element) - 1;
						break;
			case ADD: 	fprintf(file, "add\n");
						break;
			case SUB: 	fprintf(file, "sub\n");
						break;
			case MUL: 	fprintf(file, "mul\n");
						break;
			case DIV: 	fprintf(file, "div\n");
						break;
			case SIN: 	fprintf(file, "sin\n");
						break;
			case COS: 	fprintf(file, "cos\n");
						break;
			case SQRT: 	fprintf(file, "sqrt\n");
						break;
			case NEG: 	fprintf(file, "neg\n");
					  	break;
			case OUT: 	fprintf(file, "out\n");
					  	break;
			case IN: 	fprintf(file, "in\n");
					 	break;
			case DUMP: 	fprintf(file, "dump\n");
					   	break;
			case HACK: 	fprintf(file, "hack\n");
					   	break;
			case HALT: 	fprintf(file, "halt\n");
					   	break;
			default: 	fprintf(file, "DEBIL\n");
						break;
		}
		ptr += sizeof(char);
	}

	fclose(file);
}