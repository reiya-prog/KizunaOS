#pragma once
#include "main.h"

#define MAX_FILE_NAME_LENGTH 10
#define MAX_FILE_NUM 20
#define MAX_FILE_BUF 1024

typedef struct {
    unsigned int name[MAX_FILE_NAME_LENGTH];
} FILE;

void ls(EFI *efi);

extern FILE file_list[MAX_FILE_NUM];