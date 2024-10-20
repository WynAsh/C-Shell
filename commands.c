#include "headers.h"

void Warp(char* HomeDir, char* Command) {
    if (Command[4] == '\n' || Command[4] == '\0') {
        chdir(HomeDir);
        return;
    }

    char currentwd[4096];
    char InputCMD[4096];
    char* Dirs[100];
    for (int i = 0; i < 100; i++) {
        Dirs[i] = NULL;
    }

    if (getcwd(currentwd, sizeof(currentwd)) == NULL) {
        perror("cwd");
        exit(1);
    }
    strcpy(InputCMD, Command);
    char PrevDir[4096];
    strcpy(PrevDir, currentwd);    
    char* SPToken = strtok(InputCMD, " ");
    int i = 0;
    while (SPToken != NULL) {
        Dirs[i++] = SPToken;
        SPToken = strtok(NULL, " ");
    }

    for (int j = 1; j < i; j++) {
        int len = strlen(Dirs[j]);
        if (Dirs[j][len - 1] == '\n') {
            Dirs[j][len - 1] = '\0';
        }
        if (strcmp(Dirs[j], "..") == 0) {
            // printf("success\n");
            strcpy(prepath,currentwd);
            if (chdir("..") == -1) {
                // printf("failure\n");
                perror("warp");
            }
            if (getcwd(currentwd, sizeof(currentwd)) == NULL) {
                perror("cwd");
                exit(1);
            }
        }
        else if(Dirs[j][0]=='~' && Dirs[j][1]=='/'){
            strcpy(prepath,currentwd);
            strcpy(currentwd,HomeDir);
            strcat(currentwd,&Dirs[j][1]);
            if (chdir(currentwd) == -1) {
                perror("warp");
            }
        }
        else if(Dirs[j][0]=='.' && Dirs[j][1]=='/'){
            strcpy(prepath,currentwd);
            strcat(currentwd,&Dirs[j][1]);
            if (chdir(currentwd) == -1) {
                perror("warp");
            }
        }
        else if (Dirs[j][0] == '/') {
            strcpy(prepath,currentwd);
            if (chdir(Dirs[j]) == -1) {
                perror("warp");
            }
            strcpy(currentwd, Dirs[j]);
        }
        else if (strcmp(Dirs[j], "~") == 0) {
            strcpy(prepath,currentwd);
            if (chdir(HomeDir) == -1) {
                perror("warp");
            }
            strcpy(currentwd, HomeDir);
        }
        else if (strcmp(Dirs[j], ".") == 0) {
            strcpy(prepath,currentwd);
            return;
        }
        else if (strcmp(Dirs[j], "-") == 0) {
            // printf("%s\n",prepath);
            if(prepath[0]=='\0'){
                printf("OLDPWD not set!\n");
                return;
            }
            else{
                if (chdir(prepath) == -1) {
                    perror("warp");
                }
            }
        }
        else {
            strcpy(prepath,currentwd);
            strcat(currentwd, "/");
            strcat(currentwd, Dirs[j]);
            if (chdir(currentwd) == -1) {
                perror("warp");
            }
        }
    }
    if (getcwd(currentwd, sizeof(currentwd)) == NULL) {
        perror("cwd");
        exit(1);
    }
}

void PWD(){
    char currentwd[4096];
    if (getcwd(currentwd, sizeof(currentwd)) == NULL) {
        perror("cwd");
        exit(1);
    }
    printf("%s\n", currentwd);
}

