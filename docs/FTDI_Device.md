# Class: FTDI\_Device

## Table of contents

### Constructors

- [constructor](../wiki/FTDI_Device#constructor)

### Properties

- [serial\_number](../wiki/FTDI_Device#serial_number)

### Accessors

- [driver\_version](../wiki/FTDI_Device#driver_version)
- [info](../wiki/FTDI_Device#info)
- [modem\_status](../wiki/FTDI_Device#modem_status)
- [status](../wiki/FTDI_Device#status)

### Methods

- [close](../wiki/FTDI_Device#close)
- [clrDtr](../wiki/FTDI_Device#clrdtr)
- [clrRts](../wiki/FTDI_Device#clrrts)
- [eraseEE](../wiki/FTDI_Device#eraseee)
- [purge](../wiki/FTDI_Device#purge)
- [read](../wiki/FTDI_Device#read)
- [readEE](../wiki/FTDI_Device#readee)
- [resetDevice](../wiki/FTDI_Device#resetdevice)
- [setBaudRate](../wiki/FTDI_Device#setbaudrate)
- [setBreakOff](../wiki/FTDI_Device#setbreakoff)
- [setBreakOn](../wiki/FTDI_Device#setbreakon)
- [setDataCharacteristics](../wiki/FTDI_Device#setdatacharacteristics)
- [setDtr](../wiki/FTDI_Device#setdtr)
- [setFlowControl](../wiki/FTDI_Device#setflowcontrol)
- [setRts](../wiki/FTDI_Device#setrts)
- [setTimeouts](../wiki/FTDI_Device#settimeouts)
- [write](../wiki/FTDI_Device#write)
- [writeEE](../wiki/FTDI_Device#writeee)

## Constructors

### constructor

• **new FTDI_Device**()

## Properties

### serial\_number

• `Readonly` **serial\_number**: `string`

The device serial number

#### Defined in

main.d.ts:24

## Accessors

### driver\_version

• `get` **driver_version**(): `string`

Getter to the device driver version

#### Returns

`string`

#### Defined in

main.d.ts:77

___

### info

• `get` **info**(): `Object`

Getter to device information

#### Returns

`Object`

| Name | Type | Description |
| :------ | :------ | :------ |
| `description` | `string` | The device description |
| `type` | `string` | The device model type (FT232R, FT2232H)  NOTE: See `utils.c` for the list of possible types |
| `usb_pid` | `number` | The device USB Product ID |
| `usb_vid` | `number` | The device USB Vendor ID |

#### Defined in

main.d.ts:26

___

### modem\_status

• `get` **modem_status**(): `Object`

Getter to device modem status

#### Returns

`Object`

| Name | Type | Description |
| :------ | :------ | :------ |
| `break_interrupt` | `boolean` | BI (Break Interrupt) flag |
| `clear_to_send` | `boolean` | CTS (Clear To Send) flag |
| `data_carrier_detect` | `boolean` | DCD (Data Carrier Detect) flag |
| `data_set_ready` | `boolean` | DSR (Data Set Ready) flag |
| `framing_error` | `boolean` | FE (Framing Error) flag |
| `overrun_error` | `boolean` | OE (Overrun Error) flag |
| `parity_error` | `boolean` | PE (Parity Error) flag |
| `ring_indicator` | `boolean` | RI (Ring Indicator) flag |

#### Defined in

main.d.ts:57

___

### status

• `get` **status**(): `Object`

Getter to device status

#### Returns

`Object`

| Name | Type | Description |
| :------ | :------ | :------ |
| `events` | `Object` | Current state of the event status |
| `events.line` | `boolean` | Will be true if a change in the line status has been detected by the device |
| `events.modem` | `boolean` | Will be true if a change in the modem signals has been detected by the device |
| `events.rxchar` | `boolean` | Will be true if a character has been received by the device |
| `rx_queue_bytes` | `number` | Number of characters in the receive queue |
| `tx_queue_bytes` | `number` | Number of characters in the transmit queue |

#### Defined in

main.d.ts:40

## Methods

### close

▸ **close**(): `void`

Close the device

IMPORTANT: Device object is considered dead after this function has been called. Any call to a function or getter of this object will trigger an error. Device should be reopened using the [openDevice](../wiki/Home#opendevice) function that will generate a new [FTDI_Device](../wiki/FTDI_Device) object.

#### Returns

`void`

#### Defined in

main.d.ts:83

___

### clrDtr

▸ **clrDtr**(): `void`

Clears the Data Terminal Ready (DTR) control signal

#### Returns

`void`

#### Defined in

main.d.ts:131

___

### clrRts

▸ **clrRts**(): `void`

Clears the Request To Send (RTS) control signal

#### Returns

`void`

#### Defined in

main.d.ts:137

___

### eraseEE

▸ **eraseEE**(): `Promise`<`void`\>

Erases the device EEPROM

#### Returns

`Promise`<`void`\>

#### Defined in

main.d.ts:161

___

### purge

▸ **purge**(`mask`): `void`

Purges receive and transmit buffers in the device

#### Parameters

| Name | Type | Description |
| :------ | :------ | :------ |
| `mask` | `number` | Combination of FT_PURGE_RX and FT_PURGE_TX |

#### Returns

`void`

#### Defined in

main.d.ts:100

___

### read

▸ **read**(`nb_bytes_to_read`): `Promise`<`Uint8Array`\>

Read data from the device

#### Parameters

| Name | Type | Description |
| :------ | :------ | :------ |
| `nb_bytes_to_read` | `number` | Number of bytes to read from the device |

#### Returns

`Promise`<`Uint8Array`\>

Bytes read from the device

#### Defined in

main.d.ts:89

___

### readEE

▸ **readEE**(`word_offset`): `Promise`<`number`\>

Read a value from an EEPROM location

#### Parameters

| Name | Type | Description |
| :------ | :------ | :------ |
| `word_offset` | `number` | EEPROM location to read from |

#### Returns

`Promise`<`number`\>

EEPROM value (16 bit)

#### Defined in

main.d.ts:152

___

### resetDevice

▸ **resetDevice**(): `void`

Send a reset command to the device

#### Returns

`void`

#### Defined in

main.d.ts:146

___

### setBaudRate

▸ **setBaudRate**(`baud_rate`): `void`

Sets the baud rate for the device

#### Parameters

| Name | Type | Description |
| :------ | :------ | :------ |
| `baud_rate` | `number` | The baud rate to set to the device (bits per second) |

#### Returns

`void`

#### Defined in

main.d.ts:105

___

### setBreakOff

▸ **setBreakOff**(): `void`

Resets the BREAK condition for the device

#### Returns

`void`

#### Defined in

main.d.ts:143

___

### setBreakOn

▸ **setBreakOn**(): `void`

Sets the BREAK condition for the device

#### Returns

`void`

#### Defined in

main.d.ts:140

___

### setDataCharacteristics

▸ **setDataCharacteristics**(`word_length`, `stop_bits`, `parity`): `void`

Sets the data characteristics for the device

#### Parameters

| Name | Type | Description |
| :------ | :------ | :------ |
| `word_length` | `number` | Number of bits per word - must be FT_BITS_8 or FT_BITS_7 |
| `stop_bits` | `number` | Number of stop bits - must be FT_STOP_BITS_1 or FT_STOP_BITS_2 |
| `parity` | `number` | Parity - must be FT_PARITY_NONE, FT_PARITY_ODD, FT_PARITY_EVEN, FT_PARITY_MARK or FT_PARITY_SPACE |

#### Returns

`void`

#### Defined in

main.d.ts:112

___

### setDtr

▸ **setDtr**(): `void`

Sets the Data Terminal Ready (DTR) control signal

#### Returns

`void`

#### Defined in

main.d.ts:128

___

### setFlowControl

▸ **setFlowControl**(`flow_control`, `xon`, `xoff`): `void`

Sets the flow control for the device

#### Parameters

| Name | Type | Description |
| :------ | :------ | :------ |
| `flow_control` | `number` | Flow control - must be one of FT_FLOW_NONE, FT_FLOW_RTS_CTS, FT_FLOW_DTR_DSR or FT_FLOW_XON_XOFF |
| `xon` | `number` | Xon byte - Character used to signal Xon. Only used if flow control is FT_FLOW_XON_XOFF |
| `xoff` | `number` | Xoff byte - Character used to signal Xoff. Only used if flow control is FT_FLOW_XON_XOFF |

#### Returns

`void`

#### Defined in

main.d.ts:125

___

### setRts

▸ **setRts**(): `void`

Sets the Request To Send (RTS) control signal

#### Returns

`void`

#### Defined in

main.d.ts:134

___

### setTimeouts

▸ **setTimeouts**(`read_timeout`, `write_timeout`): `void`

Sets the read ans write timeouts for the device

#### Parameters

| Name | Type | Description |
| :------ | :------ | :------ |
| `read_timeout` | `number` | Read timeout in milliseconds |
| `write_timeout` | `number` | Write timeout in milliseconds |

#### Returns

`void`

#### Defined in

main.d.ts:118

___

### write

▸ **write**(`data_to_write`): `Promise`<`number`\>

Write data to the device

#### Parameters

| Name | Type | Description |
| :------ | :------ | :------ |
| `data_to_write` | `Uint8Array` | Bytes to be written to the device |

#### Returns

`Promise`<`number`\>

Number of bytes written to the device

#### Defined in

main.d.ts:95

___

### writeEE

▸ **writeEE**(`word_offset`, `value`): `Promise`<`void`\>

Write a value to an EEPROM location

#### Parameters

| Name | Type | Description |
| :------ | :------ | :------ |
| `word_offset` | `number` | EEPROM location to write to |
| `value` | `number` | EEPROM value (16 bit) |

#### Returns

`Promise`<`void`\>

#### Defined in

main.d.ts:158
