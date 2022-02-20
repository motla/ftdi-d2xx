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
- [getVIDPID](./Home.md#getvidpid)
- [openDevice](./Home.md#opendevice)
- [setVIDPID](./Home.md#setvidpid)

## Variables

### FT\_BITS\_7

• **FT\_BITS\_7**: `number`

#### Defined in

[main.d.ts:194](https://github.com/motla/ftdi-d2xx/blob/1ab01b2/main.d.ts#L194)

___

### FT\_BITS\_8

• **FT\_BITS\_8**: `number`

#### Defined in

[main.d.ts:193](https://github.com/motla/ftdi-d2xx/blob/1ab01b2/main.d.ts#L193)

___

### FT\_FLOW\_DTR\_DSR

• **FT\_FLOW\_DTR\_DSR**: `number`

#### Defined in

[main.d.ts:204](https://github.com/motla/ftdi-d2xx/blob/1ab01b2/main.d.ts#L204)

___

### FT\_FLOW\_NONE

• **FT\_FLOW\_NONE**: `number`

#### Defined in

[main.d.ts:202](https://github.com/motla/ftdi-d2xx/blob/1ab01b2/main.d.ts#L202)

___

### FT\_FLOW\_RTS\_CTS

• **FT\_FLOW\_RTS\_CTS**: `number`

#### Defined in

[main.d.ts:203](https://github.com/motla/ftdi-d2xx/blob/1ab01b2/main.d.ts#L203)

___

### FT\_FLOW\_XON\_XOFF

• **FT\_FLOW\_XON\_XOFF**: `number`

#### Defined in

[main.d.ts:205](https://github.com/motla/ftdi-d2xx/blob/1ab01b2/main.d.ts#L205)

___

### FT\_PARITY\_EVEN

• **FT\_PARITY\_EVEN**: `number`

#### Defined in

[main.d.ts:199](https://github.com/motla/ftdi-d2xx/blob/1ab01b2/main.d.ts#L199)

___

### FT\_PARITY\_MARK

• **FT\_PARITY\_MARK**: `number`

#### Defined in

[main.d.ts:200](https://github.com/motla/ftdi-d2xx/blob/1ab01b2/main.d.ts#L200)

___

### FT\_PARITY\_NONE

• **FT\_PARITY\_NONE**: `number`

#### Defined in

[main.d.ts:197](https://github.com/motla/ftdi-d2xx/blob/1ab01b2/main.d.ts#L197)

___

### FT\_PARITY\_ODD

• **FT\_PARITY\_ODD**: `number`

#### Defined in

[main.d.ts:198](https://github.com/motla/ftdi-d2xx/blob/1ab01b2/main.d.ts#L198)

___

### FT\_PARITY\_SPACE

• **FT\_PARITY\_SPACE**: `number`

#### Defined in

[main.d.ts:201](https://github.com/motla/ftdi-d2xx/blob/1ab01b2/main.d.ts#L201)

___

### FT\_PURGE\_RX

• **FT\_PURGE\_RX**: `number`

#### Defined in

[main.d.ts:206](https://github.com/motla/ftdi-d2xx/blob/1ab01b2/main.d.ts#L206)

___

### FT\_PURGE\_TX

• **FT\_PURGE\_TX**: `number`

#### Defined in

[main.d.ts:207](https://github.com/motla/ftdi-d2xx/blob/1ab01b2/main.d.ts#L207)

___

### FT\_STOP\_BITS\_1

• **FT\_STOP\_BITS\_1**: `number`

#### Defined in

[main.d.ts:195](https://github.com/motla/ftdi-d2xx/blob/1ab01b2/main.d.ts#L195)

___

### FT\_STOP\_BITS\_2

• **FT\_STOP\_BITS\_2**: `number`

#### Defined in

[main.d.ts:196](https://github.com/motla/ftdi-d2xx/blob/1ab01b2/main.d.ts#L196)

___

### library\_version

• **library\_version**: `string`

Current D2XX library version number

#### Defined in

[main.d.ts:190](https://github.com/motla/ftdi-d2xx/blob/1ab01b2/main.d.ts#L190)

## Functions

### getDeviceInfoList

▸ **getDeviceInfoList**(): `Promise`<[`FTDI_DeviceInfo`](./FTDI_DeviceInfo.md)[]\>

Get the list of FTDI devices connected to the system

#### Returns

`Promise`<[`FTDI_DeviceInfo`](./FTDI_DeviceInfo.md)[]\>

#### Defined in

[main.d.ts:167](https://github.com/motla/ftdi-d2xx/blob/1ab01b2/main.d.ts#L167)

___

### getVIDPID

▸ **getVIDPID**(): `Object`

Retrieve the current VID and PID combination from within the internal device list table.

#### Returns

`Object`

| Name | Type | Description |
| :------ | :------ | :------ |
| `pid` | `number` | Device Product ID (PID) |
| `vid` | `number` | Device Vendor ID (VID) |

#### Defined in

[main.d.ts:182](https://github.com/motla/ftdi-d2xx/blob/1ab01b2/main.d.ts#L182)

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

[main.d.ts:173](https://github.com/motla/ftdi-d2xx/blob/1ab01b2/main.d.ts#L173)

___

### setVIDPID

▸ **setVIDPID**(`vid`, `pid`): `void`

Include a custom VID and PID combination within the internal device list table. This will allow the driver to load for the specified VID and PID combination.

#### Parameters

| Name | Type | Description |
| :------ | :------ | :------ |
| `vid` | `number` | Device Vendor ID (VID) |
| `pid` | `number` | Device Product ID (PID) |

#### Returns

`void`

#### Defined in

[main.d.ts:179](https://github.com/motla/ftdi-d2xx/blob/1ab01b2/main.d.ts#L179)
