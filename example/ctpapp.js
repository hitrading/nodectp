const CTP = require('../lib/ctp');
const Market = require('./mymarket');
const Trade = require('./mytrade');



let ctp = new CTP(
    {
        frontend: {
           	BrokerID: '4040',// 银河期货
           	MdURL: 'tcp://180.166.103.21:55213',
           	TdURL: 'tcp://180.166.103.21:55205'
        }
    },
    {
        InvestorID: '369868',
        Password: 'iguzhi'
    }
);

ctp.injectLogger();

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