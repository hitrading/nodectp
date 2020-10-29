let log4js = {
  getLogger() {},
  configure() {},
  trace() {},
  debug() {},
  info() {},
  warn() {},
  error() {},
  fatal() {},
};

const logger = {};

function initLog4js() {
  log4js = require('log4js');
  const _ = require('lodash');
  const helper = require('./helper');
  const path = require('path');
  const package = require('../package.json');
  const logsDir = `${getLogsDir()}/logs/${package.name}/`;
  helper.ensureDirExists(logsDir);

  const loggerCfg = {
    defaultLevel: 'ERROR',
    level: {
      market: 'INFO',
      trade: 'INFO',
      ctp: 'INFO',
    }
  };
  
  const configure = {
    appenders: {
      console: { type: 'console' }
    },
    categories: { default: { appenders: ['console'], level: 'info' } }
  };

  _.forEach(configure.appenders, function(appender, category) {
    logger[category] = log4js.getLogger(category);
    logger[category].level = loggerCfg.level[category] || loggerCfg.defaultLevel;
  });
  // maxLogSize是以byte为单位计算的
  _.forEach(loggerCfg.level, function(level, category) {
    configure.appenders[category] = { type: 'file', filename: logsDir + category + '.log', category: category, maxLogSize: 2048000, numBackups: 3, compress: true, encoding: 'utf-8' };
    configure.categories[category] = { appenders: [category], level: level || loggerCfg.defaultLevel };
  });
  
  log4js.configure(configure);

  function getLogsDir() {
    var dir = path.dirname(__filename), prev;
    while (true) {
      if (dir === '.') {
        // Avoids an infinite loop in rare cases, like the REPL
        dir = process.cwd();
      }
      var arr = dir.split(path.sep);
      if (arr && arr[arr.length - 1] === 'node_modules') {
        dir = path.join(dir, '..');
        return dir;
      }
      if (prev === dir) {
        // Got to the top
        dir = '.'
        return dir;
      }
      // Try the parent dir next
      prev = dir
      dir = path.join(dir, '..');
    }
  }
}


exports.inject = function(obj) {
  if (obj) {
    return log4js = obj;
  }
  initLog4js();
};

/**
 * 设置日志打印级别, 若level为undefined, 则针对所有类别的日志设置打印级别
 * @param {String} category 日志类别
 * @param {String} level 打印级别
 */
exports.setLevel = function(category, level) {
  if (level) {
    logger[category].level = level;
  }
  else {
    level = category;
    for (category in logger) {
      logger.hasOwnProperty(category) && (logger[category].level = level);
    }
  }
};

exports.getLogger = function(category) {
  return logger[category];
};
