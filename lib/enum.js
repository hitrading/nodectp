'use strict';

const Enum = require('microenum');

// 交易所属性类型
exports.ExchangePropertyType = new Enum(
  { alias: 'Normal', value: '0', text: '正常' },
  { alias: 'GenOrderByTrade', value: '1', text: '根据成交生成报单' },
);

// 证件类型类型
exports.IdCardTypeType = new Enum(
  { alias: 'EID', value: '0', text: '组织机构代码' },
  { alias: 'IDCard', value: '1', text: '中国公民身份证' },
  { alias: 'OfficerIDCard', value: '2', text: '军官证' },
  { alias: 'PoliceIDCard', value: '3', text: '警官证' },
  { alias: 'SoldierIDCard', value: '4', text: '士兵证' },
  { alias: 'HouseholdRegister', value: '5', text: '户口簿' },
  { alias: 'Passport', value: '6', text: '护照' },
  { alias: 'TaiwanCompatriotIDCard', value: '7', text: '台胞证' },
  { alias: 'HomeComingCard', value: '8', text: '回乡证' },
  { alias: 'LicenseNo', value: '9', text: '营业执照号' },
  { alias: 'TaxNo', value: 'A', text: '税务登记号当地纳税ID' },
  { alias: 'HMMainlandTravelPermit', value: 'B', text: '港澳居民来往内地通行证' },
  { alias: 'TwMainlandTravelPermit', value: 'C', text: '台湾居民来往大陆通行证' },
  { alias: 'DrivingLicense', value: 'D', text: '驾照' },
  { alias: 'SocialID', value: 'F', text: '当地社保ID' },
  { alias: 'LocalID', value: 'G', text: '当地身份证' },
  { alias: 'BusinessRegistration', value: 'H', text: '商业登记证' },
  { alias: 'HKMCIDCard', value: 'I', text: '港澳永久性居民身份证' },
  { alias: 'AccountsPermits', value: 'J', text: '人行开户许可证' },
  { alias: 'FrgPrmtRdCard', value: 'K', text: '外国人永久居留证' },
  { alias: 'CptMngPrdLetter', value: 'L', text: '资管产品备案函' },
  { alias: 'UniformSocialCreditCode', value: 'N', text: '统一社会信用代码' },
  { alias: 'CorporationCertNo', value: 'O', text: '机构成立证明文件' },
  { alias: 'OtherCard', value: 'x', text: '其他证件' },
);

// 投资者范围类型
exports.InvestorRangeType = new Enum(
  { alias: 'All', value: '1', text: '所有' },
  { alias: 'Group', value: '2', text: '投资者组' },
  { alias: 'Single', value: '3', text: '单一投资者' },
);

// 投资者范围类型
exports.DepartmentRangeType = new Enum(
  { alias: 'All', value: '1', text: '所有' },
  { alias: 'Group', value: '2', text: '组织架构' },
  { alias: 'Single', value: '3', text: '单一投资者' },
);

// 数据同步状态类型
exports.DataSyncStatusType = new Enum(
  { alias: 'Asynchronous', value: '1', text: '未同步' },
  { alias: 'Synchronizing', value: '2', text: '同步中' },
  { alias: 'Synchronized', value: '3', text: '已同步' },
);

// 经纪公司数据同步状态类型
exports.BrokerDataSyncStatusType = new Enum(
  { alias: 'Synchronized', value: '1', text: '已同步' },
  { alias: 'Synchronizing', value: '2', text: '同步中' },
);

// 交易所连接状态类型
exports.ExchangeConnectStatusType = new Enum(
  { alias: 'NoConnection', value: '1', text: '没有任何连接' },
  { alias: 'QryInstrumentSent', value: '2', text: '已经发出合约查询请求' },
  { alias: 'GotInformation', value: '9', text: '已经获取信息' },
);

// 交易所交易员连接状态类型
exports.TraderConnectStatusType = new Enum(
  { alias: 'NotConnected', value: '1', text: '没有任何连接' },
  { alias: 'Connected', value: '2', text: '已经连接' },
  { alias: 'QryInstrumentSent', value: '3', text: '已经发出合约查询请求' },
  { alias: 'SubPrivateFlow', value: '4', text: '订阅私有流' },
);

// 功能代码类型
exports.FunctionCodeType = new Enum(
  { alias: 'DataAsync', value: '1', text: '数据异步化' },
  { alias: 'ForceUserLogout', value: '2', text: '强制用户登出' },
  { alias: 'UserPasswordUpdate', value: '3', text: '变更管理用户口令' },
  { alias: 'BrokerPasswordUpdate', value: '4', text: '变更经纪公司口令' },
  { alias: 'InvestorPasswordUpdate', value: '5', text: '变更投资者口令' },
  { alias: 'OrderInsert', value: '6', text: '报单插入' },
  { alias: 'OrderAction', value: '7', text: '报单操作' },
  { alias: 'SyncSystemData', value: '8', text: '同步系统数据' },
  { alias: 'SyncBrokerData', value: '9', text: '同步经纪公司数据' },
  { alias: 'BachSyncBrokerData', value: 'A', text: '批量同步经纪公司数据' },
  { alias: 'SuperQuery', value: 'B', text: '超级查询' },
  { alias: 'ParkedOrderInsert', value: 'C', text: '预埋报单插入' },
  { alias: 'ParkedOrderAction', value: 'D', text: '预埋报单操作' },
  { alias: 'SyncOTP', value: 'E', text: '同步动态令牌' },
  { alias: 'DeleteOrder', value: 'F', text: '删除未知单' },
);

// 经纪公司功能代码类型
exports.BrokerFunctionCodeType = new Enum(
  { alias: 'ForceUserLogout', value: '1', text: '强制用户登出' },
  { alias: 'UserPasswordUpdate', value: '2', text: '变更用户口令' },
  { alias: 'SyncBrokerData', value: '3', text: '同步经纪公司数据' },
  { alias: 'BachSyncBrokerData', value: '4', text: '批量同步经纪公司数据' },
  { alias: 'OrderInsert', value: '5', text: '报单插入' },
  { alias: 'OrderAction', value: '6', text: '报单操作' },
  { alias: 'AllQuery', value: '7', text: '全部查询' },
  { alias: 'log', value: 'a', text: '系统功能：登入登出修改密码等' },
  { alias: 'BaseQry', value: 'b', text: '基本查询：查询基础数据，如合约，交易所等常量' },
  { alias: 'TradeQry', value: 'c', text: '交易查询：如查成交，委托' },
  { alias: 'Trade', value: 'd', text: '交易功能：报单，撤单' },
  { alias: 'Virement', value: 'e', text: '银期转账' },
  { alias: 'Risk', value: 'f', text: '风险监控' },
  { alias: 'Session', value: 'g', text: '查询管理：查询会话，踢人等' },
  { alias: 'RiskNoticeCtl', value: 'h', text: '风控通知控制' },
  { alias: 'RiskNotice', value: 'i', text: '风控通知发送' },
  { alias: 'BrokerDeposit', value: 'j', text: '察看经纪公司资金权限' },
  { alias: 'QueryFund', value: 'k', text: '资金查询' },
  { alias: 'QueryOrder', value: 'l', text: '报单查询' },
  { alias: 'QueryTrade', value: 'm', text: '成交查询' },
  { alias: 'QueryPosition', value: 'n', text: '持仓查询' },
  { alias: 'QueryMarketData', value: 'o', text: '行情查询' },
  { alias: 'QueryUserEvent', value: 'p', text: '用户事件查询' },
  { alias: 'QueryRiskNotify', value: 'q', text: '风险通知查询' },
  { alias: 'QueryFundChange', value: 'r', text: '出入金查询' },
  { alias: 'QueryInvestor', value: 's', text: '投资者信息查询' },
  { alias: 'QueryTradingCode', value: 't', text: '交易编码查询' },
  { alias: 'ForceClose', value: 'u', text: '强平' },
  { alias: 'PressTest', value: 'v', text: '压力测试' },
  { alias: 'RemainCalc', value: 'w', text: '权益反算' },
  { alias: 'NetPositionInd', value: 'x', text: '净持仓保证金指标' },
  { alias: 'RiskPredict', value: 'y', text: '风险预算' },
  { alias: 'DataExport', value: 'z', text: '数据导出' },
  { alias: 'RiskTargetSetup', value: 'A', text: '风控指标设置' },
  { alias: 'MarketDataWarn', value: 'B', text: '行情预警' },
  { alias: 'QryBizNotice', value: 'C', text: '业务通知查询' },
  { alias: 'CfgBizNotice', value: 'D', text: '业务通知模板设置' },
  { alias: 'SyncOTP', value: 'E', text: '同步动态令牌' },
  { alias: 'SendBizNotice', value: 'F', text: '发送业务通知' },
  { alias: 'CfgRiskLevelStd', value: 'G', text: '风险级别标准设置' },
  { alias: 'TbCommand', value: 'H', text: '交易终端应急功能' },
  { alias: 'DeleteOrder', value: 'J', text: '删除未知单' },
  { alias: 'ParkedOrderInsert', value: 'K', text: '预埋报单插入' },
  { alias: 'ParkedOrderAction', value: 'L', text: '预埋报单操作' },
  { alias: 'ExecOrderNoCheck', value: 'M', text: '资金不够仍允许行权' },
  { alias: 'Designate', value: 'N', text: '指定' },
  { alias: 'StockDisposal', value: 'O', text: '证券处置' },
  { alias: 'BrokerDepositWarn', value: 'Q', text: '席位资金预警' },
  { alias: 'CoverWarn', value: 'S', text: '备兑不足预警' },
  { alias: 'PreExecOrder', value: 'T', text: '行权试算' },
  { alias: 'ExecOrderRisk', value: 'P', text: '行权交收风险' },
  { alias: 'PosiLimitWarn', value: 'U', text: '持仓限额预警' },
  { alias: 'QryPosiLimit', value: 'V', text: '持仓限额查询' },
  { alias: 'FBSign', value: 'W', text: '银期签到签退' },
  { alias: 'FBAccount', value: 'X', text: '银期签约解约' },
);

// 报单操作状态类型
exports.OrderActionStatusType = new Enum(
  { alias: 'Submitted', value: 'a', text: '已经提交' },
  { alias: 'Accepted', value: 'b', text: '已经接受' },
  { alias: 'Rejected', value: 'c', text: '已经被拒绝' },
);

// 报单状态类型
exports.OrderStatusType = new Enum(
  { alias: 'AllTraded', value: '0', text: '全部成交' },
  { alias: 'PartTradedQueueing', value: '1', text: '部分成交还在队列中' },
  { alias: 'PartTradedNotQueueing', value: '2', text: '部分成交不在队列中' },
  { alias: 'NoTradeQueueing', value: '3', text: '未成交还在队列中' },
  { alias: 'NoTradeNotQueueing', value: '4', text: '未成交不在队列中' },
  { alias: 'Canceled', value: '5', text: '撤单' },
  { alias: 'Unknown', value: 'a', text: '未知' },
  { alias: 'NotTouched', value: 'b', text: '尚未触发' },
  { alias: 'Touched', value: 'c', text: '已触发' },
);

// 报单提交状态类型
exports.OrderSubmitStatusType = new Enum(
  { alias: 'InsertSubmitted', value: '0', text: '已经提交' },
  { alias: 'CancelSubmitted', value: '1', text: '撤单已经提交' },
  { alias: 'ModifySubmitted', value: '2', text: '修改已经提交' },
  { alias: 'Accepted', value: '3', text: '已经接受' },
  { alias: 'InsertRejected', value: '4', text: '报单已经被拒绝' },
  { alias: 'CancelRejected', value: '5', text: '撤单已经被拒绝' },
  { alias: 'ModifyRejected', value: '6', text: '改单已经被拒绝' },
);

// 持仓日期类型
exports.PositionDateType = new Enum(
  { alias: 'Today', value: '1', text: '今日持仓' },
  { alias: 'History', value: '2', text: '历史持仓' },
);

// 持仓日期类型类型
exports.PositionDateTypeType = new Enum(
  { alias: 'UseHistory', value: '1', text: '使用历史持仓' },
  { alias: 'NoUseHistory', value: '2', text: '不使用历史持仓' },
);

// 交易角色类型
exports.TradingRoleType = new Enum(
  { alias: 'Broker', value: '1', text: '代理' },
  { alias: 'Host', value: '2', text: '自营' },
  { alias: 'Maker', value: '3', text: '做市商' },
);

// 产品类型类型
exports.ProductClassType = new Enum(
  { alias: 'Futures', value: '1', text: '期货' },
  { alias: 'Options', value: '2', text: '期货期权' },
  { alias: 'Combination', value: '3', text: '组合' },
  { alias: 'Spot', value: '4', text: '即期' },
  { alias: 'EFP', value: '5', text: '期转现' },
  { alias: 'SpotOption', value: '6', text: '现货期权' },
  { alias: 'TAS', value: '7', text: 'TAS合约' },
  { alias: 'MI', value: 'I', text: '金属指数' },
);

// 产品类型类型
exports.APIProductClassType = new Enum(
  { alias: 'FutureSingle', value: '1', text: '期货单一合约' },
  { alias: 'OptionSingle', value: '2', text: '期权单一合约' },
  { alias: 'Futures', value: '3', text: '可交易期货(含期货组合和期货单一合约)' },
  { alias: 'Options', value: '4', text: '可交易期权(含期权组合和期权单一合约)' },
  { alias: 'TradingComb', value: '5', text: '可下单组合（目前包含DCE和ZCE的期货组合）' },
  { alias: 'UnTradingComb', value: '6', text: '可申请的组合（dce可以申请的组合合约 包含dce可以交易的合约）' },
  { alias: 'AllTrading', value: '7', text: '所有可以交易合约' },
  { alias: 'All', value: '8', text: '所有合约（包含不能交易合约 慎用）' },
);

