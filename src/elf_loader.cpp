#include "main.h"

#define KERNEL_NAME L"KizunaOS.ELF"

EFI::EFI_GUID EFI_FILE_INFO_GUID = {0x09576e92, 0x6d3f, 0x11d2, {0x8e, 0x39, 0x00, 0xa0, 0xc9, 0x69, 0x72, 0x3b}};

extern "C" void jump_kernel(FrameBuffer *fb, unsigned long long entry_point);

void puts(EFI *efi, unsigned short *s)
{
    efi->getSystemTable()->ConOut->OutputString(efi->getSystemTable()->ConOut, s);
    efi->getSystemTable()->ConOut->OutputString(efi->getSystemTable()->ConOut, (EFI::CHAR16 *)L"\r\n");
}

void puth(EFI *efi, unsigned long long val, unsigned char num_digits)
{
    int i;
    unsigned short unicode_val;
    unsigned short str[100];

    for (i = num_digits - 1; i >= 0; i--)
    {
        unicode_val = (unsigned short)(val & 0x0f);
        if (unicode_val < 0xa)
            str[i] = L'0' + unicode_val;
        else
            str[i] = L'A' + (unicode_val - 0xa);
        val >>= 4;
    }
    str[num_digits] = L'\0';

    puts(efi, str);
}

int strcmp(const char *s1, const char *s2)
{
    const unsigned char *ss1, *ss2;
    for (ss1 = (const unsigned char *)s1, ss2 = (const unsigned char *)s2;
         *ss1 == *ss2 && *ss1 != '\0';
         ss1++, ss2++)
        ;
    return *ss1 - *ss2;
}

void memset(void *dst, int c, int n)
{
    const unsigned char uc = c;
    unsigned char *p = (unsigned char *)dst;
    while (n-- > 0)
        *p++ = uc;
}

extern "C"
{
    void memcpy(void *dst, const void *src, int n)
    {
        char *p1 = (char *)dst;
        const char *p2 = (const char *)src;

        while (n-- > 0)
            *p1++ = *p2++;
    }
}

unsigned long long file_sizeof(EFI *efi, EFI::EFI_FILE_PROTOCOL *file)
{
    EFI::EFI_FILE_INFO *file_info;
    unsigned long long file_size = 180;
    unsigned long long file_buf[180];
    unsigned long long stat = file->GetInfo(file, &EFI_FILE_INFO_GUID, &file_size, file_buf);
    file_info = (EFI::EFI_FILE_INFO *)file_buf;
    return file_info->FileSize;
}