void Peek(char* HomeDir,char* Command){
    int a_flag=0,l_flag=0,fof=0;
    char InputCMD[4096];
    char currentwd[4096];
    char* Dirs[100];
    for(int i=0;i<100;i++){
        Dirs[i]=NULL;
    }
    strcpy(InputCMD,Command);
    char* SPToken = strtok(InputCMD, " ");
    int i=0;
    while (SPToken != NULL) {
        Dirs[i++] = SPToken;
        SPToken = strtok(NULL, " ");
    }
    if (getcwd(currentwd, sizeof(currentwd)) == NULL) {
        perror("cwd");
        exit(1);
    }
    char tempDir[4096];
    strcpy(tempDir,currentwd);
    for(int j=1;j<i;j++){
        int len = strlen(Dirs[j]);
        if (Dirs[j][len - 1] == '\n') {
            Dirs[j][len - 1] = '\0';
        }
       if(strcmp(Dirs[j],"-a")==0){
           a_flag=1;
           fof++;
       }
       else if(strcmp(Dirs[j],"-l")==0){
           l_flag=1;
           fof++;
       }
       else if(strcmp(Dirs[j],"-al")==0 || strcmp(Dirs[j],"-la")==0){
           a_flag=1;
           l_flag=1;
           fof++;
       }
    }
    if(strcmp(Command,"peek")==0 || strcmp(Command,"peek -l")==0 || strcmp(Command,"peek -a")==0 || strcmp(Command,"peek -al")==0 || strcmp(Command,"peek -la")==0 || strcmp(Command,"peek -l -a")==0 || strcmp(Command,"peek -a -l")==0){
        ShowFiles(currentwd,a_flag,l_flag);
    }
    

    for(int j=1;j<i;j++){
        if(Dirs[j][0] == '-' && (Dirs[j][1] == 'a' || Dirs[j][1] == 'l')){
            continue;
        }
        if (strcmp(Dirs[j], "..") == 0) {
            if (chdir("..") == -1) {
                // printf("failure\n");
                perror("warp1");
            }
            if (getcwd(currentwd, sizeof(currentwd)) == NULL) {
                perror("cwd");
                exit(1);
            }
            ShowFiles(currentwd,a_flag,l_flag);
        }
        else if (Dirs[j][0] == '/') {
            ShowFiles(Dirs[j],a_flag,l_flag);
        }
        else if(strcmp(Dirs[j],"~")==0){
            ShowFiles(HomeDir,a_flag,l_flag);
        }
        else if(strcmp(Dirs[j],".")==0 || Dirs[j]==NULL){
            ShowFiles(currentwd,a_flag,l_flag);
        }
        if(Dirs[j][0]=='~' && Dirs[j][1]=='/'){
            strcpy(currentwd,HomeDir);
            strcat(currentwd,&Dirs[j][1]);
            ShowFiles(currentwd,a_flag,l_flag);
        }
        else if(strcmp(Dirs[j],"-")==0){
            ShowFiles(prepath,a_flag,l_flag);
        }
        else{
            strcat(currentwd, "/");
            strcat(currentwd, Dirs[j]);
            ShowFiles(currentwd,a_flag,l_flag);
        }
    }
    if(chdir(tempDir)==-1){
        perror("warp");
    }

}

void PastEvents(char* HomeDir, char* Command, nodeptr head) {
    char* temp=malloc(sizeof(char)*4096);
    strcpy(temp,HomeDir);
    strcat(temp,"/CommandCode.txt");
    // printf("%s\n",temp);
    int CommCode = open(temp, O_RDONLY);
    if (CommCode == -1) {
        perror("Error opening file");
        return;
    }

    off_t filesize = lseek(CommCode, 0, SEEK_END);
    if (filesize == -1) {
        perror("Error getting file size");
        close(CommCode);
        return;
    }

    lseek(CommCode, 0, SEEK_SET);

    char buffer[65536];
    ssize_t len = read(CommCode, buffer, sizeof(buffer));
    if (len == -1) {
        perror("Error reading file");
    }
    else {
        buffer[len] = '\0';
        if (strcmp(Command, "pastevents") == 0) {
            printf("%s", buffer);
            return;
        }
        char* SPToken=strtok(Command," ");
        SPToken=strtok(NULL," ");
        // printf("%s\n",SPToken);
        if(strcmp(SPToken,"purge")==0){
            HistoryPurge(HomeDir);
        }
        if(strcmp(SPToken,"execute")==0){
            SPToken=strtok(NULL," ");
            int num=atoi(SPToken);
            if(num>15){
                printf("Only 15 commands are stored in history!\n");
            }
            else{
                char* SPptr;
                SPToken=strtok_r(NULL," ",&SPptr);
                if(num>15){
                    printf("Only %d commands are stored in history!\n",numCommands);
                }
                else{
                    int CommCode = open(temp, O_RDWR | O_CREAT, 0777);
                    if (CommCode == -1) {
                        perror("Error opening file");
                        return;
                    }

                    off_t filesize = lseek(CommCode, 0, SEEK_END);
                    lseek(CommCode, 0, SEEK_SET);
                    ssize_t len = read(CommCode, buffer, sizeof(buffer));

                    int i = 0;
                    if (len > 0) {
                        char *SepPtr;
                        char *SepComm = strtok_r(buffer, "\n", &SepPtr);
                        while (SepComm != NULL) {
                            PastCommands[i] = (char *)malloc(strlen(SepComm) + 1);
                            strcpy(PastCommands[i++], SepComm);
                            SepComm = strtok_r(NULL, "\n", &SepPtr);
                        }
                    if (i > 0 && PastCommands[num - 1] != NULL) {
                        char tempstring[4096];
                        strcpy(tempstring,PastCommands[num - 1]);
                        RunProc(tempstring, HomeDir,head);
                    } else {
                        printf("No command found at index %d\n", num);
                    }



                    }
                }
            }
        }
    }

    close(CommCode);
}


