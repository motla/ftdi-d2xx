const repl = require("repl");

// Load FTDI library
let FTDI;
try { FTDI = require("./build/Debug/ftdi-d2xx.node"); } // Try loading the Debug build, if any
catch (e) { FTDI = require("./main.js"); } // Else load the main.js file that loads the right Release build

// Print some testing
(async function () {
  try {
    const devices = await FTDI.getDeviceInfoList();
    console.log(`${devices.length} device${devices.length > 1 ? 's' : ''} found:`, devices);
  } catch(e) {
    console.error(e);
  }
  console.log("Write « FTDI » to access to the driver functions.");

  // Start REPL
  const cli = repl.start();
  cli.context.FTDI = FTDI;
})();