// 合约生命周期状态类型
exports.InstLifePhaseType = new Enum(
  { alias: 'NotStart', value: '0', text: '未上市' },
  { alias: 'Started', value: '1', text: '上市' },
  { alias: 'Pause', value: '2', text: '停牌' },
  { alias: 'Expired', value: '3', text: '到期' },
);

// 买卖方向类型
exports.DirectionType = new Enum(
  { alias: 'Buy', value: '0', text: '买' },
  { alias: 'Sell', value: '1', text: '卖' },
);

// 持仓类型类型
exports.PositionTypeType = new Enum(
  { alias: 'Net', value: '1', text: '净持仓' },
  { alias: 'Gross', value: '2', text: '综合持仓' },
);

// 持仓多空方向类型
exports.PosiDirectionType = new Enum(
  { alias: 'Net', value: '1', text: '净' },
  { alias: 'Long', value: '2', text: '多头' },
  { alias: 'Short', value: '3', text: '空头' },
);

// 系统结算状态类型
exports.SysSettlementStatusType = new Enum(
  { alias: 'NonActive', value: '1', text: '不活跃' },
  { alias: 'Startup', value: '2', text: '启动' },
  { alias: 'Operating', value: '3', text: '操作' },
  { alias: 'Settlement', value: '4', text: '结算' },
  { alias: 'SettlementFinished', value: '5', text: '结算完成' },
);

// 费率属性类型
exports.RatioAttrType = new Enum(
  { alias: 'Trade', value: '0', text: '交易费率' },
  { alias: 'Settlement', value: '1', text: '结算费率' },
);

// 投机套保标志类型
exports.HedgeFlagType = new Enum(
  { alias: 'Speculation', value: '1', text: '投机' },
  { alias: 'Arbitrage', value: '2', text: '套利' },
  { alias: 'Hedge', value: '3', text: '套保' },
  { alias: 'MarketMaker', value: '5', text: '做市商' },
  { alias: 'SpecHedge', value: '6', text: '第一腿投机第二腿套保 大商所专用' },
  { alias: 'HedgeSpec', value: '7', text: '第一腿套保第二腿投机  大商所专用' },
);

// 投机套保标志类型
exports.BillHedgeFlagType = new Enum(
  { alias: 'Speculation', value: '1', text: '投机' },
  { alias: 'Arbitrage', value: '2', text: '套利' },
  { alias: 'Hedge', value: '3', text: '套保' },
);

// 交易编码类型类型
exports.ClientIDTypeType = new Enum(
  { alias: 'Speculation', value: '1', text: '投机' },
  { alias: 'Arbitrage', value: '2', text: '套利' },
  { alias: 'Hedge', value: '3', text: '套保' },
  { alias: 'MarketMaker', value: '5', text: '做市商' },
);

// 报单价格条件类型
exports.OrderPriceTypeType = new Enum(
  { alias: 'AnyPrice', value: '1', text: '任意价' },
  { alias: 'LimitPrice', value: '2', text: '限价' },
  { alias: 'BestPrice', value: '3', text: '最优价' },
  { alias: 'LastPrice', value: '4', text: '最新价' },
  { alias: 'LastPricePlusOneTicks', value: '5', text: '最新价浮动上浮1个ticks' },
  { alias: 'LastPricePlusTwoTicks', value: '6', text: '最新价浮动上浮2个ticks' },
  { alias: 'LastPricePlusThreeTicks', value: '7', text: '最新价浮动上浮3个ticks' },
  { alias: 'AskPrice1', value: '8', text: '卖一价' },
  { alias: 'AskPrice1PlusOneTicks', value: '9', text: '卖一价浮动上浮1个ticks' },
  { alias: 'AskPrice1PlusTwoTicks', value: 'A', text: '卖一价浮动上浮2个ticks' },
  { alias: 'AskPrice1PlusThreeTicks', value: 'B', text: '卖一价浮动上浮3个ticks' },
  { alias: 'BidPrice1', value: 'C', text: '买一价' },
  { alias: 'BidPrice1PlusOneTicks', value: 'D', text: '买一价浮动上浮1个ticks' },
  { alias: 'BidPrice1PlusTwoTicks', value: 'E', text: '买一价浮动上浮2个ticks' },
  { alias: 'BidPrice1PlusThreeTicks', value: 'F', text: '买一价浮动上浮3个ticks' },
  { alias: 'FiveLevelPrice', value: 'G', text: '五档价' },
);

// 开平标志类型
exports.OffsetFlagType = new Enum(
  { alias: 'Open', value: '0', text: '开仓' },
  { alias: 'Close', value: '1', text: '平仓' },
  { alias: 'ForceClose', value: '2', text: '强平' },
  { alias: 'CloseToday', value: '3', text: '平今' },
  { alias: 'CloseYesterday', value: '4', text: '平昨' },
  { alias: 'ForceOff', value: '5', text: '强减' },
  { alias: 'LocalForceClose', value: '6', text: '本地强平' },
);

// 强平原因类型
exports.ForceCloseReasonType = new Enum(
  { alias: 'NotForceClose', value: '0', text: '非强平' },
  { alias: 'LackDeposit', value: '1', text: '资金不足' },
  { alias: 'ClientOverPositionLimit', value: '2', text: '客户超仓' },
  { alias: 'MemberOverPositionLimit', value: '3', text: '会员超仓' },
  { alias: 'NotMultiple', value: '4', text: '持仓非整数倍' },
  { alias: 'Violation', value: '5', text: '违规' },
  { alias: 'Other', value: '6', text: '其它' },
  { alias: 'PersonDeliv', value: '7', text: '自然人临近交割' },
);

// 报单类型类型
exports.OrderTypeType = new Enum(
  { alias: 'Normal', value: '0', text: '正常' },
  { alias: 'DeriveFromQuote', value: '1', text: '报价衍生' },
  { alias: 'DeriveFromCombination', value: '2', text: '组合衍生' },
  { alias: 'Combination', value: '3', text: '组合报单' },
  { alias: 'ConditionalOrder', value: '4', text: '条件单' },
  { alias: 'Swap', value: '5', text: '互换单' },
  { alias: 'DeriveFromBlockTrade', value: '6', text: '大宗交易成交衍生' },
  { alias: 'DeriveFromEFPTrade', value: '7', text: '期转现成交衍生' },
);

// 有效期类型类型
exports.TimeConditionType = new Enum(
  { alias: 'IOC', value: '1', text: '立即完成，否则撤销' },
  { alias: 'GFS', value: '2', text: '本节有效' },
  { alias: 'GFD', value: '3', text: '当日有效' },
  { alias: 'GTD', value: '4', text: '指定日期前有效' },
  { alias: 'GTC', value: '5', text: '撤销前有效' },
  { alias: 'GFA', value: '6', text: '集合竞价有效' },
);

// 成交量类型类型
exports.VolumeConditionType = new Enum(
  { alias: 'AV', value: '1', text: '任何数量' },
  { alias: 'MV', value: '2', text: '最小数量' },
  { alias: 'CV', value: '3', text: '全部数量' },
);

// 触发条件类型
exports.ContingentConditionType = new Enum(
  { alias: 'Immediately', value: '1', text: '立即' },
  { alias: 'Touch', value: '2', text: '止损' },
  { alias: 'TouchProfit', value: '3', text: '止赢' },
  { alias: 'ParkedOrder', value: '4', text: '预埋单' },
  { alias: 'LastPriceGreaterThanStopPrice', value: '5', text: '最新价大于条件价' },
  { alias: 'LastPriceGreaterEqualStopPrice', value: '6', text: '最新价大于等于条件价' },
  { alias: 'LastPriceLesserThanStopPrice', value: '7', text: '最新价小于条件价' },
  { alias: 'LastPriceLesserEqualStopPrice', value: '8', text: '最新价小于等于条件价' },
  { alias: 'AskPriceGreaterThanStopPrice', value: '9', text: '卖一价大于条件价' },
  { alias: 'AskPriceGreaterEqualStopPrice', value: 'A', text: '卖一价大于等于条件价' },
  { alias: 'AskPriceLesserThanStopPrice', value: 'B', text: '卖一价小于条件价' },
  { alias: 'AskPriceLesserEqualStopPrice', value: 'C', text: '卖一价小于等于条件价' },
  { alias: 'BidPriceGreaterThanStopPrice', value: 'D', text: '买一价大于条件价' },
  { alias: 'BidPriceGreaterEqualStopPrice', value: 'E', text: '买一价大于等于条件价' },
  { alias: 'BidPriceLesserThanStopPrice', value: 'F', text: '买一价小于条件价' },
  { alias: 'BidPriceLesserEqualStopPrice', value: 'H', text: '买一价小于等于条件价' },
);

// 操作标志类型
exports.ActionFlagType = new Enum(
  { alias: 'Delete', value: '0', text: '删除' },
  { alias: 'Modify', value: '3', text: '修改' },
);

// 交易权限类型
exports.TradingRightType = new Enum(
  { alias: 'Allow', value: '0', text: '可以交易' },
  { alias: 'CloseOnly', value: '1', text: '只能平仓' },
  { alias: 'Forbidden', value: '2', text: '不能交易' },
);

// 报单来源类型
exports.OrderSourceType = new Enum(
  { alias: 'Participant', value: '0', text: '来自参与者' },
  { alias: 'Administrator', value: '1', text: '来自管理员' },
);

// 成交类型类型
exports.TradeTypeType = new Enum(
  { alias: 'SplitCombination', value: '#', text: '组合持仓拆分为单一持仓,初始化不应包含该类型的持仓' },
  { alias: 'Common', value: '0', text: '普通成交' },
  { alias: 'OptionsExecution', value: '1', text: '期权执行' },
  { alias: 'OTC', value: '2', text: 'OTC成交' },
  { alias: 'EFPDerived', value: '3', text: '期转现衍生成交' },
  { alias: 'CombinationDerived', value: '4', text: '组合衍生成交' },
  { alias: 'BlockTrade', value: '5', text: '大宗交易成交' },
);

// 特殊持仓明细标识类型
exports.SpecPosiTypeType = new Enum(
  { alias: 'Common', value: '#', text: '普通持仓明细' },
  { alias: 'Tas', value: '0', text: 'TAS合约成交产生的标的合约持仓明细' },
);

// 成交价来源类型
exports.PriceSourceType = new Enum(
  { alias: 'LastPrice', value: '0', text: '前成交价' },
  { alias: 'Buy', value: '1', text: '买委托价' },
  { alias: 'Sell', value: '2', text: '卖委托价' },
  { alias: 'OTC', value: '3', text: '场外成交价' },
);

// 合约交易状态类型
exports.InstrumentStatusType = new Enum(
  { alias: 'BeforeTrading', value: '0', text: '开盘前' },
  { alias: 'NoTrading', value: '1', text: '非交易' },
  { alias: 'Continous', value: '2', text: '连续交易' },
  { alias: 'AuctionOrdering', value: '3', text: '集合竞价报单' },
  { alias: 'AuctionBalance', value: '4', text: '集合竞价价格平衡' },
  { alias: 'AuctionMatch', value: '5', text: '集合竞价撮合' },
  { alias: 'Closed', value: '6', text: '收盘' },
);

// 品种进入交易状态原因类型
exports.InstStatusEnterReasonType = new Enum(
  { alias: 'Automatic', value: '1', text: '自动切换' },
  { alias: 'Manual', value: '2', text: '手动切换' },
  { alias: 'Fuse', value: '3', text: '熔断' },
);

// 处理状态类型
exports.BatchStatusType = new Enum(
  { alias: 'NoUpload', value: '1', text: '未上传' },
  { alias: 'Uploaded', value: '2', text: '已上传' },
  { alias: 'Failed', value: '3', text: '审核失败' },
);

// 按品种返还方式类型
exports.ReturnStyleType = new Enum(
  { alias: 'All', value: '1', text: '按所有品种' },
  { alias: 'ByProduct', value: '2', text: '按品种' },
);

// 返还模式类型
exports.ReturnPatternType = new Enum(
  { alias: 'ByVolume', value: '1', text: '按成交手数' },
  { alias: 'ByFeeOnHand', value: '2', text: '按留存手续费' },
);

// 返还级别类型
exports.ReturnLevelType = new Enum(
  { alias: 'Level1', value: '1', text: '级别1' },
  { alias: 'Level2', value: '2', text: '级别2' },
  { alias: 'Level3', value: '3', text: '级别3' },
  { alias: 'Level4', value: '4', text: '级别4' },
  { alias: 'Level5', value: '5', text: '级别5' },
  { alias: 'Level6', value: '6', text: '级别6' },
  { alias: 'Level7', value: '7', text: '级别7' },
  { alias: 'Level8', value: '8', text: '级别8' },
  { alias: 'Level9', value: '9', text: '级别9' },
);

// 返还标准类型
exports.ReturnStandardType = new Enum(
  { alias: 'ByPeriod', value: '1', text: '分阶段返还' },
  { alias: 'ByStandard', value: '2', text: '按某一标准' },
);

// 质押类型类型
exports.MortgageTypeType = new Enum(
  { alias: 'Out', value: '0', text: '质出' },
  { alias: 'In', value: '1', text: '质入' },
);

// 投资者结算参数代码类型
exports.InvestorSettlementParamIDType = new Enum(
  { alias: 'MortgageRatio', value: '4', text: '质押比例' },
  { alias: 'MarginWay', value: '5', text: '保证金算法' },
  { alias: 'BillDeposit', value: '9', text: '结算单结存是否包含质押' },
);

