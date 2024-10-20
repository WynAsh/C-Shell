#include "headers.h"


char *homemade_strtok(char *str, const char *delimiters) {
    static char *current = NULL;
    if (str){
        current = str;
    }
    if (!current){
        return NULL;
    }
    char *start = current;
    char *token;

    while (*current && strchr(delimiters, *current)){
        ++current;
    }
    if (!*current){
        return NULL;
    }
    start = current;
    while (*current && !strchr(delimiters, *current)){
        ++current;
    }
    if (*current) {
        *current = '\0';
        token = start;
        ++current;
    } 
    else {
        token = start;
        current = NULL;
    }

    return token;
}


void ReplaceSubstring(char* input,char* ExistingSubstring,char* NewSubstring){
    char temp[4096];
    int i=0;
    int j=0;
    while(input[i]!='\0'){
        if(input[i]==ExistingSubstring[0]){
            int k=0;
            int flag=1;
            while(ExistingSubstring[k]!='\0'){
                if(input[i+k]!=ExistingSubstring[k]){
                    flag=0;
                    break;
                }
                k++;
            }
            if(flag==1){
                int l=0;
                while(NewSubstring[l]!='\0'){
                    temp[j++]=NewSubstring[l++];
                }
                i+=k;
            }
            else{
                temp[j++]=input[i++];
            }
        }
        else{
            temp[j++]=input[i++];
        }
    }
    temp[j]='\0';
    strcpy(input,temp);
}


void UserInput(char* input, char* HomeDir,nodeptr head) {
    if (input[0] == '\n') {
        return;
    }
    manipulateString(input);
    ReplaceSubstring(input,"&","&;");
    int bgflag = 0;
    char** SCSplit=malloc(sizeof(char*)*4096);
    char* context;
    char *SCToken = strtok_r(input, ";",&context);
    char com[4096];
    while (SCToken != NULL) {
        strcpy(com,SCToken);
        char* context2;
        if(com[strlen(com)-1]=='&'){
            //replace & in string with \0
            com[strlen(com)-1]='\0';
            // printf("skill issues : %s\n",com);
            // if(com[strlen(com)-1]=='&'){
            //     bgflag=1;
            // }
            // char* AMPToken=strtok_r(com,"&",&context2);
            ExecvpBG(com, HomeDir,head);
            // AMPToken=strtok_r(NULL,"&",&context2);
            // ExecvpFG(AMPToken, HomeDir,head);
        }
        else{
            if(strchr(input,'|')!=NULL || strchr(input,'>')!=NULL || strchr(input,'<')!=NULL){
                HandlePipe(input,HomeDir,head);
                continue;
            }
            RunProc(com, HomeDir ,head);
        }
        SCToken = strtok_r(NULL, ";",&context);
    }
}

void ExecvpFG(char* Process,char* HomeDir,nodeptr head){
    int status;
    pid_t pid = fork();
    if(pid<0){
        // waitpid(pid,&status,WNOHANG);
        perror("fork");
        return;
    }
    else if(pid==0){
        char temp[4096];
        strcpy(temp,Process);
        char* SPtoken=strtok(temp," ");
        char* arguments[4096];
        int i=0;
        while(SPtoken!=NULL){
            arguments[i++]=SPtoken;
            SPtoken=strtok(NULL," ");
        }
        arguments[i]=NULL;
        if(strcmp(arguments[0],"sleep")==0){
            sleep_flag=atoi(arguments[1]);
        }
        if(execvp(arguments[0],arguments)>=0){
            // SaveCommand(Process,HomeDir);
        }
        else{
            printf("Error: Command not found : %s\n", arguments[0]);
            exit(1);
        }
    }
    else{
        fg_pid=pid;
        waitpid(pid, &status, 0);
        return;
    }
    
}

void ExecvpBG(char* Process,char* HomeDir,nodeptr head){
    int status;
    pid_t pid = fork();
    if(pid<0){
        // waitpid(pid,&status,WNOHANG);
        perror("fork");
        return;
    }
    else if(pid==0){
        setpgid(0,0);
        char temp[4096];
        strcpy(temp,Process);
        char* SPtoken=strtok(temp," ");
        char* arguments[4096];
        int i=0;
        while(SPtoken!=NULL){
            arguments[i++]=SPtoken;
            SPtoken=strtok(NULL," ");
        }
        arguments[i]=NULL;
        if(execvp(arguments[0],arguments)<0){
            printf("Error: Command not found : %s\n", arguments[0]);
        }
    }
    else{
        printf("%d\n",pid);
        AddToLL(head, pid, Process);
        return;
    }
}

