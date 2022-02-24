declare class FTDI_DeviceInfo {
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
  /** The device serial number */
  readonly serial_number: string;
  /** Getter to device connection status:
   * - If `true`, the device is still connected to the system
   * - If `false`, the device has been disconnected and should be reopened using the {@link openDevice} function that will generate a new {@link FTDI_Device} object. */
  get is_connected(): boolean;
  /** Getter to device information */
  get info(): {
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

  /** Close the device
   * 
   * IMPORTANT: Device object is considered dead after this function has been called. Any call to a function or getter of this object will throw an error. Device should be reopened using the {@link openDevice} function that will generate a new {@link FTDI_Device} object.
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
}

/** Get the list of FTDI devices connected to the system */
export function getDeviceInfoList(): Promise<FTDI_DeviceInfo[]>;

/** Try to open a device from its serial number
 * @param serial_number Device serial number
 * @returns Device object
 */
export function openDevice(serial_number: string): Promise<FTDI_Device>;

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