// 交易所结算参数代码类型
exports.ExchangeSettlementParamIDType = new Enum(
  { alias: 'MortgageRatio', value: '1', text: '质押比例' },
  { alias: 'OtherFundItem', value: '2', text: '分项资金导入项' },
  { alias: 'OtherFundImport', value: '3', text: '分项资金入交易所出入金' },
  { alias: 'CFFEXMinPrepa', value: '6', text: '中金所开户最低可用金额' },
  { alias: 'CZCESettlementType', value: '7', text: '郑商所结算方式' },
  { alias: 'ExchDelivFeeMode', value: '9', text: '交易所交割手续费收取方式' },
  { alias: 'DelivFeeMode', value: '0', text: '投资者交割手续费收取方式' },
  { alias: 'CZCEComMarginType', value: 'A', text: '郑商所组合持仓保证金收取方式' },
  { alias: 'DceComMarginType', value: 'B', text: '大商所套利保证金是否优惠' },
  { alias: 'OptOutDisCountRate', value: 'a', text: '虚值期权保证金优惠比率' },
  { alias: 'OptMiniGuarantee', value: 'b', text: '最低保障系数' },
);

// 系统参数代码类型
exports.SystemParamIDType = new Enum(
  { alias: 'InvestorIDMinLength', value: '1', text: '投资者代码最小长度' },
  { alias: 'AccountIDMinLength', value: '2', text: '投资者帐号代码最小长度' },
  { alias: 'UserRightLogon', value: '3', text: '投资者开户默认登录权限' },
  { alias: 'SettlementBillTrade', value: '4', text: '投资者交易结算单成交汇总方式' },
  { alias: 'TradingCode', value: '5', text: '统一开户更新交易编码方式' },
  { alias: 'CheckFund', value: '6', text: '结算是否判断存在未复核的出入金和分项资金' },
  { alias: 'CommModelRight', value: '7', text: '是否启用手续费模板数据权限' },
  { alias: 'MarginModelRight', value: '9', text: '是否启用保证金率模板数据权限' },
  { alias: 'IsStandardActive', value: '8', text: '是否规范用户才能激活' },
  { alias: 'UploadSettlementFile', value: 'U', text: '上传的交易所结算文件路径' },
  { alias: 'DownloadCSRCFile', value: 'D', text: '上报保证金监控中心文件路径' },
  { alias: 'SettlementBillFile', value: 'S', text: '生成的结算单文件路径' },
  { alias: 'CSRCOthersFile', value: 'C', text: '证监会文件标识' },
  { alias: 'InvestorPhoto', value: 'P', text: '投资者照片路径' },
  { alias: 'CSRCData', value: 'R', text: '全结经纪公司上传文件路径' },
  { alias: 'InvestorPwdModel', value: 'I', text: '开户密码录入方式' },
  { alias: 'CFFEXInvestorSettleFile', value: 'F', text: '投资者中金所结算文件下载路径' },
  { alias: 'InvestorIDType', value: 'a', text: '投资者代码编码方式' },
  { alias: 'FreezeMaxReMain', value: 'r', text: '休眠户最高权益' },
  { alias: 'IsSync', value: 'A', text: '手续费相关操作实时上场开关' },
  { alias: 'RelieveOpenLimit', value: 'O', text: '解除开仓权限限制' },
  { alias: 'IsStandardFreeze', value: 'X', text: '是否规范用户才能休眠' },
  { alias: 'CZCENormalProductHedge', value: 'B', text: '郑商所是否开放所有品种套保交易' },
);

// 交易系统参数代码类型
exports.TradeParamIDType = new Enum(
  { alias: 'EncryptionStandard', value: 'E', text: '系统加密算法' },
  { alias: 'RiskMode', value: 'R', text: '系统风险算法' },
  { alias: 'RiskModeGlobal', value: 'G', text: '系统风险算法是否全局 0-否 1-是' },
  { alias: 'modeEncode', value: 'P', text: '密码加密算法' },
  { alias: 'tickMode', value: 'T', text: '价格小数位数参数' },
  { alias: 'SingleUserSessionMaxNum', value: 'S', text: '用户最大会话数' },
  { alias: 'LoginFailMaxNum', value: 'L', text: '最大连续登录失败数' },
  { alias: 'IsAuthForce', value: 'A', text: '是否强制认证' },
  { alias: 'IsPosiFreeze', value: 'F', text: '是否冻结证券持仓' },
  { alias: 'IsPosiLimit', value: 'M', text: '是否限仓' },
  { alias: 'ForQuoteTimeInterval', value: 'Q', text: '郑商所询价时间间隔' },
  { alias: 'IsFuturePosiLimit', value: 'B', text: '是否期货限仓' },
  { alias: 'IsFutureOrderFreq', value: 'C', text: '是否期货下单频率限制' },
  { alias: 'IsExecOrderProfit', value: 'H', text: '行权冻结是否计算盈利' },
  { alias: 'IsCheckBankAcc', value: 'I', text: '银期开户是否验证开户银行卡号是否是预留银行账户' },
  { alias: 'PasswordDeadLine', value: 'J', text: '弱密码最后修改日期' },
  { alias: 'IsStrongPassword', value: 'K', text: '强密码校验' },
  { alias: 'BalanceMorgage', value: 'a', text: '自有资金质押比' },
  { alias: 'MinPwdLen', value: 'O', text: '最小密码长度' },
  { alias: 'LoginFailMaxNumForIP', value: 'U', text: 'IP当日最大登陆失败次数' },
  { alias: 'PasswordPeriod', value: 'V', text: '密码有效期' },
);

// 文件标识类型
exports.FileIDType = new Enum(
  { alias: 'SettlementFund', value: 'F', text: '资金数据' },
  { alias: 'Trade', value: 'T', text: '成交数据' },
  { alias: 'InvestorPosition', value: 'P', text: '投资者持仓数据' },
  { alias: 'SubEntryFund', value: 'O', text: '投资者分项资金数据' },
  { alias: 'CZCECombinationPos', value: 'C', text: '组合持仓数据' },
  { alias: 'CSRCData', value: 'R', text: '上报保证金监控中心数据' },
  { alias: 'CZCEClose', value: 'L', text: '郑商所平仓了结数据' },
  { alias: 'CZCENoClose', value: 'N', text: '郑商所非平仓了结数据' },
  { alias: 'PositionDtl', value: 'D', text: '持仓明细数据' },
  { alias: 'OptionStrike', value: 'S', text: '期权执行文件' },
  { alias: 'SettlementPriceComparison', value: 'M', text: '结算价比对文件' },
  { alias: 'NonTradePosChange', value: 'B', text: '上期所非持仓变动明细' },
);

// 文件上传类型类型
exports.FileTypeType = new Enum(
  { alias: 'Settlement', value: '0', text: '结算' },
  { alias: 'Check', value: '1', text: '核对' },
);

// 文件格式类型
exports.FileFormatType = new Enum(
  { alias: 'Txt', value: '0', text: '文本文件(.txt)' },
  { alias: 'Zip', value: '1', text: '压缩文件(.zip)' },
  { alias: 'DBF', value: '2', text: 'DBF文件(.dbf)' },
);

// 文件状态类型
exports.FileUploadStatusType = new Enum(
  { alias: 'SucceedUpload', value: '1', text: '上传成功' },
  { alias: 'FailedUpload', value: '2', text: '上传失败' },
  { alias: 'SucceedLoad', value: '3', text: '导入成功' },
  { alias: 'PartSucceedLoad', value: '4', text: '导入部分成功' },
  { alias: 'FailedLoad', value: '5', text: '导入失败' },
);

// 移仓方向类型
exports.TransferDirectionType = new Enum(
  { alias: 'Out', value: '0', text: '移出' },
  { alias: 'In', value: '1', text: '移入' },
);

// 特殊的创建规则类型
exports.SpecialCreateRuleType = new Enum(
  { alias: 'NoSpecialRule', value: '0', text: '没有特殊创建规则' },
  { alias: 'NoSpringFestival', value: '1', text: '不包含春节' },
);

// 挂牌基准价类型类型
exports.BasisPriceTypeType = new Enum(
  { alias: 'LastSettlement', value: '1', text: '上一合约结算价' },
  { alias: 'LaseClose', value: '2', text: '上一合约收盘价' },
);

// 产品生命周期状态类型
exports.ProductLifePhaseType = new Enum(
  { alias: 'Active', value: '1', text: '活跃' },
  { alias: 'NonActive', value: '2', text: '不活跃' },
  { alias: 'Canceled', value: '3', text: '注销' },
);

// 交割方式类型
exports.DeliveryModeType = new Enum(
  { alias: 'CashDeliv', value: '1', text: '现金交割' },
  { alias: 'CommodityDeliv', value: '2', text: '实物交割' },
);

// 出入金类型类型
exports.FundIOTypeType = new Enum(
  { alias: 'FundIO', value: '1', text: '出入金' },
  { alias: 'Transfer', value: '2', text: '银期转帐' },
  { alias: 'SwapCurrency', value: '3', text: '银期换汇' },
);

// 资金类型类型
exports.FundTypeType = new Enum(
  { alias: 'Deposite', value: '1', text: '银行存款' },
  { alias: 'ItemFund', value: '2', text: '分项资金' },
  { alias: 'Company', value: '3', text: '公司调整' },
  { alias: 'InnerTransfer', value: '4', text: '资金内转' },
);

// 出入金方向类型
exports.FundDirectionType = new Enum(
  { alias: 'In', value: '1', text: '入金' },
  { alias: 'Out', value: '2', text: '出金' },
);

// 资金状态类型
exports.FundStatusType = new Enum(
  { alias: 'Record', value: '1', text: '已录入' },
  { alias: 'Check', value: '2', text: '已复核' },
  { alias: 'Charge', value: '3', text: '已冲销' },
);

// 发布状态类型
exports.PublishStatusType = new Enum(
  { alias: 'None', value: '1', text: '未发布' },
  { alias: 'Publishing', value: '2', text: '正在发布' },
  { alias: 'Published', value: '3', text: '已发布' },
);

// 系统状态类型
exports.SystemStatusType = new Enum(
  { alias: 'NonActive', value: '1', text: '不活跃' },
  { alias: 'Startup', value: '2', text: '启动' },
  { alias: 'Initialize', value: '3', text: '交易开始初始化' },
  { alias: 'Initialized', value: '4', text: '交易完成初始化' },
  { alias: 'Close', value: '5', text: '收市开始' },
  { alias: 'Closed', value: '6', text: '收市完成' },
  { alias: 'Settlement', value: '7', text: '结算' },
);

// 结算状态类型
exports.SettlementStatusType = new Enum(
  { alias: 'Initialize', value: '0', text: '初始' },
  { alias: 'Settlementing', value: '1', text: '结算中' },
  { alias: 'Settlemented', value: '2', text: '已结算' },
  { alias: 'Finished', value: '3', text: '结算完成' },
);

// 投资者类型类型
exports.InvestorTypeType = new Enum(
  { alias: 'Person', value: '0', text: '自然人' },
  { alias: 'Company', value: '1', text: '法人' },
  { alias: 'Fund', value: '2', text: '投资基金' },
  { alias: 'SpecialOrgan', value: '3', text: '特殊法人' },
  { alias: 'Asset', value: '4', text: '资管户' },
);

// 经纪公司类型类型
exports.BrokerTypeType = new Enum(
  { alias: 'Trade', value: '0', text: '交易会员' },
  { alias: 'TradeSettle', value: '1', text: '交易结算会员' },
);

// 风险等级类型
exports.RiskLevelType = new Enum(
  { alias: 'Low', value: '1', text: '低风险客户' },
  { alias: 'Normal', value: '2', text: '普通客户' },
  { alias: 'Focus', value: '3', text: '关注客户' },
  { alias: 'Risk', value: '4', text: '风险客户' },
);

// 手续费收取方式类型
exports.FeeAcceptStyleType = new Enum(
  { alias: 'ByTrade', value: '1', text: '按交易收取' },
  { alias: 'ByDeliv', value: '2', text: '按交割收取' },
  { alias: 'None', value: '3', text: '不收' },
  { alias: 'FixFee', value: '4', text: '按指定手续费收取' },
);

// 密码类型类型
exports.PasswordTypeType = new Enum(
  { alias: 'Trade', value: '1', text: '交易密码' },
  { alias: 'Account', value: '2', text: '资金密码' },
);

// 盈亏算法类型
exports.AlgorithmType = new Enum(
  { alias: 'All', value: '1', text: '浮盈浮亏都计算' },
  { alias: 'OnlyLost', value: '2', text: '浮盈不计，浮亏计' },
  { alias: 'OnlyGain', value: '3', text: '浮盈计，浮亏不计' },
  { alias: 'None', value: '4', text: '浮盈浮亏都不计算' },
);

// 是否包含平仓盈利类型
exports.IncludeCloseProfitType = new Enum(
  { alias: 'Include', value: '0', text: '包含平仓盈利' },
  { alias: 'NotInclude', value: '2', text: '不包含平仓盈利' },
);

// 是否受可提比例限制类型
exports.AllWithoutTradeType = new Enum(
  { alias: 'Enable', value: '0', text: '无仓无成交不受可提比例限制' },
  { alias: 'Disable', value: '2', text: '受可提比例限制' },
  { alias: 'NoHoldEnable', value: '3', text: '无仓不受可提比例限制' },
);

// 资金密码核对标志类型
exports.FuturePwdFlagType = new Enum(
  { alias: 'UnCheck', value: '0', text: '不核对' },
  { alias: 'Check', value: '1', text: '核对' },
);

// 银期转账类型类型
exports.TransferTypeType = new Enum(
  { alias: 'BankToFuture', value: '0', text: '银行转期货' },
  { alias: 'FutureToBank', value: '1', text: '期货转银行' },
);

