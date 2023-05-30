declare class FTDI_DeviceInfo {
  /** @hidden */ constructor();

  /** The device serial number */
  readonly serial_number: string;
  /** The device description */
  readonly description: string;
  /** The device model type (`"FT232R"`, `"FT2232H"`, ...)
   * 
   * NOTE: See `src/utils.c` for the list of possible types */
  readonly type: string;
  /** Is `true` if the device is currently open */
  readonly is_open: boolean;
  /** The device USB Vendor ID */
  readonly usb_vid: number;
  /** The device USB Product ID */
  readonly usb_pid: number;
  /** The device USB port location on the system */
  readonly usb_loc_id: number;
  /** The device USB speed (`high-speed` or `full-speed`) */
  readonly usb_speed: string;
}

declare class FTDI_Device {
  /** @hidden */ constructor();
  
  /** The device serial number (only if provided to the openDevice function)
   * @deprecated Use device.info.serial_number instead
   * @hidden
   */
  readonly serial_number: string;

  /** Getter to device connection status:
   * - If `true`, the device is still connected to the system
   * - If `false`, the device has been disconnected and should be reopened using the {@link openDevice} function that will generate a new {@link FTDI_Device} object. */
  get is_connected(): boolean;
  /** Getter to device information */
  get info(): {
    /** The device serial number */
    readonly serial_number: string;

    /** The device description */
    readonly description: string;
    /** The device model type (`"FT232R"`, `"FT2232H"`, ...)
     * 
     * NOTE: See `src/utils.c` for the list of possible types */
    readonly type: string;
    /** The device USB Vendor ID */
    readonly usb_vid: number;
    /** The device USB Product ID */
    readonly usb_pid: number;
  }

  /** Getter to device status */
  get status(): {
    /** Number of characters in the receive queue */
    readonly rx_queue_bytes: number;
    /** Number of characters in the transmit queue */
    readonly tx_queue_bytes: number;
    /** Current state of the event status */
    readonly events: {
      /** Is `true` if a character has been received by the device */
      readonly rxchar: boolean;
      /** Is `true` if a change in the modem signals has been detected by the device */
      readonly modem: boolean;
      /** Is `true` if a change in the line status has been detected by the device */
      readonly line: boolean;
    }
  }

  /** Getter to device modem status */
  get modem_status(): {
    /** CTS (Clear To Send) flag */
    readonly clear_to_send: boolean;
    /** DSR (Data Set Ready) flag */
    readonly data_set_ready: boolean;
    /** RI (Ring Indicator) flag */
    readonly ring_indicator: boolean;
    /** DCD (Data Carrier Detect) flag */
    readonly data_carrier_detect: boolean;
    /** OE (Overrun Error) flag */
    readonly overrun_error: boolean;
    /** PE (Parity Error) flag */
    readonly parity_error: boolean;
    /** FE (Framing Error) flag */
    readonly framing_error: boolean;
    /** BI (Break Interrupt) flag */
    readonly break_interrupt: boolean;
  }

  /** Getter to the device driver version */
  get driver_version(): string;

  /** Getter to the current value of the latency timer (supported devices only)
   * 
   * In the FT8U232AM and FT8U245AM devices, the receive buffer timeout that is used to flush remaining
   * data from the receive buffer was fixed at 16 ms. In all other FTDI devices, this timeout is programmable
   * and can be set at 1 ms intervals between 2ms and 255 ms. This allows the device to be better optimized
   * for protocols requiring faster response times from short data packets. */
   get latency_timer(): number;

  /** Getter to the instantaneous value of the data bus
   * 
   * For a description of available bit modes for the FT232R, see the application note "Bit Bang Modes for the
   * FT232R and FT245R".
   * 
   * For a description of available bit modes for the FT2232, see the application note "Bit Mode Functions for
   * the FT2232".
   * 
   * For a description of bit bang modes for the FT232B and FT245B, see the application note
   * "FT232B/FT245B Bit Bang Mode".
   * 
   * For a description of bit modes supported by the FT4232H and FT2232H devices, please see the IC data
   * sheets.
   * 
   * These application notes are available for download from the FTDI website. */
  get bit_mode(): number;

  /** Close the device
   * 
   * > **Warning**
   * > IMPORTANT: Device object is considered dead after this function has been called. Any call to a function or getter of this object will throw an error. Device should be reopened using the {@link openDevice} function that will generate a new {@link FTDI_Device} object.
   */
  close(): Promise<void>;

