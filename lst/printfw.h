#pragma once
/**
 * printfw.h
 */

#include <windows.h>
#include <stdio.h>
#include <wchar.h>

#ifndef WPRINTF_H
#define WPRINTF_H

/**
 * Prints wide characters
 */
static inline void printfw(wchar_t *wstr) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD written;
    if (!WriteConsoleW(hConsole, wstr, wcslen(wstr), &written, NULL)) {
        fwprintf(stderr, L"Error\n");
    }
}

/**
 * Prints wide characters and a new line, smart
 */
static inline void printfwl(wchar_t *wstr) {
    size_t len = wcslen(wstr);
    if (len > 512) {
        wchar_t *buff = (wchar_t *) malloc(len + 2);
        memcpy(buff, wstr, len * sizeof(wchar_t));
        buff[len] = L'\n';
        buff[len + 1] = L'\0';
        printfw(buff);
        free(buff);
    } else {
        wchar_t buff[len + 2];
        memcpy(buff, wstr, len * sizeof(wchar_t));
        buff[len] = L'\n';
        buff[len + 1] = L'\0';
        printfw(buff);
    }
}

/**
 * Prints a wide character
 */
static inline void putcharw(wchar_t c) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD written;
    if (!WriteConsoleW(hConsole, &c, 1, &written, NULL)) {
        fwprintf(stderr, L"Error\n");
    }
}

#endif