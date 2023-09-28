#include "Header.h"


SMBIOS_TABLE_ENTRY_POINT*
GetEPS (VOID)
{
  SMBIOS_TABLE_ENTRY_POINT      *Result;
  Result = NULL;

  EfiGetSystemConfigurationTable (
    &gEfiSmbiosTableGuid,
    (VOID**)&Result
    );

  return Result;
}


SMBIOS_TABLE_3_0_ENTRY_POINT*
GetEPS3_0 (VOID)
{
  SMBIOS_TABLE_3_0_ENTRY_POINT      *Result;
  Result = NULL;

  EfiGetSystemConfigurationTable (
    &gEfiSmbios3TableGuid,
    (VOID**)&Result
    );

  return Result;
}

/**
  Main entry point for UEFI application

  @param ImageHandle   ImageHandle
  @param SystemTable   SystemTable

  @retval 0       Normal exit
*/
EFI_STATUS
EFIAPI
UefiMain (
    EFI_HANDLE                  ImageHandle, 
    EFI_SYSTEM_TABLE            *SystemTable
  ) 
{
  EFI_STATUS                    InputStatus;
  EFI_STATUS                    Status;
  EFI_SMBIOS_PROTOCOL           *Interface;
  EFI_SMBIOS_HANDLE             SmbiosHandle;
  EFI_SMBIOS_TABLE_HEADER       *Record;
  SMBIOS_TABLE_ENTRY_POINT      *EPS;
  SMBIOS_TABLE_3_0_ENTRY_POINT  *EPS3_0;
  EFI_SMBIOS_TYPE               SmbiosType;
  EFI_INPUT_KEY                 Key;
  UINTN                         Len;
  BOOLEAN                       exit;
  BOOLEAN                       Continue;

  EPS           = GetEPS ();
  EPS3_0        = GetEPS3_0 ();
  exit          = FALSE;
  
  Status = gBS->LocateProtocol (
             &gEfiSmbiosProtocolGuid,
             NULL,
             (VOID**)&Interface
             );
  
  if (EFI_ERROR(Status)) {
    return Status;
  }
  
  while (TRUE) {
    
    gST->ConOut->ClearScreen(gST->ConOut);
    Print (L"Press F1 to dump SMBIOS Entry point Structure, Press F2 to dump SMBIOS Type, Press ESC to exit\n\n");
    Continue = FALSE;

    while (TRUE) {
      gST->ConIn->ReadKeyStroke (gST->ConIn,&Key);
      if (Key.ScanCode == 0x17) {
        exit = TRUE;
        break;
      } else if (Key.ScanCode == 0x0b) {
        PrintEPS (EPS);
        Print (L"======================================================================\n\n");
        PrintEPS3_0 (EPS3_0);
        Print (L"Press Any Key To Continue\n");
        while (TRUE) {
          InputStatus = gST->ConIn->ReadKeyStroke (gST->ConIn,&Key);
          if (!EFI_ERROR (InputStatus)) {
            break;
          }
        }
        Continue = TRUE;
        break;
      } else if (Key.ScanCode == 0x0c) {
        exit = FALSE;
        break;
      } else {
        continue;
      }
    }
    
    if (exit) {
      break;
    }

    if (Continue) {
      continue;
    }
    
    Len = 0;
    CHAR16                        Str[4];   
    Print (L"Input SMBIOS Type\n");

    while (TRUE) {

      InputStatus = gST->ConIn->ReadKeyStroke (gST->ConIn,&Key);
      if (!EFI_ERROR (InputStatus)) {        
        if (Key.UnicodeChar == L'\r') {
          if (Len > 0) {
            Str[Len] = L'\0';
            break;
          }
        }
        if (Key.UnicodeChar == L'\b') {
          if (Len > 0) {
            --Len;
            Print (L"%c",Key.UnicodeChar);
            continue;
          }
        }
        if (Len >= 3) {
          continue;
        }

        if (Key.UnicodeChar < 0x30 || Key.UnicodeChar > 0x39) {
          continue;
        }
        Print (L"%c",Key.UnicodeChar);
        Str[Len++] = Key.UnicodeChar;
      }   
    }
    
    Print (L"\n");
    SmbiosHandle  = SMBIOS_HANDLE_PI_RESERVED;
    SmbiosType    = (EFI_SMBIOS_TYPE) StrDecimalToUintn (Str);
    
    do {

      Status = Interface->GetNext (
              Interface, 
              &SmbiosHandle, 
              &SmbiosType, 
              &Record, 
              NULL
            );       
                
      if (!EFI_ERROR (Status)) {
        PrintTable (Record);
      } 
      else {
        Print (L"Table Not Found\n");
      }

      Print (L"Press Any Key To Continue\n");
      while (TRUE) {
        InputStatus = gST->ConIn->ReadKeyStroke (gST->ConIn,&Key);
        if (!EFI_ERROR (InputStatus)) {
          break;
        }
      }
    } while (!EFI_ERROR (Status));
  }
  
  return EFI_SUCCESS;
}