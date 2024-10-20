#ifndef __PROMPT_H
#define __PROMPT_H

extern int sleep_flag;
extern char LongCommand[4096];
void prompt(char* CWD, char* HomeDir);
void init_shell();

#endif