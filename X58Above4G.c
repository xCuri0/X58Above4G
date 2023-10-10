/*
Copyright (c) 2023 xCuri0 <zkqri0@gmail.com>
SPDX-License-Identifier: MIT
*/

//Using reference from https://www.intel.com/content/dam/doc/datasheet/x58-express-chipset-datasheet.pdf

//Use with following in DSDT, Linux will automatically move and resize GPU to there.
/*
				QWordMemory (ResourceProducer, PosDecode, MinFixed, MaxFixed, Cacheable, ReadWrite,
					0x0000000000000000, // Granularity
					0x0000004000000000, // Range Minimum: 256GB
					0x0000008000000000, // Range Maximum: 512GB
					0x0000000000000000, // Translation Offset
					0x0000003fffffffff, // Length (Range Maximum - Range Minimum - 1)
					,, , AddressRangeMemory, TypeStatic)
*/

// Build: build --platform=X58Above4G/X58Above4G.dsc
// Load this .efi application prior to OS loading such as by placing it in rEFInd drivers folder. Use DUET to get UEFI on X58

#include <Uefi.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Protocol/PciRootBridgeIo.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/DebugLib.h>

#ifdef _MSC_VER
#pragma warning(disable : 28251)
#include <intrin.h>
#pragma warning(default : 28251)
#endif

UINT16 MMIOHBASE = 0x0;
// 256GB / 0x4000000000
UINT16 MMIOHBASEU = 0x4;

UINT16 MMIOHLIMIT = 0x0;
// 512GB / 0x8000000000
UINT16 MMIOHLIMITU = 0x8;

// Device 20 as described by Intel
UINT64 X58SYSIO = EFI_PCI_ADDRESS(0, 0x14, 0, 0);

static EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL *pciRootBridgeIo;

UINT64 pciAddrOffset(UINTN pciAddress, INTN offset)
{
	UINTN reg = (pciAddress & 0xffffffff00000000) >> 32;
	UINTN bus = (pciAddress & 0xff000000) >> 24;
	UINTN dev = (pciAddress & 0xff0000) >> 16;
	UINTN func = (pciAddress & 0xff00) >> 8;

	return EFI_PCI_ADDRESS(bus, dev, func, ((INT64)reg + offset));
}

EFI_STATUS pciWriteConfigWord(UINTN pciAddress, INTN pos, UINT16 *buf)
{
	return pciRootBridgeIo->Pci.Write(pciRootBridgeIo, EfiPciWidthUint16, pciAddrOffset(pciAddress, pos), 1, buf);
}

EFI_STATUS EFIAPI uefiMain(
		IN EFI_HANDLE imageHandle,
		IN EFI_SYSTEM_TABLE *systemTable)
{
	EFI_STATUS status;
	UINTN handleCount;
	EFI_HANDLE *handleBuffer;
	EFI_ACPI_ADDRESS_SPACE_DESCRIPTOR  *descriptors;

	status = gBS->LocateHandleBuffer(
			ByProtocol,
			&gEfiPciRootBridgeIoProtocolGuid,
			NULL,
			&handleCount,
			&handleBuffer);
	ASSERT_EFI_ERROR(status);

	status = gBS->HandleProtocol(handleBuffer[0], &gEfiPciRootBridgeIoProtocolGuid, (void **)&pciRootBridgeIo);
	ASSERT_EFI_ERROR(status);
	status = pciRootBridgeIo->Configuration(pciRootBridgeIo, (VOID **)&descriptors);
	ASSERT_EFI_ERROR(status);

	// Write LMMIOH.BASE
	pciWriteConfigWord(X58SYSIO, 0x110, &MMIOHBASE);
	pciWriteConfigWord(X58SYSIO, 0x114, &MMIOHBASEU);
	// Write LMMIOH.LIMIT
	pciWriteConfigWord(X58SYSIO, 0x112, &MMIOHLIMIT);
	pciWriteConfigWord(X58SYSIO, 0x118, &MMIOHLIMITU);

	// Write GMMIOH.BASE
	pciWriteConfigWord(X58SYSIO, 0x128, &MMIOHBASE);
	pciWriteConfigWord(X58SYSIO, 0x12C, &MMIOHBASEU);
	// Write GMMIOH.LIMIT
	pciWriteConfigWord(X58SYSIO, 0x12A, &MMIOHLIMIT);
	pciWriteConfigWord(X58SYSIO, 0x130, &MMIOHLIMITU);

	FreePool(handleBuffer);

	return EFI_SUCCESS;
}