void load_kernel(EFI::EFI_HANDLE ImageHandle, EFI *efi, FrameBuffer *fb)
{

    EFI::EFI_STATUS status = 0;
    EFI::EFI_FILE_PROTOCOL *root, *kernel_file;

    /* open kernel file */
    efi->getSystemTable()->ConOut->OutputString(efi->getSystemTable()->ConOut, (EFI::CHAR16 *)L"Open root directory...");
    status = efi->getSimpleFileSystemProtocol()->OpenVolume(efi->getSimpleFileSystemProtocol(), &root);
    if (status == EFI::EFI_SUCCESS)
    {
        efi->getSystemTable()->ConOut->OutputString(efi->getSystemTable()->ConOut, (EFI::CHAR16 *)L"done.\r\n");
    }
    else
    {
        efi->getSystemTable()->ConOut->OutputString(efi->getSystemTable()->ConOut, (EFI::CHAR16 *)L"\r\nCannot open root directory.\r\n");
        efi->getSystemTable()->ConOut->OutputString(efi->getSystemTable()->ConOut, (EFI::CHAR16 *)L"An unexpected error has occurred in opening root directory.\r\n");
        return;
    }
    efi->getSystemTable()->ConOut->OutputString(efi->getSystemTable()->ConOut, (EFI::CHAR16 *)L"Load kernel file...");
    status = root->Open(root, &kernel_file, (EFI::CHAR16 *)L"KizunaOS.ELF", EFI_FILE_MODE_READ, 0);
    if (status == EFI::EFI_SUCCESS)
    {
        efi->getSystemTable()->ConOut->OutputString(efi->getSystemTable()->ConOut, (EFI::CHAR16 *)L"done.\r\n");
        efi->getSystemTable()->ConOut->OutputString(efi->getSystemTable()->ConOut, (EFI::CHAR16 *)L"The kernel file name is KizunaOS.ELF\r\n");
    }
    else
    {
        efi->getSystemTable()->ConOut->OutputString(efi->getSystemTable()->ConOut, (EFI::CHAR16 *)L"\r\nCannot open kernel file.\r\n");
        efi->getSystemTable()->ConOut->OutputString(efi->getSystemTable()->ConOut, (EFI::CHAR16 *)L"An unexpected error has occurred in opening kernel file.\r\n");
        return;
    }
    efi->getSystemTable()->ConOut->OutputString(efi->getSystemTable()->ConOut, (EFI::CHAR16 *)L"Kernel file successfully opened!\r\n\n");

    /* read kernel data */
    unsigned long long kernel_size = 0;
    kernel_size = file_sizeof(efi, kernel_file);
    EFI::EFI_PHYSICAL_ADDRESS kernel_addr = 0x00100000lu;
    efi->getSystemTable()->ConOut->OutputString(efi->getSystemTable()->ConOut, (EFI::CHAR16 *)L"Allocate memory to 0x100000...");
    status = efi->getSystemTable()->BootServices->AllocatePages(EFI::AllocateAddress, EFI::EfiLoaderData, (kernel_size + 4095) / 4096, &kernel_addr);
    if (status == EFI::EFI_SUCCESS)
    {
        efi->getSystemTable()->ConOut->OutputString(efi->getSystemTable()->ConOut, (EFI::CHAR16 *)L"done.\r\n");
    }
    else
    {
        efi->getSystemTable()->ConOut->OutputString(efi->getSystemTable()->ConOut, (EFI::CHAR16 *)L"\r\nCannot allocate memory to 0x100000.\r\n");
        efi->getSystemTable()->ConOut->OutputString(efi->getSystemTable()->ConOut, (EFI::CHAR16 *)L"An unexpected error has occurred in allocating memory.\r\n");
        return;
    }
    efi->getSystemTable()->ConOut->OutputString(efi->getSystemTable()->ConOut, (EFI::CHAR16 *)L"Read kernel data to memory...");
    status = kernel_file->Read(kernel_file, &kernel_size, reinterpret_cast<EFI::VOID *>(kernel_addr));
    if (status == EFI::EFI_SUCCESS)
    {
        efi->getSystemTable()->ConOut->OutputString(efi->getSystemTable()->ConOut, (EFI::CHAR16 *)L"done.\r\n");
    }
    else
    {
        efi->getSystemTable()->ConOut->OutputString(efi->getSystemTable()->ConOut, (EFI::CHAR16 *)L"\r\nCannot read kernel data to memory.\r\n");
        efi->getSystemTable()->ConOut->OutputString(efi->getSystemTable()->ConOut, (EFI::CHAR16 *)L"An unexpected error has occurred in reading kernel data\r\n");
        return;
    }
    efi->getSystemTable()->ConOut->OutputString(efi->getSystemTable()->ConOut, (EFI::CHAR16 *)L"Kernel data successfully stored to memory!\r\n");

    /* check elf-header */
    Elf64_Ehdr *elf_header = reinterpret_cast<Elf64_Ehdr *>(kernel_addr);
    unsigned long long elf_head_size = sizeof(elf_header);
    /* header's magic number == ELF ? */
    efi->getSystemTable()->ConOut->OutputString(efi->getSystemTable()->ConOut, (EFI::CHAR16 *)L"Check ELF magic number in ELF header...");
    if ((EFI::CHAR8 *)elf_header->e_ident[0] == (EFI::CHAR8 *)'\x7f' && (EFI::CHAR8 *)elf_header->e_ident[1] == (EFI::CHAR8 *)'E' && (EFI::CHAR8 *)elf_header->e_ident[2] == (EFI::CHAR8 *)'L' && (EFI::CHAR8 *)elf_header->e_ident[3] == (EFI::CHAR8 *)'F'){
        efi->getSystemTable()->ConOut->OutputString(efi->getSystemTable()->ConOut, (EFI::CHAR16 *)L"done.\r\n");
        efi->getSystemTable()->ConOut->OutputString(efi->getSystemTable()->ConOut, (EFI::CHAR16 *)L"This file is correct ELF file\r\n");
    }else{
        efi->getSystemTable()->ConOut->OutputString(efi->getSystemTable()->ConOut, (EFI::CHAR16 *)L"\r\nHeader's magic number is not ELF.\r\n");
        efi->getSystemTable()->ConOut->OutputString(efi->getSystemTable()->ConOut, (EFI::CHAR16 *)L"This file is not a correct ELF file.\r\n");
        return;
    }
    Elf64_Shdr *elf_section = reinterpret_cast<Elf64_Shdr *>(kernel_addr + elf_header->e_shoff);
    Elf64_Phdr *elf_program = reinterpret_cast<Elf64_Phdr *>(kernel_addr + elf_header->e_phoff);

    unsigned long long last_offset;
    last_offset = 0;
    for (unsigned int i = 0; i < elf_header->e_phnum; ++i)
    {
        Elf64_Phdr program_header = elf_program[i];
        if (program_header.p_type != PT_LOAD)
            continue;
        last_offset = max(last_offset, program_header.p_vaddr + program_header.p_memsz);
    }
    efi->getSystemTable()->ConOut->OutputString(efi->getSystemTable()->ConOut, (EFI::CHAR16 *)L"success!\r\n");

    void *buffer;
    long long sta = efi->getSystemTable()->BootServices->AllocatePool(EFI::EfiLoaderData, last_offset, &buffer);
    if (sta == EFI::EFI_SUCCESS)
        efi->getSystemTable()->ConOut->OutputString(efi->getSystemTable()->ConOut, (EFI::CHAR16 *)L"pool success!\r\n");
    for (unsigned int i = 0; i < elf_header->e_phnum; ++i)
    {
        Elf64_Phdr program_header = elf_program[i];
        if (program_header.p_type != PT_LOAD)
            continue;
        memcpy((char *)buffer + program_header.p_vaddr, (char *)kernel_addr + program_header.p_offset, program_header.p_filesz);
        memset((char *)buffer + program_header.p_vaddr + program_header.p_filesz, 0, program_header.p_memsz - program_header.p_filesz);
    }

    efi->getSystemTable()->ConOut->OutputString(efi->getSystemTable()->ConOut, (EFI::CHAR16 *)L"success!\r\n");
    unsigned char *section_table = (unsigned char *)(kernel_addr + elf_section[elf_header->e_shstrndx].sh_offset);
    Elf64_Shdr rela_dyn_section, rela_plt_section, dynsym_section, dynstr_section;
    rela_dyn_section.sh_size = 0;
    rela_plt_section.sh_size = 0;
    dynsym_section.sh_size = 0;
    dynstr_section.sh_size = 0;
    efi->getSystemTable()->ConOut->OutputString(efi->getSystemTable()->ConOut, (EFI::CHAR16 *)L"success!\r\n");
    puth(efi, elf_header->e_shnum, 8);
    for (unsigned int i = 0; i < elf_header->e_shnum; ++i)
    {
        Elf64_Shdr section_header = elf_section[i];
        unsigned char *section_name = section_table + section_header.sh_name;
        if (!strcmp((char *)section_name, ".rela.dyn"))
        {
            puth(efi, 1, 8);
            rela_dyn_section = section_header;
            puth(efi, section_header.sh_size, 8);
        }
        else if (!strcmp((char *)section_name, ".rela.plt"))
        {
            puth(efi, 2, 8);
            rela_plt_section = section_header;
            puth(efi, section_header.sh_size, 8);
        }
        else if (!strcmp((char *)section_name, ".dynsym"))
        {
            puth(efi, 3, 8);
            dynsym_section = section_header;
            puth(efi, section_header.sh_size, 8);
        }
        else if (!strcmp((char *)section_name, ".dynstr"))
        {
            puth(efi, 4, 8);
            dynstr_section = section_header;
            puth(efi, section_header.sh_size, 8);
        }
    }
    efi->getSystemTable()->ConOut->OutputString(efi->getSystemTable()->ConOut, (EFI::CHAR16 *)L"success!\r\n");

    Elf64_Sym *sym_table = (Elf64_Sym *)(kernel_addr + dynsym_section.sh_offset);
    Elf64_Rela *rela_dyn = (Elf64_Rela *)(kernel_addr + rela_dyn_section.sh_offset);
    Elf64_Rela *rela_plt = (Elf64_Rela *)(kernel_addr + rela_plt_section.sh_offset);

    for (unsigned int i = 0; i < rela_dyn_section.sh_size / sizeof(Elf64_Rela); ++i)
    {
        Elf64_Sym s = sym_table[ELF64_R_SYM(rela_dyn[i].r_info)];
        Elf64_Rela r = rela_dyn[i];
        void *to = (char *)buffer + r.r_offset;
        *(uint64_t *)to = (uint64_t)((char *)buffer + s.st_value);
    }

    efi->getSystemTable()->ConOut->OutputString(efi->getSystemTable()->ConOut, (EFI::CHAR16 *)L"succ!\r\n");
    for (unsigned int i = 0; i < rela_plt_section.sh_size / sizeof(Elf64_Rela); ++i)
    {
        Elf64_Sym s = sym_table[ELF64_R_SYM(rela_plt[i].r_info)];
        Elf64_Rela r = rela_plt[i];

        void *to = (char *)buffer + r.r_offset;
        *(uint64_t *)to = (uint64_t)((char *)buffer + s.st_value);
    }

    uint64_t entry_offset = 0;
    for (unsigned int i = 0; i < dynsym_section.sh_size / sizeof(Elf64_Sym); ++i)
    {
        Elf64_Sym s = sym_table[i];
        char *sym_name = ((char *)(kernel_addr + dynstr_section.sh_offset)) + s.st_name;
        if (!strcmp(sym_name, "kernel_start"))
        {
            efi->getSystemTable()->ConOut->OutputString(efi->getSystemTable()->ConOut, (EFI::CHAR16 *)L"find kernel\r\n");
            entry_offset = s.st_value;
        }
    }

    /* Ready For ExitBootServices() */
    EFI::EFI_MEMORY_DESCRIPTOR *MemoryMap = nullptr;
    EFI::UINTN MemoryMapSize = 0;
    EFI::UINTN MapKey, DescriptorSize;
    EFI::UINT32 DescriptorVersion;
    do
    {
        efi->getSystemTable()->ConOut->OutputString(efi->getSystemTable()->ConOut, (EFI::CHAR16 *)L"exit\r\n");
        status = efi->getSystemTable()->BootServices->GetMemoryMap(&MemoryMapSize, MemoryMap, &MapKey, &DescriptorSize, &DescriptorVersion);
        while (status == EFI::EFI_BUFFER_TOO_SMALL)
        {
            if (MemoryMap)
            {
                efi->getSystemTable()->BootServices->FreePool(MemoryMap);
            }
            status = efi->getSystemTable()->BootServices->AllocatePool(EFI::EfiLoaderData, MemoryMapSize, reinterpret_cast<EFI::VOID **>(&MemoryMap));
            status = efi->getSystemTable()->BootServices->GetMemoryMap(&MemoryMapSize, MemoryMap, &MapKey, &DescriptorSize, &DescriptorVersion);
        }
        status = efi->getSystemTable()->BootServices->ExitBootServices(ImageHandle, MapKey);
    } while (status != EFI::EFI_SUCCESS);


    puts(fb, "KizunaOS, boot up!!\n\n");

    // kernel_start(fb);
    typedef void EntryPoint(FrameBuffer *FrameBuffer);
    EntryPoint* entry_point = (EntryPoint *)(elf_header->e_entry);
    entry_point(fb); //*/
}