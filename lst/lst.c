#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <sys/stat.h>
#include <string.h>
#include <direct.h>
#include <wchar.h>
#include "printfw.h"

wchar_t **dir(wchar_t *path, int *count) {
    WIN32_FIND_DATAW findData;
    HANDLE hFind;
    wchar_t searchPath[MAX_PATH];
    _snwprintf(searchPath, MAX_PATH, L"%s\\*", path);

    hFind = FindFirstFileW(searchPath, &findData);
    if (hFind == INVALID_HANDLE_VALUE) {
        *count = 0;
        return NULL;
    }

    wchar_t **result = NULL;
    int c = 0;

    do {
        if (wcscmp(findData.cFileName, L".") == 0 || wcscmp(findData.cFileName, L"..") == 0)
            continue;

        wchar_t **tmp = realloc(result, sizeof(wchar_t*) * (c + 1));
        if (!tmp) {
            for (int i = 0; i < c; ++i) free(result[i]);
            free(result);
            FindClose(hFind);
            *count = 0;
            return NULL;
        }
        result = tmp;
        result[c] = _wcsdup(findData.cFileName);
        if (!result[c]) {
            for (int i = 0; i < c; ++i) free(result[i]);
            free(result);
            FindClose(hFind);
            *count = 0;
            return NULL;
        }
        ++c;
    } while (FindNextFileW(hFind, &findData));

    FindClose(hFind);
    *count = c;
    return result;
}

int isFile(wchar_t *path) {
    struct _stat path_stat;
    if (_wstat(path, &path_stat) != 0) return -1;
    return (path_stat.st_mode & S_IFREG) != 0;
}

void freeList(wchar_t **list, int count) {
    for (int i = 0; i < count; ++i) free(list[i]);
    free(list);
}

void printList(wchar_t **list, int count) {
    for (int i = 0; i < count; ++i) {
        printfw(list[i]);
        printfw(L"\n");
    }
}
void printfUNICODEFUCKYEEEEEEAAAAAAAAAAAH(wchar_t *wstr) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD written;
    if (!WriteConsoleW(hConsole, wstr, wcslen(wstr), &written, NULL)) {
        wprintf(L"Hiba a kiírásnál\n");
    }
}

int ImGonnaFuckYourMomAgain(wchar_t ***list, int *count, wchar_t *path) {
    wchar_t **tmp = realloc(*list, sizeof(wchar_t*) * (*count + 1));
    if (!tmp) {
        freeList(*list, *count);
        *list = NULL;
        return -1;
    }
    *list = tmp;
    wchar_t *temp = _wcsdup(path);
    if (!temp) {
        freeList(*list, *count);
        *list = NULL;
        return -1;
    }
    (*list)[*count] = temp;
    (*count)++;
    return 0;
}

int main(int argc, wchar_t **argv) {
    wchar_t *path = argc > 1 ? argv[1] : L".";

    int count = 0;
    wchar_t **content = dir(path, &count);
    
    wchar_t **files = NULL;
    int fcount = 0;

    wchar_t **folders = NULL;
    int ffcount = 0;

    wchar_t **fucker = NULL;
    int fffcount = 0;
    for (int i = 0; i < count; i++) {
        wchar_t *fullpath = malloc((wcslen(path) + wcslen(content[i]) + 2) * sizeof(wchar_t));
        wcscpy(fullpath, path);
        wcscat(fullpath, L"\\");
        wcscat(fullpath, content[i]);
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
    if (fffcount > 0) printf("No idea what these are or why they are\n");
    printList(fucker, fffcount);
    freeList(fucker, fffcount);
    printf("=========================\n");

    return 0;
}