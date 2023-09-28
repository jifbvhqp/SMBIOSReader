#include <Uefi.h>
#include <Library/UefiApplicationEntryPoint.h>
#include <Library/UefiLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>
#include <Protocol/Smbios.h>
#include <Library/SmbiosLib.h>
#include <Guid/Smbios.h>

VOID
PrintTable (
    EFI_SMBIOS_TABLE_HEADER*  Record
);

VOID
PrintEPS (
    SMBIOS_TABLE_ENTRY_POINT* EPS
);

VOID
PrintEPS3_0 (
  SMBIOS_TABLE_3_0_ENTRY_POINT* EPS3_0
);