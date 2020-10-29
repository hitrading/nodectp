const CTP = require('../lib/ctp');

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

ctp.createTdApi();
ctp.createMdApi();

// let td = ctp.td;
// let md = ctp.md;

// console.log(td)
// for(let i in td) {
//     console.log(i)
// };

ctp.md.On('OnFrontConnected', function() {

    let { md, investor } = ctp;
    console.log('ReqUserLogin : %s', md.ReqUserLogin(investor, ctp.nRequestID()));
    console.log('OnFrontConnected');
    console.log(ctp.md.SubscribeMarketData(['au1912'], 1));
});

ctp.md.On('OnRtnDepthMarketData', function(data) {
    console.log(data);
})


ctp.registerMdFront();