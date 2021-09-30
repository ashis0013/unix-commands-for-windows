#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
    if (argc < 2) {
        fprintf(stderr, "Cannot create a file with no name\n");
        exit(0);
    }
    FILE* fptr = fopen(argv[1], "w");
    fclose(fptr);
    free(fptr);
}