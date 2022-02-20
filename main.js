const os = require('os');

// Set add-on object name depending on the current system processor architecture
const node_library_file = `./build/Release/ftdi-d2xx.${os.type()}.${os.arch()}.node`;

// Try to export the correct add-on object if it exists, else throw an error
try {
  module.exports = require(node_library_file);
} catch (e) {
  throw(new Error(`ftdi-d2xx: The library has not been compiled for this architecture (${os.type()}/${os.arch()}). Run "cmake-js rebuild".`));
}