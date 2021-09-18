#include <stdio.h>
#include <stdlib.h>

size_t getline(char **lineptr, size_t *n, FILE *stream) {
    char *bufptr = NULL;
    char *p = bufptr;
    size_t size;
    int c;

    if (lineptr == NULL || stream == NULL || n == NULL) {
        return -1;
    }
    
    bufptr = *lineptr;
    size = *n;

    c = fgetc(stream);
    if (c == EOF) {
        return -1;
    }
    if (bufptr == NULL) {
        bufptr = malloc(128);
        if (bufptr == NULL) {
            return -1;
        }
        size = 128;
    }
    p = bufptr;
    while(c != EOF) {
        if ((p - bufptr) > (size - 1)) {
            size = size + 128;
            bufptr = realloc(bufptr, size);
            if (bufptr == NULL) {
                return -1;
            }
        }
        *p++ = c;
        if (c == '\n') {
            break;
        }
        c = fgetc(stream);
    }

    *p++ = '\0';
    *lineptr = bufptr;
    *n = size;

    return p - bufptr - 1;
}

void cat(char* filename) {
    FILE* fptr = fopen(filename, "r");
    if (fptr == NULL) {
        printf("File does not exist");
        return;
    }
    char* line = NULL;
    size_t len = 0;
    while (getline(&line, &len, fptr) != -1) {
        printf("%s", line);
    }
    fclose(fptr);
    if (line) free(line);
}

int main(int argc, char** argv) {
    if (argc <= 1) {
        printf("Please enter a file name following cat");
        return 0;
    }
    cat(argv[1]);
}