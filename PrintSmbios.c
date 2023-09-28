#include <Uefi.h>
#include <Library/UefiLib.h>
#include <Protocol/Smbios.h>
#include <Library/SmbiosLib.h>
#include <Library/BaseMemoryLib.h>

VOID
PrintEPS (
  SMBIOS_TABLE_ENTRY_POINT* EPS
) 
{  
  if (EPS == NULL) {
    return;
  }
  
  UINTN Address;
  Address = (UINTN)EPS;
  CHAR8 AnchorString[5];
  CHAR8 IntermediateAnchorString[6];
  CopyMem (AnchorString,EPS->AnchorString,4);
  AnchorString[4] = '\0';
  CopyMem (IntermediateAnchorString,EPS->IntermediateAnchorString,5);
  IntermediateAnchorString[5] = '\0';

  Print (L"Address:                                     0x%08X\n",Address);
  Print (L"AnchorString:                                %a\n",AnchorString);           
  Print (L"EntryPointStructureChecksum:                 0x%02X\n",EPS->EntryPointStructureChecksum);     
  Print (L"EntryPointLength:                            0x%02X\n",EPS->EntryPointLength);
  Print (L"MajorVersion:                                0x%02X\n",EPS->MajorVersion);    
  Print (L"MinorVersion:                                0x%02X\n",EPS->MinorVersion);   
  Print (L"MaxStructureSize:                            0x%04X\n",EPS->MaxStructureSize); 
  Print (L"EntryPointRevision:                          0x%02X\n",EPS->EntryPointRevision);
  Print (L"FormattedArea[0]:                            0x%02X\n",EPS->FormattedArea[0]);   
  Print (L"FormattedArea[1]:                            0x%02X\n",EPS->FormattedArea[1]);  
  Print (L"FormattedArea[2]:                            0x%02X\n",EPS->FormattedArea[2]);  
  Print (L"FormattedArea[3]:                            0x%02X\n",EPS->FormattedArea[3]);    
  Print (L"FormattedArea[4]:                            0x%02X\n",EPS->FormattedArea[4]);      
  Print (L"IntermediateAnchorString:                    %a\n",IntermediateAnchorString);     
  Print (L"IntermediateChecksum:                        0x%02X\n",EPS->IntermediateChecksum);   
  Print (L"TableLength:                                 0x%04X\n",EPS->TableLength);
  Print (L"TableAddress:                                0x%08X\n",EPS->TableAddress);   
  Print (L"NumberOfSmbiosStructures:                    0x%04X\n",EPS->NumberOfSmbiosStructures);   
  Print (L"SmbiosBcdRevision:                           0x%02X\n",EPS->SmbiosBcdRevision);                       
}

VOID
PrintEPS3_0 (
  SMBIOS_TABLE_3_0_ENTRY_POINT* EPS3_0
) 
{  
  if (EPS3_0 == NULL) {
    return;
  }
  UINTN Address;
  Address = (UINTN)EPS3_0;
  CHAR8 AnchorString[6];
  CopyMem (AnchorString,EPS3_0->AnchorString,5);
  AnchorString[5] = '\0';

  Print (L"Address:                                     0x%08X\n",Address);
  Print (L"AnchorString:                                %a\n",AnchorString);           
  Print (L"EntryPointStructureChecksum:                 0x%02X\n",EPS3_0->EntryPointStructureChecksum);     
  Print (L"EntryPointLength:                            0x%02X\n",EPS3_0->EntryPointLength);
  Print (L"MajorVersion:                                0x%02X\n",EPS3_0->MajorVersion);    
  Print (L"MinorVersion:                                0x%02X\n",EPS3_0->MinorVersion);   
  Print (L"MinorVersion:                                0x%02X\n",EPS3_0->DocRev);     
  Print (L"MinorVersion:                                0x%02X\n",EPS3_0->EntryPointRevision);       
  Print (L"MinorVersion:                                0x%02X\n",EPS3_0->Reserved); 
  Print (L"MinorVersion:                                0x%08X\n",EPS3_0->TableMaximumSize); 
  Print (L"TableAddress:                                0x%016llX\n",EPS3_0->TableAddress);                    
}


