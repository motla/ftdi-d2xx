# FTDI D2XX Driver for Node.js
## Features
- Updated to the latest FTDI D2XX driver libraries
- 100% asynchronous (use [`Promises`](https://developer.mozilla.org/en-US/docs/Learn/JavaScript/Asynchronous/Promises) or [`async/await`](https://developer.mozilla.org/en-US/docs/Learn/JavaScript/Asynchronous/Async_await))
- Pre-compiled for Windows / macOS / Linux
- Uses Node-API and CMake
- ECMAScript / ES Module format

## Installation
```bash
npm install ftdi-d2xx
```

## Example
```js
import FTDI from 'ftdi-d2xx';

let devices = await FTDI.getDeviceInfoList();

console.log(`${devices.length} device(s) found:`, devices);
```