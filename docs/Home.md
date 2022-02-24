# ftdi-d2xx

## Table of contents

### Classes

- [FTDI\_Device](./FTDI_Device.md)
- [FTDI\_DeviceInfo](./FTDI_DeviceInfo.md)

### Variables

- [library\_version](./Home.md#library_version)
- FT\_BITS\_7
- FT\_BITS\_8
- FT\_FLOW\_DTR\_DSR
- FT\_FLOW\_NONE
- FT\_FLOW\_RTS\_CTS
- FT\_FLOW\_XON\_XOFF
- FT\_PARITY\_EVEN
- FT\_PARITY\_MARK
- FT\_PARITY\_NONE
- FT\_PARITY\_ODD
- FT\_PARITY\_SPACE
- FT\_PURGE\_RX
- FT\_PURGE\_TX
- FT\_STOP\_BITS\_1
- FT\_STOP\_BITS\_2

### Functions

- [getDeviceInfoList](./Home.md#getdeviceinfolist)
- [openDevice](./Home.md#opendevice)
- [setVIDPID](./Home.md#setvidpid)

## Variables

### library\_version

• `Const` **library\_version**: `string`

Current D2XX library version number

**`readonly`**

## Functions

### getDeviceInfoList

▸ **getDeviceInfoList**(): `Promise`<[`FTDI_DeviceInfo`](./FTDI_DeviceInfo.md)[]\>

Get the list of FTDI devices connected to the system

#### Returns

`Promise`<[`FTDI_DeviceInfo`](./FTDI_DeviceInfo.md)[]\>

___

### openDevice

▸ **openDevice**(`serial_number`): `Promise`<[`FTDI_Device`](./FTDI_Device.md)\>

Try to open a device from its serial number

#### Parameters

| Name | Type | Description |
| :------ | :------ | :------ |
| `serial_number` | `string` | Device serial number |

#### Returns

`Promise`<[`FTDI_Device`](./FTDI_Device.md)\>

Device object

___

### setVIDPID

▸ **setVIDPID**(`vid`, `pid`): `Promise`<`void`\>

This allows the driver to load only for the specified VID and PID combination.

IMPORTANT: On Windows platforms, this function forces a reload of the driver.
Please note that this function will not work correctly on 64-bit Windows when called from a 32-bit application.

#### Parameters

| Name | Type | Description |
| :------ | :------ | :------ |
| `vid` | `number` | Device Vendor ID (VID) |
| `pid` | `number` | Device Product ID (PID) |

#### Returns

`Promise`<`void`\>
