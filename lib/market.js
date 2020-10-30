const helper = require('./helper');

class Market {
  constructor(ctp, logger) {
    this.ctp = ctp;
    this.logger = logger;
    this._regsiterHandlers();
  }

  _regsiterHandlers() {
    const md = this.ctp.md;
    const allProps = helper.getAllProperties(this);
    allProps.forEach((prop) => {
      if (/^on[a-zA-Z]+$/.test(prop)) {
        md.on(prop.slice(2), this[prop].bind(this));
      }
    });
  }

  onFrontConnected() {
    this.logger && this.logger.info('OnFrontConnected');
  }

  onFrontDisconnected(nReason) {
    this.logger && this.logger.info('OnFrontDisconnected nReason: %s', nReason);
  }

  onRspUserLogin(data, rsp, nRequestID, bIsLast) {
    this.logger && this.logger.info('OnRspUserLogin: %j, %j, %s, %s', data, rsp, nRequestID, bIsLast);
  }

  onRspUserLogout(data, rsp, nRequestID, bIsLast) {
    this.logger && this.logger.info('OnRspUserLogout: %j, %j, %s, %s', data, rsp, nRequestID, bIsLast);
  }

  onRspError(rsp, nRequestID, bIsLast) {
    this.logger && this.logger.info('OnRspError: %j, %s, %s', rsp, nRequestID, bIsLast);
  }

  onRspSubMarketData(data, rsp, nRequestID, bIsLast) {
    this.logger && this.logger.info('OnRspSubMarketData: %j, %j, %s, %s', data, rsp, nRequestID, bIsLast);
  }

  onRspUnSubMarketData(data, rsp, nRequestID, bIsLast) {
    this.logger && this.logger.info('OnRspSubMarketData: %j, %j, %s, %s', data, rsp, nRequestID, bIsLast);
  }

  onRspSubForQuoteRsp(data, rsp, nRequestID, bIsLast) {
    this.logger && this.logger.info('OnRspSubForQuoteRsp: %j, %j, %s, %s', data, rsp, nRequestID, bIsLast);
  }

  onRspUnSubForQuoteRsp(data, rsp, nRequestID, bIsLast) {
    this.logger && this.logger.info('OnRspUnSubForQuoteRsp: %j, %j, %s, %s', data, rsp, nRequestID, bIsLast);
  }

  onRtnForQuoteRsp(data) {
    this.logger && this.logger.info('OnRtnForQuoteRsp: %j', data);
  }

  onRtnDepthMarketData(data) {
    this.logger && this.logger.info('OnRtnDepthMarketData: %j', data);
  }

  onRspQryMulticastInstrument(data, rsp, nRequestID, bIsLast) {
    this.logger && this.logger.info('OnRspQryMulticastInstrument: %j, %j, %s, %s', data, rsp, nRequestID, bIsLast);
  }
}

module.exports = Market;


