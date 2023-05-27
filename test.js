const repl = require("repl");
const fs = require("fs");

// Load FTDI library
fs.stat("./build/Debug/ftdi-d2xx.node", async (err) => { // Check if the Debug build exists
  let FTDI;
  if(!err) {
    console.log("test.js: Loading the Debug Build...")
    FTDI = require("./build/Debug/ftdi-d2xx.node"); // Try loading the Debug build, if any
  }
  else {
    console.log("test.js: Warning! Debug Build was not found under /build/Debug/ftdi-d2xx.node, loading the Release Build...")
    FTDI = require("./main.js"); // Else load the main.js file that loads the right Release build
  }

  // Print some testing
  try {
    const devices = await FTDI.getDeviceInfoList();
    console.log(`test.js: ${devices.length} device${devices.length > 1 ? 's' : ''} found:`, devices);
  } catch(e) {
    console.error(`test.js: ${e}`);
  }
  console.log("test.js: Write « FTDI » to access to the driver functions.");

  // Start REPL
  const cli = repl.start();
  cli.context.FTDI = FTDI;
});