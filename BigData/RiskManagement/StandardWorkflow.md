# 风控通用流程：

## 数据预处理
### 标准化
```

```
### 区间缩放
```
```
### 定量特征二值化
```
```
### 定性特征哑编码(One-Hot Encoding)
```
```
### 缺失值处理
```
```

## 特征选取
### 自有数据：  
表填数据：身份证号、手机号、手机号在平台其他用户通讯录中的存储个数、手机号归属地、户籍地址、户籍地址、户籍地址是否在村镇、银行卡号、银行卡发卡行、性别、年龄、签发机关、紧急联系人关系、紧急联系人电话、紧急联系人电话归属地和申请人手机号归属地是否一致、归属是否一致、紧急联系人是否为平台用户、学历、工作、月收入、公司、负债、地址  
### 环境数据：
网络环境： wifi/4g/5g/3g/2g  
相同mac地址不同时段申请数：一个月、三个月、六个月、一年  
相同ip不同时段申请数：一个月、三个月、六个月、一年  
相同lbs不同时段申请数：一个月、三个月、六个月、一年  
wifi名称： 是否包含风险关键词  
gps所在城市： 计算每个城市的逾期率，计算出均值和标准差。均值-3倍标准差以下的城市记为others  
IP所在城市：IP是否在境内/境外;IP与GPS是否是同一城市;IP与手机号码是否是同一城市
### 行为数据：
夜间申请  
打开落地页地点：APP;微信;浏览器  
从注册到申请的点击次数  
从注册到申请的花费时间  
首次登陆到开始申请的时间  
开始申请到申请完成的时间  
从授信到动支的时间  
历始申请次数  
上一次申请到本次申请的时间间隔  
文本框内容是复制粘贴的还是手输的  
身份证提交次数  
## 降维
## 选择模型
## 

## 常用监控指标
策略大盘：申请用户量，授信通过率，额度分布和均值，利率分布和均值，提现通过率，件均分布和均值，放贷量  
策略详情：节点通过率，节点路由，规则通过率，规则稳定性  
模型：模型等级分布，稳定性指标  
变量：变量值分布，稳定性指标  
人工环节：人工审核量，人工审核在审案件，转人工比率，人工审核通过率  
客群指标：渠道客群分布，自定义客群分布，综合信用等级分布，多头分布  
贷中指标：额度使用率，复借率  
贷后表现：入催率，逾期率，迁移率  
产品转化漏斗：从注册到放款的整体产品指标  
系统运营类：订单异常原因监控，订单耗时分析，全链路监控，变量耗时监控  
常见监控维度：渠道，产品，客群，新老客。以上的指标，都可以用上面四个维度来进行拆分和筛选。  

## 参考
[自有数据特征选取](https://zhuanlan.zhihu.com/p/90080389)