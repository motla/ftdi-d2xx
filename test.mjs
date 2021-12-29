import FTDI from "./main.mjs";

let devices = await FTDI.getDeviceInfoList();

console.log(`${devices.length} device(s) found:`, devices);
