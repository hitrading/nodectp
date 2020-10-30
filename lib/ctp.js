/**
 * 每一个交易帐号都需要实例化一个CTP
 */
require('../tool/env');
const _ = require('lodash');
const helper = require('./helper');
const path = require('path');
const shifctp = require('bindings')('shifctp');

const defaultFlowpath = './con';
const defaultMaxLoginTimes = 3;
const defaultMaxAuthTimes = 3;
let nReqId = parseInt(new Date().getTime() / 1000);

class CTP {
  /**
   * @param {Object} conf
   * @param {String} conf.flowpath 流文件存放目录
   * @param {Number} conf.maxLoginTimes 最大尝试登录次数
   * @param {Number} conf.maxAuthTimes 最大尝试认证次数
   * @param {Boolean} conf.marketAutoInit 是否自动初始化行情网关
   * @param {Boolean} conf.tradeAutoInit 是否自动初始化交易网关
   * {
   *    flowpath: './con',// 流文件存放目录
   *    maxTryLoginTimes: 10 // 最大尝试登录次数
   *    maxTryAuthTimes: 10 // 最大尝试认证次数
   * }
   * @param {Object} broker
   * @param {String} broker.brokerId 经纪商代码
   * @param {String} broker.brokerName 经纪商名称
   * @param {String} broker.mdUrl 行情前置服务器地址
   * @param {String} broker.tdUrl 交易前置服务器地址
   * @param {Object} user
   * @param {String} user.userId 交易账号
   * @param {String} user.password 交易密码
   * @param {String} user.fundPassword 资金密码
   */
  constructor({ broker = {}, user = {} }, conf = {}) {
    this.broker = broker;
    this.user = user;
    this.conf = conf;
    this._init();
  }

  _init() {
    const { flowpath, maxLoginTimes, maxAuthTimes, marketAutoInit, tradeAutoInit } = this.conf;
    this.conf.flowpath = flowpath || defaultFlowpath;
    this.conf.maxLoginTimes = maxLoginTimes || defaultMaxLoginTimes;
    this.conf.maxAuthTimes = maxAuthTimes || defaultMaxAuthTimes;
    this.conf.marketAutoInit = _.isBoolean(marketAutoInit) ? marketAutoInit : true;
    this.conf.tradeAutoInit = _.isBoolean(tradeAutoInit) ? tradeAutoInit : true;

    if (this.conf.marketAutoInit) {
      this.initMarket();
    }

    if (this.conf.tradeAutoInit) {
      this.initTrade();
    }
  }

  initMarket() {
    this._createMdApi();
    this._connectMdFront();
  }

  initTrade() {
    this._createTdApi();
    this._connectTdFront();
  }

  _createMdApi() {
    const mdFlowpath = path.join(this.conf.flowpath, this.broker.brokerId + '-' + this.user.userId + '-' + 'md', '/');
    helper.ensureDirExists(mdFlowpath);
    this._createMd();
    this.md.createFtdcMdApi(mdFlowpath);
  }

  _createTdApi() {
    let tdFlowpath = path.join(this.conf.flowpath, this.broker.brokerId + '-' + this.user.userId + '-' + 'td', '/');
    helper.ensureDirExists(tdFlowpath);
    this._createTd();
    this.td.createFtdcTraderApi(tdFlowpath);
  }

  _connectMdFront() {
    const { md } = this;
    md.registerFront(this.broker.mdUrl);
    md.init();
  }

  _connectTdFront() {
    const { td } = this;
    td.registerFront(this.broker.tdUrl);
    td.init();
  }

  dispose() {
    const { md, td, user, nReqId } = this;
    if (md) {
      md.reqUserLogout(user, nReqId());
      md.release();
    }

    if (td) {
      td.reqUserLogout(user, nReqId());
      td.release();
    }
  }

  getAddonPath() {
    return shifctp.path;
  }

  nReqId() {
    return nReqId++;
  }

  _createMd() {
    this.md = shifctp.createMd();
  }

  _createTd() {
    this.td = shifctp.createTd();
  }

}

module.exports = CTP;
