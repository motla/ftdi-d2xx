## v1.1.0
- setVIDPID() has been modified to be asynchronous, because of the need for FT_Reload call on Windows
- bugfix: rare potential crash if malloc fails on the getDeviceInfoList function

## v1.0.0
- First release
- Contains the ftd2xx library from https://ftdichip.com/drivers/d2xx-drivers/
  - Windows (Desktop): 2.12.36.4 released on 2021-07-15 for X86 (32-Bit), X64 (64-Bit), and ARM processors
  - Linux: 1.4.24 released on 2020-05-18 for X64 (64-Bit) processors
  - macOS: 1.4.24 released on 2021-05-18 for X64 (64-Bit), and ARM processors