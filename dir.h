#ifndef DIR_H_
#define DIR_H_

extern int sleep_flag;
extern char LongCommand[4096];

char* GetCurrentDir(char* HomeDir);
char* RelativePath(char* MainDir,char* SubPath);
void ShowFiles(char* AbsPath,int showHidden,int showDetails);
void PrintFileContents(char* path);
#endif