// 转账有效标志类型
exports.TransferValidFlagType = new Enum(
  { alias: 'Invalid', value: '0', text: '无效或失败' },
  { alias: 'Valid', value: '1', text: '有效' },
  { alias: 'Reverse', value: '2', text: '冲正' },
);

// 事由类型
exports.ReasonType = new Enum(
  { alias: 'CD', value: '0', text: '错单' },
  { alias: 'ZT', value: '1', text: '资金在途' },
  { alias: 'QT', value: '2', text: '其它' },
);

// 性别类型
exports.SexType = new Enum(
  { alias: 'None', value: '0', text: '未知' },
  { alias: 'Man', value: '1', text: '男' },
  { alias: 'Woman', value: '2', text: '女' },
);

// 用户类型类型
exports.UserTypeType = new Enum(
  { alias: 'Investor', value: '0', text: '投资者' },
  { alias: 'Operator', value: '1', text: '操作员' },
  { alias: 'SuperUser', value: '2', text: '管理员' },
);

// 费率类型类型
exports.RateTypeType = new Enum(
  { alias: 'MarginRate', value: '2', text: '保证金率' },
);

// 通知类型类型
exports.NoteTypeType = new Enum(
  { alias: 'TradeSettleBill', value: '1', text: '交易结算单' },
  { alias: 'TradeSettleMonth', value: '2', text: '交易结算月报' },
  { alias: 'CallMarginNotes', value: '3', text: '追加保证金通知书' },
  { alias: 'ForceCloseNotes', value: '4', text: '强行平仓通知书' },
  { alias: 'TradeNotes', value: '5', text: '成交通知书' },
  { alias: 'DelivNotes', value: '6', text: '交割通知书' },
);

// 结算单方式类型
exports.SettlementStyleType = new Enum(
  { alias: 'Day', value: '1', text: '逐日盯市' },
  { alias: 'Volume', value: '2', text: '逐笔对冲' },
);

// 结算单类型类型
exports.SettlementBillTypeType = new Enum(
  { alias: 'Day', value: '0', text: '日报' },
  { alias: 'Month', value: '1', text: '月报' },
);

// 客户权限类型类型
exports.UserRightTypeType = new Enum(
  { alias: 'Logon', value: '1', text: '登录' },
  { alias: 'Transfer', value: '2', text: '银期转帐' },
  { alias: 'EMail', value: '3', text: '邮寄结算单' },
  { alias: 'Fax', value: '4', text: '传真结算单' },
  { alias: 'ConditionOrder', value: '5', text: '条件单' },
);

// 保证金价格类型类型
exports.MarginPriceTypeType = new Enum(
  { alias: 'PreSettlementPrice', value: '1', text: '昨结算价' },
  { alias: 'SettlementPrice', value: '2', text: '最新价' },
  { alias: 'AveragePrice', value: '3', text: '成交均价' },
  { alias: 'OpenPrice', value: '4', text: '开仓价' },
);

// 结算单生成状态类型
exports.BillGenStatusType = new Enum(
  { alias: 'None', value: '0', text: '未生成' },
  { alias: 'NoGenerated', value: '1', text: '生成中' },
  { alias: 'Generated', value: '2', text: '已生成' },
);

// 算法类型类型
exports.AlgoTypeType = new Enum(
  { alias: 'HandlePositionAlgo', value: '1', text: '持仓处理算法' },
  { alias: 'FindMarginRateAlgo', value: '2', text: '寻找保证金率算法' },
);

// 持仓处理算法编号类型
exports.HandlePositionAlgoIDType = new Enum(
  { alias: 'Base', value: '1', text: '基本' },
  { alias: 'DCE', value: '2', text: '大连商品交易所' },
  { alias: 'CZCE', value: '3', text: '郑州商品交易所' },
);

// 寻找保证金率算法编号类型
exports.FindMarginRateAlgoIDType = new Enum(
  { alias: 'Base', value: '1', text: '基本' },
  { alias: 'DCE', value: '2', text: '大连商品交易所' },
  { alias: 'CZCE', value: '3', text: '郑州商品交易所' },
);

// 资金处理算法编号类型
exports.HandleTradingAccountAlgoIDType = new Enum(
  { alias: 'Base', value: '1', text: '基本' },
  { alias: 'DCE', value: '2', text: '大连商品交易所' },
  { alias: 'CZCE', value: '3', text: '郑州商品交易所' },
);

// 联系人类型类型
exports.PersonTypeType = new Enum(
  { alias: 'Order', value: '1', text: '指定下单人' },
  { alias: 'Open', value: '2', text: '开户授权人' },
  { alias: 'Fund', value: '3', text: '资金调拨人' },
  { alias: 'Settlement', value: '4', text: '结算单确认人' },
  { alias: 'Company', value: '5', text: '法人' },
  { alias: 'Corporation', value: '6', text: '法人代表' },
  { alias: 'LinkMan', value: '7', text: '投资者联系人' },
  { alias: 'Ledger', value: '8', text: '分户管理资产负责人' },
  { alias: 'Trustee', value: '9', text: '托（保）管人' },
  { alias: 'TrusteeCorporation', value: 'A', text: '托（保）管机构法人代表' },
  { alias: 'TrusteeOpen', value: 'B', text: '托（保）管机构开户授权人' },
  { alias: 'TrusteeContact', value: 'C', text: '托（保）管机构联系人' },
  { alias: 'ForeignerRefer', value: 'D', text: '境外自然人参考证件' },
  { alias: 'CorporationRefer', value: 'E', text: '法人代表参考证件' },
);

// 查询范围类型
exports.QueryInvestorRangeType = new Enum(
  { alias: 'All', value: '1', text: '所有' },
  { alias: 'Group', value: '2', text: '查询分类' },
  { alias: 'Single', value: '3', text: '单一投资者' },
);

// 投资者风险状态类型
exports.InvestorRiskStatusType = new Enum(
  { alias: 'Normal', value: '1', text: '正常' },
  { alias: 'Warn', value: '2', text: '警告' },
  { alias: 'Call', value: '3', text: '追保' },
  { alias: 'Force', value: '4', text: '强平' },
  { alias: 'Exception', value: '5', text: '异常' },
);

// 用户事件类型类型
exports.UserEventTypeType = new Enum(
  { alias: 'Login', value: '1', text: '登录' },
  { alias: 'Logout', value: '2', text: '登出' },
  { alias: 'Trading', value: '3', text: '交易成功' },
  { alias: 'TradingError', value: '4', text: '交易失败' },
  { alias: 'UpdatePassword', value: '5', text: '修改密码' },
  { alias: 'Authenticate', value: '6', text: '客户端认证' },
  { alias: 'SubmitSysInfo', value: '7', text: '终端信息上报' },
  { alias: 'Transfer', value: '8', text: '转账' },
  { alias: 'Other', value: '9', text: '其他' },
);

// 平仓方式类型
exports.CloseStyleType = new Enum(
  { alias: 'Close', value: '0', text: '先开先平' },
  { alias: 'CloseToday', value: '1', text: '先平今再平昨' },
);

// 预埋单状态类型
exports.ParkedOrderStatusType = new Enum(
  { alias: 'NotSend', value: '1', text: '未发送' },
  { alias: 'Send', value: '2', text: '已发送' },
  { alias: 'Deleted', value: '3', text: '已删除' },
);

// 处理状态类型
exports.VirDealStatusType = new Enum(
  { alias: 'Dealing', value: '1', text: '正在处理' },
  { alias: 'DeaclSucceed', value: '2', text: '处理成功' },
);

// 原有系统代码类型
exports.OrgSystemIDType = new Enum(
  { alias: 'Standard', value: '0', text: '综合交易平台' },
  { alias: 'ESunny', value: '1', text: '易盛系统' },
  { alias: 'KingStarV6', value: '2', text: '金仕达V6系统' },
);

// 交易状态类型
exports.VirTradeStatusType = new Enum(
  { alias: 'NaturalDeal', value: '0', text: '正常处理中' },
  { alias: 'SucceedEnd', value: '1', text: '成功结束' },
  { alias: 'FailedEND', value: '2', text: '失败结束' },
  { alias: 'Exception', value: '3', text: '异常中' },
  { alias: 'ManualDeal', value: '4', text: '已人工异常处理' },
  { alias: 'MesException', value: '5', text: '通讯异常 ，请人工处理' },
  { alias: 'SysException', value: '6', text: '系统出错，请人工处理' },
);

// 银行帐户类型类型
exports.VirBankAccTypeType = new Enum(
  { alias: 'BankBook', value: '1', text: '存折' },
  { alias: 'BankCard', value: '2', text: '储蓄卡' },
  { alias: 'CreditCard', value: '3', text: '信用卡' },
);

// 银行帐户类型类型
exports.VirementStatusType = new Enum(
  { alias: 'Natural', value: '0', text: '正常' },
  { alias: 'Canceled', value: '9', text: '销户' },
);

// 有效标志类型
exports.VirementAvailAbilityType = new Enum(
  { alias: 'NoAvailAbility', value: '0', text: '未确认' },
  { alias: 'AvailAbility', value: '1', text: '有效' },
  { alias: 'Repeal', value: '2', text: '冲正' },
);

// 交易代码类型
exports.VirementTradeCodeType = new Enum(
  { alias: 'BankBankToFuture', value: '102001', text: '银行发起银行资金转期货' },
  { alias: 'BankFutureToBank', value: '102002', text: '银行发起期货资金转银行' },
  { alias: 'FutureBankToFuture', value: '202001', text: '期货发起银行资金转期货' },
  { alias: 'FutureFutureToBank', value: '202002', text: '期货发起期货资金转银行' },
);

// Aml生成方式类型
exports.AMLGenStatusType = new Enum(
  { alias: 'Program', value: '0', text: '程序生成' },
  { alias: 'HandWork', value: '1', text: '人工生成' },
);

// 动态密钥类别(保证金监管)类型
exports.CFMMCKeyKindType = new Enum(
  { alias: 'REQUEST', value: 'R', text: '主动请求更新' },
  { alias: 'AUTO', value: 'A', text: 'CFMMC自动更新' },
  { alias: 'MANUAL', value: 'M', text: 'CFMMC手动更新' },
);

// 证件类型类型
exports.CertificationTypeType = new Enum(
  { alias: 'IDCard', value: '0', text: '身份证' },
  { alias: 'Passport', value: '1', text: '护照' },
  { alias: 'OfficerIDCard', value: '2', text: '军官证' },
  { alias: 'SoldierIDCard', value: '3', text: '士兵证' },
  { alias: 'HomeComingCard', value: '4', text: '回乡证' },
  { alias: 'HouseholdRegister', value: '5', text: '户口簿' },
  { alias: 'LicenseNo', value: '6', text: '营业执照号' },
  { alias: 'InstitutionCodeCard', value: '7', text: '组织机构代码证' },
  { alias: 'TempLicenseNo', value: '8', text: '临时营业执照号' },
  { alias: 'NoEnterpriseLicenseNo', value: '9', text: '民办非企业登记证书' },
  { alias: 'OtherCard', value: 'x', text: '其他证件' },
  { alias: 'SuperDepAgree', value: 'a', text: '主管部门批文' },
);

// 文件业务功能类型
exports.FileBusinessCodeType = new Enum(
  { alias: 'Others', value: '0', text: '其他' },
  { alias: 'TransferDetails', value: '1', text: '转账交易明细对账' },
  { alias: 'CustAccStatus', value: '2', text: '客户账户状态对账' },
  { alias: 'AccountTradeDetails', value: '3', text: '账户类交易明细对账' },
  { alias: 'FutureAccountChangeInfoDetails', value: '4', text: '期货账户信息变更明细对账' },
  { alias: 'CustMoneyDetail', value: '5', text: '客户资金台账余额明细对账' },
  { alias: 'CustCancelAccountInfo', value: '6', text: '客户销户结息明细对账' },
  { alias: 'CustMoneyResult', value: '7', text: '客户资金余额对账结果' },
  { alias: 'OthersExceptionResult', value: '8', text: '其它对账异常结果文件' },
  { alias: 'CustInterestNetMoneyDetails', value: '9', text: '客户结息净额明细' },
  { alias: 'CustMoneySendAndReceiveDetails', value: 'a', text: '客户资金交收明细' },
  { alias: 'CorporationMoneyTotal', value: 'b', text: '法人存管银行资金交收汇总' },
  { alias: 'MainbodyMoneyTotal', value: 'c', text: '主体间资金交收汇总' },
  { alias: 'MainPartMonitorData', value: 'd', text: '总分平衡监管数据' },
  { alias: 'PreparationMoney', value: 'e', text: '存管银行备付金余额' },
  { alias: 'BankMoneyMonitorData', value: 'f', text: '协办存管银行资金监管数据' },
);

// 汇钞标志类型
exports.CashExchangeCodeType = new Enum(
  { alias: 'Exchange', value: '1', text: '汇' },
  { alias: 'Cash', value: '2', text: '钞' },
);

// 是或否标识类型
exports.YesNoIndicatorType = new Enum(
  { alias: 'Yes', value: '0', text: '是' },
  { alias: 'No', value: '1', text: '否' },
);

// 余额类型类型
exports.BanlanceTypeType = new Enum(
  { alias: 'CurrentMoney', value: '0', text: '当前余额' },
  { alias: 'UsableMoney', value: '1', text: '可用余额' },
  { alias: 'FetchableMoney', value: '2', text: '可取余额' },
  { alias: 'FreezeMoney', value: '3', text: '冻结余额' },
);

// 性别类型
exports.GenderType = new Enum(
  { alias: 'Unknown', value: '0', text: '未知状态' },
  { alias: 'Male', value: '1', text: '男' },
  { alias: 'Female', value: '2', text: '女' },
);

