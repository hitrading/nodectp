const fs = require('fs');
const dictCreator = require('../tool/dictcreator');

/**
 * 确保路径对应的目录存在, 若不存在则新建目录, 若存在则不做任何操作(支持多级目录)
 * @param {String} dirpath 目录路径
 */
exports.ensureDirExists =  function(dirpath) {
  let sep = /\//.test(dirpath) ? '/' : (/\\/.test(dirpath) ? '\\' : '');
  let pathArr = dirpath.split(sep);
  dirpath = '';
  pathArr.forEach((s, index) => {
    if (index === 0) {
      if (s === '') {
        dirpath += sep;
      }
      else if (s === '.') {
        dirpath += '.' + sep;
      }
      else {
        dirpath += s + sep;
      }
    }
    else {
      dirpath += s + sep;
    }

    if (fs.existsSync(dirpath)) {
      let stat = fs.lstatSync(dirpath);
      if (!stat.isDirectory()) {
        fs.mkdirSync(dirpath);
      }
    }
    else {
      fs.mkdirSync(dirpath);
    };
  })
};

exports.createDictFile = function() {
  dictCreator.create();
};

exports.getAllProperties = function(obj) {
  let allProps = [], curr = obj;
  do {
    let props = Object.getOwnPropertyNames(curr);
    props.forEach(function(prop) {
      if (allProps.indexOf(prop) === -1) {
        allProps.push(prop);
      }
    });
  } while(curr = Object.getPrototypeOf(curr))
  return allProps;
};

/**
 * Gets the root directory of a module, given an arbitrary filename
 * somewhere in the module tree. The "root directory" is the directory
 * containing the `package.json` file.
 *
 *   In:  /home/nate/node-native-module/lib/index.js
 *   Out: /home/nate/node-native-module
 */
exports.getRoot = require('bindings').getRoot;