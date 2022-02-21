# Class: FTDI\_DeviceInfo

## Table of contents

### Constructors

- [constructor](./FTDI_DeviceInfo.md#constructor)

### Properties

- [description](./FTDI_DeviceInfo.md#description)
- [is\_open](./FTDI_DeviceInfo.md#is_open)
- [serial\_number](./FTDI_DeviceInfo.md#serial_number)
- [type](./FTDI_DeviceInfo.md#type)
- [usb\_loc\_id](./FTDI_DeviceInfo.md#usb_loc_id)
- [usb\_pid](./FTDI_DeviceInfo.md#usb_pid)
- [usb\_speed](./FTDI_DeviceInfo.md#usb_speed)
- [usb\_vid](./FTDI_DeviceInfo.md#usb_vid)

## Constructors

### constructor

• **new FTDI_DeviceInfo**()

## Properties

### description

• `Readonly` **description**: `string`

The device description

#### Defined in

[main.d.ts:5](https://github.com/motla/ftdi-d2xx/blob/38e724e/main.d.ts#L5)

___

### is\_open

• `Readonly` **is\_open**: `boolean`

Will be true if the device is currently open

#### Defined in

[main.d.ts:11](https://github.com/motla/ftdi-d2xx/blob/38e724e/main.d.ts#L11)

___

### serial\_number

• `Readonly` **serial\_number**: `string`

The device serial number

#### Defined in

[main.d.ts:3](https://github.com/motla/ftdi-d2xx/blob/38e724e/main.d.ts#L3)

___

### type

• `Readonly` **type**: `string`

The device model type (FT232R, FT2232H)

NOTE: See `utils.c` for the list of possible types

#### Defined in

[main.d.ts:9](https://github.com/motla/ftdi-d2xx/blob/38e724e/main.d.ts#L9)

___

### usb\_loc\_id

• `Readonly` **usb\_loc\_id**: `number`

The device USB port location on the system

#### Defined in

[main.d.ts:17](https://github.com/motla/ftdi-d2xx/blob/38e724e/main.d.ts#L17)

___

### usb\_pid

• `Readonly` **usb\_pid**: `number`

The device USB Product ID

#### Defined in

[main.d.ts:15](https://github.com/motla/ftdi-d2xx/blob/38e724e/main.d.ts#L15)

___

### usb\_speed

• `Readonly` **usb\_speed**: `string`

The device USB speed (`high-speed` or `full-speed`)

#### Defined in

[main.d.ts:19](https://github.com/motla/ftdi-d2xx/blob/38e724e/main.d.ts#L19)

___

### usb\_vid

• `Readonly` **usb\_vid**: `number`

The device USB Vendor ID

#### Defined in

[main.d.ts:13](https://github.com/motla/ftdi-d2xx/blob/38e724e/main.d.ts#L13)
