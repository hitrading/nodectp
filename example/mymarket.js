const { Market } = require('../index');

class MyMarket extends Market {

  onFrontConnected() {
    // super.onFrontConnected(...arguments);
    let { md, user, broker } = this.ctp;
    console.log('md ReqUserLogin : %s', md.reqUserLogin({ ...user, brokerId: broker.brokerId }, this.ctp.nReqId()));
  }

  onRspUserLogin(data, rsp, nReqId, bIsLast) {
    // super.onRspUserLogin(...arguments);
    console.log("md SubscribeMarketData:", this.ctp.md.subscribeMarketData(['sc1911']));
  }

  onRspSubMarketData(data, rsp, nReqId, bIsLast) {
    // super.onRspSubMarketData(...arguments);
  }

  onRspUnSubMarketData(data, rsp, nReqId, bIsLast) {
    // super.onRspUnSubMarketData(...arguments);
  }

  onRtnDepthMarketData(data) {
    // super.onRtnDepthMarketData(...arguments);
  }

}

module.exports = MyMarket;


