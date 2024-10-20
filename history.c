#include "headers.h"

void SaveCommand(char *Command, char *HomeDir) {
    char temp[4096];
    strcpy(temp, HomeDir);
    strcat(temp, "/CommandCode.txt");
    int CommCode = open(temp, O_RDWR | O_CREAT, 0777);
    if (CommCode == -1) {
        perror("Error opening file");
        return;
    }

    char buffer[61440];
    off_t filesize = lseek(CommCode, 0, SEEK_END);
    lseek(CommCode, 0, SEEK_SET);
    ssize_t len = read(CommCode, buffer, sizeof(buffer));

    int i = 0;
    if (len > 0) {
        char *SepPtr;
        char *SepComm = strtok_r(buffer, "\n", &SepPtr);
        while (SepComm != NULL) {
            // PastCommands[i] = (char *)malloc(strlen(SepComm) + 1);
            strcpy(PastCommands[i++], SepComm);
            SepComm = strtok_r(NULL, "\n", &SepPtr);
        }
    }

    close(CommCode);

    if (i >= 15) {
        free(PastCommands[0]);
        for (int j = 0; j < i - 1; j++) {
            PastCommands[j] = PastCommands[j + 1];
        }
        i = 15 - 1;
    }

    if (i > 0 && strcmp(Command, PastCommands[i - 1]) == 0) {
        return;
    }

    PastCommands[i] = (char *)malloc(strlen(Command) + 1);
    strcpy(PastCommands[i], Command);

    int NewCommCode = open(temp, O_WRONLY | O_CREAT | O_TRUNC, 0777);
    if (NewCommCode == -1) {
        perror("Error opening file");
        return;
    }
    char buffer2[4096];

    buffer2[0] = '\0';
    for (int j = 0; j <= i; j++) {
        strcat(buffer2, PastCommands[j]);
        strcat(buffer2, "\n");
    }

    write(NewCommCode, buffer2, strlen(buffer2));
    close(NewCommCode);
}

void HistoryPurge(char* HomeDir) {
    char temp[4096];
    strcpy(temp,HomeDir);
    strcat(temp,"/CommandCode.txt");
    for (int i = 0; i < 15; i++) {
        PastCommands[i][0]='\0';
    }
    FILE *file = fopen(temp, "w");
    if (file == NULL) {
        perror("Error opening the file");
        return;
    }
    fclose(file);
}