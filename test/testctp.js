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
        investorId: '369868',
        password: 'iguzhi'
    }
);

ctp.injectLogger();

ctp.createTdApi();
ctp.createMdApi();

// let td = ctp.td;
// let md = ctp.md;

// console.log(td)
// for(let i in td) {
//     console.log(i)
// };

// console.log(md)
// for(let j in md) {
//     console.log(j)
// };

ctp.td.on('FrontConnected', function() {
    console.log('td onFrontConnected')
    let { td, investor } = ctp;
    console.log('td ReqUserLogin : %s', td.reqUserLogin(investor, ctp.nRequestID()));
    console.log('td OnFrontConnected');
});

ctp.md.on('FrontConnected', function() {
    console.log('md onFrontConnected')
    let { md, investor } = ctp;
    console.log('md ReqUserLogin : %s', md.reqUserLogin(investor, ctp.nRequestID()));
    console.log('md OnFrontConnected');
    console.log(ctp.md.subscribeMarketData(['ag2012'], 1));
});

ctp.md.on('RtnDepthMarketData', function(data) {
    console.clear()
    console.log(data);
})


ctp.registerMdFront();
ctp.registerTdFront();
