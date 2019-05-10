#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void parse(char* line,char** );

int main(int argc, char* argv[]) {
    if(argc <= 1)   return 0;

    int numDisks;
    int numLines = 0;
    int numMoves;
    char** moves = malloc(1024*sizeof(char*));
    char* programName = argv[1];
    //char* programName = "./exampleProgram";
    char line[255];
    char currentDisk,startPeg,endPeg;
    FILE* proc1 = popen(programName,"r");

    while(fgets(line,sizeof(line),proc1) != NULL) {
        if(!isspace(line[0])) {
            moves[numLines] = malloc(strlen(line)+1);
            strcpy(moves[numLines],line);
            numLines++;
        }
    }
    pclose(proc1);

    sscanf(moves[0],"%*s %*s %d",&numDisks);
    sscanf(moves[numLines-1],"%*s %*s %d",&numMoves);
    printf("disks: %d\n",numDisks);

    for(int i = 1; i < numLines-1; i++) {
        sscanf(moves[i],"%*s %c %*s %c %*s %c",&currentDisk,&startPeg,&endPeg);
        printf("%c %c %c\n",currentDisk,startPeg,endPeg);
    }

    printf("moves: %d\n",numMoves);

    return 0;

}
