# FTDI D2XX Driver for Node.js

## Features
- Asynchronous, non-blocking functions (use [`Promises`](https://developer.mozilla.org/en-US/docs/Learn/JavaScript/Asynchronous/Promises) or [`async/await`](https://developer.mozilla.org/en-US/docs/Learn/JavaScript/Asynchronous/Promises#async_and_await))
- Pre-compiled for Windows / macOS / Linux
- Compatible with [Electron](https://www.electronjs.org/) (see [the note](#note-to-electron-users) below)
- Includes static FTDI Driver vendor libraries
- Written in pure C language using [Node-API](https://nodejs.org/api/n-api.html#node-api)
- Detailed error messages and codes are thrown without crashing Node.js
- Includes TypeScript typings for auto-completion and validation
- Compiled with [CMake.js](https://github.com/cmake-js/cmake-js) (no `gyp` / no Python required)


## Installation
In your Node.js project folder, run:
```bash
npm install ftdi-d2xx
```

On the top of your JavaScript file, add:
```js
const FTDI = require('ftdi-d2xx'); // CommonJS syntax (.js files)
// import FTDI from 'ftdi-d2xx'; // ESM syntax (.mjs files)
```


## Quick example
```js
let device;

async function quick_example() {

  try {
    // Get the connected devices info list 
    const list = await FTDI.getDeviceInfoList();
    console.log(`${list.length} device${list.length>1?'s':''} found:`, list);
    
    // If there is at least one device connected
    if(list.length) {
  
      // Try to open the first device from the list
      device = await FTDI.openDevice(list[0].serial_number); // alternatively openDevice({ usb_loc_id: list[0].usb_loc_id });
      console.log(`One device open:`, device);

      // Setup the device
      device.setTimeouts(1000, 1000); // set the max TX and RX duration in ms
      device.purge(FTDI.FT_PURGE_RX); // purge the RX buffer from previous received data
      //device.setBaudRate(115200); // set the UART baud rate (bits per second)
      //device.setDataCharacteristics(FTDI.FT_BITS_8, FTDI.FT_STOP_BITS_1, FTDI.FT_PARITY_NONE);
  
      // Send data from the TXD pin of the device
      await device.write(Uint8Array.from([1, 2, 3, 4]));
      console.log(`Data sent successfully.`);
  
      // Wait to receive from the RXD pin
      console.log(`Trying to receive data...`);
      const response = await device.read(4); // expected response byte length (will return either if this is reached or after an RX timeout)
      console.log(`${response.byteLength} bytes were received:`, response);

      // If TXD and RXD pins are connected together, you should get Uint8Array(4)[1, 2, 3, 4] immediately
      // If not, you should get Uint8Array(0)[] after 1 second of timeout

      // Close the device (device object must then be recreated using openDevice)
      device.close();

      // Be careful "not to loose" the device object before closing it, otherwise
      // the device will likely stay open and you will not be able to re-open it.
    }
  } catch (e) {
    console.error(e);
  }
}

// Run the example
await quick_example();
```


## Docs
- [FTDI D2XX Programmer's Guide](https://ftdichip.com/wp-content/uploads/2020/08/D2XX_Programmers_GuideFT_000071.pdf)
- [ftdi-d2xx JavaScript implementation API](docs/Home.md)

> [!NOTE]
> On Windows, FT_Reload() is implemented under FTDI.setVIDPID().

> [!NOTE]
> See the included FTDI D2XX driver library versions in the [CHANGELOG.md](CHANGELOG.md) file.


## Note to Electron users

As you may already know, Electron runs in two processes: a **main process** and a **renderer process** ([more info here](https://www.electronjs.org/docs/latest/tutorial/process-model)).

For security reasons, in the newest releases of Electron, you can only access Node.js inside the **main process**. However, you probably want to interact with this API using buttons, or to display information in the **renderer process**. It lets you two options:

- ***Option 1*** : Accessing this API only inside a `preload.js` file which has access to Node.js and can also export globals to the **renderer process** (recommended):
  - This file shall be associated to the `BrowserWindow` of your application using `webPreferences.preload` field with `webPreferences.sandbox` set to `false` to enable external modules loading ([more info here](https://www.electronjs.org/docs/latest/tutorial/process-model#preload-scripts)).
  - This file shall contain (or require) all your functions calling this FTDI library.
  - This file shall contain a `contextBridge` to expose your functions globally to the renderer process ([more info here](https://www.electronjs.org/docs/latest/api/context-bridge#usage)).
  - **Important:** information exchanged in the pipe between **main process** and **renderer process** (Electron calls it IPC) is **serialized**. That means data is converted in a JSON-like file format before being passed. [Only these data types](https://developer.mozilla.org/en-US/docs/Web/API/Web_Workers_API/Structured_clone_algorithm#supported_types) are supported ([more info here](https://www.electronjs.org/docs/latest/tutorial/ipc#object-serialization)).
  - **Note:** for the above reason, exposing the `FTDI` library object or functions directly to the **renderer process** doesn't work (it would be a bad security practice anyway).
- ***Option 2*** : Disabling the security and allowing Node.js to run in the **renderer process** ([more info here](https://www.electronjs.org/docs/latest/tutorial/security#2-do-not-enable-nodejs-integration-for-remote-content) - not recommended).

> [!IMPORTANT]
> If you use a compiler for your Electron project and you get errors, make sure to exclude this library from compilation as a native library.


## To do
To be added if there is a need for it:
- [ ] Add `FT_SetEventNotification` in a separate worker, with JS event handlers
- [ ] Add `FT_Rescan`, `FT_CyclePort`, `FT_SetResetPipeRetryCount`, `FT_StopInTask`, `FT_RestartInTask`, `FT_SetDeadmanTimeout`. Hopefully with the latest drivers and recent hardware, these functions are not needed anymore.
- [ ] Add `FT_SetChars` function
- [ ] Add the other `FT_EE_*` functions


## Development
- [Download and install CMake](https://cmake.org/download/) on your computer
- Clone this repository, add your modifications if needed
- Run `npm install` inside the repository to install development dependencies locally (cmake-js and typedoc)
- Compile the code:
  - Running `npm run cmake:rebuild-debug` will rebuild the debug version of `ftdi-d2xx.node` for your platform and processor under `build/Debug`
  - Running `npm run cmake:rebuild-release` will build `ftdi-d2xx.platform.processor.node` under `build/Release`
  - Running `npm run cmake:clean` will clean the `build` folder
- Run `npm run node:test` to execute the `/test.js` file, which loads the Debug Build and runs basic initialization code followed by a REPL console to test function calls dynamically
- Run `npm run typedoc` to regenerate the API documentation
- Make a pull request to share your work


## Sponsor
The original work for the library wrapper has been sponsored by [ONWI](https://www.onwi.fr/), a small electronics design office and production unit based near Lyon, France.


## Licensing
This library is distributed under the terms of the [GNU LGPLv3](LICENSE).

It includes the official **libftd2xx** library provided by FTDI, which is released under their specific Driver Licence Terms (https://ftdichip.com/driver-licence-terms/). Please make sure you agree to all the License Terms before using this library. See the included library versions in the [CHANGELOG.md](CHANGELOG.md) file.

**libftd2xx** uses an unmodified version of libusb (http://libusb.info) which is distributed under the terms of the [GNU Lesser General Public License](https://www.gnu.org/licenses/lgpl-2.1.html). Source code for libusb is included in this distribution for reference (lib/libusb-source).