// 费用支付标志类型
exports.FeePayFlagType = new Enum(
  { alias: 'BEN', value: '0', text: '由受益方支付费用' },
  { alias: 'OUR', value: '1', text: '由发送方支付费用' },
  { alias: 'SHA', value: '2', text: '由发送方支付发起的费用，受益方支付接受的费用' },
);

// 密钥类型类型
exports.PassWordKeyTypeType = new Enum(
  { alias: 'ExchangeKey', value: '0', text: '交换密钥' },
  { alias: 'PassWordKey', value: '1', text: '密码密钥' },
  { alias: 'MACKey', value: '2', text: 'MAC密钥' },
  { alias: 'MessageKey', value: '3', text: '报文密钥' },
);

// 密码类型类型
exports.FBTPassWordTypeType = new Enum(
  { alias: 'Query', value: '0', text: '查询' },
  { alias: 'Fetch', value: '1', text: '取款' },
  { alias: 'Transfer', value: '2', text: '转帐' },
  { alias: 'Trade', value: '3', text: '交易' },
);

// 加密方式类型
exports.FBTEncryModeType = new Enum(
  { alias: 'NoEncry', value: '0', text: '不加密' },
);

// 银行冲正标志类型
exports.BankRepealFlagType = new Enum(
  { alias: 'BankNotNeedRepeal', value: '0', text: '银行无需自动冲正' },
  { alias: 'BankWaitingRepeal', value: '1', text: '银行待自动冲正' },
  { alias: 'BankBeenRepealed', value: '2', text: '银行已自动冲正' },
);

// 期商冲正标志类型
exports.BrokerRepealFlagType = new Enum(
  { alias: 'BrokerNotNeedRepeal', value: '0', text: '期商无需自动冲正' },
  { alias: 'BrokerWaitingRepeal', value: '1', text: '期商待自动冲正' },
  { alias: 'BrokerBeenRepealed', value: '2', text: '期商已自动冲正' },
);

// 机构类别类型
exports.InstitutionTypeType = new Enum(
  { alias: 'Bank', value: '0', text: '银行' },
  { alias: 'Future', value: '1', text: '期商' },
  { alias: 'Store', value: '2', text: '券商' },
);

// 最后分片标志类型
exports.LastFragmentType = new Enum(
  { alias: 'Yes', value: '0', text: '是最后分片' },
  { alias: 'No', value: '1', text: '不是最后分片' },
);

// 银行账户状态类型
exports.BankAccStatusType = new Enum(
  { alias: 'Normal', value: '0', text: '正常' },
  { alias: 'Freeze', value: '1', text: '冻结' },
  { alias: 'ReportLoss', value: '2', text: '挂失' },
);

// 资金账户状态类型
exports.MoneyAccountStatusType = new Enum(
  { alias: 'Normal', value: '0', text: '正常' },
  { alias: 'Cancel', value: '1', text: '销户' },
);

// 存管状态类型
exports.ManageStatusType = new Enum(
  { alias: 'Point', value: '0', text: '指定存管' },
  { alias: 'PrePoint', value: '1', text: '预指定' },
  { alias: 'CancelPoint', value: '2', text: '撤销指定' },
);

// 应用系统类型类型
exports.SystemTypeType = new Enum(
  { alias: 'FutureBankTransfer', value: '0', text: '银期转帐' },
  { alias: 'StockBankTransfer', value: '1', text: '银证转帐' },
  { alias: 'TheThirdPartStore', value: '2', text: '第三方存管' },
);

// 银期转帐划转结果标志类型
exports.TxnEndFlagType = new Enum(
  { alias: 'NormalProcessing', value: '0', text: '正常处理中' },
  { alias: 'Success', value: '1', text: '成功结束' },
  { alias: 'Failed', value: '2', text: '失败结束' },
  { alias: 'Abnormal', value: '3', text: '异常中' },
  { alias: 'ManualProcessedForException', value: '4', text: '已人工异常处理' },
  { alias: 'CommuFailedNeedManualProcess', value: '5', text: '通讯异常 ，请人工处理' },
  { alias: 'SysErrorNeedManualProcess', value: '6', text: '系统出错，请人工处理' },
);

// 银期转帐服务处理状态类型
exports.ProcessStatusType = new Enum(
  { alias: 'NotProcess', value: '0', text: '未处理' },
  { alias: 'StartProcess', value: '1', text: '开始处理' },
  { alias: 'Finished', value: '2', text: '处理完成' },
);

// 客户类型类型
exports.CustTypeType = new Enum(
  { alias: 'Person', value: '0', text: '自然人' },
  { alias: 'Institution', value: '1', text: '机构户' },
);

// 银期转帐方向类型
exports.FBTTransferDirectionType = new Enum(
  { alias: 'FromBankToFuture', value: '1', text: '入金，银行转期货' },
  { alias: 'FromFutureToBank', value: '2', text: '出金，期货转银行' },
);

// 开销户类别类型
exports.OpenOrDestroyType = new Enum(
  { alias: 'Open', value: '1', text: '开户' },
  { alias: 'Destroy', value: '0', text: '销户' },
);

// 有效标志类型
exports.AvailabilityFlagType = new Enum(
  { alias: 'Invalid', value: '0', text: '未确认' },
  { alias: 'Valid', value: '1', text: '有效' },
  { alias: 'Repeal', value: '2', text: '冲正' },
);

// 机构类型类型
exports.OrganTypeType = new Enum(
  { alias: 'Bank', value: '1', text: '银行代理' },
  { alias: 'Future', value: '2', text: '交易前置' },
  { alias: 'PlateForm', value: '9', text: '银期转帐平台管理' },
);

// 机构级别类型
exports.OrganLevelType = new Enum(
  { alias: 'HeadQuarters', value: '1', text: '银行总行或期商总部' },
  { alias: 'Branch', value: '2', text: '银行分中心或期货公司营业部' },
);

// 协议类型类型
exports.ProtocalIDType = new Enum(
  { alias: 'FutureProtocal', value: '0', text: '期商协议' },
  { alias: 'ICBCProtocal', value: '1', text: '工行协议' },
  { alias: 'ABCProtocal', value: '2', text: '农行协议' },
  { alias: 'CBCProtocal', value: '3', text: '中国银行协议' },
  { alias: 'CCBProtocal', value: '4', text: '建行协议' },
  { alias: 'BOCOMProtocal', value: '5', text: '交行协议' },
  { alias: 'FBTPlateFormProtocal', value: 'X', text: '银期转帐平台协议' },
);

// 套接字连接方式类型
exports.ConnectModeType = new Enum(
  { alias: 'ShortConnect', value: '0', text: '短连接' },
  { alias: 'LongConnect', value: '1', text: '长连接' },
);

// 套接字通信方式类型
exports.SyncModeType = new Enum(
  { alias: 'ASync', value: '0', text: '异步' },
  { alias: 'Sync', value: '1', text: '同步' },
);

// 银行帐号类型类型
exports.BankAccTypeType = new Enum(
  { alias: 'BankBook', value: '1', text: '银行存折' },
  { alias: 'SavingCard', value: '2', text: '储蓄卡' },
  { alias: 'CreditCard', value: '3', text: '信用卡' },
);

// 期货公司帐号类型类型
exports.FutureAccTypeType = new Enum(
  { alias: 'BankBook', value: '1', text: '银行存折' },
  { alias: 'SavingCard', value: '2', text: '储蓄卡' },
  { alias: 'CreditCard', value: '3', text: '信用卡' },
);

// 接入机构状态类型
exports.OrganStatusType = new Enum(
  { alias: 'Ready', value: '0', text: '启用' },
  { alias: 'CheckIn', value: '1', text: '签到' },
  { alias: 'CheckOut', value: '2', text: '签退' },
  { alias: 'CheckFileArrived', value: '3', text: '对帐文件到达' },
  { alias: 'CheckDetail', value: '4', text: '对帐' },
  { alias: 'DayEndClean', value: '5', text: '日终清理' },
  { alias: 'Invalid', value: '9', text: '注销' },
);

// 建行收费模式类型
exports.CCBFeeModeType = new Enum(
  { alias: 'ByAmount', value: '1', text: '按金额扣收' },
  { alias: 'ByMonth', value: '2', text: '按月扣收' },
);

// 通讯API类型类型
exports.CommApiTypeType = new Enum(
  { alias: 'Client', value: '1', text: '客户端' },
  { alias: 'Server', value: '2', text: '服务端' },
  { alias: 'UserApi', value: '3', text: '交易系统的UserApi' },
);

// 连接状态类型
exports.LinkStatusType = new Enum(
  { alias: 'Connected', value: '1', text: '已经连接' },
  { alias: 'Disconnected', value: '2', text: '没有连接' },
);

// 密码核对标志类型
exports.PwdFlagType = new Enum(
  { alias: 'NoCheck', value: '0', text: '不核对' },
  { alias: 'BlankCheck', value: '1', text: '明文核对' },
  { alias: 'EncryptCheck', value: '2', text: '密文核对' },
);

// 期货帐号类型类型
exports.SecuAccTypeType = new Enum(
  { alias: 'AccountID', value: '1', text: '资金帐号' },
  { alias: 'CardID', value: '2', text: '资金卡号' },
  { alias: 'SHStockholderID', value: '3', text: '上海股东帐号' },
  { alias: 'SZStockholderID', value: '4', text: '深圳股东帐号' },
);

// 转账交易状态类型
exports.TransferStatusType = new Enum(
  { alias: 'Normal', value: '0', text: '正常' },
  { alias: 'Repealed', value: '1', text: '被冲正' },
);

// 发起方类型
exports.SponsorTypeType = new Enum(
  { alias: 'Broker', value: '0', text: '期商' },
  { alias: 'Bank', value: '1', text: '银行' },
);

// 请求响应类别类型
exports.ReqRspTypeType = new Enum(
  { alias: 'Request', value: '0', text: '请求' },
  { alias: 'Response', value: '1', text: '响应' },
);

// 银期转帐用户事件类型类型
exports.FBTUserEventTypeType = new Enum(
  { alias: 'SignIn', value: '0', text: '签到' },
  { alias: 'FromBankToFuture', value: '1', text: '银行转期货' },
  { alias: 'FromFutureToBank', value: '2', text: '期货转银行' },
  { alias: 'OpenAccount', value: '3', text: '开户' },
  { alias: 'CancelAccount', value: '4', text: '销户' },
  { alias: 'ChangeAccount', value: '5', text: '变更银行账户' },
  { alias: 'RepealFromBankToFuture', value: '6', text: '冲正银行转期货' },
  { alias: 'RepealFromFutureToBank', value: '7', text: '冲正期货转银行' },
  { alias: 'QueryBankAccount', value: '8', text: '查询银行账户' },
  { alias: 'QueryFutureAccount', value: '9', text: '查询期货账户' },
  { alias: 'SignOut', value: 'A', text: '签退' },
  { alias: 'SyncKey', value: 'B', text: '密钥同步' },
  { alias: 'ReserveOpenAccount', value: 'C', text: '预约开户' },
  { alias: 'CancelReserveOpenAccount', value: 'D', text: '撤销预约开户' },
  { alias: 'ReserveOpenAccountConfirm', value: 'E', text: '预约开户确认' },
  { alias: 'Other', value: 'Z', text: '其他' },
);

// 记录操作类型类型
exports.DBOperationType = new Enum(
  { alias: 'Insert', value: '0', text: '插入' },
  { alias: 'Update', value: '1', text: '更新' },
  { alias: 'Delete', value: '2', text: '删除' },
);

// 同步标记类型
exports.SyncFlagType = new Enum(
  { alias: 'Yes', value: '0', text: '已同步' },
  { alias: 'No', value: '1', text: '未同步' },
);

// 同步类型类型
exports.SyncTypeType = new Enum(
  { alias: 'OneOffSync', value: '0', text: '一次同步' },
  { alias: 'TimerSync', value: '1', text: '定时同步' },
  { alias: 'TimerFullSync', value: '2', text: '定时完全同步' },
);

// 换汇方向类型
exports.ExDirectionType = new Enum(
  { alias: 'Settlement', value: '0', text: '结汇' },
  { alias: 'Sale', value: '1', text: '售汇' },
);

// 换汇成功标志类型
exports.FBEResultFlagType = new Enum(
  { alias: 'Success', value: '0', text: '成功' },
  { alias: 'InsufficientBalance', value: '1', text: '账户余额不足' },
  { alias: 'UnknownTrading', value: '8', text: '交易结果未知' },
  { alias: 'Fail', value: 'x', text: '失败' },
);

// 换汇交易状态类型
exports.FBEExchStatusType = new Enum(
  { alias: 'Normal', value: '0', text: '正常' },
  { alias: 'ReExchange', value: '1', text: '交易重发' },
);

// 换汇文件标志类型
exports.FBEFileFlagType = new Enum(
  { alias: 'DataPackage', value: '0', text: '数据包' },
  { alias: 'File', value: '1', text: '文件' },
);

// 换汇已交易标志类型
exports.FBEAlreadyTradeType = new Enum(
  { alias: 'NotTrade', value: '0', text: '未交易' },
  { alias: 'Trade', value: '1', text: '已交易' },
);

// 银期换汇用户事件类型类型
exports.FBEUserEventTypeType = new Enum(
  { alias: 'SignIn', value: '0', text: '签到' },
  { alias: 'Exchange', value: '1', text: '换汇' },
  { alias: 'ReExchange', value: '2', text: '换汇重发' },
  { alias: 'QueryBankAccount', value: '3', text: '银行账户查询' },
  { alias: 'QueryExchDetial', value: '4', text: '换汇明细查询' },
  { alias: 'QueryExchSummary', value: '5', text: '换汇汇总查询' },
  { alias: 'QueryExchRate', value: '6', text: '换汇汇率查询' },
  { alias: 'CheckBankAccount', value: '7', text: '对账文件通知' },
  { alias: 'SignOut', value: '8', text: '签退' },
  { alias: 'Other', value: 'Z', text: '其他' },
);

