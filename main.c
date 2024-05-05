#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

char *infoTxt="info.txt";
int main() {
    pid_t pid1, pid2;
    pid1 = fork();
    FILE *file=fopen(infoTxt,"a+");
    if (file==NULL)
    {
        printf("file does not opened sucessfully...\n");
    }
    
    if (pid1 == 0) {
        execlp("ls", "ls", "-l", NULL);
    } else if (pid1 > 0) {
        pid2 = fork();
        if (pid2 == 0) {
            execlp("date", "date", NULL); 
        } else if (pid2 > 0) {
            waitpid(pid1, NULL, 0);
            waitpid(pid2, NULL, 0);
            fprintf(file,"%s","first process done succesfully..\n");
            fprintf(file,"%s","second process done succesfully..\n");
        } else {
            fprintf(file,"%s","Error creating child process 2\n");
        }
    } else {
          fprintf(file,"%s","Error creating child process 1\n");
    }
    fclose(file);
    return 0;
}



   


