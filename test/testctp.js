const XYCTP = require('../lib/ctp');

const ctp = new XYCTP({
  broker: {
    brokerId: '1010',
    brokerName: '认证测试',
    mdUrl: 'tcp://106.39.36.105:32213',
    tdUrl: 'tcp://106.39.36.105:32205'
  },
  user: {
    userId: '10000010',
    password: 'abc@123456'
  }
});

ctp.td.on('FrontConnected', function() {
  console.log('td onFrontConnected')
  const { td, user, broker } = ctp;
  td.reqAuthenticate({ authCode: 'YHQHYHQHYHQHYHQH', appId: 'client_ng_2.0.0', brokerId: broker.brokerId, userId: user.userId }, ctp.nReqId());

  console.log('td OnFrontConnected');
});

ctp.td.on('RspAuthenticate', function(data, rsp, nReqId, bIsLast) {
  console.log('td RspAuthenticate', data, rsp, nReqId, bIsLast);
  const { td, user, broker } = ctp;
  console.log('td reqUserLogin', td.reqUserLogin({ ...user, brokerId: broker.brokerId }, ctp.nReqId()));
});

ctp.td.on('RspUserLogin', function(data, rsp, nReqId, bIsLast) {
  console.log('td RspUserLogin', data, rsp, nReqId, bIsLast);
});

// ctp.md.on('FrontConnected', function() {
//   console.log('md onFrontConnected')
//   const { md, user } = ctp;
//   console.log('md ReqUserLogin : %s', md.reqUserLogin(user, ctp.nReqId()));
//   console.log('md OnFrontConnected');
//   console.log(ctp.md.subscribeMarketData(['T2012'], 1));
// });

// ctp.md.on('RtnDepthMarketData', function(data) {
//   // console.clear();
//   console.log(data);
// });

