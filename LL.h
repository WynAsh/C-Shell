#ifndef LL_H_
#define LL_H_

extern int sleep_flag;
extern char LongCommand[4096];

nodeptr CreateHeadNode();
void AddToLL(nodeptr head, pid_t pid, char *name);
void RemoveFromLL(nodeptr head);

#endif