void RunProc(char* Process,char* HomeDir,nodeptr head){
    char temp[4096];
    clock_t start, end;
    double cpu_time_used;
    strcpy(temp,Process);
    char* SPtoken=strtok(temp," ");
    for (int i = 0; i < strlen(SPtoken); i++) {
        if (SPtoken[i] == '\n') {
            SPtoken[i] = '\0';
        }
    }
    int t;
    if(strcmp(SPtoken,"warp")==0){
        // SaveCommand(Process,HomeDir);
        t=time(NULL);
        Warp(HomeDir,Process);
        t=time(NULL)-t;
    }
    else if(strcmp(SPtoken,"pwd")==0){
        // SaveCommand(Process,HomeDir);
        t=time(NULL);
        PWD();
        t=time(NULL)-t;
    }
    else if(strcmp(SPtoken,"peek")==0){
        // SaveCommand(Process,HomeDir);
        t=time(NULL);
        Peek(HomeDir,Process);
        t=time(NULL)-t;
    }
    else if(strcmp(SPtoken,"pastevents")==0){
        t=time(NULL);
        PastEvents(HomeDir,Process,head);
        t=time(NULL)-t;
    }
    else if(strcmp(SPtoken,"proclore")==0){
        // SaveCommand(Process,HomeDir);
        t=time(NULL);
        Proclore(Process,HomeDir,head);
        t=time(NULL)-t;
    }
    else if(strcmp(SPtoken,"seek")==0){
        // SaveCommand(Process,HomeDir);
        t=time(NULL);
        Seek(HomeDir,Process);
        t=time(NULL)-t;
    }
    else if(strcmp(SPtoken,"activities")==0){
        // SaveCommand(Process,HomeDir);
        t=time(NULL);
        Activities(Process,HomeDir);
        t=time(NULL)-t;
    }
    else if(strcmp(SPtoken,"neonate")==0){
        // SaveCommand(Process,HomeDir);
        t=time(NULL);
        Neonate(Process,HomeDir,head);
        t=time(NULL)-t;
    }
    else if(strcmp(SPtoken,"fg")==0){
        // SaveCommand(Process,HomeDir);
        t=time(NULL);
        fg(Process,HomeDir,head);
        t=time(NULL)-t;
    }
    
    else if(strcmp(SPtoken,"exit")==0){
        printf("\e[1;1H\e[2J"); // regex command to clear the screen
        printf("Shell Terminated\n");
        sleep(1);
        printf("\e[1;1H\e[2J"); // regex command to clear the screen
        exit(0);
    }
    else if(strcmp(SPtoken,"activities2")==0){
        Activities2(Process,HomeDir,head);
    }
    else if(strcmp(SPtoken,"bgproc")==0){
        nodeptr temp=temp_head;
        while(temp!=NULL){
            printf("%d , %s , %d\n",temp->pid,temp->name,temp->active);
            temp=temp->next;
        }
    }
    else if(strcmp(SPtoken,"iMan")==0 || strcmp(SPtoken,"iman")==0){
        // SaveCommand(Process,HomeDir);
        t=time(NULL);
        IMan(Process,HomeDir,head);
        t=time(NULL)-t;
    }
    else{
        // printf(RED "ERROR : %s",SPtoken);
        // printf(" is not a valid command.\n");
        t=time(NULL);
        ExecvpFG(Process,HomeDir,head);
        t=time(NULL)-t;
    }
    // cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    // int rounded_seconds = (int)cpu_time_used;
    // // floor(cpu_time_used);
    if(t>=2){
        sleep_flag=t;
        strcpy(LongCommand,SPtoken);
    }

}


void manipulateString(char *input) {
    char space = ' ';
    char *pos;

    char *tab = "\t";
    pos = strchr(input, '\t');
    while (pos != NULL) {
        *pos = space;
        pos = strchr(pos + 1, '\t');
    }

    pos = strchr(input, '\n');
    while (pos != NULL) {
        *pos = '\0';
        pos = strchr(pos + 1, '\n');
    }

    pos = strstr(input, "  ");
    while (pos != NULL) {
        char *start = pos;
        char *end = pos + 1;
        while (*end == ' ') {
            end++;
        }
        memmove(start + 1, end, strlen(end) + 1);
        pos = strstr(input, "  ");
    }
}

// void InputParsing(char* input,char* HomeDir,nodeptr head){


//     struct termios o1, o2;
//     tcgetattr(STDIN_FILENO, &o1);
//     o2 = o1;
//     o2.c_lflag &= ~(ICANON | ECHO);
//     tcsetattr(STDIN_FILENO, TCSAFLUSH, &o2);
//     setbuf(stdout, NULL);


//     char inp;
//     char* inputstring=malloc(sizeof(char)*4096);
//     int index=0;
//     while(read(STDIN_FILENO,&inp,1)==1){
//         // if(inp=='x'){
//         //     printf("X_flag is set");
//         // }
//         if(!iscntrl(inp)){
//             printf("%c",inp);
//             inputstring[index++]=inp;
//             inputstring[index]='\0';
//         }
//         if(inp==127){
//             if(index>0){
//                 printf("\b \b");
//                 inputstring[--index]='\0';
//             }
//         }
//         else if(inp=='\n'){
//             printf("\n");
//             inputstring[index]='\0';
//             if(strchr(inputstring,'|')!=NULL){
//                 HandlePipe(inputstring,HomeDir,head);
//             }
//             else{
//                 UserInput(inputstring,HomeDir,head);
//             }
//             // UserInput(inputstring,HomeDir,head);
//             index=0;
//             return;
//         }
//     }
//     tcsetattr(STDIN_FILENO, TCSAFLUSH, &o1);
    
// }