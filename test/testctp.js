const XYCTP = require('../lib/ctp');

const ctp = new XYCTP({
  broker: {
    brokerId: '4040',
    brokerName: '银河期货',
    mdUrl: 'tcp://180.166.103.21:55213',
    tdUrl: 'tcp://180.166.103.21:55205'
  },
  user: {
    userId: '369868',
    password: 'iguzhi'
  }
});

ctp.td.on('FrontConnected', function() {
  console.log('td onFrontConnected')
  const { td, user } = ctp;
  console.log('td ReqUserLogin : %s', td.reqUserLogin(user, ctp.nReqId()));
  console.log('td OnFrontConnected');
});

ctp.md.on('FrontConnected', function() {
  console.log('md onFrontConnected')
  const { md, user } = ctp;
  console.log('md ReqUserLogin : %s', md.reqUserLogin(user, ctp.nReqId()));
  console.log('md OnFrontConnected');
  console.log(ctp.md.subscribeMarketData(['T2012'], 1));
});

ctp.md.on('RtnDepthMarketData', function(data) {
  // console.clear();
  console.log(data);
});

