const os = require('os');

// Set add-on object name depending on the current system processor architecture
// and try to export the correct add-on object if it exists, else throw an error

let os_type = os.type();
if(os_type == "Windows_NT") os_type = "Windows";

let os_arch = os.arch();
if(os_type == "Windows" && os_arch == "x64") os_arch = "AMD64";

try {
  module.exports = require(`./build/Release/ftdi-d2xx.${os_type}.${os_arch}.node`);
} catch (e) {
  try {
    if(os.arch() == "x86" || os.arch() == "x64") {
      module.exports = require(`./build/Release/ftdi-d2xx.${os_type}.x86_64.node`);
    } else throw(true);
  } catch (e) {
    throw(new Error(`ftdi-d2xx: The library has not been compiled for this architecture (${os_type}/${os_arch}). Run "cmake-js rebuild".`));
  }
}