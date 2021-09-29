#include <stdio.h>
#include <windows.h>

typedef struct _lsItem {
    char fileName[260];
    int isFolder;
    int isHidden;
    struct _lsItem* next;
} lsItem;

lsItem* listHead = NULL;

int maxLineItems = 4;

lsItem* getNode(WIN32_FIND_DATA fdFile) {
    lsItem* node = (lsItem* ) malloc(sizeof(lsItem));
    strcpy(node->fileName, fdFile.cFileName);
    node->isFolder = (fdFile.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) ? 1 : 0;
    node->isHidden = (fdFile.dwFileAttributes & FILE_ATTRIBUTE_HIDDEN) ? 1 : 0;
    node->next = NULL;
    return node;
}

void insert(WIN32_FIND_DATA fdFile) {
    if (listHead == NULL) {
        listHead = getNode(fdFile);
        return;
    }
    lsItem* cur = listHead;
    while (cur->next != NULL) {
        cur = cur->next;
    }
    cur->next = getNode(fdFile);
}

void printDefault(int showHidden) {
    lsItem* cur = listHead;
    int lineLen = 0;
    while (cur != NULL) {
        if (cur->isHidden == 0 || (cur->isHidden & showHidden)) {
            if (cur->isFolder) printf("\033[0;36m");
            printf("%s\t\t", cur->fileName);
            printf("\033[0m");
            if (++lineLen == maxLineItems) {
                printf("\n");
                lineLen = 0;
            }
        }
        cur = cur->next;
    } printf("\n");
}

int ListDirectoryContents(const char *sDir)
{
    WIN32_FIND_DATA fdFile;
    HANDLE hFind = NULL;
    
    char sPath[2048];

    sprintf(sPath, "%s\\*.*", sDir);

    if((hFind = FindFirstFile(sPath, &fdFile)) == INVALID_HANDLE_VALUE)
    {
        printf("Path not found: [%s]\n", sDir);
        return 0;
    }

    do {
        if(strcmp(fdFile.cFileName, ".") == 0 || strcmp(fdFile.cFileName, "..") == 0) continue;
        insert(fdFile);
    } while(FindNextFile(hFind, &fdFile));

    FindClose(hFind);
    return 1;
}

void parseArgs(int argc, char** argv) {
    if (argc == 1) {
        printDefault(0);
        return;
    }
    if (strcmp(argv[1], "-a") == 0) {
        printDefault(1);
    } else if (strcmp(argv[1], "-l") == 0) {
        system("Get-ChildItem");
    } else if (strlen(argv[1]) == 2 && argv[1][0] == '-' && argv[1][1] >= '1' && argv[1][1] <= '3'){
        maxLineItems = (int) (argv[1][1] - '0');
        printDefault(0);
    } else if (argv[1][0] == '-'){
        printf("\033[1;31m");
        printf("ls: Provided option does not exist!\n");
        printf("\033[0m");
        printDefault(0);
    } else {
        printDefault(0);
    }
}

int main(int argc, char** argv) {
    char *path = (char*) malloc(2048 * sizeof(char));
    GetCurrentDirectory(2048, path);
    if (argc == 3) {
        strcpy(path, argv[2]);
    } else if ((argc == 2 && argv[1][0] != '-')) {
        strcpy(path, argv[1]);
    }
    if (strlen(path) >= 2 && path[0] == '.' && path[1] == '\\') path += 2;
    if (path[strlen(path) - 1] == '\\') path[strlen(path) - 1] = '\0';
    char *rootPath = (char*) malloc(2048 * sizeof(char));
    GetCurrentDirectory(2048, rootPath);
    if (strlen(path) != 0) {
        sprintf(rootPath, "%s\\", rootPath);
        strncat(rootPath, path, strlen(path));
    }
    if (strlen(path) >= 2 && (path[0] == 'C' || path[0] == 'c') && path[1] == ':') strcpy(rootPath, path);
    ListDirectoryContents(rootPath);
    parseArgs(argc, argv);
}