// 换汇发送标志类型
exports.FBEReqFlagType = new Enum(
  { alias: 'UnProcessed', value: '0', text: '未处理' },
  { alias: 'WaitSend', value: '1', text: '等待发送' },
  { alias: 'SendSuccess', value: '2', text: '发送成功' },
  { alias: 'SendFailed', value: '3', text: '发送失败' },
  { alias: 'WaitReSend', value: '4', text: '等待重发' },
);

// 风险通知类型类型
exports.NotifyClassType = new Enum(
  { alias: 'NOERROR', value: '0', text: '正常' },
  { alias: 'Warn', value: '1', text: '警示' },
  { alias: 'Call', value: '2', text: '追保' },
  { alias: 'Force', value: '3', text: '强平' },
  { alias: 'CHUANCANG', value: '4', text: '穿仓' },
  { alias: 'Exception', value: '5', text: '异常' },
);

// 强平单类型类型
exports.ForceCloseTypeType = new Enum(
  { alias: 'Manual', value: '0', text: '手工强平' },
  { alias: 'Single', value: '1', text: '单一投资者辅助强平' },
  { alias: 'Group', value: '2', text: '批量投资者辅助强平' },
);

// 风险通知途径类型
exports.RiskNotifyMethodType = new Enum(
  { alias: 'System', value: '0', text: '系统通知' },
  { alias: 'SMS', value: '1', text: '短信通知' },
  { alias: 'EMail', value: '2', text: '邮件通知' },
  { alias: 'Manual', value: '3', text: '人工通知' },
);

// 风险通知状态类型
exports.RiskNotifyStatusType = new Enum(
  { alias: 'NotGen', value: '0', text: '未生成' },
  { alias: 'Generated', value: '1', text: '已生成未发送' },
  { alias: 'SendError', value: '2', text: '发送失败' },
  { alias: 'SendOk', value: '3', text: '已发送未接收' },
  { alias: 'Received', value: '4', text: '已接收未确认' },
  { alias: 'Confirmed', value: '5', text: '已确认' },
);

// 风控用户操作事件类型
exports.RiskUserEventType = new Enum(
  { alias: 'ExportData', value: '0', text: '导出数据' },
);

// 条件单索引条件类型
exports.ConditionalOrderSortTypeType = new Enum(
  { alias: 'LastPriceAsc', value: '0', text: '使用最新价升序' },
  { alias: 'LastPriceDesc', value: '1', text: '使用最新价降序' },
  { alias: 'AskPriceAsc', value: '2', text: '使用卖价升序' },
  { alias: 'AskPriceDesc', value: '3', text: '使用卖价降序' },
  { alias: 'BidPriceAsc', value: '4', text: '使用买价升序' },
  { alias: 'BidPriceDesc', value: '5', text: '使用买价降序' },
);

// 报送状态类型
exports.SendTypeType = new Enum(
  { alias: 'NoSend', value: '0', text: '未发送' },
  { alias: 'Sended', value: '1', text: '已发送' },
  { alias: 'Generated', value: '2', text: '已生成' },
  { alias: 'SendFail', value: '3', text: '报送失败' },
  { alias: 'Success', value: '4', text: '接收成功' },
  { alias: 'Fail', value: '5', text: '接收失败' },
  { alias: 'Cancel', value: '6', text: '取消报送' },
);

// 交易编码状态类型
exports.ClientIDStatusType = new Enum(
  { alias: 'NoApply', value: '1', text: '未申请' },
  { alias: 'Submited', value: '2', text: '已提交申请' },
  { alias: 'Sended', value: '3', text: '已发送申请' },
  { alias: 'Success', value: '4', text: '完成' },
  { alias: 'Refuse', value: '5', text: '拒绝' },
  { alias: 'Cancel', value: '6', text: '已撤销编码' },
);

// 特有信息类型类型
exports.QuestionTypeType = new Enum(
  { alias: 'Radio', value: '1', text: '单选' },
  { alias: 'Option', value: '2', text: '多选' },
  { alias: 'Blank', value: '3', text: '填空' },
);

// 业务类型类型
exports.BusinessTypeType = new Enum(
  { alias: 'Request', value: '1', text: '请求' },
  { alias: 'Response', value: '2', text: '应答' },
  { alias: 'Notice', value: '3', text: '通知' },
);

// 监控中心返回码类型
exports.CfmmcReturnCodeType = new Enum(
  { alias: 'Success', value: '0', text: '成功' },
  { alias: 'Working', value: '1', text: '该客户已经有流程在处理中' },
  { alias: 'InfoFail', value: '2', text: '监控中客户资料检查失败' },
  { alias: 'IDCardFail', value: '3', text: '监控中实名制检查失败' },
  { alias: 'OtherFail', value: '4', text: '其他错误' },
);

// 客户类型类型
exports.ClientTypeType = new Enum(
  { alias: 'All', value: '0', text: '所有' },
  { alias: 'Person', value: '1', text: '个人' },
  { alias: 'Company', value: '2', text: '单位' },
  { alias: 'Other', value: '3', text: '其他' },
  { alias: 'SpecialOrgan', value: '4', text: '特殊法人' },
  { alias: 'Asset', value: '5', text: '资管户' },
);

// 交易所编号类型
exports.ExchangeIDTypeType = new Enum(
  { alias: 'SHFE', value: 'S', text: '上海期货交易所' },
  { alias: 'CZCE', value: 'Z', text: '郑州商品交易所' },
  { alias: 'DCE', value: 'D', text: '大连商品交易所' },
  { alias: 'CFFEX', value: 'J', text: '中国金融期货交易所' },
  { alias: 'INE', value: 'N', text: '上海国际能源交易中心股份有限公司' },
);

// 交易编码类型类型
exports.ExClientIDTypeType = new Enum(
  { alias: 'Hedge', value: '1', text: '套保' },
  { alias: 'Arbitrage', value: '2', text: '套利' },
  { alias: 'Speculation', value: '3', text: '投机' },
);

// 更新状态类型
exports.UpdateFlagType = new Enum(
  { alias: 'NoUpdate', value: '0', text: '未更新' },
  { alias: 'Success', value: '1', text: '更新全部信息成功' },
  { alias: 'Fail', value: '2', text: '更新全部信息失败' },
  { alias: 'TCSuccess', value: '3', text: '更新交易编码成功' },
  { alias: 'TCFail', value: '4', text: '更新交易编码失败' },
  { alias: 'Cancel', value: '5', text: '已丢弃' },
);

// 申请动作类型
exports.ApplyOperateIDType = new Enum(
  { alias: 'OpenInvestor', value: '1', text: '开户' },
  { alias: 'ModifyIDCard', value: '2', text: '修改身份信息' },
  { alias: 'ModifyNoIDCard', value: '3', text: '修改一般信息' },
  { alias: 'ApplyTradingCode', value: '4', text: '申请交易编码' },
  { alias: 'CancelTradingCode', value: '5', text: '撤销交易编码' },
  { alias: 'CancelInvestor', value: '6', text: '销户' },
  { alias: 'FreezeAccount', value: '8', text: '账户休眠' },
  { alias: 'ActiveFreezeAccount', value: '9', text: '激活休眠账户' },
);

// 申请状态类型
exports.ApplyStatusIDType = new Enum(
  { alias: 'NoComplete', value: '1', text: '未补全' },
  { alias: 'Submited', value: '2', text: '已提交' },
  { alias: 'Checked', value: '3', text: '已审核' },
  { alias: 'Refused', value: '4', text: '已拒绝' },
  { alias: 'Deleted', value: '5', text: '已删除' },
);

// 发送方式类型
exports.SendMethodType = new Enum(
  { alias: 'ByAPI', value: '1', text: '文件发送' },
  { alias: 'ByFile', value: '2', text: '电子发送' },
);

// 操作方法类型
exports.EventModeType = new Enum(
  { alias: 'ADD', value: '1', text: '增加' },
  { alias: 'UPDATE', value: '2', text: '修改' },
  { alias: 'DELETE', value: '3', text: '删除' },
  { alias: 'CHECK', value: '4', text: '复核' },
  { alias: 'COPY', value: '5', text: '复制' },
  { alias: 'CANCEL', value: '6', text: '注销' },
  { alias: 'Reverse', value: '7', text: '冲销' },
);

// 统一开户申请自动发送类型
exports.UOAAutoSendType = new Enum(
  { alias: 'ASR', value: '1', text: '自动发送并接收' },
  { alias: 'ASNR', value: '2', text: '自动发送，不自动接收' },
  { alias: 'NSAR', value: '3', text: '不自动发送，自动接收' },
  { alias: 'NSR', value: '4', text: '不自动发送，也不自动接收' },
);

// 流程ID类型
exports.FlowIDType = new Enum(
  { alias: 'InvestorGroupFlow', value: '1', text: '投资者对应投资者组设置' },
  { alias: 'InvestorRate', value: '2', text: '投资者手续费率设置' },
  { alias: 'InvestorCommRateModel', value: '3', text: '投资者手续费率模板关系设置' },
);

// 复核级别类型
exports.CheckLevelType = new Enum(
  { alias: 'Zero', value: '0', text: '零级复核' },
  { alias: 'One', value: '1', text: '一级复核' },
  { alias: 'Two', value: '2', text: '二级复核' },
);

// 复核级别类型
exports.CheckStatusType = new Enum(
  { alias: 'Init', value: '0', text: '未复核' },
  { alias: 'Checking', value: '1', text: '复核中' },
  { alias: 'Checked', value: '2', text: '已复核' },
  { alias: 'Refuse', value: '3', text: '拒绝' },
  { alias: 'Cancel', value: '4', text: '作废' },
);

// 生效状态类型
exports.UsedStatusType = new Enum(
  { alias: 'Unused', value: '0', text: '未生效' },
  { alias: 'Used', value: '1', text: '已生效' },
  { alias: 'Fail', value: '2', text: '生效失败' },
);

// 账户来源类型
exports.BankAcountOriginType = new Enum(
  { alias: 'ByAccProperty', value: '0', text: '手工录入' },
  { alias: 'ByFBTransfer', value: '1', text: '银期转账' },
);

// 结算单月报成交汇总方式类型
exports.MonthBillTradeSumType = new Enum(
  { alias: 'ByInstrument', value: '0', text: '同日同合约' },
  { alias: 'ByDayInsPrc', value: '1', text: '同日同合约同价格' },
  { alias: 'ByDayIns', value: '2', text: '同合约' },
);

// 银期交易代码枚举类型
exports.FBTTradeCodeEnumType = new Enum(
  { alias: 'BankLaunchBankToBroker', value: '102001', text: '银行发起银行转期货' },
  { alias: 'BrokerLaunchBankToBroker', value: '202001', text: '期货发起银行转期货' },
  { alias: 'BankLaunchBrokerToBank', value: '102002', text: '银行发起期货转银行' },
  { alias: 'BrokerLaunchBrokerToBank', value: '202002', text: '期货发起期货转银行' },
);

// 动态令牌类型类型
exports.OTPTypeType = new Enum(
  { alias: 'NONE', value: '0', text: '无动态令牌' },
  { alias: 'TOTP', value: '1', text: '时间令牌' },
);

// 动态令牌状态类型
exports.OTPStatusType = new Enum(
  { alias: 'Unused', value: '0', text: '未使用' },
  { alias: 'Used', value: '1', text: '已使用' },
  { alias: 'Disuse', value: '2', text: '注销' },
);

// 经济公司用户类型类型
exports.BrokerUserTypeType = new Enum(
  { alias: 'Investor', value: '1', text: '投资者' },
  { alias: 'BrokerUser', value: '2', text: '操作员' },
);

// 期货类型类型
exports.FutureTypeType = new Enum(
  { alias: 'Commodity', value: '1', text: '商品期货' },
  { alias: 'Financial', value: '2', text: '金融期货' },
);

// 资金管理操作类型类型
exports.FundEventTypeType = new Enum(
  { alias: 'Restriction', value: '0', text: '转账限额' },
  { alias: 'TodayRestriction', value: '1', text: '当日转账限额' },
  { alias: 'Transfer', value: '2', text: '期商流水' },
  { alias: 'Credit', value: '3', text: '资金冻结' },
  { alias: 'InvestorWithdrawAlm', value: '4', text: '投资者可提资金比例' },
  { alias: 'BankRestriction', value: '5', text: '单个银行帐户转账限额' },
  { alias: 'Accountregister', value: '6', text: '银期签约账户' },
  { alias: 'ExchangeFundIO', value: '7', text: '交易所出入金' },
  { alias: 'InvestorFundIO', value: '8', text: '投资者出入金' },
);

// 资金账户来源类型
exports.AccountSourceTypeType = new Enum(
  { alias: 'FBTransfer', value: '0', text: '银期同步' },
  { alias: 'ManualEntry', value: '1', text: '手工录入' },
);

// 交易编码来源类型
exports.CodeSourceTypeType = new Enum(
  { alias: 'UnifyAccount', value: '0', text: '统一开户(已规范)' },
  { alias: 'ManualEntry', value: '1', text: '手工录入(未规范)' },
);

// 操作员范围类型
exports.UserRangeType = new Enum(
  { alias: 'All', value: '0', text: '所有' },
  { alias: 'Single', value: '1', text: '单一操作员' },
);

// 交易统计表按客户统计方式类型
exports.ByGroupType = new Enum(
  { alias: 'Investor', value: '2', text: '按投资者统计' },
  { alias: 'Group', value: '1', text: '按类统计' },
);

