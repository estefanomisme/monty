#define _GNU_SOURCE
#include "monty.h"

/**
 * match_func - looks for a given instruction in the monty functions and
 * executes it if found
 * @s: the given instruction
 * @stack: the stack on which the function will be executed
 * @line: the number of the line when is the given instruction
 *
 * Return: 1 if the function could be executed succesfully, or 0 otherwise
 */
int match_func(char **s, stack_t **stack, unsigned int line)
{
	int i = 0;
	instruction_t instruct[] = {
		{"push", _push},
		{"pall", _pall},
		{"pint", _pint},
		{"pop", _pop},
		{"swap", _swap},
		{"pchar", _pchar},
		{"add", _add},
		{"sub", _sub},
		{"mul", _mul},
		{"div", _div},
		{"mod", _mod},
		{"nop", _nop},
		{"rotl", _rotl},
		{"rotr", _rotr},
		{"pstr", _pstr},
		{"stack", _stack},
		{"queue", _queue},
		{NULL, NULL},
	};

	while (instruct[i].f != NULL &&
			strcmp(instruct[i].opcode, s[0]) != 0)
		i++;
	if (instruct[i].f == NULL)
	{
		fprintf(stderr, "L%d: unknown instruction %s\n", line, s[0]);
		return (0);
	}
	arguments = s;
	instruct[i].f(stack, line);
	if (statusfunc == 0)
		return (0);
	return (1);
}

/**
 * read_file - reads the given file and executes all its monty instructions
 * @file: the name of the file. It must have a ".m" extension
 * @stack: the stack on which all the instructions will be executed
 *
 * If there was an error, the function will "EXIT_FAILURE", but if there
 * wasn't, the function returns to main
 * Return: Nothing
 */
void read_file(char *file, stack_t **stack)
{
	FILE *monty;
	size_t buffer_len = 0;
	char *buffer = NULL, *buffercur = NULL;
	char **args;
	int line = 1, stat = -1;

	monty = fopen(file, "r");
	montyflag = 0;
	if (monty == NULL)
	{
		fprintf(stderr, "Error: Can't open file %s\n", file);
		exit(EXIT_FAILURE);
	}
	while (getline(&buffer, &buffer_len, monty) != EOF)
	{
		buffercur = cure_buffer(buffer);
		if (buffercur != NULL)
		{
			if (*buffercur != '#')
			{
				args = _strtok_all(buffercur, " \n");
				stat = match_func(args, stack, line);
				free_args(args);
			}
			free(buffercur);
		}
		free(buffer);
		buffer = NULL;
		if (stat == 0)
		{
			free_stack((*stack));
			fclose(monty);
			exit(EXIT_FAILURE);
		}
		line++;
	}
	free(buffer);
	fclose(monty);
}
