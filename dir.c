#include "headers.h"


// char* GetCurrentDir(char* HomeDir){
//     char currentwd[4096];
//     if (getcwd(currentwd, sizeof(currentwd)) == NULL) {
//             perror("cwd");
//             exit(1);
//     }

//     char* CommonDir=strstr(currentwd,HomeDir);


// }

char* GetCurrentDir(char* HomeDir) {
    char currentwd[4096];
    if (getcwd(currentwd, sizeof(currentwd)) == NULL) {
        perror("cwd");
        exit(1);
    }
    

    // strcat(currentwd,"/home/min");

    int i=0;

    while(HomeDir[i]!='\0'){
        if(HomeDir[i]!=currentwd[i]){
            break;
        }
        i++;
    }
    char* CommonDir = malloc(sizeof(char)*4096);
    strcpy(CommonDir,currentwd+i+1);
    // printf("test");
    return CommonDir;
}

char* RelativePath(char* MainDir,char* SubPath){
    int i=0;
    while(MainDir[i]!='\0'){
        if(MainDir[i]!=SubPath[i]){
            break;
        }
        i++;
    }
    char* CommonDir = malloc(sizeof(char)*4096);
    strcpy(CommonDir,SubPath+i+1);
    // printf("test");
    return CommonDir;
}

void ShowFiles(char* AbsPath, int showHidden, int showDetails) {
    struct dirent *entry;
    DIR *dir = opendir(AbsPath);

    if (!dir) {
        perror("opendir");
        return;
    }

    while ((entry = readdir(dir)) != NULL) {
        if (!showHidden && entry->d_name[0] == '.') {
            continue;
        }
        if (showDetails) {
            struct stat fileStat;
            char fullPath[4096];
            snprintf(fullPath, sizeof(fullPath), "%s/%s", AbsPath, entry->d_name);

            if (stat(fullPath, &fileStat) < 0) {
                perror("stat");
                continue;
            }

            printf("%s", (S_ISDIR(fileStat.st_mode)) ? BLUE "d" : (fileStat.st_mode & S_IXUSR || fileStat.st_mode & S_IXGRP || fileStat.st_mode & S_IXOTH) ?GREEN "-" : WHITE "-");

            printf("%c%c%c%c%c%c%c%c%c%c ", 
                (fileStat.st_mode & S_IRUSR) ? 'r' : '-',
                (fileStat.st_mode & S_IWUSR) ? 'w' : '-',
                (fileStat.st_mode & S_IXUSR) ? 'x' : '-',
                (fileStat.st_mode & S_IRGRP) ? 'r' : '-',
                (fileStat.st_mode & S_IWGRP) ? 'w' : '-',
                (fileStat.st_mode & S_IXGRP) ? 'x' : '-',
                (fileStat.st_mode & S_IROTH) ? 'r' : '-',
                (fileStat.st_mode & S_IWOTH) ? 'w' : '-',
                (fileStat.st_mode & S_IXOTH) ? 'x' : '-',
                (S_ISDIR(fileStat.st_mode)) ? '/' : ' '
            );

            printf("%ld %s %s %ld %s ",fileStat.st_nlink,getpwuid(fileStat.st_uid)->pw_name,getgrgid(fileStat.st_gid)->gr_name,fileStat.st_size,ctime(&fileStat.st_mtime));

            if (S_ISDIR(fileStat.st_mode)){
                printf(BLUE "%s\n" COLOR_RESET, entry->d_name);
            }
            else if (fileStat.st_mode & S_IXUSR || fileStat.st_mode & S_IXGRP || fileStat.st_mode & S_IXOTH){
                printf(GREEN "%s\n" COLOR_RESET, entry->d_name);
            }
            else{
                printf(WHITE "%s\n" COLOR_RESET, entry->d_name);
            }
        } else {
            struct stat fileStat;
            char fullPath[4096];
            snprintf(fullPath, sizeof(fullPath), "%s/%s", AbsPath, entry->d_name);
            if (stat(fullPath, &fileStat) < 0) {
                perror("stat");
                continue;
            }
            if (S_ISDIR(fileStat.st_mode)){
                printf(BLUE "%s\n" COLOR_RESET, entry->d_name);
            }
            else if (fileStat.st_mode & S_IXUSR || fileStat.st_mode & S_IXGRP || fileStat.st_mode & S_IXOTH){
                printf(GREEN "%s\n" COLOR_RESET, entry->d_name);
            }
            else{
                printf(WHITE "%s\n" COLOR_RESET, entry->d_name);
            }
            // printf("%s\n", entry->d_name);
        }
    }

    closedir(dir);
}


void PrintFileContents(char* path){
    int file=open(path,O_RDONLY);
    if(file<0){
        perror("open");
        return;
    }
    char buffer[4096];
    int len=read(file,buffer,sizeof(buffer));
    if(len<0){
        perror("read");
        return;
    }
    buffer[len]='\0';
    while(len>0){
        printf("%s",buffer);
        len=read(file,buffer,sizeof(buffer));
        if(len<0){
            perror("read");
            return;
        }
        buffer[len]='\0';
    }
}