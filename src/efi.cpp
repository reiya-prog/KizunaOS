#include "main.h"
#include "efi.h"

EFI::EFI_GUID GraphicsOutputProtocol_GUID = {
    0x9042a9de, 0x23dc, 0x4a38,
   {0x96, 0xfb, 0x7a, 0xde,
    0xd0, 0x80, 0x51, 0x6a}
};

void EFI::EFIBootInit(){
    SystemTable->BootServices->SetWatchdogTimer(0, 0, 0, nullptr);
    SystemTable->BootServices->LocateProtocol(&GraphicsOutputProtocol_GUID, nullptr, (void **)&this->GraphicsOutputProtocol);
}
