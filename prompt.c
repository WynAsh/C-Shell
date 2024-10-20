#include "headers.h"

void prompt(char* CWD, char* HomeDir) {
    // Do not hardcode the prmopt
    char currentwd[4096],hostname[4096],username[4096];
    if (getcwd(currentwd, sizeof(currentwd)) == NULL) {
            perror("cwd");
            exit(1);
    }
    if (gethostname(hostname, sizeof(hostname)) != 0) {
        perror("Hostname");
        exit(1);
    }

    struct passwd *pw;
    uid_t uid = geteuid();
    pw = getpwuid(uid);
    if (pw == NULL) {
        perror("PasswordID");
        exit(1);
    }

    char *baseDir = strrchr(currentwd, '/');
    if (baseDir) {
        baseDir++;
    } else {
        baseDir = currentwd;
    }

    if(strcmp(HomeDir,currentwd)==0){
        if(sleep_flag>0){
            printf( GREEN BOLD"%s@%s:" BLUE "~ %s : %d"WHITE "$ " NORMAL, pw->pw_name, hostname,LongCommand,sleep_flag);
        }
        else{
            printf( GREEN BOLD"%s@%s:" BLUE "~"WHITE "$ " NORMAL, pw->pw_name, hostname);
        }
    }
    else if(strlen(HomeDir)>strlen(currentwd)){
        if(sleep_flag>0){
            printf( GREEN BOLD "%s@%s:" BLUE "%s %s : %d"WHITE "$ " NORMAL, pw->pw_name, hostname,currentwd,LongCommand,sleep_flag);
        }
        else{
            printf( GREEN BOLD "%s@%s:" BLUE "%s"WHITE "$ " NORMAL, pw->pw_name, hostname,currentwd);
        }
    }
    
    else{
        char* CommonDir = GetCurrentDir(HomeDir);
        if(sleep_flag>0){
            printf( GREEN BOLD "<%s@%s:" BLUE "~/%s %s : %d> "WHITE NORMAL, pw->pw_name, hostname, CommonDir,LongCommand,sleep_flag);
        }
        else{   
            printf( GREEN BOLD "<%s@%s:" BLUE "~/%s$> "WHITE NORMAL, pw->pw_name, hostname, CommonDir);
        }
    }
    // printf(" %d",sleep_flag);
    sleep_flag=0;
    LongCommand[0]='\0';
}

void init_shell(){
    printf("\e[1;1H\e[2J");
     // regex command to clear the screen
    printf("Shell Initialized\n");
    sleep(1);
    printf("\e[1;1H\e[2J");
}