void Proclore(char* input, char* HomeDir, nodeptr head){
    char procpath[4096]="/proc/";
    char* ProcSplit[10];
    char* SPToken=strtok(input," ");
    int i=0;
    while(SPToken!=NULL){
        ProcSplit[i++]=SPToken;
        SPToken=strtok(NULL," ");
    }
    if(i==1){
        strcat(procpath,"self/stat");
    }
    else{
        strcat(procpath,ProcSplit[1]);
        strcat(procpath,"/stat");
    }
    FILE* fd=fopen(procpath,"r");
    if(fd==NULL){
        perror("proclore");
        return;
    }
    char ProcLine[4096];
    fgets(ProcLine,4096,fd);
    // printf("%s\n",ProcLine);

    int pid;
    char status;
    int pgrp;
    unsigned long vmem;
    char exepath[4096];

    sscanf(ProcLine, "%d %*s %c %d %*s %*s %*s %*s %*s %*s %*s %lu", &pid, &status, &pgrp, &vmem);
    snprintf(exepath, sizeof(exepath), "/proc/%d/exe", pid);

    char statusStr[10];
    if (status == 'R') {
        if (pgrp == tcgetpgrp(STDIN_FILENO)) {
            strcpy(statusStr, "R+");
        } else {
            strcpy(statusStr, "R");
        }
    } else if (status == 'S') {
        if (pgrp == tcgetpgrp(STDIN_FILENO)) {
            strcpy(statusStr, "S+");
        } else {
            strcpy(statusStr, "S");
        }
    } else if (status == 'Z') {
        strcpy(statusStr, "Z");
    } else {
        strcpy(statusStr, "Unknown");
    }

    printf("PID: %d\n", pid);
    printf("Process Status: %s\n", statusStr);
    printf("Process Group: %d\n", pgrp);
    printf("Virtual Memory: %lu\n", vmem);
    printf("Executable Path: %s\n", exepath);

    fclose(fd);
}

void Seek(char* HomeDir,char* Command){
    int d_flag=0,e_flag=0,f_flag=0,searchflag=0;
    char InputCMD[4096];
    char currentwd[4096];
    if(getcwd(currentwd,sizeof(currentwd))==NULL){
        perror("cwd");
        exit(1);
    }
    char* SPToken=strtok(Command," ");
    char* Dirs[100];
    int i=0;
    while(SPToken!=NULL){
        if(strcmp(SPToken,"-d")==0){
            if(f_flag==1){
                printf("Invalid Flags!\n");
                return;
            }
            d_flag=1;
        }
        else if(strcmp(SPToken,"-e")==0){
            e_flag=1;
        }
        else if(strcmp(SPToken,"-f")==0){
            if(d_flag==1){
                printf("Invalid Flags!\n");
                return;
            }
            f_flag=1;
        }
        // else{
        //     Dirs[i++]=SPToken;
        // }
        Dirs[i++]=SPToken;
        SPToken=strtok(NULL," ");
    }
    char SearchQuery[4096],Target[4096];
    Target[0]='\0';
    for(int j=1;j<i;j++){
        if(Dirs[j][0]=='-'){
            continue;
        }
        else if(Dirs[j][0]=='~' && Dirs[j][1]=='/'){
            if(searchflag==0){
                // strcpy(SearchQuery,HomeDir);
                // strcat(SearchQuery,&Dirs[j][1]);
                strcpy(SearchQuery,Dirs[j]);
                searchflag=1;
            }
            else{
                strcpy(Target,HomeDir);
                strcat(Target,&Dirs[j][1]);
            }
        }
        else if(Dirs[j][0]=='.' && Dirs[j][1]=='/'){
            if(searchflag==0){
                // strcpy(SearchQuery,currentwd);
                // strcat(SearchQuery,&Dirs[j][1]);
                strcpy(SearchQuery,Dirs[j]);
                searchflag=1;
            }
            else{
                strcpy(Target,currentwd);
                strcat(Target,&Dirs[j][1]);
            }
        }
        else if(Dirs[j][0]=='/'){
            if(searchflag==0){
                // strcpy(SearchQuery,Dirs[j]);
                strcpy(SearchQuery,Dirs[j]);
                searchflag=1;
            }
            else{
                strcpy(Target,Dirs[j]);
            }
        }
        else if(strcmp(Dirs[j],"~")==0){
            if(searchflag==0){
                // strcpy(SearchQuery,HomeDir);
                strcpy(SearchQuery,Dirs[j]);
                searchflag=1;
            }
            else{
                strcpy(Target,HomeDir);
            }
        }
        else if(strcmp(Dirs[j],".")==0){
            if(searchflag==0){
                // strcpy(SearchQuery,currentwd);
                strcpy(SearchQuery,Dirs[j]);
                searchflag=1;
            }
            else{
                strcpy(Target,currentwd);
            }
        }
        else{
            if(searchflag==0){
                // strcat(SearchQuery,currentwd);
                // strcat(SearchQuery,"/");
                // strcat(SearchQuery,Dirs[j]);
                strcpy(SearchQuery,Dirs[j]);
                searchflag=1;
            }
            else{
                strcat(Target,currentwd);
                strcat(Target,"/");
                strcat(Target,Dirs[j]);
            }
        }            
    }
    if(Target[0]=='\0'){
        strcpy(Target,currentwd);
    }
    // printf("d_flag=%d e_flag=%d f_flag=%d ",d_flag,e_flag,f_flag);
    SeekRecursive(SearchQuery,Target,d_flag,f_flag,e_flag,Target);

}


