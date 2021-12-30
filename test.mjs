import FTDI from "./main.js";

let devices = await FTDI.getDeviceInfoList();

console.log(`${devices.length} device(s) found:`, devices);
