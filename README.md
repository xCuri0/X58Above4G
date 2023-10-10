## X58 Above 4G Decoding / Resizable BAR
Load this .efi before OS loads using rEFInd drivers folder or something else.

Credit to whiskytango9 in Miyconst Discord for the idea and figuring out the registers and Max_UA in the same server for testing it with an RX 5600.

This also gets working Resizable BAR despite X58 only supporting PCIe Gen2. Only works on Linux because Windows keeps the existing PCI allocation.

Add the following to DSDT ```PCI0.CRS```, you can follow [Arch Wiki guide](https://wiki.archlinux.org/title/DSDT) on how to do a DSDT override. If there's any errors see [Common DSDT errors and fixes](https://github.com/xCuri0/ReBarUEFI/wiki/DSDT-Patching#common-dsdt-errors-and-fixes)

```
QWordMemory (ResourceProducer, PosDecode, MinFixed, MaxFixed, Cacheable, ReadWrite,
    0x0000000000000000, // Granularity
    0x0000004000000000, // Range Minimum: 256GB
    0x0000008000000000, // Range Maximum: 512GB
    0x0000000000000000, // Translation Offset
    0x0000004000000000, // Length
    ,, , AddressRangeMemory, TypeStatic)
```

If necessary you can modify the EFI program and DSDT for more BAR space than 256GB default.

If you can figure out how to replace DSDT, resize and reallocate GPU in the new 64-bit MMIOH region before boot this will work on Windows.

### Build
Clone into EDK2 tree and run after running edksetup.
```
build --platform=X58Above4G/X58Above4G.dsc
```