void SeekRecursive(char *SearchQuery, char *Target, int d_flag, int f_flag, int e_flag, char *currentwd) {
    DIR *dir = opendir(Target);
    if (dir == NULL) {
        return;
    }

    struct dirent *entry;
    int dir_count = 0;
    int file_count = 0;

    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0 || entry->d_name[0] == '.') {
            continue;
        }

        char full_path[4096];
        snprintf(full_path, sizeof(full_path), "%s/%s", Target, entry->d_name);

        struct stat entry_stat;
        if (stat(full_path, &entry_stat) == -1) {
            continue;
        }

        if (S_ISDIR(entry_stat.st_mode)) {
            if (strstr(entry->d_name, SearchQuery) != NULL) {
                if (f_flag) {
                    continue;
                }
                if (e_flag) {
                    if (dir_count == 0 && file_count == 0) {
                        // Only one directory, change current working directory
                        if (access(full_path, X_OK) == 0) {
                            chdir(full_path);
                        } else {
                            printf(RED "Missing permissions for task!\n");
                        }
                    } else {
                        printf(RED "Multiple directories found!\n");
                    }
                    closedir(dir);
                    return;
                }
                printf(GREEN "./%s\n" NORMAL, RelativePath(currentwd, full_path));
            }
            dir_count++;
            SeekRecursive(SearchQuery, full_path, d_flag, f_flag, e_flag, currentwd);
        } else if (S_ISREG(entry_stat.st_mode)) {
            if (strstr(entry->d_name, SearchQuery) != NULL) {
                if (d_flag) {
                    continue;
                }
                if (e_flag) {
                    if (dir_count == 0 && file_count == 0) {
                        // Only one file, print its contents
                        if (access(full_path, R_OK) == 0) {
                            PrintFileContents(full_path);
                        } else {
                            printf(RED "Missing permissions for task!\n");
                        }
                    } else {
                        printf(RED "Multiple files found!\n");
                    }
                    closedir(dir);
                    return;
                }
                printf(BLUE "./%s\n" NORMAL, RelativePath(currentwd, full_path));
            }
            file_count++;
        }
    }
    closedir(dir);
}


void Ping(char* input, char* HomeDir, nodeptr head) {
    char* space;
    char* SPToken = strtok_r(input, " ", &space);
    SPToken = strtok_r(NULL, " ", &space);
    
    if (SPToken == NULL) {
        printf("Invalid Command!\n");
        return;
    }
    
    char* pingsplit[2];
    int i = 0;
    while (SPToken != NULL) {
        pingsplit[i++] = SPToken;
        SPToken = strtok_r(NULL, " ", &space);
    }

    int target_pid = atoi(pingsplit[0]);
    int signal_code = atoi(pingsplit[1]) % 32;

    if (kill(target_pid, signal_code) == 0) {
        printf("Sent signal %d to process with PID %d\n", signal_code, target_pid);
    } else {
        if (errno == ESRCH) {
            printf("No process found with PID %d\n", target_pid);
        } else {
            perror("kill");
        }
    }
}

