const CTP = require('../lib/ctp');

let ctp = new CTP(
    {
        frontend: {
           	brokerId: '4040',// 银河期货
           	mdUrl: 'tcp://180.166.103.21:55213',
           	tdUrl: 'tcp://180.166.103.21:55205'
        }
    },
    {
        investorId: '369863',
        password: 'iguzhi-1288'
    }
);

ctp.injectLogger();

ctp.createTdApi();
ctp.createMdApi();

let td = ctp.td;
let md = ctp.md;

console.log(td)
for(let i in td) {
    console.log(i)
};

console.log(md)
for(let j in md) {
    console.log(j)
};

// ctp.md.on('onFrontConnected', function() {
//     console.log('onFrontConnected')
//     let { md, investor } = ctp;
//     console.log('ReqUserLogin : %s', md.reqUserLogin(investor, ctp.nRequestID()));
//     console.log('OnFrontConnected');
//     console.log(ctp.md.subscribeMarketData(['T2012'], 1));
// });

// ctp.md.on('onRtnDepthMarketData', function(data) {
//     console.log(data);
// })


ctp.registerMdFront();
