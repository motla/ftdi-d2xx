# ftdi-d2xx

## Table of contents

### Classes

- [FTDI\_Device](./FTDI_Device.md)
- [FTDI\_DeviceInfo](./FTDI_DeviceInfo.md)

### Variables

- [FT\_BITS\_7](./Home.md#ft_bits_7)
- [FT\_BITS\_8](./Home.md#ft_bits_8)
- [FT\_FLOW\_DTR\_DSR](./Home.md#ft_flow_dtr_dsr)
- [FT\_FLOW\_NONE](./Home.md#ft_flow_none)
- [FT\_FLOW\_RTS\_CTS](./Home.md#ft_flow_rts_cts)
- [FT\_FLOW\_XON\_XOFF](./Home.md#ft_flow_xon_xoff)
- [FT\_PARITY\_EVEN](./Home.md#ft_parity_even)
- [FT\_PARITY\_MARK](./Home.md#ft_parity_mark)
- [FT\_PARITY\_NONE](./Home.md#ft_parity_none)
- [FT\_PARITY\_ODD](./Home.md#ft_parity_odd)
- [FT\_PARITY\_SPACE](./Home.md#ft_parity_space)
- [FT\_PURGE\_RX](./Home.md#ft_purge_rx)
- [FT\_PURGE\_TX](./Home.md#ft_purge_tx)
- [FT\_STOP\_BITS\_1](./Home.md#ft_stop_bits_1)
- [FT\_STOP\_BITS\_2](./Home.md#ft_stop_bits_2)
- [library\_version](./Home.md#library_version)

### Functions

- [getDeviceInfoList](./Home.md#getdeviceinfolist)
- [openDevice](./Home.md#opendevice)
- [setVIDPID](./Home.md#setvidpid)

## Variables

### FT\_BITS\_7

• `Const` **FT\_BITS\_7**: `number`

#### Defined in

[main.d.ts:190](https://github.com/motla/ftdi-d2xx/blob/38e724e/main.d.ts#L190)

___

### FT\_BITS\_8

• `Const` **FT\_BITS\_8**: `number`

#### Defined in

[main.d.ts:189](https://github.com/motla/ftdi-d2xx/blob/38e724e/main.d.ts#L189)

___

### FT\_FLOW\_DTR\_DSR

• `Const` **FT\_FLOW\_DTR\_DSR**: `number`

#### Defined in

[main.d.ts:200](https://github.com/motla/ftdi-d2xx/blob/38e724e/main.d.ts#L200)

___

### FT\_FLOW\_NONE

• `Const` **FT\_FLOW\_NONE**: `number`

#### Defined in

[main.d.ts:198](https://github.com/motla/ftdi-d2xx/blob/38e724e/main.d.ts#L198)

___

### FT\_FLOW\_RTS\_CTS

• `Const` **FT\_FLOW\_RTS\_CTS**: `number`

#### Defined in

[main.d.ts:199](https://github.com/motla/ftdi-d2xx/blob/38e724e/main.d.ts#L199)

___

### FT\_FLOW\_XON\_XOFF

• `Const` **FT\_FLOW\_XON\_XOFF**: `number`

#### Defined in

[main.d.ts:201](https://github.com/motla/ftdi-d2xx/blob/38e724e/main.d.ts#L201)

___

### FT\_PARITY\_EVEN

• `Const` **FT\_PARITY\_EVEN**: `number`

#### Defined in

[main.d.ts:195](https://github.com/motla/ftdi-d2xx/blob/38e724e/main.d.ts#L195)

___

### FT\_PARITY\_MARK

• `Const` **FT\_PARITY\_MARK**: `number`

#### Defined in

[main.d.ts:196](https://github.com/motla/ftdi-d2xx/blob/38e724e/main.d.ts#L196)

___

### FT\_PARITY\_NONE

• `Const` **FT\_PARITY\_NONE**: `number`

#### Defined in

[main.d.ts:193](https://github.com/motla/ftdi-d2xx/blob/38e724e/main.d.ts#L193)

___

### FT\_PARITY\_ODD

• `Const` **FT\_PARITY\_ODD**: `number`

#### Defined in

[main.d.ts:194](https://github.com/motla/ftdi-d2xx/blob/38e724e/main.d.ts#L194)

___

### FT\_PARITY\_SPACE

• `Const` **FT\_PARITY\_SPACE**: `number`

#### Defined in

[main.d.ts:197](https://github.com/motla/ftdi-d2xx/blob/38e724e/main.d.ts#L197)

___

### FT\_PURGE\_RX

• `Const` **FT\_PURGE\_RX**: `number`

#### Defined in

[main.d.ts:202](https://github.com/motla/ftdi-d2xx/blob/38e724e/main.d.ts#L202)

___

### FT\_PURGE\_TX

• `Const` **FT\_PURGE\_TX**: `number`

#### Defined in

[main.d.ts:203](https://github.com/motla/ftdi-d2xx/blob/38e724e/main.d.ts#L203)

___

### FT\_STOP\_BITS\_1

• `Const` **FT\_STOP\_BITS\_1**: `number`

#### Defined in

[main.d.ts:191](https://github.com/motla/ftdi-d2xx/blob/38e724e/main.d.ts#L191)

___

### FT\_STOP\_BITS\_2

• `Const` **FT\_STOP\_BITS\_2**: `number`

#### Defined in

[main.d.ts:192](https://github.com/motla/ftdi-d2xx/blob/38e724e/main.d.ts#L192)

___

### library\_version

• `Const` **library\_version**: `string`

Current D2XX library version number

#### Defined in

[main.d.ts:186](https://github.com/motla/ftdi-d2xx/blob/38e724e/main.d.ts#L186)

## Functions

### getDeviceInfoList

▸ **getDeviceInfoList**(): `Promise`<[`FTDI_DeviceInfo`](./FTDI_DeviceInfo.md)[]\>

Get the list of FTDI devices connected to the system

#### Returns

`Promise`<[`FTDI_DeviceInfo`](./FTDI_DeviceInfo.md)[]\>

#### Defined in

[main.d.ts:167](https://github.com/motla/ftdi-d2xx/blob/38e724e/main.d.ts#L167)

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

#### Defined in

[main.d.ts:173](https://github.com/motla/ftdi-d2xx/blob/38e724e/main.d.ts#L173)

___

### setVIDPID

▸ **setVIDPID**(`vid`, `pid`): `void`

This allows the driver to load only for the specified VID and PID combination.

IMPORTANT: On Windows platforms, this function forces a reload of the driver.
Please note that this function will not work correctly on 64-bit Windows when called from a 32-bit application.

#### Parameters

| Name | Type | Description |
| :------ | :------ | :------ |
| `vid` | `number` | Device Vendor ID (VID) |
| `pid` | `number` | Device Product ID (PID) |

#### Returns

`void`

#### Defined in

[main.d.ts:183](https://github.com/motla/ftdi-d2xx/blob/38e724e/main.d.ts#L183)
