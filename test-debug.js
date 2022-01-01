const FTDI = {
  ...require("./build/Debug/ftdi-d2xx.node"),
  [Symbol.toStringTag]: "FTDI D2XX Driver"
}

async function test () {

  try {
  
    let devices = await FTDI.getDeviceInfoList();
    
    console.log(`${devices.length} device(s) found:`, devices);
  
  } catch(e) {
  
    console.log(e);
  }
  
  console.log("ok");

}

test();