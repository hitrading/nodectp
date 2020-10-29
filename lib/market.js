const logger = require('./logger').getLogger('market');
const helper = require('./helper');

class Market {
  constructor(ctp) {
    this.ctp = ctp;
    this._init();
  }

  _init() {
    this.createApi();
    this._regsiterHandlers();
    this.registerFront();
  }

  _regsiterHandlers() {
    let md = this.ctp.md;
    let allProps = helper.getAllProperties(this);
    allProps.forEach((prop) => {
      if (/^on[a-zA-Z]+$/.test(prop)) {
        md.on(prop, this[prop].bind(this));
      }
    });
  }

  createApi() {
    this.ctp.createMdApi();
  }

  registerFront() {
    this.ctp.registerMdFront();
  }

  onFrontConnected() {
    logger.info('OnFrontConnected');
  }

  onFrontDisconnected(nReason) {
    logger.info('OnFrontDisconnected nReason: %s', nReason);
  }

  onRspUserLogin(data, rsp, nRequestID, bIsLast) {
    logger.info('OnRspUserLogin: %j, %j, %s, %s', data, rsp, nRequestID, bIsLast);
  }

  onRspUserLogout(data, rsp, nRequestID, bIsLast) {
    logger.info('OnRspUserLogout: %j, %j, %s, %s', data, rsp, nRequestID, bIsLast);
  }

  onRspError(rsp, nRequestID, bIsLast) {
    logger.info('OnRspError: %j, %s, %s', rsp, nRequestID, bIsLast);
  }

  onRspSubMarketData(data, rsp, nRequestID, bIsLast) {
    logger.info('OnRspSubMarketData: %j, %j, %s, %s', data, rsp, nRequestID, bIsLast);
  }

  onRspUnSubMarketData(data, rsp, nRequestID, bIsLast) {
    logger.info('OnRspSubMarketData: %j, %j, %s, %s', data, rsp, nRequestID, bIsLast);
  }

  onRspSubForQuoteRsp(data, rsp, nRequestID, bIsLast) {
    logger.info('OnRspSubForQuoteRsp: %j, %j, %s, %s', data, rsp, nRequestID, bIsLast);
  }

  onRspUnSubForQuoteRsp(data, rsp, nRequestID, bIsLast) {
    logger.info('OnRspUnSubForQuoteRsp: %j, %j, %s, %s', data, rsp, nRequestID, bIsLast);
  }

  onRtnForQuoteRsp(data) {
    logger.info('OnRtnForQuoteRsp: %j', data);
  }

  onRtnDepthMarketData(data) {
    logger.info('OnRtnDepthMarketData: %j', data);
  }

  onRspQryMulticastInstrument(data, rsp, nRequestID, bIsLast) {
    logger.info('OnRspQryMulticastInstrument: %j, %j, %s, %s', data, rsp, nRequestID, bIsLast);
  }
}

module.exports = Market;


