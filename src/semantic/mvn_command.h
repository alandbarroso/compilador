/*
*	mvn_command.h
*
* 	Created on: Nov 29, 2013
*		Author: alan
*/

#ifndef MVN_COMMAND_H_
#define MVN_COMMAND_H_

#include "../linked_list/linked_list.h"

typedef enum
{
	ORG,
	K,
	BM,
	FIM,
	ORG2,
	EP,
	EX,
	JP,
	JZ,
	JN,
	LV,
	ADD,
	SUB,
	MUL,
	DIV,
	LD,
	MM,
	SC,
	RS,
	HM,
	GD,
	PD,
	OS
} Command;

typedef struct
{
	char* label;
	Command command;
	char* operand;
} MvnCommand;

extern const char cmd_ORG[];
extern const char cmd_K[];
extern const char cmd_BM[];
extern const char cmd_FIM[];
extern const char cmd_ORG2[];
extern const char cmd_EP[];
extern const char cmd_EX[];
extern const char cmd_JP[];
extern const char cmd_JZ[];
extern const char cmd_JN[];
extern const char cmd_LV[];
extern const char cmd_ADD[];
extern const char cmd_SUB[];
extern const char cmd_MUL[];
extern const char cmd_DIV[];
extern const char cmd_LD[];
extern const char cmd_MM[];
extern const char cmd_SC[];
extern const char cmd_RS[];
extern const char cmd_HM[];
extern const char cmd_GD[];
extern const char cmd_PD[];
extern const char cmd_OS[];

MvnCommand* init_command(char* label, Command cmd, char *operand);

void command_set_label(MvnCommand* command, char* label);

void command_set_operand(MvnCommand* command, char* operand);

char* print_command(MvnCommand* command);

int equals_mvn_command(ElementType, ElementType);

#endif /* MVN_COMMAND_H_ */