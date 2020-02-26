#include "efi.h"
#include "file.h"
#include "stdfunc.h"

FILE file_list[MAX_FILE_NUM];

void ls(EFI *efi){
    unsigned long long status;
    EFI::EFI_FILE_PROTOCOL *root;
    unsigned long long buf_size;
    unsigned char file_buf[MAX_FILE_BUF];
    EFI::EFI_FILE_INFO *file_info;
    int idx = 0;
    int file_num;

    status = efi->getSimpleFileSystemProtocol()->OpenVolume(efi->getSimpleFileSystemProtocol(), &root);

    while(1){
        buf_size = MAX_FILE_BUF;
        status = root->Read(root, &buf_size, (void *)file_buf);
        if(!buf_size) break;

        file_info = (EFI::EFI_FILE_INFO *)file_buf;
        strncpy(file_list[idx].name, (unsigned int *)file_info->FileName, MAX_FILE_NAME_LENGTH - 1);
        file_list[idx].name[MAX_FILE_NAME_LENGTH - 1] = L'\0';
        puts(efi, (EFI::CHAR16 *)file_list[idx].name);
        puts(efi, (EFI::CHAR16 *)L" ");

        ++idx;
    }
    putc(efi, L'\n');
}