// 交易统计表按范围统计方式类型
exports.TradeSumStatModeType = new Enum(
  { alias: 'Instrument', value: '1', text: '按合约统计' },
  { alias: 'Product', value: '2', text: '按产品统计' },
  { alias: 'Exchange', value: '3', text: '按交易所统计' },
);

// 日期表达式设置类型类型
exports.ExprSetModeType = new Enum(
  { alias: 'Relative', value: '1', text: '相对已有规则设置' },
  { alias: 'Typical', value: '2', text: '典型设置' },
);

// 投资者范围类型
exports.RateInvestorRangeType = new Enum(
  { alias: 'All', value: '1', text: '公司标准' },
  { alias: 'Model', value: '2', text: '模板' },
  { alias: 'Single', value: '3', text: '单一投资者' },
);

// 主次用系统数据同步状态类型
exports.SyncDataStatusType = new Enum(
  { alias: 'Initialize', value: '0', text: '未同步' },
  { alias: 'Settlementing', value: '1', text: '同步中' },
  { alias: 'Settlemented', value: '2', text: '已同步' },
);

// 成交来源类型
exports.TradeSourceType = new Enum(
  { alias: 'NORMAL', value: '0', text: '来自交易所普通回报' },
  { alias: 'QUERY', value: '1', text: '来自查询' },
);

// 产品合约统计方式类型
exports.FlexStatModeType = new Enum(
  { alias: 'Product', value: '1', text: '产品统计' },
  { alias: 'Exchange', value: '2', text: '交易所统计' },
  { alias: 'All', value: '3', text: '统计所有' },
);

// 投资者范围统计方式类型
exports.ByInvestorRangeType = new Enum(
  { alias: 'Property', value: '1', text: '属性统计' },
  { alias: 'All', value: '2', text: '统计所有' },
);

// 投资者范围类型
exports.PropertyInvestorRangeType = new Enum(
  { alias: 'All', value: '1', text: '所有' },
  { alias: 'Property', value: '2', text: '投资者属性' },
  { alias: 'Single', value: '3', text: '单一投资者' },
);

// 文件状态类型
exports.FileStatusType = new Enum(
  { alias: 'NoCreate', value: '0', text: '未生成' },
  { alias: 'Created', value: '1', text: '已生成' },
  { alias: 'Failed', value: '2', text: '生成失败' },
);

// 文件生成方式类型
exports.FileGenStyleType = new Enum(
  { alias: 'FileTransmit', value: '0', text: '下发' },
  { alias: 'FileGen', value: '1', text: '生成' },
);

// 系统日志操作方法类型
exports.SysOperModeType = new Enum(
  { alias: 'Add', value: '1', text: '增加' },
  { alias: 'Update', value: '2', text: '修改' },
  { alias: 'Delete', value: '3', text: '删除' },
  { alias: 'Copy', value: '4', text: '复制' },
  { alias: 'AcTive', value: '5', text: '激活' },
  { alias: 'CanCel', value: '6', text: '注销' },
  { alias: 'ReSet', value: '7', text: '重置' },
);

// 系统日志操作类型类型
exports.SysOperTypeType = new Enum(
  { alias: 'UpdatePassword', value: '0', text: '修改操作员密码' },
  { alias: 'UserDepartment', value: '1', text: '操作员组织架构关系' },
  { alias: 'RoleManager', value: '2', text: '角色管理' },
  { alias: 'RoleFunction', value: '3', text: '角色功能设置' },
  { alias: 'BaseParam', value: '4', text: '基础参数设置' },
  { alias: 'SetUserID', value: '5', text: '设置操作员' },
  { alias: 'SetUserRole', value: '6', text: '用户角色设置' },
  { alias: 'UserIpRestriction', value: '7', text: '用户IP限制' },
  { alias: 'DepartmentManager', value: '8', text: '组织架构管理' },
  { alias: 'DepartmentCopy', value: '9', text: '组织架构向查询分类复制' },
  { alias: 'Tradingcode', value: 'A', text: '交易编码管理' },
  { alias: 'InvestorStatus', value: 'B', text: '投资者状态维护' },
  { alias: 'InvestorAuthority', value: 'C', text: '投资者权限管理' },
  { alias: 'PropertySet', value: 'D', text: '属性设置' },
  { alias: 'ReSetInvestorPasswd', value: 'E', text: '重置投资者密码' },
  { alias: 'InvestorPersonalityInfo', value: 'F', text: '投资者个性信息维护' },
);

// 上报数据查询类型类型
exports.CSRCDataQueyTypeType = new Enum(
  { alias: 'Current', value: '0', text: '查询当前交易日报送的数据' },
  { alias: 'History', value: '1', text: '查询历史报送的代理经纪公司的数据' },
);

// 休眠状态类型
exports.FreezeStatusType = new Enum(
  { alias: 'Normal', value: '1', text: '活跃' },
  { alias: 'Freeze', value: '0', text: '休眠' },
);

// 规范状态类型
exports.StandardStatusType = new Enum(
  { alias: 'Standard', value: '0', text: '已规范' },
  { alias: 'NonStandard', value: '1', text: '未规范' },
);

// 配置类型类型
exports.RightParamTypeType = new Enum(
  { alias: 'Freeze', value: '1', text: '休眠户' },
  { alias: 'FreezeActive', value: '2', text: '激活休眠户' },
  { alias: 'OpenLimit', value: '3', text: '开仓权限限制' },
  { alias: 'RelieveOpenLimit', value: '4', text: '解除开仓权限限制' },
);

// 反洗钱审核表数据状态类型
exports.DataStatusType = new Enum(
  { alias: 'Normal', value: '0', text: '正常' },
  { alias: 'Deleted', value: '1', text: '已删除' },
);

// 审核状态类型
exports.AMLCheckStatusType = new Enum(
  { alias: 'Init', value: '0', text: '未复核' },
  { alias: 'Checking', value: '1', text: '复核中' },
  { alias: 'Checked', value: '2', text: '已复核' },
  { alias: 'RefuseReport', value: '3', text: '拒绝上报' },
);

// 日期类型类型
exports.AmlDateTypeType = new Enum(
  { alias: 'DrawDay', value: '0', text: '检查日期' },
  { alias: 'TouchDay', value: '1', text: '发生日期' },
);

// 审核级别类型
exports.AmlCheckLevelType = new Enum(
  { alias: 'CheckLevel0', value: '0', text: '零级审核' },
  { alias: 'CheckLevel1', value: '1', text: '一级审核' },
  { alias: 'CheckLevel2', value: '2', text: '二级审核' },
  { alias: 'CheckLevel3', value: '3', text: '三级审核' },
);

// 结算配置类型类型
exports.SettleManagerTypeType = new Enum(
  { alias: 'Before', value: '1', text: '结算前准备' },
  { alias: 'Settlement', value: '2', text: '结算' },
  { alias: 'After', value: '3', text: '结算后核对' },
  { alias: 'Settlemented', value: '4', text: '结算后处理' },
);

// 结算配置等级类型
exports.SettleManagerLevelType = new Enum(
  { alias: 'Must', value: '1', text: '必要' },
  { alias: 'Alarm', value: '2', text: '警告' },
  { alias: 'Prompt', value: '3', text: '提示' },
  { alias: 'Ignore', value: '4', text: '不检查' },
);

// 模块分组类型
exports.SettleManagerGroupType = new Enum(
  { alias: 'Exhcange', value: '1', text: '交易所核对' },
  { alias: 'ASP', value: '2', text: '内部核对' },
  { alias: 'CSRC', value: '3', text: '上报数据核对' },
);

// 保值额度使用类型类型
exports.LimitUseTypeType = new Enum(
  { alias: 'Repeatable', value: '1', text: '可重复使用' },
  { alias: 'Unrepeatable', value: '2', text: '不可重复使用' },
);

// 数据来源类型
exports.DataResourceType = new Enum(
  { alias: 'Settle', value: '1', text: '本系统' },
  { alias: 'Exchange', value: '2', text: '交易所' },
  { alias: 'CSRC', value: '3', text: '报送数据' },
);

// 保证金类型类型
exports.MarginTypeType = new Enum(
  { alias: 'ExchMarginRate', value: '0', text: '交易所保证金率' },
  { alias: 'InstrMarginRate', value: '1', text: '投资者保证金率' },
  { alias: 'InstrMarginRateTrade', value: '2', text: '投资者交易保证金率' },
);

// 生效类型类型
exports.ActiveTypeType = new Enum(
  { alias: 'Intraday', value: '1', text: '仅当日生效' },
  { alias: 'Long', value: '2', text: '长期生效' },
);

// 冲突保证金率类型类型
exports.MarginRateTypeType = new Enum(
  { alias: 'Exchange', value: '1', text: '交易所保证金率' },
  { alias: 'Investor', value: '2', text: '投资者保证金率' },
  { alias: 'InvestorTrade', value: '3', text: '投资者交易保证金率' },
);

// 备份数据状态类型
exports.BackUpStatusType = new Enum(
  { alias: 'UnBak', value: '0', text: '未生成备份数据' },
  { alias: 'BakUp', value: '1', text: '备份数据生成中' },
  { alias: 'BakUped', value: '2', text: '已生成备份数据' },
  { alias: 'BakFail', value: '3', text: '备份数据失败' },
);

// 结算初始化状态类型
exports.InitSettlementType = new Enum(
  { alias: 'UnInitialize', value: '0', text: '结算初始化未开始' },
  { alias: 'Initialize', value: '1', text: '结算初始化中' },
  { alias: 'Initialized', value: '2', text: '结算初始化完成' },
);

// 报表数据生成状态类型
exports.ReportStatusType = new Enum(
  { alias: 'NoCreate', value: '0', text: '未生成报表数据' },
  { alias: 'Create', value: '1', text: '报表数据生成中' },
  { alias: 'Created', value: '2', text: '已生成报表数据' },
  { alias: 'CreateFail', value: '3', text: '生成报表数据失败' },
);

// 数据归档状态类型
exports.SaveStatusType = new Enum(
  { alias: 'UnSaveData', value: '0', text: '归档未完成' },
  { alias: 'SaveDatad', value: '1', text: '归档完成' },
);

// 结算确认数据归档状态类型
exports.SettArchiveStatusType = new Enum(
  { alias: 'UnArchived', value: '0', text: '未归档数据' },
  { alias: 'Archiving', value: '1', text: '数据归档中' },
  { alias: 'Archived', value: '2', text: '已归档数据' },
  { alias: 'ArchiveFail', value: '3', text: '归档数据失败' },
);

// CTP交易系统类型类型
exports.CTPTypeType = new Enum(
  { alias: 'Unkown', value: '0', text: '未知类型' },
  { alias: 'MainCenter', value: '1', text: '主中心' },
  { alias: 'BackUp', value: '2', text: '备中心' },
);

// 平仓处理类型类型
exports.CloseDealTypeType = new Enum(
  { alias: 'Normal', value: '0', text: '正常' },
  { alias: 'SpecFirst', value: '1', text: '投机平仓优先' },
);

// 货币质押资金可用范围类型
exports.MortgageFundUseRangeType = new Enum(
  { alias: 'None', value: '0', text: '不能使用' },
  { alias: 'Margin', value: '1', text: '用于保证金' },
  { alias: 'All', value: '2', text: '用于手续费、盈亏、保证金' },
  { alias: 'CNY3', value: '3', text: '人民币方案3' },
);

// 特殊产品类型类型
exports.SpecProductTypeType = new Enum(
  { alias: 'CzceHedge', value: '1', text: '郑商所套保产品' },
  { alias: 'IneForeignCurrency', value: '2', text: '货币质押产品' },
  { alias: 'DceOpenClose', value: '3', text: '大连短线开平仓产品' },
);

// 货币质押类型类型
exports.FundMortgageTypeType = new Enum(
  { alias: 'Mortgage', value: '1', text: '质押' },
  { alias: 'Redemption', value: '2', text: '解质' },
);

// 投资者账户结算参数代码类型
exports.AccountSettlementParamIDType = new Enum(
  { alias: 'BaseMargin', value: '1', text: '基础保证金' },
  { alias: 'LowestInterest', value: '2', text: '最低权益标准' },
);

// 货币质押方向类型
exports.FundMortDirectionType = new Enum(
  { alias: 'In', value: '1', text: '货币质入' },
  { alias: 'Out', value: '2', text: '货币质出' },
);

// 换汇类别类型
exports.BusinessClassType = new Enum(
  { alias: 'Profit', value: '0', text: '盈利' },
  { alias: 'Loss', value: '1', text: '亏损' },
  { alias: 'Other', value: 'Z', text: '其他' },
);

// 换汇数据来源类型
exports.SwapSourceTypeType = new Enum(
  { alias: 'Manual', value: '0', text: '手工' },
  { alias: 'Automatic', value: '1', text: '自动生成' },
);

// 换汇类型类型
exports.CurrExDirectionType = new Enum(
  { alias: 'Settlement', value: '0', text: '结汇' },
  { alias: 'Sale', value: '1', text: '售汇' },
);

// 申请状态类型
exports.CurrencySwapStatusType = new Enum(
  { alias: 'Entry', value: '1', text: '已录入' },
  { alias: 'Approve', value: '2', text: '已审核' },
  { alias: 'Refuse', value: '3', text: '已拒绝' },
  { alias: 'Revoke', value: '4', text: '已撤销' },
  { alias: 'Send', value: '5', text: '已发送' },
  { alias: 'Success', value: '6', text: '换汇成功' },
  { alias: 'Failure', value: '7', text: '换汇失败' },
);

// 换汇发送标志类型
exports.ReqFlagType = new Enum(
  { alias: 'NoSend', value: '0', text: '未发送' },
  { alias: 'SendSuccess', value: '1', text: '发送成功' },
  { alias: 'SendFailed', value: '2', text: '发送失败' },
  { alias: 'WaitReSend', value: '3', text: '等待重发' },
);