  /** Reads data from the device
   * @param nb_bytes_to_read Number of bytes to read from the device
   * @returns Bytes read from the device
   */
  read(nb_bytes_to_read: number): Promise<Uint8Array>;

  /** Writes data to the device
   * @param data_to_write Bytes to be written to the device
   * @returns Number of bytes written to the device
   */
  write(data_to_write: Uint8Array): Promise<number>;

  /** Purges receive and transmit buffers in the device
   * @param mask Combination of FT_PURGE_RX and FT_PURGE_TX
   */
  purge(mask: number): void;

  /** Sets the baud rate for the device
   * @param baud_rate The baud rate to set to the device (bits per second)
   */
  setBaudRate(baud_rate: number): void;

  /** Sets the data characteristics for the device
   * @param word_length Number of bits per word - must be FT_BITS_8 or FT_BITS_7
   * @param stop_bits Number of stop bits - must be FT_STOP_BITS_1 or FT_STOP_BITS_2
   * @param parity Parity - must be FT_PARITY_NONE, FT_PARITY_ODD, FT_PARITY_EVEN, FT_PARITY_MARK or FT_PARITY_SPACE
   */
  setDataCharacteristics(word_length: number, stop_bits: number, parity: number): void;

  /** Sets the read ans write timeouts for the device
   * @param read_timeout Read timeout in milliseconds
   * @param write_timeout Write timeout in milliseconds
   */
  setTimeouts(read_timeout: number, write_timeout: number): void;

  /** Sets the flow control for the device
   * @param flow_control Flow control - must be one of FT_FLOW_NONE, FT_FLOW_RTS_CTS, FT_FLOW_DTR_DSR or FT_FLOW_XON_XOFF
   * @param xon Xon byte - Character used to signal Xon. Only used if flow control is FT_FLOW_XON_XOFF
   * @param xoff Xoff byte - Character used to signal Xoff. Only used if flow control is FT_FLOW_XON_XOFF
   */
  setFlowControl(flow_control: number, xon: number, xoff: number): void;

  /** Sets the Data Terminal Ready (DTR) control signal */
  setDtr(): void;

  /** Clears the Data Terminal Ready (DTR) control signal */
  clrDtr(): void;

  /** Sets the Request To Send (RTS) control signal */
  setRts(): void;

  /** Clears the Request To Send (RTS) control signal */
  clrRts(): void;

  /** Sets the BREAK condition for the device */
  setBreakOn(): void;

  /** Resets the BREAK condition for the device */
  setBreakOff(): void;

  /** Send a reset command to the device */
  resetDevice(): void;

  /** Reads a value from an EEPROM location
   * @param word_offset EEPROM location to read from
   * @returns EEPROM value (16 bit)
   */
  readEE(word_offset: number): Promise<number>;

  /** Writes a value to an EEPROM location
   * @param word_offset EEPROM location to write to
   * @param value EEPROM value (16 bit)
   */
  writeEE(word_offset: number, value: number): Promise<void>;

  /** Erases the device EEPROM */
  eraseEE(): Promise<void>;

  /** Sets the latency timer value (supported devices only)
   * @param timer Latency timer value, in milliseconds. Valid range is 2 to 255.
   */
  setLatencyTimer(timer: number): void;

