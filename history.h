#ifndef __HISTORY_H
#define __HISTORY_H

extern char* PastCommands[15];
extern int numCommands;

extern int sleep_flag;
extern char LongCommand[4096];

void SaveCommand(char *Command, char *HomeDir);
void HistoryPurge(char* HomeDir);

#endif