// 换汇返回成功标志类型
exports.ResFlagType = new Enum(
  { alias: 'Success', value: '0', text: '成功' },
  { alias: 'InsuffiCient', value: '1', text: '账户余额不足' },
  { alias: 'UnKnown', value: '8', text: '交易结果未知' },
);

// 修改状态类型
exports.ExStatusType = new Enum(
  { alias: 'Before', value: '0', text: '修改前' },
  { alias: 'After', value: '1', text: '修改后' },
);

// 开户客户地域类型
exports.ClientRegionType = new Enum(
  { alias: 'Domestic', value: '1', text: '国内客户' },
  { alias: 'GMT', value: '2', text: '港澳台客户' },
  { alias: 'Foreign', value: '3', text: '国外客户' },
);

// 是否有董事会类型
exports.HasBoardType = new Enum(
  { alias: 'No', value: '0', text: '没有' },
  { alias: 'Yes', value: '1', text: '有' },
);

// 启动模式类型
exports.StartModeType = new Enum(
  { alias: 'Normal', value: '1', text: '正常' },
  { alias: 'Emerge', value: '2', text: '应急' },
  { alias: 'Restore', value: '3', text: '恢复' },
);

// 模型类型类型
exports.TemplateTypeType = new Enum(
  { alias: 'Full', value: '1', text: '全量' },
  { alias: 'Increment', value: '2', text: '增量' },
  { alias: 'BackUp', value: '3', text: '备份' },
);

// 登录模式类型
exports.LoginModeType = new Enum(
  { alias: 'Trade', value: '0', text: '交易' },
  { alias: 'Transfer', value: '1', text: '转账' },
);

// 日历提示类型类型
exports.PromptTypeType = new Enum(
  { alias: 'Instrument', value: '1', text: '合约上下市' },
  { alias: 'Margin', value: '2', text: '保证金分段生效' },
);

// 是否有托管人类型
exports.HasTrusteeType = new Enum(
  { alias: 'Yes', value: '1', text: '有' },
  { alias: 'No', value: '0', text: '没有' },
);

// 机构类型类型
exports.AmTypeType = new Enum(
  { alias: 'Bank', value: '1', text: '银行' },
  { alias: 'Securities', value: '2', text: '证券公司' },
  { alias: 'Fund', value: '3', text: '基金公司' },
  { alias: 'Insurance', value: '4', text: '保险公司' },
  { alias: 'Trust', value: '5', text: '信托公司' },
  { alias: 'Other', value: '9', text: '其他' },
);

// 出入金类型类型
exports.CSRCFundIOTypeType = new Enum(
  { alias: 'FundIO', value: '0', text: '出入金' },
  { alias: 'SwapCurrency', value: '1', text: '银期换汇' },
);

// 结算账户类型类型
exports.CusAccountTypeType = new Enum(
  { alias: 'Futures', value: '1', text: '期货结算账户' },
  { alias: 'AssetmgrFuture', value: '2', text: '纯期货资管业务下的资管结算账户' },
  { alias: 'AssetmgrTrustee', value: '3', text: '综合类资管业务下的期货资管托管账户' },
  { alias: 'AssetmgrTransfer', value: '4', text: '综合类资管业务下的资金中转账户' },
);

// 通知语言类型类型
exports.LanguageTypeType = new Enum(
  { alias: 'Chinese', value: '1', text: '中文' },
  { alias: 'English', value: '2', text: '英文' },
);

// 资产管理客户类型类型
exports.AssetmgrClientTypeType = new Enum(
  { alias: 'Person', value: '1', text: '个人资管客户' },
  { alias: 'Organ', value: '2', text: '单位资管客户' },
  { alias: 'SpecialOrgan', value: '4', text: '特殊单位资管客户' },
);

// 投资类型类型
exports.AssetmgrTypeType = new Enum(
  { alias: 'Futures', value: '3', text: '期货类' },
  { alias: 'SpecialOrgan', value: '4', text: '综合类' },
);

// 合约比较类型类型
exports.CheckInstrTypeType = new Enum(
  { alias: 'HasExch', value: '0', text: '合约交易所不存在' },
  { alias: 'HasATP', value: '1', text: '合约本系统不存在' },
  { alias: 'HasDiff', value: '2', text: '合约比较不一致' },
);

// 交割类型类型
exports.DeliveryTypeType = new Enum(
  { alias: 'HandDeliv', value: '1', text: '手工交割' },
  { alias: 'PersonDeliv', value: '2', text: '到期交割' },
);

// 大额单边保证金算法类型
exports.MaxMarginSideAlgorithmType = new Enum(
  { alias: 'NO', value: '0', text: '不使用大额单边保证金算法' },
  { alias: 'YES', value: '1', text: '使用大额单边保证金算法' },
);

// 资产管理客户类型类型
exports.DAClientTypeType = new Enum(
  { alias: 'Person', value: '0', text: '自然人' },
  { alias: 'Company', value: '1', text: '法人' },
  { alias: 'Other', value: '2', text: '其他' },
);

// 投资类型类型
exports.UOAAssetmgrTypeType = new Enum(
  { alias: 'Futures', value: '1', text: '期货类' },
  { alias: 'SpecialOrgan', value: '2', text: '综合类' },
);

// 期权类型类型
exports.OptionsTypeType = new Enum(
  { alias: 'CallOptions', value: '1', text: '看涨' },
  { alias: 'PutOptions', value: '2', text: '看跌' },
);

// 执行方式类型
exports.StrikeModeType = new Enum(
  { alias: 'Continental', value: '0', text: '欧式' },
  { alias: 'American', value: '1', text: '美式' },
  { alias: 'Bermuda', value: '2', text: '百慕大' },
);

// 执行类型类型
exports.StrikeTypeType = new Enum(
  { alias: 'Hedge', value: '0', text: '自身对冲' },
  { alias: 'Match', value: '1', text: '匹配执行' },
);

// 中金所期权放弃执行申请类型类型
exports.ApplyTypeType = new Enum(
  { alias: 'NotStrikeNum', value: '4', text: '不执行数量' },
);

// 放弃执行申请数据来源类型
exports.GiveUpDataSourceType = new Enum(
  { alias: 'Gen', value: '0', text: '系统生成' },
  { alias: 'Hand', value: '1', text: '手工添加' },
);

// 执行结果类型
exports.ExecResultType = new Enum(
  { alias: 'NoExec', value: 'n', text: '没有执行' },
  { alias: 'Canceled', value: 'c', text: '已经取消' },
  { alias: 'OK', value: '0', text: '执行成功' },
  { alias: 'NoPosition', value: '1', text: '期权持仓不够' },
  { alias: 'NoDeposit', value: '2', text: '资金不够' },
  { alias: 'NoParticipant', value: '3', text: '会员不存在' },
  { alias: 'NoClient', value: '4', text: '客户不存在' },
  { alias: 'NoInstrument', value: '6', text: '合约不存在' },
  { alias: 'NoRight', value: '7', text: '没有执行权限' },
  { alias: 'InvalidVolume', value: '8', text: '不合理的数量' },
  { alias: 'NoEnoughHistoryTrade', value: '9', text: '没有足够的历史成交' },
  { alias: 'Unknown', value: 'a', text: '未知' },
);

// 组合类型类型
exports.CombinationTypeType = new Enum(
  { alias: 'Future', value: '0', text: '期货组合' },
  { alias: 'BUL', value: '1', text: '垂直价差BUL' },
  { alias: 'BER', value: '2', text: '垂直价差BER' },
  { alias: 'STD', value: '3', text: '跨式组合' },
  { alias: 'STG', value: '4', text: '宽跨式组合' },
  { alias: 'PRT', value: '5', text: '备兑组合' },
  { alias: 'CLD', value: '6', text: '时间价差组合' },
  { alias: 'OPL', value: '7', text: '期权对锁组合' },
  { alias: 'BFO', value: '8', text: '买备兑组合' },
);

// 组合类型类型
exports.DceCombinationTypeType = new Enum(
  { alias: 'SPL', value: '0', text: '期货对锁组合' },
  { alias: 'OPL', value: '1', text: '期权对锁组合' },
  { alias: 'SP', value: '2', text: '期货跨期组合' },
  { alias: 'SPC', value: '3', text: '期货跨品种组合' },
  { alias: 'BLS', value: '4', text: '买入期权垂直价差组合' },
  { alias: 'BES', value: '5', text: '卖出期权垂直价差组合' },
  { alias: 'CAS', value: '6', text: '期权日历价差组合' },
  { alias: 'STD', value: '7', text: '期权跨式组合' },
  { alias: 'STG', value: '8', text: '期权宽跨式组合' },
  { alias: 'BFO', value: '9', text: '买入期货期权组合' },
  { alias: 'SFO', value: 'a', text: '卖出期货期权组合' },
);

// 期权权利金价格类型类型
exports.OptionRoyaltyPriceTypeType = new Enum(
  { alias: 'PreSettlementPrice', value: '1', text: '昨结算价' },
  { alias: 'OpenPrice', value: '4', text: '开仓价' },
  { alias: 'MaxPreSettlementPrice', value: '5', text: '最新价与昨结算价较大值' },
);

// 权益算法类型
exports.BalanceAlgorithmType = new Enum(
  { alias: 'Default', value: '1', text: '不计算期权市值盈亏' },
  { alias: 'IncludeOptValLost', value: '2', text: '计算期权市值亏损' },
);

// 执行类型类型
exports.ActionTypeType = new Enum(
  { alias: 'Exec', value: '1', text: '执行' },
  { alias: 'Abandon', value: '2', text: '放弃' },
);

// 询价状态类型
exports.ForQuoteStatusType = new Enum(
  { alias: 'Submitted', value: 'a', text: '已经提交' },
  { alias: 'Accepted', value: 'b', text: '已经接受' },
  { alias: 'Rejected', value: 'c', text: '已经被拒绝' },
);

// 取值方式类型
exports.ValueMethodType = new Enum(
  { alias: 'Absolute', value: '0', text: '按绝对值' },
  { alias: 'Ratio', value: '1', text: '按比率' },
);

// 期权行权后是否保留期货头寸的标记类型
exports.ExecOrderPositionFlagType = new Enum(
  { alias: 'Reserve', value: '0', text: '保留' },
  { alias: 'UnReserve', value: '1', text: '不保留' },
);

// 期权行权后生成的头寸是否自动平仓类型
exports.ExecOrderCloseFlagType = new Enum(
  { alias: 'AutoClose', value: '0', text: '自动平仓' },
  { alias: 'NotToClose', value: '1', text: '免于自动平仓' },
);

// 产品类型类型
exports.ProductTypeType = new Enum(
  { alias: 'Futures', value: '1', text: '期货' },
  { alias: 'Options', value: '2', text: '期权' },
);

// 组合指令方向类型
exports.CombDirectionType = new Enum(
  { alias: 'Comb', value: '0', text: '申请组合' },
  { alias: 'UnComb', value: '1', text: '申请拆分' },
  { alias: 'DelComb', value: '2', text: '操作员删组合单' },
);

// 行权偏移类型类型
exports.StrikeOffsetTypeType = new Enum(
  { alias: 'RealValue', value: '1', text: '实值额' },
  { alias: 'ProfitValue', value: '2', text: '盈利额' },
  { alias: 'RealRatio', value: '3', text: '实值比例' },
  { alias: 'ProfitRatio', value: '4', text: '盈利比例' },
);

// 预约开户状态类型
exports.ReserveOpenAccStasType = new Enum(
  { alias: 'Processing', value: '0', text: '等待处理中' },
  { alias: 'Cancelled', value: '1', text: '已撤销' },
  { alias: 'Opened', value: '2', text: '已开户' },
  { alias: 'Invalid', value: '3', text: '无效请求' },
);

// 弱密码来源类型
exports.WeakPasswordSourceType = new Enum(
  { alias: 'Lib', value: '1', text: '弱密码库' },
  { alias: 'Manual', value: '2', text: '手工录入' },
);

// 期权行权的头寸是否自对冲类型
exports.OptSelfCloseFlagType = new Enum(
  { alias: 'CloseSelfOptionPosition', value: '1', text: '自对冲期权仓位' },
  { alias: 'ReserveOptionPosition', value: '2', text: '保留期权仓位' },
  { alias: 'SellCloseSelfFuturePosition', value: '3', text: '自对冲卖方履约后的期货仓位' },
  { alias: 'ReserveFuturePosition', value: '4', text: '保留卖方履约后的期货仓位' },
);

// 业务类型类型
exports.BizTypeType = new Enum(
  { alias: 'Future', value: '1', text: '期货' },
  { alias: 'Stock', value: '2', text: '证券' },
);

// 用户App类型类型
exports.AppTypeType = new Enum(
  { alias: 'Investor', value: '1', text: '直连的投资者' },
  { alias: 'InvestorRelay', value: '2', text: '为每个投资者都创建连接的中继' },
  { alias: 'OperatorRelay', value: '3', text: '所有投资者共享一个操作员连接的中继' },
  { alias: 'UnKnown', value: '4', text: '未知' },
);

// 应答类型类型
exports.ResponseValueType = new Enum(
  { alias: 'Right', value: '0', text: '检查成功' },
  { alias: 'Refuse', value: '1', text: '检查失败' },
);

// OTC成交类型类型
exports.OTCTradeTypeType = new Enum(
  { alias: 'Block', value: '0', text: '大宗交易' },
  { alias: 'EFP', value: '1', text: '期转现' },
);

// 期现风险匹配方式类型
exports.MatchTypeType = new Enum(
  { alias: 'DV01', value: '1', text: '基点价值' },
  { alias: 'ParValue', value: '2', text: '面值' },
);
