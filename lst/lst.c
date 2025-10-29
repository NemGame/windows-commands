#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <sys/stat.h>
#include <string.h>
#include <direct.h>
#include <wchar.h>
#include <my/printfw.h>
#include <my/table.h>
#include <my/args.h>
#include <shellapi.h>
#include <windows.h>

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

void printListW(wchar_t **list, int count) {
    for (int i = 0; i < count; ++i) {
        printfw(list[i]);
        if (i != count - 1) printfw(L"\n");
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

int listContainsW(wchar_t **list, wchar_t *val) {
    for (int i = 0; list[i] != NULL; ++i) {
        if (wcscmp(list[i], val) == 0) {
            return 1;
        }
    }
    return 0;
}

wchar_t *joinListW(wchar_t **list, int skip) {
    wchar_t *result = NULL;
    int length = 0;
    for (int i = skip; list[i] != NULL; ++i) {
        length += wcslen(list[i]);
    }
    result = malloc((length + 1) * sizeof(wchar_t));
    if (!result) return NULL;
    result[0] = L'\0';
    for (int i = skip; list[i] != NULL; ++i) {
        wcscat(result, list[i]);
    }
    if (wcscmp(result, L"") == 0) {
        free(result);
        result = malloc(1 * sizeof(wchar_t));
        result[0] = L'.';
        result[1] = L'\0';
        return result;
    }
    return result;
}

int wmain(int argc, wchar_t *argv[]) {
    float version = 1.0;
    attrw attributes[MAX_ATTRS];
    wchar_t *added[MAX_OUT] = {NULL};
    wchar_t *noidea[MAX_OUT] = {NULL};

    processArgsAW(argc, argv, attributes, added, noidea, 0);
    if (listContainsW(noidea, L"/")) return 0;
    if (valueOfAttrW(attributes, L"--version") != NULL) {
        wchar_t verStr[10];
        _snwprintf(verStr, 10, L"%.1f\n", version);
        printfw(verStr);
        return 0;
    }
    if (listContainsW(noidea, L"/?") || listContainsW(added, L"-help") || valueOfAttrW(attributes, L"--help") != NULL) {
        wchar_t *help[] = {
            L"Lists the contents of the given/current directory.\n",
            L"Parameters:",
            L"    /?, -help, --help\t\t    |\tShows this help message",
            L"    -l\t\t\t\t    |\tPrints the output in a table format",
            L"    --type [files|folders|unknown]  |\tFilters the output by type",
            L"    |   Shorthands: files = f, file; folders = ff, dir, folder; unknown = fff, u, fuck",
            L"    -nd, -no-decoration\t\t    |\tDisables the decorative lines in the output",
            L"    -h, -header\t\t\t    |\tEnables headers for sections",
            L"    --version\t\t\t    |\tShows the version of the program",
        };
        printfwallj(help, sizeof(help) / sizeof(help[0]), L"\n");
        return 0;
    }
    wchar_t *type = valueOfAttrW(attributes, L"--type");
    wchar_t *types[] = {L"all", L"files", L"folders", L"unknown"};
    int isTypeValid = 0;
    if (type == NULL) type = L"all";
    else for (int i = 0; i < 4; ++i) {
        if (wcscmp(type, types[i]) == 0) {
            isTypeValid = 1;
            break;
        } else isTypeValid = 0;
        if (wcscmp(type, L"f") == 0 || wcscmp(type, L"file") == 0) {
            type = L"files";
            isTypeValid = 1;
            break;
        }
        if (wcscmp(type, L"ff") == 0 || wcscmp(type, L"dir") == 0 || wcscmp(type, L"folder") == 0) {
            type = L"folders";
            isTypeValid = 1;
            break;
        }
        if (wcscmp(type, L"fff") == 0 || wcscmp(type, L"u") == 0 || wcscmp(type, L"fuck") == 0) {
            type = L"unknown";
            isTypeValid = 1;
            break;
        }
    }
    if (!isTypeValid) type = L"all";
    
    wchar_t *path = joinListW(noidea, 1);

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

    int showFolders = (wcscmp(type, L"all") == 0 || wcscmp(type, L"folders") == 0);
    int showFiles = (wcscmp(type, L"all") == 0 || wcscmp(type, L"files") == 0);
    int showUnknown = (wcscmp(type, L"all") == 0 || wcscmp(type, L"unknown") == 0);

    int hasFolders = (ffcount > 0 && showFolders);
    int hasFiles = (fcount > 0 && showFiles);
    int hasUnknown = (fffcount > 0 && showUnknown);

    if (hasFolders == 0 && hasFiles == 0 && hasUnknown == 0) {
        printf("The given folder doesn't contain anything");
        free(content);
        free(path);
        return 0;
    }
    int header = listContainsW(added, L"-header") || listContainsW(added, L"-h");
    if (listContainsW(added, L"-l")) {
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
        int width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
        if (header && hasFolders) {
            char *centered = centeredText("Folders", width - 1);
            printf("%s", centered);
            free(centered);
        }
        if (ffcount > 0 && showFolders) printCommandTableW(folders, ffcount, 90);
        if (header && hasFiles) {
            if (hasFolders) putchar('\n');
            char *centered = centeredText("Files", width - 1);
            printf("%s", centered);
            free(centered);
        }
        if (fcount > 0 && showFiles) printCommandTableW(files, fcount, 90);
        if (header && hasUnknown) {
            if (hasFolders || hasFiles) putchar('\n');
            char *centered = centeredText("Unknown", width - 1);
            printf("%s", centered);
            free(centered);
        }
        if (fffcount > 0 && showUnknown) printCommandTableW(fucker, fffcount, 90);
        free(content);
        free(path);
        return 0;
    }
    
    int decoration = !(listContainsW(added, L"-no-decoration") || listContainsW(added, L"-nd"));

    if (decoration) {
        if (header) {
            if (hasFolders) printf("=========FOLDERS=========\n");
        } else printf("=========================\n");
    }
    if (hasFolders) printListW(folders, ffcount);
    if (hasFolders && (hasFiles || hasUnknown)) putchar('\n');
    freeList(folders, ffcount);
    if (ffcount > 0 && hasFolders && (hasFiles || hasUnknown)) putchar('\n');
    if (ffcount > 0 && hasFiles && header && decoration) printf("==========FILES==========\n");
    if (hasFiles) printListW(files, fcount);
    if (hasFiles && hasUnknown) putchar('\n');
    freeList(files, fcount);
    if (hasUnknown && (hasFolders || hasFiles)) putchar('\n');
    if (hasUnknown && decoration) printf("=========UNKNOWN=========\n");
    if (hasUnknown) printListW(fucker, fffcount);
    freeList(fucker, fffcount);
    if (decoration) printf("\n=========================");

    free(content);
    free(path);
    return 0;
}

int main(int argc, char **argv) {
    LPWSTR *args = CommandLineToArgvW(GetCommandLineW(), &argc);
    if (args == NULL) return 1;
    int res = wmain(argc, args);
    LocalFree(args);

    return res;
}
