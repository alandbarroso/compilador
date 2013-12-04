/*
* mvn_command.c
*
*  Created on: Nov 29, 2013
*      Author: alan
*/

#include "mvn_command.h"
#include <stdlib.h>
#include <string.h>

const char cmd_ORG[]= "@";
const char cmd_K[]= "K";
const char cmd_BM[]= "$";
const char cmd_FIM[]= "#";
const char cmd_ORG2[]= "&";
const char cmd_EP[]= ">";
const char cmd_EX[]= "<";
const char cmd_JP[] = "JP";
const char cmd_JZ[] = "JZ";
const char cmd_JN[] = "JN";
const char cmd_LV[] = "LV";
const char cmd_ADD[] = "+";
const char cmd_SUB[] = "-";
const char cmd_MUL[] = "*";
const char cmd_DIV[] = "/";
const char cmd_LD[] = "LD";
const char cmd_MM[] = "MM";
const char cmd_SC[] = "SC";
const char cmd_RS[] = "RS";
const char cmd_HM[] = "HM";
const char cmd_GD[] = "GD";
const char cmd_PD[] = "PD";
const char cmd_OS[] = "OS";

MvnCommand* init_command(char* label, Command cmd, char *operand)
{
	MvnCommand* command = (MvnCommand*) malloc(sizeof(MvnCommand));

	command->label = (char*) malloc(sizeof(char));
	command->label[0] = '\0';

	command->command = cmd;

	command->operand = (char*) malloc(sizeof(char));
	command->operand[0] = '\0';

	command_set_label(command, label);
	command_set_operand(command, operand);

	return command;
}

void command_set_label(MvnCommand* command, char* label)
{
	free(command->label);

	command->label = (char*) malloc((strlen(label) + 1)*sizeof(char));
	strcpy(command->label, label);
}

char* print_command(MvnCommand* command)
{
	char* line = (char*) malloc((strlen(command->label) + 1 + 2 + 1 + strlen(command->operand) + 2)*sizeof(char));

	if(strlen(command->label) > 1)
	{
		strcpy(line, command->label);

		strcat(line, " ");
	}

	switch(command->command)
	{
		case ORG:
			strcat(line, cmd_ORG);
			break;
		case K:
			strcat(line, cmd_K);
			break;
		case BM:
			strcat(line, cmd_BM);
			break;
		case FIM:
			strcat(line, cmd_FIM);
			break;
		case ORG2:
			strcat(line, cmd_ORG2);
			break;
		case EP:
			strcat(line, cmd_EP);
			break;
		case EX:
			strcat(line, cmd_EX);
			break;
		case JP:
			strcat(line, cmd_JP);
			break;
		case JZ:
			strcat(line, cmd_JZ);
			break;
		case JN:
			strcat(line, cmd_JN);
			break;
		case LV:
			strcat(line, cmd_LV);
			break;
		case ADD:
			strcat(line, cmd_ADD);
			break;
		case SUB:
			strcat(line, cmd_SUB);
			break;
		case MUL:
			strcat(line, cmd_MUL);
			break;
		case DIV:
			strcat(line, cmd_DIV);
			break;
		case LD:
			strcat(line, cmd_LD);
			break;
		case MM:
			strcat(line, cmd_MM);
			break;
		case SC:
			strcat(line, cmd_SC);
			break;
		case RS:
			strcat(line, cmd_RS);
			break;
		case HM:
			strcat(line, cmd_HM);
			break;
		case GD:
			strcat(line, cmd_GD);
			break;
		case PD:
			strcat(line, cmd_PD);
			break;
		case OS:
			strcat(line, cmd_OS);
			break;
	}

	strcat(line, " ");

	strcat(line, command->operand);

	strcat(line, "\n");

	return line;
}

void command_set_operand(MvnCommand* command, char* operand)
{
	free(command->operand);

	command->operand = (char*) malloc((strlen(operand) + 1)*sizeof(char));
	strcpy(command->operand, operand);
}

int equals_mvn_command(ElementType x1, ElementType x2)
{
	return 0;
}