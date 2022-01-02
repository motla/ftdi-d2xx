const FTDI = require("./main.js");

async function test () {

  try {
  
    let devices = await FTDI.listDevices();
    
    console.log(`${devices.length} device(s) found:`, devices);
  
  } catch(e) {
  
    console.log(e);
  }
  
  console.log("ok");

}

test();