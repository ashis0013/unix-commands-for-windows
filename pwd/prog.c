#include <stdio.h>
#include <windows.h>

int main() {
    char *path = (char*) malloc(2048 * sizeof(char));
    GetCurrentDirectory(2048, path);
    printf("%s\n", path);
}