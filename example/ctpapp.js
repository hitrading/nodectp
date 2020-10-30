const CTP = require('../lib/ctp');
const Market = require('./mymarket');
const Trade = require('./mytrade');



const ctp = new CTP({
  broker: {
    brokerId: '4040',// 银河期货
    mdUrl: 'tcp://180.166.103.21:55213',
    tdUrl: 'tcp://180.166.103.21:55205'
  },
  user: {
    userId: '369868',
    password: 'iguzhi'
  }
});


new Market(ctp);
new Trade(
  ctp,
  {
    privateTopicMode: 0,
    publicTopicModel: 0
  }
);


// let { md, td } = ctp;
// // 调用交易相关接口, 具体有哪些接口请参看CTP文档
// td.ReqXXXXXX();
// // 调用行情相关接口, 具体有哪些接口请参看CTP文档
// md.ReqXXXXXX();
