# Class: FTDI\_Device

## Table of contents

### Properties

- [serial\_number](./FTDI_Device.md#serial_number)

### Accessors

- [driver\_version](./FTDI_Device.md#driver_version)
- [info](./FTDI_Device.md#info)
- [is\_connected](./FTDI_Device.md#is_connected)
- [modem\_status](./FTDI_Device.md#modem_status)
- [status](./FTDI_Device.md#status)

### Methods

- [close](./FTDI_Device.md#close)
- [clrDtr](./FTDI_Device.md#clrdtr)
- [clrRts](./FTDI_Device.md#clrrts)
- [eraseEE](./FTDI_Device.md#eraseee)
- [purge](./FTDI_Device.md#purge)
- [read](./FTDI_Device.md#read)
- [readEE](./FTDI_Device.md#readee)
- [resetDevice](./FTDI_Device.md#resetdevice)
- [setBaudRate](./FTDI_Device.md#setbaudrate)
- [setBreakOff](./FTDI_Device.md#setbreakoff)
- [setBreakOn](./FTDI_Device.md#setbreakon)
- [setDataCharacteristics](./FTDI_Device.md#setdatacharacteristics)
- [setDtr](./FTDI_Device.md#setdtr)
- [setFlowControl](./FTDI_Device.md#setflowcontrol)
- [setRts](./FTDI_Device.md#setrts)
- [setTimeouts](./FTDI_Device.md#settimeouts)
- [write](./FTDI_Device.md#write)
- [writeEE](./FTDI_Device.md#writeee)

## Properties

### serial\_number

• `Readonly` **serial\_number**: `string`

The device serial number

## Accessors

### driver\_version

• `get` **driver_version**(): `string`

Getter to the device driver version

#### Returns

`string`

___

### info

• `get` **info**(): `Object`

Getter to device information

#### Returns

`Object`

| Name | Type | Description |
| :------ | :------ | :------ |
| `description` | `string` | The device description |
| `type` | `string` | The device model type (`"FT232R"`, `"FT2232H"`, ...)  NOTE: See `src/utils.c` for the list of possible types |
| `usb_pid` | `number` | The device USB Product ID |
| `usb_vid` | `number` | The device USB Vendor ID |

___

### is\_connected

• `get` **is_connected**(): `boolean`

Getter to device connection status:
- If `true`, the device is still connected to the system
- If `false`, the device has been disconnected and should be reopened using the [openDevice](./Home.md#opendevice) function that will generate a new [FTDI_Device](./FTDI_Device.md) object.

#### Returns

`boolean`

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

___

### status

• `get` **status**(): `Object`

Getter to device status

#### Returns

`Object`

| Name | Type | Description |
| :------ | :------ | :------ |
| `events` | { `line`: `boolean` ; `modem`: `boolean` ; `rxchar`: `boolean`  } | Current state of the event status |
| `events.line` | `boolean` | Is `true` if a change in the line status has been detected by the device |
| `events.modem` | `boolean` | Is `true` if a change in the modem signals has been detected by the device |
| `events.rxchar` | `boolean` | Is `true` if a character has been received by the device |
| `rx_queue_bytes` | `number` | Number of characters in the receive queue |
| `tx_queue_bytes` | `number` | Number of characters in the transmit queue |

## Methods

### close

▸ **close**(): `Promise`<`void`\>

Close the device

IMPORTANT: Device object is considered dead after this function has been called. Any call to a function or getter of this object will throw an error. Device should be reopened using the [openDevice](./Home.md#opendevice) function that will generate a new [FTDI_Device](./FTDI_Device.md) object.

#### Returns

`Promise`<`void`\>

___

### clrDtr

▸ **clrDtr**(): `void`

Clears the Data Terminal Ready (DTR) control signal

#### Returns

`void`

___

### clrRts

▸ **clrRts**(): `void`

Clears the Request To Send (RTS) control signal

#### Returns

`void`

___

### eraseEE

▸ **eraseEE**(): `Promise`<`void`\>

Erases the device EEPROM

#### Returns

`Promise`<`void`\>

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

___

### read

▸ **read**(`nb_bytes_to_read`): `Promise`<`Uint8Array`\>

Reads data from the device

#### Parameters

| Name | Type | Description |
| :------ | :------ | :------ |
| `nb_bytes_to_read` | `number` | Number of bytes to read from the device |

#### Returns

`Promise`<`Uint8Array`\>

Bytes read from the device

___

### readEE

▸ **readEE**(`word_offset`): `Promise`<`number`\>

Reads a value from an EEPROM location

#### Parameters

| Name | Type | Description |
| :------ | :------ | :------ |
| `word_offset` | `number` | EEPROM location to read from |

#### Returns

`Promise`<`number`\>

EEPROM value (16 bit)

___

### resetDevice

▸ **resetDevice**(): `void`

Send a reset command to the device

#### Returns

`void`

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

___

### setBreakOff

▸ **setBreakOff**(): `void`

Resets the BREAK condition for the device

#### Returns

`void`

___

### setBreakOn

▸ **setBreakOn**(): `void`

Sets the BREAK condition for the device

#### Returns

`void`

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

___

### setDtr

▸ **setDtr**(): `void`

Sets the Data Terminal Ready (DTR) control signal

#### Returns

`void`

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

___

### setRts

▸ **setRts**(): `void`

Sets the Request To Send (RTS) control signal

#### Returns

`void`

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

___

### write

▸ **write**(`data_to_write`): `Promise`<`number`\>

Writes data to the device

#### Parameters

| Name | Type | Description |
| :------ | :------ | :------ |
| `data_to_write` | `Uint8Array` | Bytes to be written to the device |

#### Returns

`Promise`<`number`\>

Number of bytes written to the device

___

### writeEE

▸ **writeEE**(`word_offset`, `value`): `Promise`<`void`\>

Writes a value to an EEPROM location

#### Parameters

| Name | Type | Description |
| :------ | :------ | :------ |
| `word_offset` | `number` | EEPROM location to write to |
| `value` | `number` | EEPROM value (16 bit) |

#### Returns

`Promise`<`void`\>
