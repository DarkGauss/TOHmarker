#include <stdio.h>

int main() {
    char line[255];
    FILE *inputFile = fopen("input.txt","r");
    while(fgets(line,sizeof(line),inputFile) != NULL) {
        printf("%s",line);
    }

    return 0;
}
