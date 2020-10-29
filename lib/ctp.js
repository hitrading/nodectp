/**
 * 每一个交易帐号都需要实例化一个CTP
 */
require('../tool/env');
const helper = require('./helper');
const path = require('path');
const logger = require('./logger');
const shifctp = require('bindings')('shifctp');

const defaultFlowpath = './con';
const defaultMaxTryLoginTimes = 3;
const defaultMaxTryAuthTimes = 3;
let nRequestID = parseInt(new Date().getTime() / 1000);

class CTP {
  /**
   * @param {Object} setting 之所以很多key用的是首字母大写, 是为了对应ctp c++接口的数据类型字段
   * {
   *    flowpath: './con',// 流文件存放目录
   *    frontend: {
   *      BrokerID: '4040',// 银河期货
   *      MdURL: 'tcp://180.166.103.21:51213', 
   *      TdURL: 'tcp://180.166.103.21:51205'
   *    },
   *    maxTryLoginTimes: 10 // 最大尝试登录次数
   *    maxTryAuthTimes: 10 // 最大尝试认证次数
   * }
   * @param {Object} investor 投资者
   * @param {String} investor.InvestorID 投资者代码
   * @param {String} investor.Password 投资者交易帐号登录密码, 即所谓的交易密码
   */
  constructor(setting={}, investor) {
    this.setting = setting;
    this.investor = investor;
    this.init();
  }

  init() {
    let { flowpath, frontend, maxTryLoginTimes, maxTryAuthTimes } = this.setting;
    this.setting.flowpath = flowpath || defaultFlowpath;
    this.setting.maxTryLoginTimes = maxTryLoginTimes || defaultMaxTryLoginTimes;
    this.setting.maxTryAuthTimes = maxTryAuthTimes || defaultMaxTryAuthTimes;

    let investor = this.investor;
    investor.BrokerID = frontend.BrokerID;
    investor.AccountID = investor.InvestorID;
    investor.UserID = investor.InvestorID;
  }

  createMdApi() {
    let { flowpath, frontend } = this.setting;
    let mdFlowpath = path.join(flowpath, frontend.BrokerID + '-' + this.investor.InvestorID + '-' + 'md', '/');
    helper.ensureDirExists(mdFlowpath);
    this.createMd();
    this.md.CreateFtdcMdApi(mdFlowpath);
  }

  createTdApi() {
    let { flowpath, frontend } = this.setting;
    let tdFlowpath = path.join(flowpath, frontend.BrokerID + '-' + this.investor.InvestorID + '-' + 'td', '/');
    helper.ensureDirExists(tdFlowpath);
    this.createTd();
    this.td.CreateFtdcTraderApi(tdFlowpath);
  }

  registerMdFront() {
    let { md, setting } = this;
    md.RegisterFront(setting.frontend.MdURL);
    md.Init();
  }

  registerTdFront() {
    let { td, setting } = this;
    td.RegisterFront(setting.frontend.TdURL);
    td.Init();
  }

  dispose() {
    let { md, td, investor, nRequestID } = this;
    if (md) {
      md.ReqUserLogout(investor, nRequestID());
      md.Release();
    }

    if (td) {
      td.ReqUserLogout(investor, nRequestID());
      td.Release();
    }
  }

  getAddonPath() {
    return shifctp.path;
  }

  nRequestID() {
    return nRequestID++;
  }

  createMd() {
    this.md = shifctp.crmd();
  }

  createTd() {
    this.td = shifctp.crtd();
  }

  injectLogger(log4js) {
    logger.inject(log4js);
  }
}

module.exports = CTP;