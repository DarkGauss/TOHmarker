#include <stdio.h>

int main(int argc, char* argv[]) {
    if(argc <= 1)   return 0;
    char* programName = argv[1];
    char line[255];
    FILE* proc1 = popen(programName,"r");

    while(fgets(line,sizeof(line),proc1) != NULL) {
        printf("%s",line);
    }

    pclose(proc1);

    return 0;

}
