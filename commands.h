#ifndef COMMANDS_H_
#define COMMANDS_H_
extern char* prepath;

extern int sleep_flag;
extern char LongCommand[4096];
extern pid_t shell_pid;
extern pid_t fg_pid;
extern nodeptr temp_head;
extern char HomeDirGlob[4096];


void Warp(char* HomeDir,char* Command);
void PWD();
void Peek(char* HomeDir,char* Command);
void PastEvents(char* HomeDir,char* Command,nodeptr head);
void Proclore(char* input, char* HomeDir, nodeptr head);
void Seek(char* HomeDir,char* Command);
void SeekRecursive(char* SearchQuery,char* Target,int d_flag,int f_flag,int e_flag,char* currentwd);
void Activities2(char* input,char* HomeDir,nodeptr head);
void Activities(char* input, char* HomeDir);
void Neonate(char* input,char* HomeDir,nodeptr head);
void fg(char* input, char* HomeDir, nodeptr head);
void CtrlC();
void CtrlZ();
void CtrlD();
void IMan(char* input,char* HomeDir,nodeptr head);

#endif