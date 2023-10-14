#ifndef SHELL-H
#define SHELL-H

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

void read-command(char *formmat,size_t size);
void execute_command(const char *formmat);
void Aisha_print(const char *formmat);
void display_the_prompt(void);


#endif