  /** Enables different chip modes (puts the device in a mode other than the default UART or FIFO mode).
    * @param mask Bit mode mask
    * Sets up which bits are inputs and which are outputs. 
    * A bit value of 0 sets the corresponding pin to an input, a bit value of 1 sets the corresponding pin to an output. 
    * In the case of CBUS Bit Bang, the upper nibble of this value controls which pins are inputs and outputs, while the lower nibble controls which of the outputs are high and low.
    * @param bit_mode Mode value. Can be one of the following:
    * For FT232H devices, valid values are FT_BIT_MODE_RESET, FT_BIT_MODE_ASYNC_BITBANG, FT_BIT_MODE_MPSSE, FT_BIT_MODE_SYNC_BITBANG, FT_BIT_MODE_CBUS_BITBANG, FT_BIT_MODE_MCU_HOST, FT_BIT_MODE_FAST_SERIAL, FT_BIT_MODE_SYNC_FIFO.
    * For FT2232H devices, valid values are FT_BIT_MODE_RESET, FT_BIT_MODE_ASYNC_BITBANG, FT_BIT_MODE_MPSSE, FT_BIT_MODE_SYNC_BITBANG, FT_BIT_MODE_MCU_HOST, FT_BIT_MODE_FAST_SERIAL, FT_BIT_MODE_SYNC_FIFO.
    * For FT4232H devices, valid values are FT_BIT_MODE_RESET, FT_BIT_MODE_ASYNC_BITBANG, FT_BIT_MODE_MPSSE, FT_BIT_MODE_SYNC_BITBANG.
    * For FT232R devices, valid values are FT_BIT_MODE_RESET, FT_BIT_MODE_ASYNC_BITBANG, FT_BIT_MODE_SYNC_BITBANG, FT_BIT_MODE_CBUS_BITBANG.
    * For FT245R devices, valid values are FT_BIT_MODE_RESET, FT_BIT_MODE_ASYNC_BITBANG, FT_BIT_MODE_SYNC_BITBANG.
    * For FT2232 devices, valid values are FT_BIT_MODE_RESET, FT_BIT_MODE_ASYNC_BITBANG, FT_BIT_MODE_MPSSE, FT_BIT_MODE_SYNC_BITBANG, FT_BIT_MODE_MCU_HOST, FT_BIT_MODE_FAST_SERIAL.
    * For FT232B and FT245B devices, valid values are FT_BIT_MODE_RESET, FT_BIT_MODE_ASYNC_BITBANG.
    */
  setBitMode(mask: number, bit_mode: number): void;

  /** Sets the USB request transfer size
   * 
   * This function can be used to change the transfer sizes from the default transfer size of 4096 bytes to
   * better suit the application requirements. Transfer sizes must be set to a multiple of 64 bytes between 64
   * bytes and 64k bytes.
   * When FT_SetUSBParameters is called, the change comes into effect immediately and any data that was
   * held in the driver at the time of the change is lost.
   * Note that, at present, only `in_transfer_size` is supported by the FTDI vendor driver.
   *
   * @param in_transfer_size Transfer size in bits for USB IN request
   * @param out_transfer_size Transfer size in bits for USB OUT request (unsupported yet)
   */
  setUSBParameters(in_transfer_size: number, out_transfer_size: number): void;
}

/** Get the list of FTDI devices connected to the system */
export function getDeviceInfoList(): Promise<FTDI_DeviceInfo[]>;

/** Try to open a device
 * @param identifier Device serial number (string), or an object containing either its `serial_number` (string), its `usb_loc_id` (number) or its `description` (string) property
 * @returns Device object
 */
export function openDevice(identifier: string | { serial_number?: string, usb_loc_id?: number, description?: string }): Promise<FTDI_Device>;

/** This allows the driver to load only for the specified VID and PID combination.
 * 
 * IMPORTANT: On Windows platforms, this function forces a reload of the driver.
 * Please note that this function will not work correctly on 64-bit Windows when called from a 32-bit application.
 * 
 * @param vid Device Vendor ID (VID)
 * @param pid Device Product ID (PID)
 */
export function setVIDPID(vid: number, pid: number): Promise<void>;

/** Current D2XX library version number
 * @readonly */
export const library_version: string;

// Constants
export const FT_BITS_8: number;
export const FT_BITS_7: number;
export const FT_STOP_BITS_1: number;
export const FT_STOP_BITS_2: number;
export const FT_PARITY_NONE: number;
export const FT_PARITY_ODD: number;
export const FT_PARITY_EVEN: number;
export const FT_PARITY_MARK: number;
export const FT_PARITY_SPACE: number;
export const FT_FLOW_NONE: number;
export const FT_FLOW_RTS_CTS: number;
export const FT_FLOW_DTR_DSR: number;
export const FT_FLOW_XON_XOFF: number;
export const FT_PURGE_RX: number;
export const FT_PURGE_TX: number;
export const FT_BITMODE_RESET: number;
export const FT_BITMODE_ASYNC_BITBANG: number;
export const FT_BITMODE_MPSSE: number;
export const FT_BITMODE_SYNC_BITBANG: number;
export const FT_BITMODE_MCU_HOST: number;
export const FT_BITMODE_FAST_SERIAL: number;
export const FT_BITMODE_CBUS_BITBANG: number;
export const FT_BITMODE_SYNC_FIFO: number;
