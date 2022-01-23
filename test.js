// Start REPL
var repl = require("repl");
var cli = repl.start();

// Load FTDI library
let FTDI;
try { FTDI = require("./build/Debug/ftdi-d2xx.node"); } // Try loading the Debug build, if any
catch (e) { FTDI = require("./main.js"); } // Else load the main.js file that loads the right Release build

// Expose FTDI to the REPL
cli.context.FTDI = FTDI;

// Print some testing
(async function () {

  try {
  
    let devices = await FTDI.getDeviceInfoList();
    cli.context.devices = devices;
    
    console.log(`${devices.length} device(s) found:`, devices);
  
  } catch(e) {
    console.log("Error!", e);
  }
  
})();