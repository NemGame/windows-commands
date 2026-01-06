#include <my/list.h>
#include <my/printfw.h>

int main() {
    char **list = malloc(2 * sizeof(char *));
    list[0] = malloc(10 * sizeof(char));
    list[1] = malloc(10 * sizeof(char));
    strcpy(list[0], "str1");
    strcpy(list[1], "str2");
    printList(list, 2, "\n");
    printf("\n");
    freeList(list, 2);

    printfw(L"Anyádat");

    return 0;
}