#pragma once

#define IN
#define OUT
#define CONST const
#define EFIAPI

#define EFI_BOOT_SERVICES_SIGNATURE 0x56524553544f4f42

class EFI
{
public:
    typedef bool BOOLEAN;
    typedef long long INTN;
    typedef unsigned long long UINTN;
    typedef char INT8;
    typedef unsigned char UINT8;
    typedef short INT16;
    typedef unsigned short UINT16;
    typedef int INT32;
    typedef unsigned int UINT32;
    typedef long long INT64;
    typedef unsigned long long UINT64;
    typedef unsigned char CHAR8;
    typedef unsigned short CHAR16;
    typedef void VOID;
    // typedef ? EFI_GUID;
    typedef UINTN EFI_STATUS;
    typedef VOID *EFI_HANDLE;
    typedef VOID *EFI_EVENT;
    typedef UINT64 EFI_LBA;
    typedef UINTN EFI_TPL;
    // typedef ? EFI_MAC_ADDRESS;
    // typedef ? EFI_IPv4_ADDRESS;
    // typedef ? EFI_IPv6_ADDRESS;
    // typedef ? EFI_IP_ADDRESS;

    struct _EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL;
    struct _EFI_SIMPLE_TEXT_INPUT_PROTOCOL;

    typedef struct
    {
        UINT16 ScanCode;
        CHAR16 UnicodeChar;
    } EFI_INPUT_KEY;

    typedef struct _EFI_SIMPLE_TEXT_INPUT_PROTOCOL
    {
        EFI_STATUS (EFIAPI *Reset)(
            IN struct _EFI_SIMPLE_TEXT_INPUT_PROTOCOL *This,
            IN BOOLEAN ExtendedVerification);
        EFI_STATUS (EFIAPI *ReadKeyStroke)(
            IN struct _EFI_SIMPLE_TEXT_INPUT_PROTOCOL *This,
            OUT EFI_INPUT_KEY *Key);
        EFI_EVENT WaitForKey;
    } EFI_SIMPLE_TEXT_INPUT_PROTOCOL;

    typedef struct{
        INT32 MaxMode;
        INT32 Mode;
        INT32 Attribute;
        INT32 CursorColumn;
        INT32 CursorRow;
        BOOLEAN CursorVisible;
    } SIMPLE_TEXT_OUTPUT_MODE;

    typedef struct _EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL
    {
        EFI_STATUS (EFIAPI *Reset)(
            IN struct _EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This,
            IN BOOLEAN ExtendedVerification);
        EFI_STATUS (EFIAPI *OutputString)(
            IN struct _EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This,
            IN CHAR16 *String);
        EFI_STATUS (EFIAPI *TestString)(
            IN struct _EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This,
            IN CHAR16 *String);
        EFI_STATUS (EFIAPI *QueryMode)(
            IN struct _EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This,
            IN UINTN ModeNumber,
            OUT UINTN *Columns,
            OUT UINTN *Rows);
        EFI_STATUS (EFIAPI *SetMode)(
            IN struct _EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This,
            IN UINTN ModeNumber);
        EFI_STATUS (EFIAPI *SetAttribute)(
            IN struct _EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This,
            IN UINTN Attribute);
        EFI_STATUS (EFIAPI *ClearScreen)(
            IN struct _EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This);
    } EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL;

    typedef struct
    {
        char buf1[24];
        //
        // Task Priority Services
        //
        unsigned long long buf2[2];

        //
        // Memory Services
        //
        unsigned long long buf3[5];

        //
        // Event & Timer Services
        //
        unsigned long long buf4[2];
        EFI_STATUS (EFIAPI *WaitForEvent)(
            IN UINTN NumberOfEvents,
            IN EFI_EVENT *Event,
            OUT UINTN *Index);
        unsigned long long buf5[3];

        //
        // Protocol Handler Services
        //
        unsigned long long buf6[9];

        //
        // Image Services
        //
        unsigned long long buf7[5];

        //
        // Miscellaneous Services
        //
        unsigned long long buf8[2];
        EFI_STATUS (EFIAPI *SetWatchdogTimer)(
            IN UINTN Timeout,
            IN UINT64 WatchdogCode,
            IN UINTN DataSize,
            IN CHAR16 *WatchdogData);

        //
        // DriverSupport Services
        //
        unsigned long long buf9[2];

        //
        // Open and Close Protocol Services
        //
        unsigned long long buf10[3];

        //
        // Library Services
        //
        unsigned long long buf11[5];

        //
        // 32-bit CRC Services
        //
        unsigned long long buf12;

        //
        // Miscellaneous Services
        //
        unsigned long long buf13[3];
    } EFI_BOOT_SERVICES;

    typedef struct
    {
        char buf[36];
        EFI_HANDLE ConsoleInHandle;
        EFI_SIMPLE_TEXT_INPUT_PROTOCOL *ConIn;
        EFI_HANDLE ConsoleOutHandle;
        EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *ConOut;
        EFI_HANDLE StandardErrorHandle;
        EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *StdErr;

        EFI_BOOT_SERVICES *BootServices;
    } EFI_SYSTEM_TABLE;
};

EFI::EFI_STATUS EFIAPI efi_boot_loader(IN EFI::EFI_HANDLE ImageHandle, IN EFI::EFI_SYSTEM_TABLE *SystemTable);