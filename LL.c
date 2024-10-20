#include "headers.h"

nodeptr CreateHeadNode(){
    nodeptr head = (nodeptr)malloc(sizeof(node));
    head->pid = -1;
    head->active = 0;
    head->name = NULL;
    head->next = NULL;
    return head;
}

void AddToLL(nodeptr head, pid_t pid, char *name){
    nodeptr temp = head;
    while(temp->next != NULL){
        temp = temp->next;
    }
    nodeptr newnode = (nodeptr)malloc(sizeof(node));
    newnode->pid = pid;
    newnode->name = (char *)malloc(strlen(name) + 1);
    newnode->active = 1;
    strcpy(newnode->name, name);
    newnode->next = NULL;
    temp->next = newnode;
}

void RemoveFromLL(nodeptr head){
    //reads pid from struct and if process status is completed using WIFEXITED it prints a line and removes it from the linked list
    nodeptr temp = head;
    while(temp->next != NULL){
        nodeptr prev = temp;
        temp = temp->next;
        int status;
        pid_t wpid = waitpid(temp->pid, &status, WNOHANG);
        if(wpid == -1){
            // perror("waitpid");
            continue;
            // exit(EXIT_FAILURE);
        }
        else if(wpid == 0){
            continue;
        }
        else{
            if(WIFEXITED(status)){
                char* token = strtok(temp->name, " ");
                if(temp->active == 1){
                    printf("%s with pid %d exited normally\n", token, temp->pid);
                    temp->active = 0;
                }
                // prev->next = temp->next;
                // free(temp->name);
                // free(temp);
                // temp = prev;
            }
        }
    }

}

void DeleteLL(nodeptr head){
    nodeptr temp = head;
    while(temp->next != NULL){
        nodeptr prev = temp;
        temp = temp->next;
        prev->next = temp->next;
        free(temp->name);
        free(temp);
        temp = prev;
    }
    free(head);
}