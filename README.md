# FTDI D2XX Driver for Node.js
## Features
- Asynchronous, non-blocking functions (use [`Promises`](https://developer.mozilla.org/en-US/docs/Learn/JavaScript/Asynchronous/Promises) or [`async/await`](https://developer.mozilla.org/en-US/docs/Learn/JavaScript/Asynchronous/Async_await))
- Pre-compiled for Windows / macOS / Linux
- Compatible with [Electron](https://www.electronjs.org/)
- Includes static FTDI Driver vendor libraries
- Written in pure C language using [Node-API](https://nodejs.org/api/n-api.html#node-api)
- Detailed error messages and codes are thrown without crashing Node.js
- Includes TypeScript typings for auto-completion and validation
- Compiled with [CMake.js](https://github.com/cmake-js/cmake-js) (no `gyp` / no Python required)

## Installation
###### In your Node.js project:
```bash
npm install ftdi-d2xx
```

## Example
```js
const FTDI = require('ftdi-d2xx'); // CommonJS syntax
// import FTDI from 'ftdi-d2xx'; // ESM syntax

let devices = await FTDI.getDeviceInfoList();

console.log(`${devices.length} device(s) found:`, devices);
```

## To do
To be added if the community needs it:
- [ ] Add `FT_SetEventNotification` in a worker with JS event handlers
- [ ] Add `FT_Rescan`, `FT_Reload`, `FT_CyclePort`, `FT_Rescan`, `FT_Reload`, `FT_SetResetPipeRetryCount`, `FT_StopInTask`, `FT_RestartInTask`, `FT_SetDeadmanTimeout`. Hopefully with the latest drivers on recent hardware, these functions are not needed anymore.
- [ ] Add FT_SetChars function
- [ ] Add FT_EE* functions