# Class: FTDI\_DeviceInfo

## Table of contents

### Properties

- [description](./FTDI_DeviceInfo.md#description)
- [is\_open](./FTDI_DeviceInfo.md#is_open)
- [serial\_number](./FTDI_DeviceInfo.md#serial_number)
- [type](./FTDI_DeviceInfo.md#type)
- [usb\_loc\_id](./FTDI_DeviceInfo.md#usb_loc_id)
- [usb\_pid](./FTDI_DeviceInfo.md#usb_pid)
- [usb\_speed](./FTDI_DeviceInfo.md#usb_speed)
- [usb\_vid](./FTDI_DeviceInfo.md#usb_vid)

## Properties

### description

• `Readonly` **description**: `string`

The device description

___

### is\_open

• `Readonly` **is\_open**: `boolean`

Is `true` if the device is currently open

___

### serial\_number

• `Readonly` **serial\_number**: `string`

The device serial number

___

### type

• `Readonly` **type**: `string`

The device model type (`"FT232R"`, `"FT2232H"`, ...)

NOTE: See `src/utils.c` for the list of possible types

___

### usb\_loc\_id

• `Readonly` **usb\_loc\_id**: `number`

The device USB port location on the system

___

### usb\_pid

• `Readonly` **usb\_pid**: `number`

The device USB Product ID

___

### usb\_speed

• `Readonly` **usb\_speed**: `string`

The device USB speed (`high-speed` or `full-speed`)

___

### usb\_vid

• `Readonly` **usb\_vid**: `number`

The device USB Vendor ID
