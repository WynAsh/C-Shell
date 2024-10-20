#ifndef __USERIO_H
#define __USERIO_H

extern char* prepath;
extern int sleep_flag;
extern char* PastCommands[15];
extern int numCommands;

extern int sleep_flag;
extern char LongCommand[4096];
extern pid_t shell_pid;
extern pid_t fg_pid;
extern nodeptr temp_head;

char *homemade_strtok(char *str, const char *delimiters);
void UserInput(char* input,char* HomeDir,nodeptr head);
void RunProc(char* Process,char* HomeDir,nodeptr head); 
void ExecvpBG(char* Process,char* HomeDir,nodeptr head);
void ExecvpFG(char* Process,char* HomeDir,nodeptr head);
void manipulateString(char *input);
void ReplaceSubstring(char* input,char* ExistingSubstring,char* NewSubstring);
// void InputParsing(char* input,char* HomeDir,nodeptr head);

#endif