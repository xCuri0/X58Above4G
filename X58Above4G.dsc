[DEFINES]
	DSC_SPECIFICATION = 1.28
	PLATFORM_NAME = X58Above4G
	PLATFORM_GUID = 55e06837-6ae6-4f1a-96c6-aafdaec38aa7
	PLATFORM_VERSION = 1.00
	OUTPUT_DIRECTORY = Build/X58Above4G
	SUPPORTED_ARCHITECTURES = X64
	BUILD_TARGETS = DEBUG|RELEASE|NOOPT
	SKUID_IDENTIFIER = DEFAULT

[Components]
	X58Above4G\X58Above4G.inf

!include MdePkg/MdeLibs.dsc.inc
[LibraryClasses]
	UefiLib|MdePkg/Library/UefiLib/UefiLib.inf
	UefiDriverEntryPoint|MdePkg/Library/UefiDriverEntryPoint/UefiDriverEntryPoint.inf
	UefiApplicationEntryPoint|MdePkg/Library/UefiApplicationEntryPoint/UefiApplicationEntryPoint.inf
	UefiBootServicesTableLib|MdePkg/Library/UefiBootServicesTableLib/UefiBootServicesTableLib.inf
	UefiRuntimeServicesTableLib|MdePkg/Library/UefiRuntimeServicesTableLib/UefiRuntimeServicesTableLib.inf
	PrintLib|MdePkg/Library/BasePrintLib/BasePrintLib.inf
	DebugLib|MdePkg/Library/BaseDebugLibNull/BaseDebugLibNull.inf
	BaseLib|MdePkg/Library/BaseLib/BaseLib.inf
	PcdLib|MdePkg/Library/BasePcdLibNull/BasePcdLibNull.inf
	BaseMemoryLib|MdePkg/Library/BaseMemoryLib/BaseMemoryLib.inf
	ShellLib|ShellPkg/Library/UefiShellLib/UefiShellLib.inf
	MemoryAllocationLib|MdePkg/Library/UefiMemoryAllocationLib/UefiMemoryAllocationLib.inf
	DevicePathLib|MdePkg/Library/UefiDevicePathLib/UefiDevicePathLib.inf
	FileHandleLib|MdePkg/Library/UefiFileHandleLib/UefiFileHandleLib.inf
	HiiLib|MdeModulePkg/Library/UefiHiiLib/UefiHiiLib.inf
	SortLib|MdeModulePkg/Library/BaseSortLib/BaseSortLib.inf
	UefiHiiServicesLib|MdeModulePkg/Library/UefiHiiServicesLib/UefiHiiServicesLib.inf
	DxeServicesTableLib|MdePkg/Library/DxeServicesTableLib/DxeServicesTableLib.inf