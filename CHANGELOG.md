## v1.3.1
- Fix [Issue 7](https://github.com/motla/ftdi-d2xx/issues/7): making `Device.read()` work with Electron v20.3.9+ (replacing an externally managed ArrayBuffer by a Node-API managed ArrayBuffer at the cost of using `memcpy()` to fill it)

## v1.3.0
- `device.serial_number` property is now **deprecated** as the device can be open with Description or USB location, in which case the serial number is not retrieved. Use the new property `device.info.serial_number` instead, which is a getter asking the driver for the device serial number.

## v1.2.0
- User can now open a device from its Description or USB location, in addition to its Serial Number.
- Support for `Device.setBitMode` thanks to @ArcherGu
- Support for `Device.setUSBParameters` and `Device.setLatencyTimer`
- Developer instructions in the README.md

## v1.1.2
- Print the correct arch in error message when arch is not compiled (main.js)
- Precisions in the README.md file concerning Electron IPC

## v1.1.1
- just adding the "electron" keyword for NPM search algorithm

## v1.1.0
- setVIDPID() has been modified to be asynchronous, because of the need for FT_Reload call on Windows
- bugfix: rare potential crash if malloc fails on the getDeviceInfoList function

## v1.0.0
- First release
- Contains the ftd2xx library from https://ftdichip.com/drivers/d2xx-drivers/
  - Windows (Desktop): 2.12.36.4 released on 2021-07-15 for X86 (32-Bit), X64 (64-Bit), and ARM processors
  - Linux: 1.4.24 released on 2020-05-18 for X64 (64-Bit) processors
  - macOS: 1.4.24 released on 2021-05-18 for X64 (64-Bit), and ARM processors