#ifndef HEADERS_H_
#define HEADERS_H_

#include <ctype.h>
#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <grp.h>
#include <math.h>
#include <pwd.h>
#include <signal.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <termios.h>
#include <time.h>
#include <unistd.h>
#include <netdb.h>
#include <arpa/inet.h>

#define GREEN "\033[00;32m"
#define BLUE "\033[00;36m"
#define RED "\033[00;31m"
#define YELLOW "\033[00;33m"
#define WHITE "\033[00;37m"
#define COLOR_RESET "\033[00m"
#define BOLD "\033[1m"
#define NORMAL "\033[0m"



typedef struct node {
    pid_t pid;
    int active;
    char *name;
    struct node *next;
} node;

typedef node* nodeptr;

extern char* prepath;
extern int sleep_flag;
extern char LongCommand[4096];
extern pid_t shell_pid;
extern pid_t fg_pid;
extern nodeptr temp_head;
extern char HomeDirGlob[4096];


#include "prompt.h"
#include "dir.h"
#include "userio.h"
#include "commands.h"
#include "history.h"
#include "LL.h"
#include "redirection.h"

void RunTerminal(char* HomeDir,char* CWD,nodeptr head);

#endif