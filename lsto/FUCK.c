#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <sys/stat.h>
#include <string.h>
#include <direct.h>

char **dir(char *path, int *count) {
    WIN32_FIND_DATAA findData;
    HANDLE hFind;
    char searchPath[MAX_PATH];
    snprintf(searchPath, sizeof(searchPath), "%s\\*", path);

    hFind = FindFirstFileA(searchPath, &findData);
    if (hFind == INVALID_HANDLE_VALUE) {
        *count = 0;
        return NULL;
    }

    char **result = NULL;
    int c = 0;

    do {
        if (strcmp(findData.cFileName, ".") == 0 || strcmp(findData.cFileName, "..") == 0)
            continue;

        char **tmp = realloc(result, sizeof(char*) * (c + 1));
        if (!tmp) {
            for (int i = 0; i < c; ++i) free(result[i]);
            free(result);
            FindClose(hFind);
            *count = 0;
            return NULL;
        }
        result = tmp;
        result[c] = _strdup(findData.cFileName);
        if (!result[c]) {
            for (int i = 0; i < c; ++i) free(result[i]);
            free(result);
            FindClose(hFind);
            *count = 0;
            return NULL;
        }
        ++c;
    } while (FindNextFileA(hFind, &findData));

    FindClose(hFind);
    *count = c;
    return result;
}

int isFile(char *path) {
    struct stat path_stat;
    if (stat(path, &path_stat) != 0) return -1;
    return (path_stat.st_mode & S_IFREG) != 0;
}

void freeList(char **list, int count) {
    for (int i = 0; i < count; ++i) free(list[i]);
    free(list);
}

void printList(char **list, int count) {
    for (int i = 0; i < count; ++i) {
        printf("%s\n", list[i]);
    }
}

int ImGonnaFuckYourMomAgain(char ***list, int *count, char *path) {
    char **tmp = realloc(*list, sizeof(char*) * (*count + 1));
    if (!tmp) {
        freeList(*list, *count);
        *list = NULL;
        return -1;
    }
    *list = tmp;
    char *temp = _strdup(path);
    if (!temp) {
        freeList(*list, *count);
        *list = NULL;
        return -1;
    }
    (*list)[*count] = temp;
    (*count)++;
    return 0;
}

int main(int argc, char **argv) {
    char *path = argc > 1 ? argv[1] : ".";

    SetConsoleOutputCP(CP_UTF8);

    int count = 0;
    char **content = dir(path, &count);
    
    char **files = NULL;
    int fcount = 0;

    char **folders = NULL;
    int ffcount = 0;

    char **fucker = NULL;
    int fffcount = 0;
    for (int i = 0; i < count; i++) {
        char *fullpath = malloc(strlen(path) + strlen(content[i]) + 2);
        strcpy(fullpath, path);
        strcat(fullpath, "\\");
        strcat(fullpath, content[i]);
        int isfile = isFile(fullpath);
        if (isfile) {  // Fájl
            int truth = ImGonnaFuckYourMomAgain(&files, &fcount, content[i]);
            if (truth == -1) break;
        } else if (isfile == 0) {  // Mappa
            int truth = ImGonnaFuckYourMomAgain(&folders, &ffcount, content[i]);
            if (truth == -1) break;
        } else {  // Fucking piece of shit
            int truth = ImGonnaFuckYourMomAgain(&fucker, &fffcount, content[i]);
            if (truth == -1) break;
        }
        // printf("%s\n", content[i]);
        free(content[i]);
        free(fullpath);
    }
    printf("=========================\n");
    printList(folders, ffcount);
    freeList(folders, ffcount);
    if (ffcount > 0) printf("\n");
    printList(files, fcount);
    freeList(files, fcount);
    if (fffcount > 0) printf("\n");
    printList(fucker, fffcount);
    freeList(fucker, fffcount);
    printf("=========================\n");

    return 0;
}