#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

clock_t start, end;

int main(int argc, char** argv) {
    char* cmd = (char* )malloc(2048 * sizeof(char));
    if (argc <= 1) {
        printf("Nothing executed in 0.0s\n");
        exit(0);
    }
    int i;
    for (i = 1; i < argc ; i++) {
        if (i == 1) {
            strcpy(cmd, argv[i]);
        } else sprintf(cmd, "%s %s", cmd, argv[i]);
    }
    start = clock();
    system(cmd);
    end = clock();
    double time_spent = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("\nuser: %lf s", time_spent);
}