void Activities2(char* input,char* HomeDir,nodeptr head){
    //print a list of all the processes currently running that were spawned by your shell
    nodeptr temp=head->next;
    char state[4096];
    while(temp!=NULL){
        if(temp->active==1){
            strcpy(state,"Running");
        }
        else{
            strcpy(state,"Stopped");
        }
        printf("%d : %s - %s\n",temp->pid,temp->name,state);
        temp=temp->next;
    }    
}

void Activities(char* input, char* HomeDir) {
    DIR *procdir;
    struct dirent *entry;
    if((procdir=opendir("/proc"))==NULL){
        perror("OpenDir");
        return;
    }

    while((entry=readdir(procdir))!=NULL){
        // printf("%s\n",entry->d_name);
        if(entry->d_type == DT_DIR && strspn(entry->d_name,"9876543210")==strlen(entry->d_name)){
            int pid=atoi(entry->d_name);
            char statpath[4096];
            snprintf(statpath,4096,"/proc/%d/status",pid);
            FILE *statfile=fopen(statpath,"r");
            if(statfile==NULL){
                perror("fopen");
                return;
            }

            char line[4096];
            int procppid=-1;
            while(fgets(line,4096,statfile)){
                if(strncmp(line,"PPid:",5)==0){
                    sscanf(line,"PPid:\t%d",&procppid);
                    break;
                }
            }
            fclose(statfile);

            if(procppid==shell_pid){
                char procstatpath[4096];
                snprintf(procstatpath,4096,"/proc/%d/stat",pid);
                FILE *procstatfile=fopen(procstatpath,"r");
                if(procstatfile==NULL){
                    perror("fopen");
                    return;
                }
                int statPid;
                char statName[4096],statState;
                char statStateStr[4096];
                if(fscanf(procstatfile,"%d (%[^)])  %c",&statPid,statName,&statState)==3){
                    if(statState=='R'){
                        strcpy(statStateStr,"Running");
                    }
                    else if(statState=='S'){
                        strcpy(statStateStr,"Sleeping");
                    }
                    else if(statState=='D'){
                        strcpy(statStateStr,"Waiting");
                    }
                    else if(statState=='Z'){
                        strcpy(statStateStr,"Zombie");
                    }
                    else if(statState=='T'){
                        strcpy(statStateStr,"Stopped");
                    }
                    else{
                        strcpy(statStateStr,"Unknown");
                    }
                    printf("%d : %s - %s\n",statPid,statName,statStateStr);
                }
                    
                // fscanf(procstatfile,"%d (%[^)])  %c",&statPid,statName,&statState);
                fclose(procstatfile);
                // printf("%d : %s - %c\n",statPid,statName,statState);
            }
        }
    }
    closedir(procdir);
}


void Neonate(char* input, char* HomeDir, nodeptr head) {
    char* space;
    char* SPToken = strtok_r(input, " ", &space);
    if (SPToken == NULL) {
        printf("Invalid Command!\n");
        return;
    }
    char* NeonateSplit[3];
    int i = 0;
    while (SPToken != NULL) {
        NeonateSplit[i++] = SPToken;
        SPToken = strtok_r(NULL, " ", &space);
    }
    int timer = atoi(NeonateSplit[2]);
    
    time_t start_time, current_time;

    struct termios o1, o2;
    tcgetattr(STDIN_FILENO, &o1);
    o2 = o1;
    o2.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &o2);
    setbuf(stdout, NULL);

    int flags = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, flags | O_NONBLOCK);

    char inp;
    int index = 0;
    int should_exit = 0;

    DIR* dir = opendir("/proc");
    if (!dir) {
        perror("opendir");
        exit(EXIT_FAILURE);
    }

    struct dirent* entry;
    int numFound = 0;

    while (read(STDIN_FILENO, &inp, 1)){
        if(inp=='x'){
            break;
        }
        int pid = getpid();
        printf("%d\n", pid);        
        start_time = time(NULL);
        do {
            current_time = time(NULL);
        } while (current_time - start_time < timer);
    }
    closedir(dir);
    tcsetattr(STDIN_FILENO, TCSANOW, &o1);
    fcntl(STDIN_FILENO, F_SETFL, flags);
}

