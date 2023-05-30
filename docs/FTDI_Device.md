# Class: FTDI\_Device

## Table of contents

### Accessors

- [bit\_mode](./FTDI_Device.md#bit_mode)
- [driver\_version](./FTDI_Device.md#driver_version)
- [info](./FTDI_Device.md#info)
- [is\_connected](./FTDI_Device.md#is_connected)
- [latency\_timer](./FTDI_Device.md#latency_timer)
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
- [setBitMode](./FTDI_Device.md#setbitmode)
- [setBreakOff](./FTDI_Device.md#setbreakoff)
- [setBreakOn](./FTDI_Device.md#setbreakon)
- [setDataCharacteristics](./FTDI_Device.md#setdatacharacteristics)
- [setDtr](./FTDI_Device.md#setdtr)
- [setFlowControl](./FTDI_Device.md#setflowcontrol)
- [setLatencyTimer](./FTDI_Device.md#setlatencytimer)
- [setRts](./FTDI_Device.md#setrts)
- [setTimeouts](./FTDI_Device.md#settimeouts)
- [setUSBParameters](./FTDI_Device.md#setusbparameters)
- [write](./FTDI_Device.md#write)
- [writeEE](./FTDI_Device.md#writeee)

## Accessors

### bit\_mode

• `get` **bit_mode**(): `number`

Getter to the instantaneous value of the data bus

For a description of available bit modes for the FT232R, see the application note "Bit Bang Modes for the
FT232R and FT245R".

For a description of available bit modes for the FT2232, see the application note "Bit Mode Functions for
the FT2232".

For a description of bit bang modes for the FT232B and FT245B, see the application note
"FT232B/FT245B Bit Bang Mode".

For a description of bit modes supported by the FT4232H and FT2232H devices, please see the IC data
sheets.

These application notes are available for download from the FTDI website.

#### Returns

`number`

___

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
| `serial_number` | `string` | The device serial number |
| `type` | `string` | The device model type (`"FT232R"`, `"FT2232H"`, ...) NOTE: See `src/utils.c` for the list of possible types |
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

### latency\_timer

• `get` **latency_timer**(): `number`

Getter to the current value of the latency timer (supported devices only)

In the FT8U232AM and FT8U245AM devices, the receive buffer timeout that is used to flush remaining
data from the receive buffer was fixed at 16 ms. In all other FTDI devices, this timeout is programmable
and can be set at 1 ms intervals between 2ms and 255 ms. This allows the device to be better optimized
for protocols requiring faster response times from short data packets.

#### Returns

`number`

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

> **Warning**
> IMPORTANT: Device object is considered dead after this function has been called. Any call to a function or getter of this object will throw an error. Device should be reopened using the [openDevice](./Home.md#opendevice) function that will generate a new [FTDI_Device](./FTDI_Device.md) object.

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

### setBitMode

▸ **setBitMode**(`mask`, `bit_mode`): `void`

Enables different chip modes (puts the device in a mode other than the default UART or FIFO mode).

#### Parameters

| Name | Type | Description |
| :------ | :------ | :------ |
| `mask` | `number` | Bit mode mask Sets up which bits are inputs and which are outputs. A bit value of 0 sets the corresponding pin to an input, a bit value of 1 sets the corresponding pin to an output. In the case of CBUS Bit Bang, the upper nibble of this value controls which pins are inputs and outputs, while the lower nibble controls which of the outputs are high and low. |
| `bit_mode` | `number` | Mode value. Can be one of the following: For FT232H devices, valid values are FT_BIT_MODE_RESET, FT_BIT_MODE_ASYNC_BITBANG, FT_BIT_MODE_MPSSE, FT_BIT_MODE_SYNC_BITBANG, FT_BIT_MODE_CBUS_BITBANG, FT_BIT_MODE_MCU_HOST, FT_BIT_MODE_FAST_SERIAL, FT_BIT_MODE_SYNC_FIFO. For FT2232H devices, valid values are FT_BIT_MODE_RESET, FT_BIT_MODE_ASYNC_BITBANG, FT_BIT_MODE_MPSSE, FT_BIT_MODE_SYNC_BITBANG, FT_BIT_MODE_MCU_HOST, FT_BIT_MODE_FAST_SERIAL, FT_BIT_MODE_SYNC_FIFO. For FT4232H devices, valid values are FT_BIT_MODE_RESET, FT_BIT_MODE_ASYNC_BITBANG, FT_BIT_MODE_MPSSE, FT_BIT_MODE_SYNC_BITBANG. For FT232R devices, valid values are FT_BIT_MODE_RESET, FT_BIT_MODE_ASYNC_BITBANG, FT_BIT_MODE_SYNC_BITBANG, FT_BIT_MODE_CBUS_BITBANG. For FT245R devices, valid values are FT_BIT_MODE_RESET, FT_BIT_MODE_ASYNC_BITBANG, FT_BIT_MODE_SYNC_BITBANG. For FT2232 devices, valid values are FT_BIT_MODE_RESET, FT_BIT_MODE_ASYNC_BITBANG, FT_BIT_MODE_MPSSE, FT_BIT_MODE_SYNC_BITBANG, FT_BIT_MODE_MCU_HOST, FT_BIT_MODE_FAST_SERIAL. For FT232B and FT245B devices, valid values are FT_BIT_MODE_RESET, FT_BIT_MODE_ASYNC_BITBANG. |

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

### setLatencyTimer

▸ **setLatencyTimer**(`timer`): `void`

Sets the latency timer value (supported devices only)

#### Parameters

| Name | Type | Description |
| :------ | :------ | :------ |
| `timer` | `number` | Latency timer value, in milliseconds. Valid range is 2 to 255. |

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

### setUSBParameters

▸ **setUSBParameters**(`in_transfer_size`, `out_transfer_size`): `void`

Sets the USB request transfer size

This function can be used to change the transfer sizes from the default transfer size of 4096 bytes to
better suit the application requirements. Transfer sizes must be set to a multiple of 64 bytes between 64
bytes and 64k bytes.
When FT_SetUSBParameters is called, the change comes into effect immediately and any data that was
held in the driver at the time of the change is lost.
Note that, at present, only `in_transfer_size` is supported by the FTDI vendor driver.

#### Parameters

| Name | Type | Description |
| :------ | :------ | :------ |
| `in_transfer_size` | `number` | Transfer size in bits for USB IN request |
| `out_transfer_size` | `number` | Transfer size in bits for USB OUT request (unsupported yet) |

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
