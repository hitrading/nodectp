const helper = require('./helper');
class Market {
  constructor(ctp) {
    this.ctp = ctp;
    this._regsiterHandlers();
  }

  _regsiterHandlers() {
    const md = this.ctp.md;
    const allProps = helper.getAllProperties(this);
    allProps.forEach((prop) => {
      if (/^on[A-Z][a-zA-Z]*$/.test(prop)) {
        md.on(prop.slice(2), this[prop].bind(this));
      }
    });
  }

  // onFrontConnected() {

  // }

  // onFrontDisconnected(nReason) {

  // }

  // onRspUserLogin(data, rsp, nReqId, bIsLast) {

  // }

  // onRspUserLogout(data, rsp, nReqId, bIsLast) {

  // }

  // onRspError(rsp, nReqId, bIsLast) {

  // }

  // onRspSubMarketData(data, rsp, nReqId, bIsLast) {

  // }

  // onRspUnSubMarketData(data, rsp, nReqId, bIsLast) {

  // }

  // onRspSubForQuoteRsp(data, rsp, nReqId, bIsLast) {

  // }

  // onRspUnSubForQuoteRsp(data, rsp, nReqId, bIsLast) {

  // }

  // onRtnForQuoteRsp(data) {

  // }

  // onRtnDepthMarketData(data) {

  // }

  // onRspQryMulticastInstrument(data, rsp, nReqId, bIsLast) {

  // }
}

module.exports = Market;


