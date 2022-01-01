const FTDI = require("./main.js");

try {

  let devices = await FTDI.getDeviceInfoList();
  
  console.log(`${devices.length} device(s) found:`, devices);

} catch(e) {

  console.log(e);
}

console.log("ok");