VOID
PrintTable (
    EFI_SMBIOS_TABLE_HEADER*  Record
)
{
    UINTN                     Address;
    SMBIOS_STRUCTURE_POINTER  SMBIOSStruct;
  
  if (Record->Type == 0) {
      Address     = (UINTN) Record;
      SMBIOSStruct.Type0 = (SMBIOS_TABLE_TYPE0*) Address;
      Print (L"Address:                                0x%08X\n",Address);
      Print (L"Type:                                   0x%02X\n",SMBIOSStruct.Type0->Hdr.Type);
      Print (L"Length:                                 0x%02X\n",SMBIOSStruct.Type0->Hdr.Length);
      Print (L"Handle:                                 0x%04X\n",SMBIOSStruct.Type0->Hdr.Handle);
      Print (L"Vendor:                                 %a\n",SmbiosLibReadString (&(SMBIOSStruct.Type0->Hdr),SMBIOSStruct.Type0->Vendor));
      Print (L"BiosVersion:                            %a\n",SmbiosLibReadString (&(SMBIOSStruct.Type0->Hdr),SMBIOSStruct.Type0->BiosVersion));
      Print (L"BiosSegment:                            0x%04X\n",SMBIOSStruct.Type0->BiosSegment);
      Print (L"BiosReleaseDate:                        %a\n",SmbiosLibReadString (&(SMBIOSStruct.Type0->Hdr),SMBIOSStruct.Type0->BiosReleaseDate));
      Print (L"BiosSize:                               0x%02X\n",SMBIOSStruct.Type0->BiosSize);
      Print (L"BiosCharacteristics:                    0x%016llX\n",SMBIOSStruct.Type0->BiosCharacteristics);
      Print (L"BIOSCharacteristicsExtensionBytes[0]:   0x%02X\n",SMBIOSStruct.Type0->BIOSCharacteristicsExtensionBytes[0]);
      Print (L"BIOSCharacteristicsExtensionBytes[1]:   0x%02X\n",SMBIOSStruct.Type0->BIOSCharacteristicsExtensionBytes[1]);
      Print (L"SystemBiosMajorRelease:                 0x%02X\n",SMBIOSStruct.Type0->SystemBiosMajorRelease);
      Print (L"SystemBiosMinorRelease:                 0x%02X\n",SMBIOSStruct.Type0->SystemBiosMinorRelease);
      Print (L"EmbeddedControllerFirmwareMajorRelease: 0x%02X\n",SMBIOSStruct.Type0->EmbeddedControllerFirmwareMajorRelease);
      Print (L"EmbeddedControllerFirmwareMinorRelease: 0x%02X\n",SMBIOSStruct.Type0->EmbeddedControllerFirmwareMinorRelease);
      Print (L"ExtendedBiosSize:                       0x%04X\n",SMBIOSStruct.Type0->ExtendedBiosSize);
    } else if (Record->Type == 1) {
      Address     = (UINTN) Record;
      SMBIOSStruct.Type1 = (SMBIOS_TABLE_TYPE1*) Address;
      Print (L"Address:                                0x%08X\n",Address);
      Print (L"Type:                                   0x%02X\n",SMBIOSStruct.Type1->Hdr.Type);
      Print (L"Length:                                 0x%02X\n",SMBIOSStruct.Type1->Hdr.Length);
      Print (L"Handle:                                 0x%04X\n",SMBIOSStruct.Type1->Hdr.Handle);
      Print (L"Manufacturer:                           %a\n",SmbiosLibReadString (&(SMBIOSStruct.Type1->Hdr),SMBIOSStruct.Type1->Manufacturer));
      Print (L"ProductName:                            %a\n",SmbiosLibReadString (&(SMBIOSStruct.Type1->Hdr),SMBIOSStruct.Type1->ProductName));
      Print (L"Version:                                %a\n",SmbiosLibReadString (&(SMBIOSStruct.Type1->Hdr),SMBIOSStruct.Type1->Version));
      Print (L"SerialNumber:                           %a\n",SmbiosLibReadString (&(SMBIOSStruct.Type1->Hdr),SMBIOSStruct.Type1->SerialNumber));
      Print (L"Uuid:                                   %g\n",SMBIOSStruct.Type1->Uuid);
      Print (L"WakeUpType:                             0x%02X\n",SMBIOSStruct.Type1->WakeUpType);
      Print (L"SKUNumber:                              %a\n",SmbiosLibReadString (&(SMBIOSStruct.Type1->Hdr),SMBIOSStruct.Type1->SKUNumber));
      Print (L"Family:                                 %a\n",SmbiosLibReadString (&(SMBIOSStruct.Type1->Hdr),SMBIOSStruct.Type1->Family));
    } else if (Record->Type == 2) {
      Address     = (UINTN) Record;
      SMBIOSStruct.Type2 = (SMBIOS_TABLE_TYPE2*) Address;
      Print (L"Address:                                0x%08X\n",Address);
      Print (L"Type:                                   0x%02X\n",SMBIOSStruct.Type2->Hdr.Type);
      Print (L"Length:                                 0x%02X\n",SMBIOSStruct.Type2->Hdr.Length);
      Print (L"Handle:                                 0x%04X\n",SMBIOSStruct.Type2->Hdr.Handle);
      Print (L"Manufacturer:                           %a\n",SmbiosLibReadString (&(SMBIOSStruct.Type2->Hdr),SMBIOSStruct.Type2->Manufacturer));
      Print (L"ProductName:                            %a\n",SmbiosLibReadString (&(SMBIOSStruct.Type2->Hdr),SMBIOSStruct.Type2->ProductName));
      Print (L"Version:                                %a\n",SmbiosLibReadString (&(SMBIOSStruct.Type2->Hdr),SMBIOSStruct.Type2->Version));
      Print (L"SerialNumber:                           %a\n",SmbiosLibReadString (&(SMBIOSStruct.Type2->Hdr),SMBIOSStruct.Type2->SerialNumber));
      Print (L"AssetTag:                               %a\n",SmbiosLibReadString (&(SMBIOSStruct.Type2->Hdr),SMBIOSStruct.Type2->AssetTag));
      Print (L"FeatureFlag:                            0x%02X\n",SMBIOSStruct.Type2->FeatureFlag);
      Print (L"LocationInChassis:                      %a\n",SmbiosLibReadString (&(SMBIOSStruct.Type2->Hdr),SMBIOSStruct.Type2->LocationInChassis));
      Print (L"ChassisHandle:                          0x%04X\n",SMBIOSStruct.Type2->ChassisHandle);
      Print (L"BoardType:                              0x%02X\n",SMBIOSStruct.Type2->BoardType);
      Print (L"NumberOfContainedObjectHandles:         0x%02X\n",SMBIOSStruct.Type2->NumberOfContainedObjectHandles);
      Print (L"ContainedObjectHandles:                 0x%04X\n",SMBIOSStruct.Type2->ContainedObjectHandles[0]);
    } else if (Record->Type == 3) {
      Address     = (UINTN) Record;
      SMBIOSStruct.Type3 = (SMBIOS_TABLE_TYPE3*) Address;
      Print (L"Address:                                0x%08X\n",Address);
      Print (L"Type:                                   0x%02X\n",SMBIOSStruct.Type3->Hdr.Type);
      Print (L"Length:                                 0x%02X\n",SMBIOSStruct.Type3->Hdr.Length);
      Print (L"Handle:                                 0x%04X\n",SMBIOSStruct.Type3->Hdr.Handle);
      Print (L"Version:                                %a\n",SmbiosLibReadString (&(SMBIOSStruct.Type3->Hdr),SMBIOSStruct.Type3->Version));
      Print (L"SerialNumber:                           %a\n",SmbiosLibReadString (&(SMBIOSStruct.Type3->Hdr),SMBIOSStruct.Type3->SerialNumber));
      Print (L"AssetTag:                               %a\n",SmbiosLibReadString (&(SMBIOSStruct.Type3->Hdr),SMBIOSStruct.Type3->AssetTag));
      Print (L"BootupState:                            0x%02X\n",SMBIOSStruct.Type3->BootupState);
      Print (L"PowerSupplyState:                       0x%02X\n",SMBIOSStruct.Type3->PowerSupplyState);
      Print (L"ThermalState:                           0x%02X\n",SMBIOSStruct.Type3->ThermalState);
      Print (L"SecurityStatus:                         0x%02X\n",SMBIOSStruct.Type3->SecurityStatus);
      Print (L"OemDefined[0]:                          0x%02X\n",SMBIOSStruct.Type3->OemDefined[0]);
      Print (L"OemDefined[1]:                          0x%02X\n",SMBIOSStruct.Type3->OemDefined[1]);
      Print (L"OemDefined[2]:                          0x%02X\n",SMBIOSStruct.Type3->OemDefined[2]);
      Print (L"OemDefined[3]:                          0x%02X\n",SMBIOSStruct.Type3->OemDefined[3]);
      Print (L"Height:                                 0x%02X\n",SMBIOSStruct.Type3->Height);
      Print (L"NumberofPowerCords:                     0x%02X\n",SMBIOSStruct.Type3->NumberofPowerCords);
      Print (L"ContainedElementCount:                  0x%02X\n",SMBIOSStruct.Type3->ContainedElementCount);
      Print (L"ContainedElementRecordLength:           0x%02X\n",SMBIOSStruct.Type3->ContainedElementRecordLength);
      Print (L"ContainedElementMaximum:                0x%02X\n",SMBIOSStruct.Type3->ContainedElements[0].ContainedElementMaximum);
      Print (L"ContainedElementMinimum:                0x%02X\n",SMBIOSStruct.Type3->ContainedElements[0].ContainedElementMinimum);
      Print (L"ContainedElementType:                   0x%02X\n",SMBIOSStruct.Type3->ContainedElements[0].ContainedElementType);
    } else if (Record->Type == 4) {
      Address     = (UINTN) Record;
      SMBIOSStruct.Type4 = (SMBIOS_TABLE_TYPE4*) Address;
      Print (L"Address:                                0x%08X\n",Address);
      Print (L"Type:                                   0x%02X\n",SMBIOSStruct.Type4->Hdr.Type);
      Print (L"Length:                                 0x%02X\n",SMBIOSStruct.Type4->Hdr.Length);
      Print (L"Handle:                                 0x%04X\n",SMBIOSStruct.Type4->Hdr.Handle);
      Print (L"Socket:                                 %a\n",SmbiosLibReadString (&(SMBIOSStruct.Type4->Hdr),SMBIOSStruct.Type4->Socket));
      Print (L"ProcessorType:                          0x%02X\n",SMBIOSStruct.Type4->ProcessorType);
      Print (L"ProcessorFamily:                        0x%02X\n",SMBIOSStruct.Type4->ProcessorFamily);
      Print (L"ProcessorManufacturer:                  %a\n",SmbiosLibReadString (&(SMBIOSStruct.Type4->Hdr),SMBIOSStruct.Type4->ProcessorManufacturer));
      Print (L"Signature:                              0x%08X\n",SMBIOSStruct.Type4->ProcessorId.Signature);
      Print (L"FeatureFlags:                           0x%08X\n",SMBIOSStruct.Type4->ProcessorId.FeatureFlags);
      Print (L"ProcessorVersion:                       %a\n",SmbiosLibReadString (&(SMBIOSStruct.Type4->Hdr),SMBIOSStruct.Type4->ProcessorVersion));
      Print (L"Voltage:                                0x%02X\n",SMBIOSStruct.Type4->Voltage);
      Print (L"ExternalClock:                          0x%04X\n",SMBIOSStruct.Type4->ExternalClock);
      Print (L"MaxSpeed:                               0x%04X\n",SMBIOSStruct.Type4->MaxSpeed);
      Print (L"CurrentSpeed:                           0x%04X\n",SMBIOSStruct.Type4->CurrentSpeed);
      Print (L"Status:                                 0x%02X\n",SMBIOSStruct.Type4->Status);
      Print (L"ProcessorUpgrade:                       0x%02X\n",SMBIOSStruct.Type4->ProcessorUpgrade);
      Print (L"L1CacheHandle:                          0x%04X\n",SMBIOSStruct.Type4->L1CacheHandle);
      Print (L"L2CacheHandle:                          0x%04X\n",SMBIOSStruct.Type4->L2CacheHandle);
      Print (L"L3CacheHandle:                          0x%04X\n",SMBIOSStruct.Type4->L3CacheHandle);
      Print (L"SerialNumber:                           %a\n",SmbiosLibReadString (&(SMBIOSStruct.Type4->Hdr),SMBIOSStruct.Type4->SerialNumber));
      Print (L"AssetTag:                               %a\n",SmbiosLibReadString (&(SMBIOSStruct.Type4->Hdr),SMBIOSStruct.Type4->AssetTag));
      Print (L"PartNumber:                             %a\n",SmbiosLibReadString (&(SMBIOSStruct.Type4->Hdr),SMBIOSStruct.Type4->PartNumber));
      Print (L"CoreCount:                              0x%02X\n",SMBIOSStruct.Type4->CoreCount);
      Print (L"EnabledCoreCount:                       0x%02X\n",SMBIOSStruct.Type4->EnabledCoreCount);
      Print (L"ThreadCount:                            0x%02X\n",SMBIOSStruct.Type4->ThreadCount);
      Print (L"ProcessorCharacteristics:               0x%04X\n",SMBIOSStruct.Type4->ProcessorCharacteristics);
      Print (L"ProcessorFamily2:                       0x%04X\n",SMBIOSStruct.Type4->ProcessorFamily2);
      Print (L"CoreCount2:                             0x%04X\n",SMBIOSStruct.Type4->CoreCount2);
      Print (L"EnabledCoreCount2:                      0x%04X\n",SMBIOSStruct.Type4->EnabledCoreCount2);
      Print (L"ThreadCount2:                           0x%04X\n",SMBIOSStruct.Type4->ThreadCount2);
      Print (L"ThreadEnabled:                          0x%04X\n",SMBIOSStruct.Type4->ThreadEnabled);
    } else if (Record->Type == 5) {
      Address     = (UINTN) Record;
      SMBIOSStruct.Type5 = (SMBIOS_TABLE_TYPE5*) Address;
      Print (L"Address:                                0x%08X\n",Address);
      Print (L"Type:                                   0x%02X\n",SMBIOSStruct.Type5->Hdr.Type);
      Print (L"Length:                                 0x%02X\n",SMBIOSStruct.Type5->Hdr.Length);
      Print (L"Handle:                                 0x%04X\n",SMBIOSStruct.Type5->Hdr.Handle);
      Print (L"ErrDetectMethod:                        0x%02X\n",SMBIOSStruct.Type5->ErrDetectMethod);
      Print (L"ErrCorrectCapability:                   0x%02X\n",SMBIOSStruct.Type5->ErrCorrectCapability);
      Print (L"SupportInterleave:                      0x%02X\n",SMBIOSStruct.Type5->SupportInterleave);
      Print (L"CurrentInterleave:                      0x%02X\n",SMBIOSStruct.Type5->CurrentInterleave);
      Print (L"MaxMemoryModuleSize:                    0x%02X\n",SMBIOSStruct.Type5->MaxMemoryModuleSize);
      Print (L"SupportSpeed:                           0x%04X\n",SMBIOSStruct.Type5->SupportSpeed);
      Print (L"SupportMemoryType:                      0x%04X\n",SMBIOSStruct.Type5->SupportMemoryType);
      Print (L"MemoryModuleVoltage:                    0x%02X\n",SMBIOSStruct.Type5->MemoryModuleVoltage);
      Print (L"AssociatedMemorySlotNum:                0x%02X\n",SMBIOSStruct.Type5->AssociatedMemorySlotNum);
      Print (L"MemoryModuleConfigHandles:              0x%04X\n",SMBIOSStruct.Type5->MemoryModuleConfigHandles[0]);
    } else if (Record->Type == 6) {
      Address     = (UINTN) Record;
      SMBIOSStruct.Type6 = (SMBIOS_TABLE_TYPE6*) Address;
      Print (L"Address:                                0x%08X\n",Address);
      Print (L"Type:                                   0x%02X\n",SMBIOSStruct.Type6->Hdr.Type);
      Print (L"Length:                                 0x%02X\n",SMBIOSStruct.Type6->Hdr.Length);
      Print (L"Handle:                                 0x%04X\n",SMBIOSStruct.Type6->Hdr.Handle);
      Print (L"SocketDesignation:                      %a\n",SmbiosLibReadString (&(SMBIOSStruct.Type6->Hdr),SMBIOSStruct.Type6->SocketDesignation));
      Print (L"BankConnections:                        0x%02X\n",SMBIOSStruct.Type6->BankConnections);
      Print (L"CurrentSpeed:                           0x%02X\n",SMBIOSStruct.Type6->CurrentSpeed);
      Print (L"CurrentMemoryType:                      0x%04X\n",SMBIOSStruct.Type6->CurrentMemoryType);
      Print (L"InstalledSize:                          0x%02X\n",SMBIOSStruct.Type6->InstalledSize);
      Print (L"EnabledSize:                            0x%02X\n",SMBIOSStruct.Type6->EnabledSize);
      Print (L"ErrorStatus:                            0x%02X\n",SMBIOSStruct.Type6->ErrorStatus);
    } else if (Record->Type == 7) {
      Address     = (UINTN) Record;
      SMBIOSStruct.Type7 = (SMBIOS_TABLE_TYPE7*) Address;
      Print (L"Address:                                0x%08X\n",Address);
      Print (L"Type:                                   0x%02X\n",SMBIOSStruct.Type7->Hdr.Type);
      Print (L"Length:                                 0x%02X\n",SMBIOSStruct.Type7->Hdr.Length);
      Print (L"Handle:                                 0x%04X\n",SMBIOSStruct.Type7->Hdr.Handle);
      Print (L"SocketDesignation:                      %a\n",SmbiosLibReadString (&(SMBIOSStruct.Type7->Hdr),SMBIOSStruct.Type7->SocketDesignation));
      Print (L"CacheConfiguration:                     0x%04X\n",SMBIOSStruct.Type7->CacheConfiguration);
      Print (L"MaximumCacheSize:                       0x%04X\n",SMBIOSStruct.Type7->MaximumCacheSize);
      Print (L"InstalledSize:                          0x%04X\n",SMBIOSStruct.Type7->InstalledSize);
      Print (L"SupportedSRAMType:                      0x%04X\n",SMBIOSStruct.Type7->SupportedSRAMType);
      Print (L"CurrentSRAMType:                        0x%04X\n",SMBIOSStruct.Type7->CurrentSRAMType);
      Print (L"CacheSpeed:                             0x%02X\n",SMBIOSStruct.Type7->CacheSpeed);
      Print (L"ErrorCorrectionType:                    0x%02X\n",SMBIOSStruct.Type7->ErrorCorrectionType);
      Print (L"SystemCacheType:                        0x%02X\n",SMBIOSStruct.Type7->SystemCacheType);
      Print (L"Associativity:                          0x%02X\n",SMBIOSStruct.Type7->Associativity);
      Print (L"MaximumCacheSize2:                      0x%08X\n",SMBIOSStruct.Type7->MaximumCacheSize2);
      Print (L"InstalledSize2:                         0x%08X\n",SMBIOSStruct.Type7->InstalledSize2);
    } else if (Record->Type == 8) {
      Address     = (UINTN) Record;
      SMBIOSStruct.Type8 = (SMBIOS_TABLE_TYPE8*) Address;
      Print (L"Address:                                0x%08X\n",Address);
      Print (L"Type:                                   0x%02X\n",SMBIOSStruct.Type8->Hdr.Type);
      Print (L"Length:                                 0x%02X\n",SMBIOSStruct.Type8->Hdr.Length);
      Print (L"Handle:                                 0x%04X\n",SMBIOSStruct.Type8->Hdr.Handle);
      Print (L"InternalReferenceDesignator:            %a\n",SmbiosLibReadString (&(SMBIOSStruct.Type8->Hdr),SMBIOSStruct.Type8->InternalReferenceDesignator));
      Print (L"InternalConnectorType:                  0x%02X\n",SMBIOSStruct.Type8->InternalConnectorType);
      Print (L"ExternalReferenceDesignator:            %a\n",SmbiosLibReadString (&(SMBIOSStruct.Type8->Hdr),SMBIOSStruct.Type8->ExternalReferenceDesignator));
      Print (L"ExternalConnectorType:                  0x%02X\n",SMBIOSStruct.Type8->ExternalConnectorType);
      Print (L"PortType:                               0x%02X\n",SMBIOSStruct.Type8->PortType);
    } else if (Record->Type == 9) {
      Address     = (UINTN) Record;
      SMBIOSStruct.Type9 = (SMBIOS_TABLE_TYPE9*) Address;
      Print (L"Address:                                0x%08X\n",Address);
      Print (L"Type:                                   0x%02X\n",SMBIOSStruct.Type9->Hdr.Type);
      Print (L"Length:                                 0x%02X\n",SMBIOSStruct.Type9->Hdr.Length);
      Print (L"Handle:                                 0x%04X\n",SMBIOSStruct.Type9->Hdr.Handle);
      Print (L"SlotDesignation:                        %a\n",SmbiosLibReadString (&(SMBIOSStruct.Type9->Hdr),SMBIOSStruct.Type9->SlotDesignation));
      Print (L"SlotType:                               0x%02X\n",SMBIOSStruct.Type9->SlotType);
      Print (L"SlotDataBusWidth:                       0x%02X\n",SMBIOSStruct.Type9->SlotDataBusWidth);
      Print (L"CurrentUsage:                           0x%02X\n",SMBIOSStruct.Type9->CurrentUsage);
      Print (L"SlotLength:                             0x%02X\n",SMBIOSStruct.Type9->SlotLength);
      Print (L"SlotID:                                 0x%04X\n",SMBIOSStruct.Type9->SlotID);
      Print (L"SlotCharacteristics1:                   0x%02X\n",SMBIOSStruct.Type9->SlotCharacteristics1);
      Print (L"SlotCharacteristics2:                   0x%02X\n",SMBIOSStruct.Type9->SlotCharacteristics2);
      Print (L"SegmentGroupNum:                        0x%04X\n",SMBIOSStruct.Type9->SegmentGroupNum);
      Print (L"BusNum:                                 0x%02X\n",SMBIOSStruct.Type9->BusNum);
      Print (L"DevFuncNum:                             0x%02X\n",SMBIOSStruct.Type9->DevFuncNum);
      Print (L"DataBusWidth:                           0x%02X\n",SMBIOSStruct.Type9->DataBusWidth);
      Print (L"PeerGroupingCount:                      0x%02X\n",SMBIOSStruct.Type9->PeerGroupingCount);
      Print (L"PeerGroups[0].BusNum:                   0x%02X\n",SMBIOSStruct.Type9->PeerGroups[0].BusNum);
      Print (L"PeerGroups[0].DataBusWidth:             0x%02X\n",SMBIOSStruct.Type9->PeerGroups[0].DataBusWidth);
      Print (L"PeerGroups[0].DevFuncNum:               0x%02X\n",SMBIOSStruct.Type9->PeerGroups[0].DevFuncNum);
      Print (L"PeerGroups[0].SegmentGroupNum:          0x%02X\n",SMBIOSStruct.Type9->PeerGroups[0].SegmentGroupNum);
    } else if (Record->Type == 10) {
      Address     = (UINTN) Record;
      SMBIOSStruct.Type10 = (SMBIOS_TABLE_TYPE10*) Address;
      Print (L"Address:                                0x%08X\n",Address);
      Print (L"Type:                                   0x%02X\n",SMBIOSStruct.Type10->Hdr.Type);
      Print (L"Length:                                 0x%02X\n",SMBIOSStruct.Type10->Hdr.Length);
      Print (L"Handle:                                 0x%04X\n",SMBIOSStruct.Type10->Hdr.Handle);
      Print (L"Device[0].DeviceType:                   0x%02X\n",SMBIOSStruct.Type10->Device[0].DeviceType);
      Print (L"Device[0].DescriptionString:            %a\n",SmbiosLibReadString (&(SMBIOSStruct.Type10->Hdr),SMBIOSStruct.Type10->Device[0].DescriptionString));
    } else if (Record->Type == 11) {
      Address     = (UINTN) Record;
      SMBIOSStruct.Type11 = (SMBIOS_TABLE_TYPE11*) Address;
      Print (L"Address:                                0x%08X\n",Address);
      Print (L"Type:                                   0x%02X\n",SMBIOSStruct.Type11->Hdr.Type);
      Print (L"Length:                                 0x%02X\n",SMBIOSStruct.Type11->Hdr.Length);
      Print (L"Handle:                                 0x%04X\n",SMBIOSStruct.Type11->Hdr.Handle);
      Print (L"StringCount:                            0x%02X\n",SMBIOSStruct.Type11->StringCount);
    } else if (Record->Type == 12) {
      Address     = (UINTN) Record;
      SMBIOSStruct.Type12 = (SMBIOS_TABLE_TYPE12*) Address;
      Print (L"Address:                                0x%08X\n",Address);
      Print (L"Type:                                   0x%02X\n",SMBIOSStruct.Type12->Hdr.Type);
      Print (L"Length:                                 0x%02X\n",SMBIOSStruct.Type12->Hdr.Length);
      Print (L"Handle:                                 0x%04X\n",SMBIOSStruct.Type12->Hdr.Handle);
      Print (L"StringCount:                            0x%02X\n",SMBIOSStruct.Type12->StringCount);
    } else if (Record->Type == 13) {
      Address     = (UINTN) Record;
      SMBIOSStruct.Type13 = (SMBIOS_TABLE_TYPE13*) Address;
      Print (L"Address:                                0x%08X\n",Address);
      Print (L"Type:                                   0x%02X\n",SMBIOSStruct.Type13->Hdr.Type);
      Print (L"Length:                                 0x%02X\n",SMBIOSStruct.Type13->Hdr.Length);
      Print (L"Handle:                                 0x%04X\n",SMBIOSStruct.Type13->Hdr.Handle);
      Print (L"InstallableLanguages:                   0x%02X\n",SMBIOSStruct.Type13->InstallableLanguages);
      Print (L"Flags:                                  0x%02X\n",SMBIOSStruct.Type13->Flags);
      Print (L"Reserved[0]:                            0x%02X\n",SMBIOSStruct.Type13->Reserved[0]);
      Print (L"Reserved[1]:                            0x%02X\n",SMBIOSStruct.Type13->Reserved[1]);
      Print (L"Reserved[2]:                            0x%02X\n",SMBIOSStruct.Type13->Reserved[2]);
      Print (L"Reserved[3]:                            0x%02X\n",SMBIOSStruct.Type13->Reserved[3]);
      Print (L"Reserved[4]:                            0x%02X\n",SMBIOSStruct.Type13->Reserved[4]);
      Print (L"Reserved[5]:                            0x%02X\n",SMBIOSStruct.Type13->Reserved[5]);
      Print (L"Reserved[6]:                            0x%02X\n",SMBIOSStruct.Type13->Reserved[6]);
      Print (L"Reserved[7]:                            0x%02X\n",SMBIOSStruct.Type13->Reserved[7]);
      Print (L"Reserved[8]:                            0x%02X\n",SMBIOSStruct.Type13->Reserved[8]);
      Print (L"Reserved[9]:                            0x%02X\n",SMBIOSStruct.Type13->Reserved[9]);
      Print (L"Reserved[10]:                           0x%02X\n",SMBIOSStruct.Type13->Reserved[10]);
      Print (L"Reserved[11]:                           0x%02X\n",SMBIOSStruct.Type13->Reserved[11]);
      Print (L"Reserved[12]:                           0x%02X\n",SMBIOSStruct.Type13->Reserved[12]);
      Print (L"Reserved[13]:                           0x%02X\n",SMBIOSStruct.Type13->Reserved[13]);
      Print (L"Reserved[14]:                           0x%02X\n",SMBIOSStruct.Type13->Reserved[14]);
      Print (L"CurrentLanguages:                       %a\n",SmbiosLibReadString (&(SMBIOSStruct.Type13->Hdr),SMBIOSStruct.Type13->CurrentLanguages));
    } else if (Record->Type == 14) {
      Address     = (UINTN) Record;
      SMBIOSStruct.Type14 = (SMBIOS_TABLE_TYPE14*) Address;
      Print (L"Address:                                0x%08X\n",Address);
      Print (L"Type:                                   0x%02X\n",SMBIOSStruct.Type14->Hdr.Type);
      Print (L"Length:                                 0x%02X\n",SMBIOSStruct.Type14->Hdr.Length);
      Print (L"Handle:                                 0x%04X\n",SMBIOSStruct.Type14->Hdr.Handle);
      Print (L"GroupName:                              %a\n",SmbiosLibReadString (&(SMBIOSStruct.Type14->Hdr),SMBIOSStruct.Type14->GroupName));
      Print (L"Group[0].ItemType:                      0x%02X\n",SMBIOSStruct.Type14->Group[0].ItemType);
      Print (L"Group[0].ItemHandle:                    0x%04X\n",SMBIOSStruct.Type14->Group[0].ItemHandle);
    } else if (Record->Type == 15) {
      Address     = (UINTN) Record;
      SMBIOSStruct.Type15 = (SMBIOS_TABLE_TYPE15*) Address;
      Print (L"Address:                                0x%08X\n",Address);
      Print (L"Type:                                   0x%02X\n",SMBIOSStruct.Type15->Hdr.Type);
      Print (L"Length:                                 0x%02X\n",SMBIOSStruct.Type15->Hdr.Length);
      Print (L"Handle:                                 0x%04X\n",SMBIOSStruct.Type15->Hdr.Handle);
      Print (L"LogAreaLength:                          0x%04X\n",SMBIOSStruct.Type15->LogAreaLength);
      Print (L"LogHeaderStartOffset:                   0x%04X\n",SMBIOSStruct.Type15->LogHeaderStartOffset);
      Print (L"LogDataStartOffset:                     0x%04X\n",SMBIOSStruct.Type15->LogDataStartOffset);
      Print (L"AccessMethod:                           0x%02X\n",SMBIOSStruct.Type15->AccessMethod);
      Print (L"LogStatus:                              0x%02X\n",SMBIOSStruct.Type15->LogStatus);
      Print (L"LogChangeToken:                         0x%08X\n",SMBIOSStruct.Type15->LogChangeToken);
      Print (L"AccessMethodAddress:                    0x%08X\n",SMBIOSStruct.Type15->AccessMethodAddress);
      Print (L"LogHeaderFormat:                        0x%02X\n",SMBIOSStruct.Type15->LogHeaderFormat);
      Print (L"NumberOfSupportedLogTypeDescriptors:    0x%02X\n",SMBIOSStruct.Type15->NumberOfSupportedLogTypeDescriptors);
      Print (L"LengthOfLogTypeDescriptor:              0x%02X\n",SMBIOSStruct.Type15->LengthOfLogTypeDescriptor);
      Print (L"EventLogTypeDescriptors[0].DataFormatType:              0x%02X\n",SMBIOSStruct.Type15->EventLogTypeDescriptors[0].DataFormatType);
      Print (L"EventLogTypeDescriptors[0].LogType:     0x%02X\n",SMBIOSStruct.Type15->EventLogTypeDescriptors[0].LogType);
    } else if (Record->Type == 16) {
      Address     = (UINTN) Record;
      SMBIOSStruct.Type16 = (SMBIOS_TABLE_TYPE16*) Address;
      Print (L"Address:                                0x%08X\n",Address);
      Print (L"Type:                                   0x%02X\n",SMBIOSStruct.Type16->Hdr.Type);
      Print (L"Length:                                 0x%02X\n",SMBIOSStruct.Type16->Hdr.Length);
      Print (L"Handle:                                 0x%04X\n",SMBIOSStruct.Type16->Hdr.Handle);
      Print (L"Location:                               0x%02X\n",SMBIOSStruct.Type16->Location);
      Print (L"Use:                                    0x%02X\n",SMBIOSStruct.Type16->Use);
      Print (L"MemoryErrorCorrection:                  0x%02X\n",SMBIOSStruct.Type16->MemoryErrorCorrection);
      Print (L"MaximumCapacity:                        0x%08X\n",SMBIOSStruct.Type16->MaximumCapacity);
      Print (L"MemoryErrorInformationHandle:           0x%04X\n",SMBIOSStruct.Type16->MemoryErrorInformationHandle);
      Print (L"NumberOfMemoryDevices:                  0x%04X\n",SMBIOSStruct.Type16->NumberOfMemoryDevices);
      Print (L"ExtendedMaximumCapacity:                0x%08X\n",SMBIOSStruct.Type16->ExtendedMaximumCapacity);
    } else if (Record->Type == 17) {
      Address     = (UINTN) Record;
      SMBIOSStruct.Type17 = (SMBIOS_TABLE_TYPE17*) Address;
      Print (L"Address:                                0x%08X\n",Address);
      Print (L"Type:                                   0x%02X\n",SMBIOSStruct.Type17->Hdr.Type);
      Print (L"Length:                                 0x%02X\n",SMBIOSStruct.Type17->Hdr.Length);
      Print (L"Handle:                                 0x%04X\n",SMBIOSStruct.Type17->Hdr.Handle);
      Print (L"MemoryArrayHandle:                      0x%04X\n",SMBIOSStruct.Type17->MemoryArrayHandle);
      Print (L"MemoryErrorInformationHandle:           0x%04X\n",SMBIOSStruct.Type17->MemoryErrorInformationHandle);
      Print (L"TotalWidth:                             0x%04X\n",SMBIOSStruct.Type17->TotalWidth);
      Print (L"DataWidth:                              0x%04X\n",SMBIOSStruct.Type17->DataWidth);
      Print (L"Size:                                   0x%04X\n",SMBIOSStruct.Type17->Size);
      Print (L"FormFactor:                             0x%02X\n",SMBIOSStruct.Type17->FormFactor);
      Print (L"DeviceSet:                              0x%02X\n",SMBIOSStruct.Type17->DeviceSet);
      Print (L"DeviceLocator:                          %a\n",SmbiosLibReadString (&(SMBIOSStruct.Type17->Hdr),SMBIOSStruct.Type17->DeviceLocator));
      Print (L"BankLocator:                            %a\n",SmbiosLibReadString (&(SMBIOSStruct.Type17->Hdr),SMBIOSStruct.Type17->BankLocator));
      Print (L"MemoryType:                             0x%02X\n",SMBIOSStruct.Type17->MemoryType);
      Print (L"TypeDetail:                             0x%04X\n",SMBIOSStruct.Type17->TypeDetail);
      Print (L"Speed:                                  0x%04X\n",SMBIOSStruct.Type17->Speed);
      Print (L"Manufacturer:                           %a\n",SmbiosLibReadString (&(SMBIOSStruct.Type17->Hdr),SMBIOSStruct.Type17->Manufacturer));
      Print (L"SerialNumber:                           %a\n",SmbiosLibReadString (&(SMBIOSStruct.Type17->Hdr),SMBIOSStruct.Type17->SerialNumber));
      Print (L"AssetTag:                               %a\n",SmbiosLibReadString (&(SMBIOSStruct.Type17->Hdr),SMBIOSStruct.Type17->AssetTag));
      Print (L"PartNumber:                             %a\n",SmbiosLibReadString (&(SMBIOSStruct.Type17->Hdr),SMBIOSStruct.Type17->PartNumber));
      Print (L"Attributes:                             0x%02X\n",SMBIOSStruct.Type17->Attributes);
      Print (L"ExtendedSize:                           0x%08X\n",SMBIOSStruct.Type17->ExtendedSize);
      Print (L"ConfiguredMemoryClockSpeed:             0x%04X\n",SMBIOSStruct.Type17->ConfiguredMemoryClockSpeed);
      Print (L"MinimumVoltage:                         0x%04X\n",SMBIOSStruct.Type17->MinimumVoltage);
      Print (L"MaximumVoltage:                         0x%04X\n",SMBIOSStruct.Type17->MaximumVoltage);
      Print (L"ConfiguredVoltage:                      0x%04X\n",SMBIOSStruct.Type17->ConfiguredVoltage);
      Print (L"MemoryTechnology:                       0x%02X\n",SMBIOSStruct.Type17->MemoryTechnology);
      Print (L"MemoryOperatingModeCapability.Bits:     0x%04X\n",SMBIOSStruct.Type17->MemoryOperatingModeCapability.Bits);
      Print (L"MemoryOperatingModeCapability.Uint16:   0x%04X\n",SMBIOSStruct.Type17->MemoryOperatingModeCapability.Uint16);
      Print (L"FirmwareVersion:                        %a\n",SmbiosLibReadString (&(SMBIOSStruct.Type17->Hdr),SMBIOSStruct.Type17->FirmwareVersion));
      Print (L"ModuleManufacturerID:                   0x%04X\n",SMBIOSStruct.Type17->ModuleManufacturerID);
      Print (L"ModuleProductID:                        0x%04X\n",SMBIOSStruct.Type17->ModuleProductID);
      Print (L"MemorySubsystemControllerManufacturerID:0x%04X\n",SMBIOSStruct.Type17->MemorySubsystemControllerManufacturerID);
      Print (L"MemorySubsystemControllerProductID:     0x%04X\n",SMBIOSStruct.Type17->MemorySubsystemControllerProductID);
      Print (L"NonVolatileSize:                        0x%016llX\n",SMBIOSStruct.Type17->NonVolatileSize);
      Print (L"VolatileSize:                           0x%016llX\n",SMBIOSStruct.Type17->VolatileSize);
      Print (L"CacheSize:                              0x%016llX\n",SMBIOSStruct.Type17->CacheSize);
      Print (L"LogicalSize:                            0x%016llX\n",SMBIOSStruct.Type17->LogicalSize);
      Print (L"ExtendedSpeed:                          0x%08X\n",SMBIOSStruct.Type17->ExtendedSpeed);
      Print (L"ExtendedConfiguredMemorySpeed:          0x%08X\n",SMBIOSStruct.Type17->ExtendedConfiguredMemorySpeed);
    } else if (Record->Type == 18) {
      Address     = (UINTN) Record;
      SMBIOSStruct.Type18 = (SMBIOS_TABLE_TYPE18*) Address;
      Print (L"Address:                                0x%08X\n",Address);
      Print (L"Type:                                   0x%02X\n",SMBIOSStruct.Type18->Hdr.Type);
      Print (L"Length:                                 0x%02X\n",SMBIOSStruct.Type18->Hdr.Length);
      Print (L"Handle:                                 0x%04X\n",SMBIOSStruct.Type18->Hdr.Handle);
      Print (L"ErrorType:                              0x%02X\n",SMBIOSStruct.Type18->ErrorType);
      Print (L"ErrorGranularity:                       0x%02X\n",SMBIOSStruct.Type18->ErrorGranularity);
      Print (L"ErrorOperation:                         0x%02X\n",SMBIOSStruct.Type18->ErrorOperation);
      Print (L"VendorSyndrome:                         0x%08X\n",SMBIOSStruct.Type18->VendorSyndrome);
      Print (L"MemoryArrayErrorAddress:                0x%08X\n",SMBIOSStruct.Type18->MemoryArrayErrorAddress);
      Print (L"DeviceErrorAddress:                     0x%08X\n",SMBIOSStruct.Type18->DeviceErrorAddress);
      Print (L"ErrorResolution:                        0x%08X\n",SMBIOSStruct.Type18->ErrorResolution);
    } else if (Record->Type == 19) {
      Address     = (UINTN) Record;
      SMBIOSStruct.Type19 = (SMBIOS_TABLE_TYPE19*) Address;
      Print (L"Address:                                0x%08X\n",Address);
      Print (L"Type:                                   0x%02X\n",SMBIOSStruct.Type19->Hdr.Type);
      Print (L"Length:                                 0x%02X\n",SMBIOSStruct.Type19->Hdr.Length);
      Print (L"Handle:                                 0x%04X\n",SMBIOSStruct.Type19->Hdr.Handle);
      Print (L"StartingAddress:                        0x%08X\n",SMBIOSStruct.Type19->StartingAddress);
      Print (L"EndingAddress:                          0x%08X\n",SMBIOSStruct.Type19->EndingAddress);
      Print (L"MemoryArrayHandle:                      0x%04X\n",SMBIOSStruct.Type19->MemoryArrayHandle);
      Print (L"PartitionWidth:                         0x%02X\n",SMBIOSStruct.Type19->PartitionWidth);
      Print (L"ExtendedStartingAddress:                0x%016llX\n",SMBIOSStruct.Type19->ExtendedStartingAddress);
      Print (L"ExtendedEndingAddress:                  0x%016llX\n",SMBIOSStruct.Type19->ExtendedEndingAddress);
    } else if (Record->Type == 20) {
      Address     = (UINTN) Record;
      SMBIOSStruct.Type20 = (SMBIOS_TABLE_TYPE20*) Address;
      Print (L"Address:                                0x%08X\n",Address);
      Print (L"Type:                                   0x%02X\n",SMBIOSStruct.Type20->Hdr.Type);
      Print (L"Length:                                 0x%02X\n",SMBIOSStruct.Type20->Hdr.Length);
      Print (L"Handle:                                 0x%04X\n",SMBIOSStruct.Type20->Hdr.Handle);
      Print (L"StartingAddress:                        0x%08X\n",SMBIOSStruct.Type20->StartingAddress);
      Print (L"EndingAddress:                          0x%08X\n",SMBIOSStruct.Type20->EndingAddress);
      Print (L"MemoryDeviceHandle:                     0x%04X\n",SMBIOSStruct.Type20->MemoryDeviceHandle);
      Print (L"MemoryArrayMappedAddressHandle:         0x%04X\n",SMBIOSStruct.Type20->MemoryArrayMappedAddressHandle);
      Print (L"PartitionRowPosition:                   0x%02X\n",SMBIOSStruct.Type20->PartitionRowPosition);
      Print (L"InterleavePosition:                     0x%02X\n",SMBIOSStruct.Type20->InterleavePosition);
      Print (L"InterleavedDataDepth:                   0x%02X\n",SMBIOSStruct.Type20->InterleavedDataDepth);
      Print (L"ExtendedStartingAddress:                0x%016llX\n",SMBIOSStruct.Type20->ExtendedStartingAddress);
      Print (L"ExtendedEndingAddress:                  0x%016llX\n",SMBIOSStruct.Type20->ExtendedEndingAddress);
    } else if (Record->Type == 21) {
      Address     = (UINTN) Record;
      SMBIOSStruct.Type21 = (SMBIOS_TABLE_TYPE21*) Address;
      Print (L"Address:                                0x%08X\n",Address);
      Print (L"Type:                                   0x%02X\n",SMBIOSStruct.Type21->Hdr.Type);
      Print (L"Length:                                 0x%02X\n",SMBIOSStruct.Type21->Hdr.Length);
      Print (L"Handle:                                 0x%04X\n",SMBIOSStruct.Type21->Hdr.Handle);
      Print (L"Type:                                   0x%02X\n",SMBIOSStruct.Type21->Type);
      Print (L"Interface:                              0x%02X\n",SMBIOSStruct.Type21->Interface);
      Print (L"NumberOfButtons:                        0x%02X\n",SMBIOSStruct.Type21->NumberOfButtons);
    } else if (Record->Type == 22) {
      Address     = (UINTN) Record;
      SMBIOSStruct.Type22 = (SMBIOS_TABLE_TYPE22*) Address;
      Print (L"Address:                                0x%08X\n",Address);
      Print (L"Type:                                   0x%02X\n",SMBIOSStruct.Type22->Hdr.Type);
      Print (L"Length:                                 0x%02X\n",SMBIOSStruct.Type22->Hdr.Length);
      Print (L"Handle:                                 0x%04X\n",SMBIOSStruct.Type22->Hdr.Handle);
      Print (L"Location:                               %a\n",SmbiosLibReadString (&(SMBIOSStruct.Type22->Hdr),SMBIOSStruct.Type22->Location));
      Print (L"Manufacturer:                           %a\n",SmbiosLibReadString (&(SMBIOSStruct.Type22->Hdr),SMBIOSStruct.Type22->Manufacturer));
      Print (L"ManufactureDate:                        %a\n",SmbiosLibReadString (&(SMBIOSStruct.Type22->Hdr),SMBIOSStruct.Type22->ManufactureDate));
      Print (L"SerialNumber:                           %a\n",SmbiosLibReadString (&(SMBIOSStruct.Type22->Hdr),SMBIOSStruct.Type22->SerialNumber));
      Print (L"DeviceName:                             %a\n",SmbiosLibReadString (&(SMBIOSStruct.Type22->Hdr),SMBIOSStruct.Type22->DeviceName));
      Print (L"DeviceChemistry:                        0x%02X\n",SMBIOSStruct.Type22->DeviceChemistry);
      Print (L"DeviceCapacity:                         0x%04X\n",SMBIOSStruct.Type22->DeviceCapacity);
      Print (L"DesignVoltage:                          0x%04X\n",SMBIOSStruct.Type22->DesignVoltage);
      Print (L"SBDSVersionNumber:                      %a\n",SmbiosLibReadString (&(SMBIOSStruct.Type22->Hdr),SMBIOSStruct.Type22->SBDSVersionNumber));
      Print (L"MaximumErrorInBatteryData:              0x%02X\n",SMBIOSStruct.Type22->MaximumErrorInBatteryData);
      Print (L"SBDSSerialNumber:                       0x%04X\n",SMBIOSStruct.Type22->SBDSSerialNumber);
      Print (L"SBDSManufactureDate:                    0x%04X\n",SMBIOSStruct.Type22->SBDSManufactureDate);
      Print (L"SBDSDeviceChemistry:                    %a\n",SmbiosLibReadString (&(SMBIOSStruct.Type22->Hdr),SMBIOSStruct.Type22->SBDSDeviceChemistry));
      Print (L"DesignCapacityMultiplier:               0x%02X\n",SMBIOSStruct.Type22->DesignCapacityMultiplier);
      Print (L"OEMSpecific:                            0x%08X\n",SMBIOSStruct.Type22->OEMSpecific);
    } else if (Record->Type == 23) {
      Address     = (UINTN) Record;
      SMBIOSStruct.Type23 = (SMBIOS_TABLE_TYPE23*) Address;
      Print (L"Address:                                0x%08X\n",Address);
      Print (L"Type:                                   0x%02X\n",SMBIOSStruct.Type23->Hdr.Type);
      Print (L"Length:                                 0x%02X\n",SMBIOSStruct.Type23->Hdr.Length);
      Print (L"Handle:                                 0x%04X\n",SMBIOSStruct.Type23->Hdr.Handle);
      Print (L"Capabilities:                           0x%02X\n",SMBIOSStruct.Type23->Capabilities);
      Print (L"ResetCount:                             0x%04X\n",SMBIOSStruct.Type23->ResetCount);
      Print (L"ResetLimit:                             0x%04X\n",SMBIOSStruct.Type23->ResetLimit);
      Print (L"TimerInterval:                          0x%04X\n",SMBIOSStruct.Type23->TimerInterval);
      Print (L"Timeout:                                0x%04X\n",SMBIOSStruct.Type23->Timeout);
    } else if (Record->Type == 24) {
      Address     = (UINTN) Record;
      SMBIOSStruct.Type24 = (SMBIOS_TABLE_TYPE24*) Address;
      Print (L"Address:                                0x%08X\n",Address);
      Print (L"Type:                                   0x%02X\n",SMBIOSStruct.Type24->Hdr.Type);
      Print (L"Length:                                 0x%02X\n",SMBIOSStruct.Type24->Hdr.Length);
      Print (L"Handle:                                 0x%04X\n",SMBIOSStruct.Type24->Hdr.Handle);
      Print (L"HardwareSecuritySettings:               0x%02X\n",SMBIOSStruct.Type24->HardwareSecuritySettings);
    } else if (Record->Type == 25) {
      Address     = (UINTN) Record;
      SMBIOSStruct.Type25 = (SMBIOS_TABLE_TYPE25*) Address;
      Print (L"Address:                                0x%08X\n",Address);
      Print (L"Type:                                   0x%02X\n",SMBIOSStruct.Type25->Hdr.Type);
      Print (L"Length:                                 0x%02X\n",SMBIOSStruct.Type25->Hdr.Length);
      Print (L"Handle:                                 0x%04X\n",SMBIOSStruct.Type25->Hdr.Handle);
      Print (L"NextScheduledPowerOnMonth:              0x%02X\n",SMBIOSStruct.Type25->NextScheduledPowerOnMonth);
      Print (L"NextScheduledPowerOnDayOfMonth:         0x%02X\n",SMBIOSStruct.Type25->NextScheduledPowerOnDayOfMonth);
      Print (L"NextScheduledPowerOnHour:               0x%02X\n",SMBIOSStruct.Type25->NextScheduledPowerOnHour);
      Print (L"NextScheduledPowerOnMinute:             0x%02X\n",SMBIOSStruct.Type25->NextScheduledPowerOnMinute);
      Print (L"NextScheduledPowerOnSecond:             0x%02X\n",SMBIOSStruct.Type25->NextScheduledPowerOnSecond);
    } else if (Record->Type == 26) {
      Address     = (UINTN) Record;
      SMBIOSStruct.Type26 = (SMBIOS_TABLE_TYPE26*) Address;
      Print (L"Address:                                0x%08X\n",Address);
      Print (L"Type:                                   0x%02X\n",SMBIOSStruct.Type26->Hdr.Type);
      Print (L"Length:                                 0x%02X\n",SMBIOSStruct.Type26->Hdr.Length);
      Print (L"Handle:                                 0x%04X\n",SMBIOSStruct.Type26->Hdr.Handle);
      Print (L"Description:                            %a\n",SmbiosLibReadString (&(SMBIOSStruct.Type26->Hdr),SMBIOSStruct.Type26->Description));
      Print (L"LocationAndStatus:                      0x%02X\n",SMBIOSStruct.Type26->LocationAndStatus);
      Print (L"MaximumValue:                           0x%04X\n",SMBIOSStruct.Type26->MaximumValue);
      Print (L"MinimumValue:                           0x%04X\n",SMBIOSStruct.Type26->MinimumValue);
      Print (L"Resolution:                             0x%04X\n",SMBIOSStruct.Type26->Resolution);
      Print (L"Tolerance:                              0x%04X\n",SMBIOSStruct.Type26->Tolerance);
      Print (L"Accuracy:                               0x%04X\n",SMBIOSStruct.Type26->Accuracy);
      Print (L"OEMDefined:                             0x%08X\n",SMBIOSStruct.Type26->OEMDefined);
      Print (L"NominalValue:                           0x%04X\n",SMBIOSStruct.Type26->NominalValue);
    } else if (Record->Type == 27) {
      Address     = (UINTN) Record;
      SMBIOSStruct.Type27 = (SMBIOS_TABLE_TYPE27*) Address;
      Print (L"Address:                                0x%08X\n",Address);
      Print (L"Type:                                   0x%02X\n",SMBIOSStruct.Type27->Hdr.Type);
      Print (L"Length:                                 0x%02X\n",SMBIOSStruct.Type27->Hdr.Length);
      Print (L"Handle:                                 0x%04X\n",SMBIOSStruct.Type27->Hdr.Handle);
      Print (L"TemperatureProbeHandle:                 0x%04X\n",SMBIOSStruct.Type27->TemperatureProbeHandle);
      Print (L"DeviceTypeAndStatus:                    0x%02X\n",SMBIOSStruct.Type27->DeviceTypeAndStatus);
      Print (L"CoolingUnitGroup:                       0x%02X\n",SMBIOSStruct.Type27->CoolingUnitGroup);
      Print (L"OEMDefined:                             0x%08X\n",SMBIOSStruct.Type27->OEMDefined);
      Print (L"NominalSpeed:                           0x%04X\n",SMBIOSStruct.Type27->NominalSpeed);
      Print (L"Description:                            %a\n",SmbiosLibReadString (&(SMBIOSStruct.Type27->Hdr),SMBIOSStruct.Type27->Description));
    } else if (Record->Type == 28) {
      Address     = (UINTN) Record;
      SMBIOSStruct.Type28 = (SMBIOS_TABLE_TYPE28*) Address;
      Print (L"Address:                                0x%08X\n",Address);
      Print (L"Type:                                   0x%02X\n",SMBIOSStruct.Type28->Hdr.Type);
      Print (L"Length:                                 0x%02X\n",SMBIOSStruct.Type28->Hdr.Length);
      Print (L"Handle:                                 0x%04X\n",SMBIOSStruct.Type28->Hdr.Handle);
      Print (L"Description:                            %a\n",SmbiosLibReadString (&(SMBIOSStruct.Type28->Hdr),SMBIOSStruct.Type28->Description));
      Print (L"LocationAndStatus:                      0x%02X\n",SMBIOSStruct.Type28->LocationAndStatus);
      Print (L"MaximumValue:                           0x%04X\n",SMBIOSStruct.Type28->MaximumValue);
      Print (L"MinimumValue:                           0x%04X\n",SMBIOSStruct.Type28->MinimumValue);
      Print (L"Resolution:                             0x%04X\n",SMBIOSStruct.Type28->Resolution);
      Print (L"Tolerance:                              0x%04X\n",SMBIOSStruct.Type28->Tolerance);
      Print (L"Accuracy:                               0x%04X\n",SMBIOSStruct.Type28->Accuracy);
      Print (L"OEMDefined:                             0x%08X\n",SMBIOSStruct.Type28->OEMDefined);
      Print (L"NominalValue:                           0x%04X\n",SMBIOSStruct.Type28->NominalValue);
    } else if (Record->Type == 29) {
      Address     = (UINTN) Record;
      SMBIOSStruct.Type29 = (SMBIOS_TABLE_TYPE29*) Address;
      Print (L"Address:                                0x%08X\n",Address);
      Print (L"Type:                                   0x%02X\n",SMBIOSStruct.Type29->Hdr.Type);
      Print (L"Length:                                 0x%02X\n",SMBIOSStruct.Type29->Hdr.Length);
      Print (L"Handle:                                 0x%04X\n",SMBIOSStruct.Type29->Hdr.Handle);
      Print (L"Description:                            %a\n",SmbiosLibReadString (&(SMBIOSStruct.Type29->Hdr),SMBIOSStruct.Type29->Description));
      Print (L"LocationAndStatus:                      0x%02X\n",SMBIOSStruct.Type29->LocationAndStatus);
      Print (L"MaximumValue:                           0x%04X\n",SMBIOSStruct.Type29->MaximumValue);
      Print (L"MinimumValue:                           0x%04X\n",SMBIOSStruct.Type29->MinimumValue);
      Print (L"Resolution:                             0x%04X\n",SMBIOSStruct.Type29->Resolution);
      Print (L"Tolerance:                              0x%04X\n",SMBIOSStruct.Type29->Tolerance);
      Print (L"Accuracy:                               0x%04X\n",SMBIOSStruct.Type29->Accuracy);
      Print (L"OEMDefined:                             0x%08X\n",SMBIOSStruct.Type29->OEMDefined);
      Print (L"NominalValue:                           0x%04X\n",SMBIOSStruct.Type29->NominalValue);
    } else if (Record->Type == 30) {
      Address     = (UINTN) Record;
      SMBIOSStruct.Type30 = (SMBIOS_TABLE_TYPE30*) Address;
      Print (L"Address:                                0x%08X\n",Address);
      Print (L"Type:                                   0x%02X\n",SMBIOSStruct.Type30->Hdr.Type);
      Print (L"Length:                                 0x%02X\n",SMBIOSStruct.Type30->Hdr.Length);
      Print (L"Handle:                                 0x%04X\n",SMBIOSStruct.Type30->Hdr.Handle);
      Print (L"ManufacturerName:                       %a\n",SmbiosLibReadString (&(SMBIOSStruct.Type30->Hdr),SMBIOSStruct.Type30->ManufacturerName));
      Print (L"Connections:                            0x%02X\n",SMBIOSStruct.Type30->Connections);
    } else if (Record->Type == 31) {
      Address     = (UINTN) Record;
      SMBIOSStruct.Type31 = (SMBIOS_TABLE_TYPE31*) Address;
      Print (L"Address:                                0x%08X\n",Address);
      Print (L"Type:                                   0x%02X\n",SMBIOSStruct.Type31->Hdr.Type);
      Print (L"Length:                                 0x%02X\n",SMBIOSStruct.Type31->Hdr.Length);
      Print (L"Handle:                                 0x%04X\n",SMBIOSStruct.Type31->Hdr.Handle);
      Print (L"Checksum:                               0x%02X\n",SMBIOSStruct.Type31->Checksum);
      Print (L"Reserved1:                              0x%02X\n",SMBIOSStruct.Type31->Reserved1);
      Print (L"Reserved2:                              0x%04X\n",SMBIOSStruct.Type31->Reserved2);
      Print (L"BisEntry16:                             0x%08X\n",SMBIOSStruct.Type31->BisEntry16);
      Print (L"BisEntry32:                             0x%08X\n",SMBIOSStruct.Type31->BisEntry32);
      Print (L"Reserved3:                              0x%016llX\n",SMBIOSStruct.Type31->Reserved3);
      Print (L"Reserved4:                              0x%08X\n",SMBIOSStruct.Type31->Reserved4);
    } else if (Record->Type == 32) {
      Address     = (UINTN) Record;
      SMBIOSStruct.Type32 = (SMBIOS_TABLE_TYPE32*) Address;
      Print (L"Address:                                0x%08X\n",Address);
      Print (L"Type:                                   0x%02X\n",SMBIOSStruct.Type32->Hdr.Type);
      Print (L"Length:                                 0x%02X\n",SMBIOSStruct.Type32->Hdr.Length);
      Print (L"Handle:                                 0x%04X\n",SMBIOSStruct.Type32->Hdr.Handle);
      Print (L"Reserved[0]:                            0x%02X\n",SMBIOSStruct.Type32->Reserved[0]);
      Print (L"Reserved[1]:                            0x%02X\n",SMBIOSStruct.Type32->Reserved[1]);
      Print (L"Reserved[2]:                            0x%02X\n",SMBIOSStruct.Type32->Reserved[2]);
      Print (L"Reserved[3]:                            0x%02X\n",SMBIOSStruct.Type32->Reserved[3]);
      Print (L"Reserved[4]:                            0x%02X\n",SMBIOSStruct.Type32->Reserved[4]);
      Print (L"Reserved[5]:                            0x%02X\n",SMBIOSStruct.Type32->Reserved[5]);
      Print (L"BootStatus:                             0x%02X\n",SMBIOSStruct.Type32->BootStatus);
    } else if (Record->Type == 33) {
      Address     = (UINTN) Record;
      SMBIOSStruct.Type33 = (SMBIOS_TABLE_TYPE33*) Address;
      Print (L"Address:                                0x%08X\n",Address);
      Print (L"Type:                                   0x%02X\n",SMBIOSStruct.Type33->Hdr.Type);
      Print (L"Length:                                 0x%02X\n",SMBIOSStruct.Type33->Hdr.Length);
      Print (L"Handle:                                 0x%04X\n",SMBIOSStruct.Type33->Hdr.Handle);
      Print (L"ErrorType:                              0x%02X\n",SMBIOSStruct.Type33->ErrorType);
      Print (L"ErrorGranularity:                       0x%02X\n",SMBIOSStruct.Type33->ErrorGranularity);
      Print (L"ErrorOperation:                         0x%02X\n",SMBIOSStruct.Type33->ErrorOperation);
      Print (L"VendorSyndrome:                         0x%08X\n",SMBIOSStruct.Type33->VendorSyndrome);
      Print (L"MemoryArrayErrorAddress:                0x%016llX\n",SMBIOSStruct.Type33->MemoryArrayErrorAddress);
      Print (L"DeviceErrorAddress:                     0x%016llX\n",SMBIOSStruct.Type33->DeviceErrorAddress);
      Print (L"ErrorResolution:                        0x%08X\n",SMBIOSStruct.Type33->ErrorResolution);
    } else if (Record->Type == 34) {
      Address     = (UINTN) Record;
      SMBIOSStruct.Type34 = (SMBIOS_TABLE_TYPE34*) Address;
      Print (L"Address:                                0x%08X\n",Address);
      Print (L"Type:                                   0x%02X\n",SMBIOSStruct.Type34->Hdr.Type);
      Print (L"Length:                                 0x%02X\n",SMBIOSStruct.Type34->Hdr.Length);
      Print (L"Handle:                                 0x%04X\n",SMBIOSStruct.Type34->Hdr.Handle);
      Print (L"Description:                            %a\n",SmbiosLibReadString (&(SMBIOSStruct.Type34->Hdr),SMBIOSStruct.Type34->Description));
      Print (L"Type:                                   0x%02X\n",SMBIOSStruct.Type34->Type);
      Print (L"Address:                                0x%08X\n",SMBIOSStruct.Type34->Address);
      Print (L"AddressType:                            0x%02X\n",SMBIOSStruct.Type34->AddressType);
    } else if (Record->Type == 35) {
      Address     = (UINTN) Record;
      SMBIOSStruct.Type35 = (SMBIOS_TABLE_TYPE35*) Address;
      Print (L"Address:                                0x%08X\n",Address);
      Print (L"Type:                                   0x%02X\n",SMBIOSStruct.Type35->Hdr.Type);
      Print (L"Length:                                 0x%02X\n",SMBIOSStruct.Type35->Hdr.Length);
      Print (L"Handle:                                 0x%04X\n",SMBIOSStruct.Type35->Hdr.Handle);
      Print (L"Description:                            %a\n",SmbiosLibReadString (&(SMBIOSStruct.Type35->Hdr),SMBIOSStruct.Type35->Description));
      Print (L"ManagementDeviceHandle:                 0x%04X\n",SMBIOSStruct.Type35->ManagementDeviceHandle);
      Print (L"ComponentHandle:                        0x%04X\n",SMBIOSStruct.Type35->ComponentHandle);
      Print (L"ThresholdHandle:                        0x%04X\n",SMBIOSStruct.Type35->ThresholdHandle);
    } else if (Record->Type == 36) {
      Address     = (UINTN) Record;
      SMBIOSStruct.Type36 = (SMBIOS_TABLE_TYPE36*) Address;
      Print (L"Address:                                0x%08X\n",Address);
      Print (L"Type:                                   0x%02X\n",SMBIOSStruct.Type36->Hdr.Type);
      Print (L"Length:                                 0x%02X\n",SMBIOSStruct.Type36->Hdr.Length);
      Print (L"Handle:                                 0x%04X\n",SMBIOSStruct.Type36->Hdr.Handle);
      Print (L"LowerThresholdNonCritical:              0x%04X\n",SMBIOSStruct.Type36->LowerThresholdNonCritical);
      Print (L"UpperThresholdNonCritical:              0x%04X\n",SMBIOSStruct.Type36->UpperThresholdNonCritical);
      Print (L"LowerThresholdCritical:                 0x%04X\n",SMBIOSStruct.Type36->LowerThresholdCritical);
      Print (L"UpperThresholdCritical:                 0x%04X\n",SMBIOSStruct.Type36->UpperThresholdCritical);
      Print (L"LowerThresholdNonRecoverable:           0x%04X\n",SMBIOSStruct.Type36->LowerThresholdNonRecoverable);
      Print (L"UpperThresholdNonRecoverable:           0x%04X\n",SMBIOSStruct.Type36->UpperThresholdNonRecoverable);
    } else if (Record->Type == 37) {
      Address     = (UINTN) Record;
      SMBIOSStruct.Type37 = (SMBIOS_TABLE_TYPE37*) Address;
      Print (L"Address:                                0x%08X\n",Address);
      Print (L"Type:                                   0x%02X\n",SMBIOSStruct.Type37->Hdr.Type);
      Print (L"Length:                                 0x%02X\n",SMBIOSStruct.Type37->Hdr.Length);
      Print (L"Handle:                                 0x%04X\n",SMBIOSStruct.Type37->Hdr.Handle);
      Print (L"ChannelType:                            0x%02X\n",SMBIOSStruct.Type37->ChannelType);
      Print (L"MaximumChannelLoad:                     0x%02X\n",SMBIOSStruct.Type37->MaximumChannelLoad);
      Print (L"MemoryDeviceCount:                      0x%02X\n",SMBIOSStruct.Type37->MemoryDeviceCount);
      Print (L"MemoryDevice[0].DeviceLoad:             0x%02X\n",SMBIOSStruct.Type37->MemoryDevice[0].DeviceLoad);
      Print (L"MemoryDevice[0].DeviceHandle:           0x%04X\n",SMBIOSStruct.Type37->MemoryDevice[0].DeviceHandle);
    } else if (Record->Type == 38) {
      Address     = (UINTN) Record;
      SMBIOSStruct.Type38 = (SMBIOS_TABLE_TYPE38*) Address;
      Print (L"Address:                                0x%08X\n",Address);
      Print (L"Type:                                   0x%02X\n",SMBIOSStruct.Type38->Hdr.Type);
      Print (L"Length:                                 0x%02X\n",SMBIOSStruct.Type38->Hdr.Length);
      Print (L"Handle:                                 0x%04X\n",SMBIOSStruct.Type38->Hdr.Handle);
      Print (L"InterfaceType:                          0x%02X\n",SMBIOSStruct.Type38->InterfaceType);
      Print (L"IPMISpecificationRevision:              0x%02X\n",SMBIOSStruct.Type38->IPMISpecificationRevision);
      Print (L"I2CSlaveAddress:                        0x%02X\n",SMBIOSStruct.Type38->I2CSlaveAddress);
      Print (L"NVStorageDeviceAddress:                 0x%02X\n",SMBIOSStruct.Type38->NVStorageDeviceAddress);
      Print (L"BaseAddress:                            0x%016llX\n",SMBIOSStruct.Type38->BaseAddress);
      Print (L"BaseAddressModifier_InterruptInfo:      0x%02X\n",SMBIOSStruct.Type38->BaseAddressModifier_InterruptInfo);
      Print (L"InterruptNumber:                        0x%02X\n",SMBIOSStruct.Type38->InterruptNumber);
    } else if (Record->Type == 39) {
      Address     = (UINTN) Record;
      SMBIOSStruct.Type39 = (SMBIOS_TABLE_TYPE39*) Address;
      Print (L"Address:                                0x%08X\n",Address);
      Print (L"Type:                                   0x%02X\n",SMBIOSStruct.Type39->Hdr.Type);
      Print (L"Length:                                 0x%02X\n",SMBIOSStruct.Type39->Hdr.Length);
      Print (L"Handle:                                 0x%04X\n",SMBIOSStruct.Type39->Hdr.Handle);
      Print (L"Location:                               %a\n",SmbiosLibReadString (&(SMBIOSStruct.Type39->Hdr),SMBIOSStruct.Type39->Location));
      Print (L"DeviceName:                             %a\n",SmbiosLibReadString (&(SMBIOSStruct.Type39->Hdr),SMBIOSStruct.Type39->DeviceName));
      Print (L"Manufacturer:                           %a\n",SmbiosLibReadString (&(SMBIOSStruct.Type39->Hdr),SMBIOSStruct.Type39->Manufacturer));
      Print (L"SerialNumber:                           %a\n",SmbiosLibReadString (&(SMBIOSStruct.Type39->Hdr),SMBIOSStruct.Type39->SerialNumber));
      Print (L"AssetTagNumber:                         %a\n",SmbiosLibReadString (&(SMBIOSStruct.Type39->Hdr),SMBIOSStruct.Type39->AssetTagNumber));
      Print (L"ModelPartNumber:                        %a\n",SmbiosLibReadString (&(SMBIOSStruct.Type39->Hdr),SMBIOSStruct.Type39->ModelPartNumber));
      Print (L"RevisionLevel:                          %a\n",SmbiosLibReadString (&(SMBIOSStruct.Type39->Hdr),SMBIOSStruct.Type39->RevisionLevel));
      Print (L"MaxPowerCapacity:                       0x%04X\n",SMBIOSStruct.Type39->MaxPowerCapacity);
      Print (L"PowerSupplyCharacteristics:             0x%04X\n",SMBIOSStruct.Type39->PowerSupplyCharacteristics);
      Print (L"InputVoltageProbeHandle:                0x%04X\n",SMBIOSStruct.Type39->InputVoltageProbeHandle);
      Print (L"CoolingDeviceHandle:                    0x%04X\n",SMBIOSStruct.Type39->CoolingDeviceHandle);
      Print (L"InputCurrentProbeHandle:                0x%04X\n",SMBIOSStruct.Type39->InputCurrentProbeHandle);
    } else if (Record->Type == 40) {
      Address     = (UINTN) Record;
      SMBIOSStruct.Type40 = (SMBIOS_TABLE_TYPE40*) Address;
      Print (L"Address:                                0x%08X\n",Address);
      Print (L"Type:                                   0x%02X\n",SMBIOSStruct.Type40->Hdr.Type);
      Print (L"Length:                                 0x%02X\n",SMBIOSStruct.Type40->Hdr.Length);
      Print (L"Handle:                                 0x%04X\n",SMBIOSStruct.Type40->Hdr.Handle);
      Print (L"NumberOfAdditionalInformationEntries:   0x%02X\n",SMBIOSStruct.Type40->NumberOfAdditionalInformationEntries);
      Print (L"AdditionalInfoEntries[0].EntryLength:   0x%02X\n",SMBIOSStruct.Type40->AdditionalInfoEntries[0].EntryLength);
      Print (L"AdditionalInfoEntries[0].ReferencedHandle:   0x%04X\n",SMBIOSStruct.Type40->AdditionalInfoEntries[0].ReferencedHandle);
      Print (L"AdditionalInfoEntries[0].ReferencedOffset:   0x%02X\n",SMBIOSStruct.Type40->AdditionalInfoEntries[0].ReferencedOffset);
      Print (L"AdditionalInfoEntries[0].EntryString:   %a\n",SmbiosLibReadString (&(SMBIOSStruct.Type40->Hdr),SMBIOSStruct.Type40->AdditionalInfoEntries[0].EntryString));
      Print (L"AdditionalInfoEntries[0].Value[0]:      0x%02X\n",SMBIOSStruct.Type40->AdditionalInfoEntries[0].Value[0]);
    } else if (Record->Type == 41) {
      Address     = (UINTN) Record;
      SMBIOSStruct.Type41 = (SMBIOS_TABLE_TYPE41*) Address;
      Print (L"Address:                                0x%08X\n",Address);
      Print (L"Type:                                   0x%02X\n",SMBIOSStruct.Type41->Hdr.Type);
      Print (L"Length:                                 0x%02X\n",SMBIOSStruct.Type41->Hdr.Length);
      Print (L"Handle:                                 0x%04X\n",SMBIOSStruct.Type41->Hdr.Handle);
      Print (L"ReferenceDesignation:                   %a\n",SmbiosLibReadString (&(SMBIOSStruct.Type41->Hdr),SMBIOSStruct.Type41->ReferenceDesignation));
      Print (L"DeviceType:                             0x%02X\n",SMBIOSStruct.Type41->DeviceType);
      Print (L"DeviceTypeInstance:                     0x%02X\n",SMBIOSStruct.Type41->DeviceTypeInstance);
      Print (L"SegmentGroupNum:                        0x%04X\n",SMBIOSStruct.Type41->SegmentGroupNum);
      Print (L"BusNum:                                 0x%02X\n",SMBIOSStruct.Type41->BusNum);
      Print (L"DevFuncNum:                             0x%02X\n",SMBIOSStruct.Type41->DevFuncNum);
    } else if (Record->Type == 42) {
      Address     = (UINTN) Record;
      SMBIOSStruct.Type42 = (SMBIOS_TABLE_TYPE42*) Address;
      Print (L"Address:                                0x%08X\n",Address);
      Print (L"Type:                                   0x%02X\n",SMBIOSStruct.Type42->Hdr.Type);
      Print (L"Length:                                 0x%02X\n",SMBIOSStruct.Type42->Hdr.Length);
      Print (L"Handle:                                 0x%04X\n",SMBIOSStruct.Type42->Hdr.Handle);
      Print (L"InterfaceType:                          0x%02X\n",SMBIOSStruct.Type42->InterfaceType);
      Print (L"InterfaceTypeSpecificDataLength:        0x%02X\n",SMBIOSStruct.Type42->InterfaceTypeSpecificDataLength);
      Print (L"InterfaceTypeSpecificData[0]:           0x%02X\n",SMBIOSStruct.Type42->InterfaceTypeSpecificData[0]);
      Print (L"InterfaceTypeSpecificData[1]:           0x%02X\n",SMBIOSStruct.Type42->InterfaceTypeSpecificData[1]);
      Print (L"InterfaceTypeSpecificData[2]:           0x%02X\n",SMBIOSStruct.Type42->InterfaceTypeSpecificData[2]);
      Print (L"InterfaceTypeSpecificData[3]:           0x%02X\n",SMBIOSStruct.Type42->InterfaceTypeSpecificData[3]);
    } else if (Record->Type == 43) {
      Address     = (UINTN) Record;
      SMBIOSStruct.Type43 = (SMBIOS_TABLE_TYPE43*) Address;
      Print (L"Address:                                0x%08X\n",Address);
      Print (L"Type:                                   0x%02X\n",SMBIOSStruct.Type43->Hdr.Type);
      Print (L"Length:                                 0x%02X\n",SMBIOSStruct.Type43->Hdr.Length);
      Print (L"Handle:                                 0x%04X\n",SMBIOSStruct.Type43->Hdr.Handle);
      Print (L"VendorID[0]:                            0x%02X\n",SMBIOSStruct.Type43->VendorID[0]);
      Print (L"VendorID[1]:                            0x%02X\n",SMBIOSStruct.Type43->VendorID[1]);
      Print (L"VendorID[2]:                            0x%02X\n",SMBIOSStruct.Type43->VendorID[2]);
      Print (L"VendorID[3]:                            0x%02X\n",SMBIOSStruct.Type43->VendorID[3]);
      Print (L"MajorSpecVersion:                       0x%02X\n",SMBIOSStruct.Type43->MajorSpecVersion);
      Print (L"MinorSpecVersion:                       0x%02X\n",SMBIOSStruct.Type43->MinorSpecVersion);
      Print (L"FirmwareVersion1:                       0x%08X\n",SMBIOSStruct.Type43->FirmwareVersion1);
      Print (L"FirmwareVersion2:                       0x%08X\n",SMBIOSStruct.Type43->FirmwareVersion2);
      Print (L"Description:                            %a\n",SmbiosLibReadString (&(SMBIOSStruct.Type43->Hdr),SMBIOSStruct.Type43->Description));
      Print (L"Characteristics:                        0x%016llX\n",SMBIOSStruct.Type43->Characteristics);
      Print (L"OemDefined:                             0x%08X\n",SMBIOSStruct.Type43->OemDefined);
    } else if (Record->Type == 44) {
      Address     = (UINTN) Record;
      SMBIOSStruct.Type44 = (SMBIOS_TABLE_TYPE44*) Address;
      Print (L"Address:                                0x%08X\n",Address);
      Print (L"Type:                                   0x%02X\n",SMBIOSStruct.Type44->Hdr.Type);
      Print (L"Length:                                 0x%02X\n",SMBIOSStruct.Type44->Hdr.Length);
      Print (L"Handle:                                 0x%04X\n",SMBIOSStruct.Type44->Hdr.Handle);
      Print (L"RefHandle:                              0x%04X\n",SMBIOSStruct.Type44->RefHandle);
      Print (L"ProcessorSpecificBlock.Length:          0x%02X\n",SMBIOSStruct.Type44->ProcessorSpecificBlock.Length);
      Print (L"ProcessorSpecificBlock.ProcessorArchType:   0x%02X\n",SMBIOSStruct.Type44->ProcessorSpecificBlock.ProcessorArchType);    
    } else if (Record->Type == 45) {
      Address     = (UINTN) Record;
      SMBIOSStruct.Type45 = (SMBIOS_TABLE_TYPE45*) Address;
      Print (L"Address:                                0x%08X\n",Address);
      Print (L"Type:                                   0x%02X\n",SMBIOSStruct.Type45->Hdr.Type);
      Print (L"Length:                                 0x%02X\n",SMBIOSStruct.Type45->Hdr.Length);
      Print (L"Handle:                                 0x%04X\n",SMBIOSStruct.Type45->Hdr.Handle);
      Print (L"FirmwareComponentName:                  %a\n",SmbiosLibReadString (&(SMBIOSStruct.Type45->Hdr),SMBIOSStruct.Type45->FirmwareComponentName));
      Print (L"FirmwareVersion:                        %a\n",SmbiosLibReadString (&(SMBIOSStruct.Type45->Hdr),SMBIOSStruct.Type45->FirmwareVersion));
      Print (L"FirmwareVersionFormat:                  0x%02X\n",SMBIOSStruct.Type45->FirmwareVersionFormat);
      Print (L"FirmwareId:                             %a\n",SmbiosLibReadString (&(SMBIOSStruct.Type45->Hdr),SMBIOSStruct.Type45->FirmwareId));
      Print (L"FirmwareIdFormat:                       0x%02X\n",SMBIOSStruct.Type45->FirmwareIdFormat);
      Print (L"ReleaseDate:                            %a\n",SmbiosLibReadString (&(SMBIOSStruct.Type45->Hdr),SMBIOSStruct.Type45->ReleaseDate));
      Print (L"Manufacturer:                           %a\n",SmbiosLibReadString (&(SMBIOSStruct.Type45->Hdr),SMBIOSStruct.Type45->Manufacturer));
      Print (L"LowestSupportedVersion:                 %a\n",SmbiosLibReadString (&(SMBIOSStruct.Type45->Hdr),SMBIOSStruct.Type45->LowestSupportedVersion));
      Print (L"ImageSize:                              0x%016llX\n",SMBIOSStruct.Type45->ImageSize);
      Print (L"Characteristics:                        0x%04X\n",SMBIOSStruct.Type45->Characteristics);
      Print (L"State:                                  0x%02X\n",SMBIOSStruct.Type45->State);
      Print (L"AssociatedComponentCount:               0x%02X\n",SMBIOSStruct.Type45->AssociatedComponentCount);
    } else if (Record->Type == 46) {
      Address     = (UINTN) Record;
      SMBIOSStruct.Type46 = (SMBIOS_TABLE_TYPE46*) Address;
      Print (L"Address:                                0x%08X\n",Address);
      Print (L"Type:                                   0x%02X\n",SMBIOSStruct.Type46->Hdr.Type);
      Print (L"Length:                                 0x%02X\n",SMBIOSStruct.Type46->Hdr.Length);
      Print (L"Handle:                                 0x%04X\n",SMBIOSStruct.Type46->Hdr.Handle);
      Print (L"StringPropertyId:                       0x%04X\n",SMBIOSStruct.Type46->StringPropertyId);
      Print (L"StringPropertyValue:                    %a\n",SmbiosLibReadString (&(SMBIOSStruct.Type46->Hdr),SMBIOSStruct.Type46->StringPropertyValue));
      Print (L"ParentHandle:                           0x%04X\n",SMBIOSStruct.Type46->ParentHandle);
    } else if (Record->Type == 126) {
      Address     = (UINTN) Record;
      SMBIOSStruct.Type126 = (SMBIOS_TABLE_TYPE126*) Address;
      Print (L"Address:                                0x%08X\n",Address);
      Print (L"Type:                                   0x%02X\n",SMBIOSStruct.Type126->Hdr.Type);
      Print (L"Length:                                 0x%02X\n",SMBIOSStruct.Type126->Hdr.Length);
      Print (L"Handle:                                 0x%04X\n",SMBIOSStruct.Type126->Hdr.Handle);
    } else if (Record->Type == 127) {
      Address     = (UINTN) Record;
      SMBIOSStruct.Type127 = (SMBIOS_TABLE_TYPE127*) Address;
      Print (L"Address:                                0x%08X\n",Address);
      Print (L"Type:                                   0x%02X\n",SMBIOSStruct.Type127->Hdr.Type);
      Print (L"Length:                                 0x%02X\n",SMBIOSStruct.Type127->Hdr.Length);
      Print (L"Handle:                                 0x%04X\n",SMBIOSStruct.Type127->Hdr.Handle);
    }

    Print (L"======================================================================\n\n");
}
