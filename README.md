# warning
目前仅支持linux64和win64平台(win32平台未测试，理论上支持)

支持的nodejs版本: 8.x.x, 如: 8.16.1  ***(8以上版本不被支持)***

# compile
windows平台需要安装编译工具：`npm install --global --production windows-build-tools`

执行脚本：
```
npm run rebuild 或 yarn rebuild
```

# execute
run example
```
node ./example/ctpapp.js
```

# Example
请参看[example](https://github.com/iamweilee/nodectp-example.git)

# version
适配看穿式监管库, 实配的库版本: 6.3.15_20190220、v6.3.15_P2_mdapi_se_20190403 (实现了ctp所有的接口, 其中包含客户端认证及组播接口)

### 可能遇到的报错问题
执行 `yarn build` 命令时可能会遇到node.lib文件损坏的情况, 此时可去官网下载node.lib文件替换, 下载地址：[https://nodejs.org/dist/latest-v8.x/win-x64/node.lib]


### API

```
  WrapTd {}:
      - getApiVersion
      - init
      - release
      - dispose
      - createFtdcTraderApi
      - getTradingDay
      - registerFront
      - registerNameServer
      - registerFensUserInfo
      - subscribePrivateTopic
      - subscribePublicTopic
      - reqAuthenticate
      - reqUserLogin
      - reqUserLogout
      - reqUserPasswordUpdate
      - reqTradingAccountPasswordUpdate
      - reqOrderInsert
      - reqParkedOrderInsert
      - reqParkedOrderAction
      - reqOrderAction
      - reqQueryMaxOrderVolume
      - reqSettlementInfoConfirm
      - reqRemoveParkedOrder
      - reqRemoveParkedOrderAction
      - reqExecOrderInsert
      - reqExecOrderAction
      - reqForQuoteInsert
      - reqQuoteInsert
      - reqQuoteAction
      - reqBatchOrderAction
      - reqCombActionInsert
      - reqQryOrder
      - reqQryTrade
      - reqQryInvestorPosition
      - reqQryTradingAccount
      - reqQryInvestor
      - reqQryTradingCode
      - reqQryInstrumentMarginRate
      - reqQryInstrumentCommissionRate
      - reqQryExchange
      - reqQryProduct
      - reqQryInstrument
      - reqQryDepthMarketData
      - reqQrySettlementInfo
      - reqQryTransferBank
      - reqQryInvestorPositionDetail
      - reqQryNotice
      - reqQrySettlementInfoConfirm
      - reqQryCFMMCTradingAccountKey
      - reqQryEWarrantOffset
      - reqQryInvestorProductGroupMargin
      - reqQryExchangeMarginRate
      - reqQryExchangeMarginRateAdjust
      - reqQryExchangeRate
      - reqQrySecAgentACIDMap
      - reqQryProductExchRate
      - reqQryProductGroup
      - reqQryMMInstrumentCommissionRate
      - reqQryMMOptionInstrCommRate
      - reqQryInstrumentOrderCommRate
      - reqQryOptionInstrTradeCost
      - reqQryOptionInstrCommRate
      - reqQryExecOrder
      - reqQryForQuote
      - reqQryQuote
      - reqQryCombInstrumentGuard
      - reqQryCombAction
      - reqQryTransferSerial
      - reqQryAccountregister
      - reqQryContractBank
      - reqQryParkedOrder
      - reqQryParkedOrderAction
      - reqQryTradingNotice
      - reqQryBrokerTradingParams
      - reqQryBrokerTradingAlgos
      - reqQueryCFMMCTradingAccountToken
      - reqFromBankToFutureByFuture
      - reqFromFutureToBankByFuture
      - reqQueryBankAccountMoneyByFuture
      - reqQryInvestorPositionCombineDetail
      - registerUserSystemInfo
      - submitUserSystemInfo
      - reqUserAuthMethod
      - reqGenUserCaptcha
      - reqGenUserText
      - reqUserLoginWithCaptcha
      - reqUserLoginWithText
      - reqUserLoginWithOTP
      - reqQrySecAgentTradeInfo
      - reqQrySecAgentTradingAccount
      - reqQrySecAgentCheckMode
      - on
    
    callback events:
      - onFrontConnected
      - onFrontDisconnected
      - onHeartBeatWarning
      - onRspAuthenticate
      - onRspUserLogin
      - onRspUserLogout
      - onRspUserPasswordUpdate
      - onRspTradingAccountPasswordUpdate
      - onRspOrderInsert
      - onRspParkedOrderInsert
      - onRspParkedOrderAction
      - onRspOrderAction
      - onRspQueryMaxOrderVolume
      - onRspSettlementInfoConfirm
      - onRspRemoveParkedOrder
      - onRspRemoveParkedOrderAction
      - onRspExecOrderInsert
      - onRspExecOrderAction
      - onRspForQuoteInsert
      - onRspQuoteInsert
      - onRspQuoteAction
      - onRspBatchOrderAction
      - onRspCombActionInsert
      - onRspQryOrder
      - onRspQryTrade
      - onRspQryInvestorPosition
      - onRspQryTradingAccount
      - onRspQryInvestor
      - onRspQryTradingCode
      - onRspQryInstrumentMarginRate
      - onRspQryInstrumentCommissionRate
      - onRspQryExchange
      - onRspQryProduct
      - onRspQryInstrument
      - onRspQryDepthMarketData
      - onRspQrySettlementInfo
      - onRspQryTransferBank
      - onRspQryInvestorPositionDetail
      - onRspQryNotice
      - onRspQrySettlementInfoConfirm
      - onRspQryInvestorPositionCombineDetail
      - onRspQryCFMMCTradingAccountKey
      - onRspQryEWarrantOffset
      - onRspQryInvestorProductGroupMargin
      - onRspQryExchangeMarginRate
      - onRspQryExchangeMarginRateAdjust
      - onRspQryExchangeRate
      - onRspQrySecAgentACIDMap
      - onRspQryProductExchRate
      - onRspQryProductGroup
      - onRspQryMMInstrumentCommissionRate
      - onRspQryMMOptionInstrCommRate
      - onRspQryInstrumentOrderCommRate
      - onRspQryOptionInstrTradeCost
      - onRspQryOptionInstrCommRate
      - onRspQryExecOrder
      - onRspQryForQuote
      - onRspQryQuote
      - onRspQryCombInstrumentGuard
      - onRspQryCombAction
      - onRspQryTransferSerial
      - onRspQryAccountregister
      - onRspError
      - onRtnOrder
      - onRtnTrade
      - onErrRtnOrderInsert
      - onErrRtnOrderAction
      - onRtnInstrumentStatus
      - onRtnBulletin
      - onRtnTradingNotice
      - onRtnErrorConditionalOrder
      - onRtnExecOrder
      - onErrRtnExecOrderInsert
      - onErrRtnExecOrderAction
      - onErrRtnForQuoteInsert
      - onRtnQuote
      - onErrRtnQuoteInsert
      - onErrRtnQuoteAction
      - onRtnForQuoteRsp
      - onRtnCFMMCTradingAccountToken
      - onErrRtnBatchOrderAction
      - onRtnCombAction
      - onErrRtnCombActionInsert
      - onRspQryContractBank
      - onRspQryParkedOrder
      - onRspQryParkedOrderAction
      - onRspQryTradingNotice
      - onRspQryBrokerTradingParams
      - onRspQryBrokerTradingAlgos
      - onRspQueryCFMMCTradingAccountToken
      - onRtnFromBankToFutureByBank
      - onRtnFromFutureToBankByBank
      - onRtnRepealFromBankToFutureByBank
      - onRtnRepealFromFutureToBankByBank
      - onRtnFromBankToFutureByFuture
      - onRtnFromFutureToBankByFuture
      - onRtnRepealFromBankToFutureByFutureManual
      - onRtnRepealFromFutureToBankByFutureManual
      - onRtnQueryBankBalanceByFuture
      - onErrRtnBankToFutureByFuture
      - onErrRtnFutureToBankByFuture
      - onErrRtnRepealBankToFutureByFutureManual
      - onErrRtnRepealFutureToBankByFutureManual
      - onErrRtnQueryBankBalanceByFuture
      - onRtnRepealFromBankToFutureByFuture
      - onRtnRepealFromFutureToBankByFuture
      - onRspFromBankToFutureByFuture
      - onRspFromFutureToBankByFuture
      - onRspQueryBankAccountMoneyByFuture
      - onRtnOpenAccountByBank
      - onRtnCancelAccountByBank
      - onRtnChangeAccountByBank
      // 穿透式监管新增响应事件
      - onRspUserAuthMethod
      - onRspGenUserCaptcha
      - onRspGenUserText
      - onRspQrySecAgentTradeInfo
      - onRspQrySecAgentTradingAccount
      - onRspQrySecAgentCheckMode

  WrapMd {}:
      - init
      - release
      - dispose
      - createFtdcMdApi
      - getApiVersion
      - getTradingDay
      - registerFront
      - registerNameServer
      - registerFensUserInfo
      - reqUserLogin
      - reqUserLogout
      - subscribeMarketData
      - unSubscribeMarketData
      - subscribeForQuoteRsp
      - unSubscribeForQuoteRsp
      - reqQryMulticastInstrument
      - on
  
    callback events:
      - onFrontConnected
      - onFrontDisconnected
      - onHeartBeatWarning
      - onRspUserLogin
      - onRspUserLogout
      - onRspQryMulticastInstrument
      - onRspError
      - onRspSubMarketData
      - onRspUnSubMarketData
      - onRspSubForQuoteRsp
      - onRspUnSubForQuoteRsp
      - onRtnDepthMarketData
      - onRtnForQuoteRsp
```

### 适配Nan

参考 https://github.com/octalmage/robotjs/pull/523/files
