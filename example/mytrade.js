const { Trade } = require('../index');

class MyTrade extends Trade {

	onFrontConnected() {
		super.onFrontConnected(...arguments);
		let { user, td, conf } = this.ctp;
		// 登录失败达到maxTryLoginTimes次, 则释放该账户的ctp对象
		if (!user.loginTimes || user.loginTimes < conf.maxLoginTimes) {
			user.loginTimes = user.loginTimes || 0;
			user.loginTimes++;

			this.logger && this.logger.info('ReqUserLogin : %s', td.reqUserLogin(user, this.ctp.nReqId()));
		}
		else {
			td.release();
			this.logger && this.logger.info('Try ReqUserLogin %s times by User: %j, but failed!', conf.maxLoginTimes, user);
		}
	}

	onRspUserLogin(data, rsp, nReqId, bIsLast) {
	  super.onRspUserLogin(...arguments);

	  let user = this.ctp.user;
	  // 投资者结算结果确认, 做完这一步才可以进行正常的交易
	  this.ctp.td.reqSettlementInfoConfirm({
	  	brokerId: user.brokerId,
	  	investorId: user.userId,
	  	confirmDate: data.tradingDay,
	  	confirmTime: data.shfeTime
	  }, this.ctp.nReqId());
	  // ctp.td.reqQryTradingAccount(user, ctp.nReqId());
	  //this.logger && this.logger.info('ReqQryTradingAccount=', ctp.td.reqQryTradingAccount(q, (new Date()).valueOf()/1000));
	  //sleep(2000);
	  //this.logger && this.logger.info('ReqQryInvestorPosition=', ctp.td.reqQryInvestorPosition(q, (new Date()).valueOf()/1000));
	  //this.logger && this.logger.info('ReqQryTrade=', ctp.td.reqQryTrade(q, (new Date()).valueOf()/1000));
	  //this.logger && this.logger.info('ReqQryOrder=', ctp.td.reqQryOrder(q, (new Date()).valueOf()/1000));
	  //this.logger && this.logger.info('ReqQryProduct=', ctp.td.reqQryProduct(q, (new Date()).valueOf()/1000));
	  //this.logger && this.logger.info('ReqQryInstrument=', ctp.td.reqQryInstrument(q, (new Date()).valueOf()/1000));
	  //this.logger && this.logger.info('-----before ReqQryContractBank-----')
	  // ctp.td.reqQryContractBank({
	  // 	bankId: '5',
			// bankBranchId: '0000',
			// brokerId: '4040',
	  // }, ctp.nReqId());
	  // this.logger && this.logger.info('-----after ReqQryContractBank-----')

	  //ReqFromBankToFutureByFuture
		// ctp.td.reqFromFutureToBankByFuture({
		// 	tradeCode: '202002',
		// 	bankId: '5',
		// 	BankBranchId: '0000',
		// 	brokerId: '4040',
		// 	bankAccount: '', // 是否必填, 不确定
		// 	bankPassWord: '',
		// 	accountId: user.userId,
		// 	password: user.fundPassword,
		// 	secuPwdFlag: '1',// 明文核对
		// 	currencyId: 'CNY',
		// 	tradeAmount: 2000
		// }, ctp.nReqId());

		// ctp.td.reqFromBankToFutureByFuture({
		// 	tradeCode: '202001',
		// 	bankId: '5',
		// 	bankBranchId: '0000',
		// 	brokerId: '4040',
		// 	bankAccount: '', // 是否必填, 不确定
		// 	bankPassWord: '',
		// 	accountId: user.userId,
		// 	password: user.fundPassword,
		// 	secuPwdFlag: '1',// 明文核对
		// 	currencyId: 'CNY',
		// 	tradeAmount: 2000
		// }, ctp.nReqId());
	}

	onRspUserLogout(data, rsp, nReqId, bIsLast) {
		super.onRspUserLogout(...arguments);
	}
	// 报单通知
	onRtnOrder(data) {
		super.onRtnOrder(...arguments);
	  // this.logger && this.logger.info('onRtnOrder: %j',  data)
	}
	// 成交通知
	onRtnTrade(data) {
		super.onRtnTrade(...arguments);
		// 在这里查资金状况, 根据判断发出通知和出金改密操作
		// 平仓: OffsetFlag==3, 开仓: OffsetFlag==0
		data.OffsetFlag != 0 && this.ctp.td.reqQryTradingAccount(this.ctp.user, this.ctp.nReqId());

	}

	onRspQryTradingAccount(data, rsp, nReqId, bIsLast) {
		super.onRspQryTradingAccount(...arguments);
	}

	onRspFromFutureToBankByFuture(data, rsp, nReqId, bIsLast) {
		super.onRspFromFutureToBankByFuture(...arguments);
	}

	onRspFromBankToFutureByFuture(data, rsp, nReqId, bIsLast) {
		super.onRspFromBankToFutureByFuture(...arguments);
		// ctp.td.ReqTradingAccountPasswordUpdate({
		// 	BrokerID: '4040',
		// 	AccountID: '',
		// 	OldPassword: '',
		// 	NewPassword: '',
		// 	CurrencyID: ''
		// }, ctp.nReqId());
	}

	onRspTradingAccountPasswordUpdate(data, rsp, nReqId, bIsLast) {
		super.onRspTradingAccountPasswordUpdate(...arguments);
	}

}

module.exports = MyTrade;
