#pragma once
#include <math.h>
#include "src/strcmp.h"
#include "src/stack.h"

struct Proc{
	Stack tack;
	int* registers;
};

enum commands{
	PUSH = 1,
	ADD,
	SUB,
	MUL,
	DIV,
	SIN,
	COS,
	SQRT,
	NEG,
	OUT, //printf(POP)
	IN,
	DUMP, //printf DUMP
	HACK,
	HALT //stop processor
};

void PrintCommand(char com, FILE* file);

void PrintValue(double val, FILE* file);

void Assembler(char* buffer, char* code);

void Disassembler(char* code, char* text);

int Processor(char* code);