//TODO check node version

const os = require('os');

// Set add-on object name depending on the current system processor architecture
// and try to require it. It will throw an error if the file doesn't exist.

let os_type = os.type();
if(os_type == "Windows_NT") os_type = "Windows";

let os_arch = os.arch();
if(os_type == "Windows" && os_arch == "x64") os_arch = "AMD64";

try {
  module.exports = require(`./build/Release/ftdi-d2xx.${os_type}.${os_arch}.node`);
} catch (e) {

  //TODO manage errors other than file not found
  
  try {
    if(os.arch() == "x86" || os.arch() == "x64") {
      module.exports = require(`./build/Release/ftdi-d2xx.${os_type}.x86_64.node`);
    } else throw(true);
  } catch (e) {
    throw(new Error(`ftdi-d2xx: Library executable was not found for this architecture (${os_type}/${os_arch}). Run "cmake-js rebuild" from the ftdi-d2xx folder.`));
  }
}