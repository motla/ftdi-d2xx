# Class: FTDI\_DeviceInfo

## Table of contents

### Constructors

- [constructor](../wiki/FTDI_DeviceInfo#constructor)

### Properties

- [description](../wiki/FTDI_DeviceInfo#description)
- [is\_open](../wiki/FTDI_DeviceInfo#is_open)
- [serial\_number](../wiki/FTDI_DeviceInfo#serial_number)
- [type](../wiki/FTDI_DeviceInfo#type)
- [usb\_loc\_id](../wiki/FTDI_DeviceInfo#usb_loc_id)
- [usb\_pid](../wiki/FTDI_DeviceInfo#usb_pid)
- [usb\_speed](../wiki/FTDI_DeviceInfo#usb_speed)
- [usb\_vid](../wiki/FTDI_DeviceInfo#usb_vid)

## Constructors

### constructor

• **new FTDI_DeviceInfo**()

## Properties

### description

• `Readonly` **description**: `string`

The device description

#### Defined in

main.d.ts:5

___

### is\_open

• `Readonly` **is\_open**: `boolean`

Will be true if the device is currently open

#### Defined in

main.d.ts:11

___

### serial\_number

• `Readonly` **serial\_number**: `string`

The device serial number

#### Defined in

main.d.ts:3

___

### type

• `Readonly` **type**: `string`

The device model type (FT232R, FT2232H)

NOTE: See `utils.c` for the list of possible types

#### Defined in

main.d.ts:9

___

### usb\_loc\_id

• `Readonly` **usb\_loc\_id**: `number`

The device USB port location on the system

#### Defined in

main.d.ts:17

___

### usb\_pid

• `Readonly` **usb\_pid**: `number`

The device USB Product ID

#### Defined in

main.d.ts:15

___

### usb\_speed

• `Readonly` **usb\_speed**: `string`

The device USB speed (`high-speed` or `full-speed`)

#### Defined in

main.d.ts:19

___

### usb\_vid

• `Readonly` **usb\_vid**: `number`

The device USB Vendor ID

#### Defined in

main.d.ts:13
