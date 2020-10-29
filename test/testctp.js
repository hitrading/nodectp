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
// TODO: to check why has no any data responsed to this function
ctp.td.On('OnFrontConnected', function() {
  console.log('td OnFrontConnected');
  let { td, investor } = ctp;
  console.log('td ReqUserLogin : %s', td.ReqUserLogin(investor, ctp.nRequestID()));

});

ctp.md.On('OnFrontConnected', function() {

    let { md, investor } = ctp;
    console.log('md ReqUserLogin : %s', md.ReqUserLogin(investor, ctp.nRequestID()));
    console.log('md OnFrontConnected');
    console.log(ctp.md.SubscribeMarketData(['ru2101'], 1));
});

ctp.md.On('OnRtnDepthMarketData', function(data) {
    console.log(data);
})


ctp.registerMdFront();
