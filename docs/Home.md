# ftdi-d2xx

## Table of contents

### Classes

- [FTDI\_Device](../wiki/FTDI_Device)
- [FTDI\_DeviceInfo](../wiki/FTDI_DeviceInfo)

### Variables

- [FT\_BITS\_7](../wiki/Home#ft_bits_7)
- [FT\_BITS\_8](../wiki/Home#ft_bits_8)
- [FT\_FLOW\_DTR\_DSR](../wiki/Home#ft_flow_dtr_dsr)
- [FT\_FLOW\_NONE](../wiki/Home#ft_flow_none)
- [FT\_FLOW\_RTS\_CTS](../wiki/Home#ft_flow_rts_cts)
- [FT\_FLOW\_XON\_XOFF](../wiki/Home#ft_flow_xon_xoff)
- [FT\_PARITY\_EVEN](../wiki/Home#ft_parity_even)
- [FT\_PARITY\_MARK](../wiki/Home#ft_parity_mark)
- [FT\_PARITY\_NONE](../wiki/Home#ft_parity_none)
- [FT\_PARITY\_ODD](../wiki/Home#ft_parity_odd)
- [FT\_PARITY\_SPACE](../wiki/Home#ft_parity_space)
- [FT\_PURGE\_RX](../wiki/Home#ft_purge_rx)
- [FT\_PURGE\_TX](../wiki/Home#ft_purge_tx)
- [FT\_STOP\_BITS\_1](../wiki/Home#ft_stop_bits_1)
- [FT\_STOP\_BITS\_2](../wiki/Home#ft_stop_bits_2)
- [library\_version](../wiki/Home#library_version)

### Functions

- [getDeviceInfoList](../wiki/Home#getdeviceinfolist)
- [getVIDPID](../wiki/Home#getvidpid)
- [openDevice](../wiki/Home#opendevice)
- [setVIDPID](../wiki/Home#setvidpid)

## Variables

### FT\_BITS\_7

• **FT\_BITS\_7**: `number`

#### Defined in

main.d.ts:191

___

### FT\_BITS\_8

• **FT\_BITS\_8**: `number`

#### Defined in

main.d.ts:190

___

### FT\_FLOW\_DTR\_DSR

• **FT\_FLOW\_DTR\_DSR**: `number`

#### Defined in

main.d.ts:201

___

### FT\_FLOW\_NONE

• **FT\_FLOW\_NONE**: `number`

#### Defined in

main.d.ts:199

___

### FT\_FLOW\_RTS\_CTS

• **FT\_FLOW\_RTS\_CTS**: `number`

#### Defined in

main.d.ts:200

___

### FT\_FLOW\_XON\_XOFF

• **FT\_FLOW\_XON\_XOFF**: `number`

#### Defined in

main.d.ts:202

___

### FT\_PARITY\_EVEN

• **FT\_PARITY\_EVEN**: `number`

#### Defined in

main.d.ts:196

___

### FT\_PARITY\_MARK

• **FT\_PARITY\_MARK**: `number`

#### Defined in

main.d.ts:197

___

### FT\_PARITY\_NONE

• **FT\_PARITY\_NONE**: `number`

#### Defined in

main.d.ts:194

___

### FT\_PARITY\_ODD

• **FT\_PARITY\_ODD**: `number`

#### Defined in

main.d.ts:195

___

### FT\_PARITY\_SPACE

• **FT\_PARITY\_SPACE**: `number`

#### Defined in

main.d.ts:198

___

### FT\_PURGE\_RX

• **FT\_PURGE\_RX**: `number`

#### Defined in

main.d.ts:203

___

### FT\_PURGE\_TX

• **FT\_PURGE\_TX**: `number`

#### Defined in

main.d.ts:204

___

### FT\_STOP\_BITS\_1

• **FT\_STOP\_BITS\_1**: `number`

#### Defined in

main.d.ts:192

___

### FT\_STOP\_BITS\_2

• **FT\_STOP\_BITS\_2**: `number`

#### Defined in

main.d.ts:193

___

### library\_version

• **library\_version**: `string`

Current D2XX library version number

#### Defined in

main.d.ts:187

## Functions

### getDeviceInfoList

▸ **getDeviceInfoList**(): `Promise`<[`FTDI_DeviceInfo`](../wiki/FTDI_DeviceInfo)[]\>

Get the list of FTDI devices connected to the system

#### Returns

`Promise`<[`FTDI_DeviceInfo`](../wiki/FTDI_DeviceInfo)[]\>

#### Defined in

main.d.ts:165

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

main.d.ts:179

___

### openDevice

▸ **openDevice**(`serial_number`): `Promise`<[`FTDI_Device`](../wiki/FTDI_Device)\>

Try to open a device from its serial number

#### Parameters

| Name | Type | Description |
| :------ | :------ | :------ |
| `serial_number` | `string` | Device serial number |

#### Returns

`Promise`<[`FTDI_Device`](../wiki/FTDI_Device)\>

#### Defined in

main.d.ts:170

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

main.d.ts:176
