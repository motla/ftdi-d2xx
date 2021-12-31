//TODO switch platforms
const FTDI = {
  ...require("./build/Release/ftdi-d2xx.node"),
  [Symbol.toStringTag]: "FTDI D2XX Driver"
}

// Export add-on object
module.exports = FTDI;