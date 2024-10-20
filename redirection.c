#include "headers.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void HandlePipe(char* input, char* HomeDir, nodeptr head) {
    int pip_count = 0, i = 0;
    for (i = 0; i < strlen(input); i++) {
        if (input[i] == '|') {
            pip_count++;
        }
    }
    // char* pip_parts[pip_count + 1];
    // char* pt;
    // i = 0;
    // char* PipeToken = strtok_r(input, "|", &pt);
    // while (PipeToken != NULL) {
    //     pip_parts[i++] = PipeToken;
    //     PipeToken = strtok_r(NULL, "|", &pt);
    // }

    char** pip_parts = malloc((pip_count + 1) * sizeof(char*));
    if (pip_parts == NULL) {
        perror("malloc");
        exit(1);
    }
    char* pt;
    i = 0;
    char* PipeToken = strtok_r(input, "|", &pt);
    while (PipeToken != NULL) {
        pip_parts[i] = strdup(PipeToken);
        if (pip_parts[i] == NULL) {
            perror("strdup");
            exit(1);
        }
        i++;
        PipeToken = strtok_r(NULL, "|", &pt);
    }



    if(pip_count!=i-1){
        printf("Invalid Use of Pipe\n");
        return;
    }

    for(int j=0;j<i;j++){
        if(pip_parts[j][strlen(pip_parts[j])-1]==' '){
            pip_parts[j][strlen(pip_parts[j])-1]='\0';
        }
        else if(pip_parts[j][0]==' '){
            pip_parts[j]++;
        }
    }

    int pipes[pip_count][2];
    for (i = 0; i < pip_count; i++) {
        if (pipe(pipes[i]) == -1) {
            perror("Pipe");
            exit(1);
        }
    }

    int pid;
    int input_fd = STDIN_FILENO;
    for (i = 0; i <= pip_count; i++) {
        pid = fork();
        if (pid == -1) {
            perror("fork");
            exit(1);
        } else if (pid == 0) {
            for(int j=0;j<pip_count;j++){
                for(int k=0;k<2;k++){
                    if((j==i && k==1) || (j==i-1 && k==0)){
                        continue;
                    }
                    close(pipes[j][k]);
                }
            }
            if(i>0){
                close(pipes[i-1][1]);
                dup2(pipes[i-1][0],STDIN_FILENO);
            }
            if(i<pip_count){
                dup2(pipes[i][1],STDOUT_FILENO);
            }
            // RunProc(pip_parts[i], HomeDir, head);
            UserInput(pip_parts[i], HomeDir, head);
            exit(0);
        }

    }
    for(int i=0;i<pip_count;i++){
        close(pipes[i][0]);
        close(pipes[i][1]);
    }

    for (i = 0; i <= pip_count; i++) {
        wait(NULL);
    }
}

void HandlePipesAndRedirection(char* input, char* HomeDir, nodeptr head){
    ReplaceSubstring(input,">>",";?");
    ReplaceSubstring(input,">",";>");
    ReplaceSubstring(input,"<",";<");
    ReplaceSubstring(input,"|",";");
    int splits=0;
    for(int i=0;i<strlen(input);i++){
        if(input[i]==';'){
            splits++;
        }
    }
    char* parts[splits+1];
    char* pt;
    char* SCToken = strtok_r(input, ";",&pt);
    int i=0;
    while (SCToken != NULL) {
        parts[i++]=SCToken;
        SCToken = strtok_r(NULL, ";",&pt);
    }

    if(i<=splits){
        printf("Invalid Use of Pipe\n");
        return;
    }
}