void  fg(char* input, char* HomeDir, nodeptr head){
    char* space;
    char* SPToken = strtok_r(input, " ", &space);
    if (SPToken == NULL) {
        printf("Invalid Command!\n");
        return;
    }
    char* fgSplit[2];
    int i = 0;
    while (SPToken != NULL) {
        fgSplit[i++] = SPToken;
        SPToken = strtok_r(NULL, " ", &space);
    }

    int job_id = atoi(fgSplit[1]);
    pid_t fg_pgid = getpgid(STDIN_FILENO);
    if (tcsetpgrp(STDIN_FILENO, job_id) == -1) {
        perror("tcsetpgrp");
        return;
    }
    int handling=kill(job_id,SIGCONT);
    if(handling==-1){
        printf("No such process found!");
        perror("bg");
    }
    else{
       if(errno==ESRCH){
           printf("No such process found!");
           perror("bg");
       }
       else{
            perror("kill");
       }
    }
    int status;
    waitpid(job_id, &status, 0);
    tcsetpgrp(STDIN_FILENO, job_id);
    return;
}


void  bg(char* input, char* HomeDir, nodeptr head){
    char* space;
    char* SPToken = strtok_r(input, " ", &space);
    if (SPToken == NULL) {
        printf("Invalid Command!\n");
        return;
    }
    char* bgSplit[2];
    int i = 0;
    while (SPToken != NULL) {
        bgSplit[i++] = SPToken;
        SPToken = strtok_r(NULL, " ", &space);
    }

    int job_id = atoi(bgSplit[1]);
    int handling=kill(job_id,SIGCONT);
    if(handling==-1){
        printf("No such process found!");
        perror("bg");
    }
    else{
       if(errno==ESRCH){
           printf("No such process found!");
           perror("bg");
       }
       else{
            perror("kill");
       }
    }
}


void CtrlC(){
    //implement the same functionality of shell when CtrlC is pressed
    printf("\n");
    if(fg_pid!=-1){
        if(kill(fg_pid,SIGINT)==-1){
            perror("CtrlC");
            return;
        }
    }else{
       RunTerminal(HomeDirGlob,HomeDirGlob,temp_head); 
    }
}

void CtrlZ(){
    //implement the same functionality of shell when CtrlZ is pressed
   if(fg_pid!=-1){
        if(kill(fg_pid,SIGTSTP)==-1){
            perror("CtrlZ");
            return;
        }
        // printf("%p,    %s\n",temp_head,HomeDirGlob);
        // printf("\n");
        // RunTerminal(HomeDirGlob,HomeDirGlob,temp_head);

   }
    printf("\n");
    RunTerminal(HomeDirGlob,HomeDirGlob,temp_head);

}

void CtrlD(int signum){
    return;
}

void IMan(char* input,char* HomeDir,nodeptr head){
    const char website[255] = "man.he.net";
    char* SPToken=strtok(input," ");
    SPToken=strtok(NULL," ");

    struct hostent *host = gethostbyname(website);
    if (host == NULL){
        perror("DNS lookup failed");
        return;
    }

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0){
        perror("Socket creation failed");
        return;
    }

    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(80);
    memcpy(&server_addr.sin_addr.s_addr, host->h_addr_list[0], host->h_length);

    char request[4096];
    int flag = 0, connect_return_val = 7;

    for (int i = 0; i < 8; i++){
        snprintf(request, 4096, "GET /man%d/%s HTTP/1.1\r\nHost: %s\r\n\r\n", i, SPToken, website);
        connect_return_val = connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr));
        if (connect_return_val == 0){
            flag = 1;
            break;
        }
    }

    if (flag == 0){
        printf("No manual entry for %s", SPToken);
        return;
    }

    if (send(sockfd, request, strlen(request), 0) < 0){
        perror("Send failed");
        return;
    }

    char *response = (char *)calloc(5 * 4096, sizeof(char));

    if (recv(sockfd, response, 4096, 0) < 0){
        perror("Receive failed");
        return;
    }


    char *ptr = strstr(response, "NAME");
    ptr++;
    ptr=strstr(ptr,"NAME");
    char *end_ptr = strstr(ptr, "AUTHOR");

    char *html_parser = strtok(ptr, " ");

    if (ptr == NULL){
        printf("No Man entry for %s\n", SPToken);
        return;
    }

    while (html_parser != NULL && html_parser != end_ptr){
        printf("%s ", html_parser);
        html_parser = strtok(NULL, " ");
    }

    printf("\n");
    close(sockfd);
    return;
}

