#include "headers.h"




char* prepath;
int sleep_flag;
char LongCommand[4096];
pid_t shell_pid;
pid_t fg_pid;
nodeptr temp_head;
char HomeDirGlob[4096];

char* PastCommands[15];
int numCommands;


void RunTerminal(char* HomeDir,char* CWD,nodeptr head){
    while (1)
    {
        sigset_t oldmask; sigemptyset(&oldmask); sigprocmask(SIG_BLOCK, NULL, &oldmask); 
        sigaddset(&oldmask, SIGTSTP);
        sigaddset(&oldmask, SIGINT);
        sigaddset(&oldmask, SIGQUIT);
        sigprocmask(SIG_UNBLOCK, &oldmask, NULL);

        
        fg_pid=-1;
        prompt(CWD,HomeDir);
        char input[4096];
        char* Checks=fgets(input, 4096, stdin);
        
        if(Checks==NULL){
            printf("\e[1;1H\e[2J"); // regex command to clear the screen
            exit(0);
        }
        RemoveFromLL(head);
        manipulateString(input);
        SaveCommand(input,HomeDir);
        UserInput(input,HomeDir,head);
        // break;
    }
}




int main()
{
    init_shell();
    char HomeDir[4096];
    if (getcwd(HomeDir, sizeof(HomeDir)) == NULL) {
            perror("cwd");
            exit(1);
    }
    strcpy(HomeDirGlob,HomeDir);
    char CWD[4096];
    strcpy(CWD,HomeDir);
    strcpy(HomeDirGlob,HomeDir);
    prepath=malloc(sizeof(char)*4096);
    shell_pid=getpid();
    numCommands=0;
    sleep_flag=0;
    for(int i=0;i<15;i++){
        PastCommands[i]=malloc(sizeof(char)*4096);
    }
    nodeptr head = CreateHeadNode();
    temp_head=head;


    signal(SIGINT,CtrlC);
    signal(SIGTSTP,CtrlZ);

    // struct sigaction act;
    // act.sa_flags = SA_RESTART;
    // act.sa_handler = CtrlC;
    // sigaction(SIGINT, &act, NULL);




    // printf("%p,  %s\n",temp_head,Ho);
    RunTerminal(HomeDir,CWD,head);
    
}
