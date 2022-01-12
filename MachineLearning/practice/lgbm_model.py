import numpy as np
import pandas as pd
from sklearn.datasets import load_iris
import lightgbm as lgb
from sklearn.model_selection import train_test_split
from hyperopt import fmin, tpe, hp, partial
from sklearn.metrics import mean_squared_error
from sklearn.metrics import f1_score, precision_score, recall_score, accuracy_score
from sklearn.metrics import confusion_matrix,classification_report

class lightgbm_model():
    def __init__(self):
        self.train_data = None
        self.test_data = None
        self.X_test =None
        self.y_test =None
        self.model_lgb =None

    space = {"max_depth": hp.randint("max_depth", 15),
         "num_trees": hp.randint("num_trees", 300),
         'learning_rate': hp.uniform('learning_rate', 1e-3, 5e-1),
         "bagging_fraction": hp.randint("bagging_fraction", 5),
         "num_leaves": hp.randint("num_leaves", 6),
         }

    def argsDict_tranform(self,argsDict, isPrint=False):
        argsDict["max_depth"] = argsDict["max_depth"] + 5
        argsDict['num_trees'] = argsDict['num_trees'] + 150
        argsDict["learning_rate"] = argsDict["learning_rate"] * 0.02 + 0.05
        argsDict["bagging_fraction"] = argsDict["bagging_fraction"] * 0.1 + 0.5
        argsDict["num_leaves"] = argsDict["num_leaves"] * 3 + 10
        if isPrint:
            print(argsDict)
        else:
            pass
        return argsDict
    
    def lightgbm_factory(self,argsDict):
        argsDict = self.argsDict_tranform(argsDict)
        params = {'nthread': -1,  # 进程数
              'max_depth': argsDict['max_depth'],  # 最大深度
              'num_trees': argsDict['num_trees'],  # 树的数量
              'eta': argsDict['learning_rate'],  # 学习率
              'bagging_fraction': argsDict['bagging_fraction'],  # bagging采样数
              'num_leaves': argsDict['num_leaves'],  # 终点节点最小样本占比的和
              'objective': 'regression',
              'feature_fraction': 0.7,  # 样本列采样
              'lambda_l1': 0,  # L1 正则化
              'lambda_l2': 0,  # L2 正则化
              'bagging_seed': 100,  # 随机种子,light中默认为100
              }
        #rmse
        params['metric'] = ['rmse']
        self.model_lgb = lgb.train(params, self.train_data, num_boost_round=300, valid_sets=[self.test_data,],early_stopping_rounds=100)
        return self.get_tranformer_score(self.model_lgb)
    
    def get_tranformer_score(self,tranformer):
        model = tranformer
        prediction = model.predict(self.X_test, num_iteration=model.best_iteration)
        return mean_squared_error(self.y_test, prediction)
        
    def create_best_model(self,X,y): 
        X_train, self.X_test, y_train, self.y_test = train_test_split(X, y, test_size=0.2, random_state=100)
        self.train_data = lgb.Dataset(data=X_train,label=y_train)
        self.test_data = lgb.Dataset(data=self.X_test,label=self.y_test)
        algo = partial(tpe.suggest, n_startup_jobs=1)
        best = fmin(self.lightgbm_factory, self.space, algo=algo, max_evals=20, pass_expr_memo_ctrl=None)
        self.lightgbm_factory(self.argsDict_tranform(best,isPrint=True))
        best_model = self.model_lgb
        return best_model 
     
     #二分类
    def get_best_pro(self,X,y,begin=0,times=-1,range_=1):#当样本过大时，可使用参数进行定位
        if y.nunique()>2:
            return 0
        else:
            model_train = pd.DataFrame()
            model_train['correct'] = y  # y_train存在index 合并会出错
            model_train['yes_prob'] = self.model_lgb.predict(X)
            model_train.sort_values(by='yes_prob', ascending=False, inplace=True)  # ascending=False 倒叙
            model_train.reset_index(drop=True, inplace=True)
            pred = [0] * model_train.shape[0]
            f1_prob_dict = dict()
            if times < 0:
                times = model_train.shape[0] - 1
            for x in range(begin, times,range_):
                pred[:x] = [1]*x
                f1 = round(f1_score(y_pred=pred, y_true=model_train['correct'], average='binary', pos_label=1), 3)
                this_prob = model_train['yes_prob'][x:x + 2].mean()
                f1_prob_dict[this_prob] = f1
                print(str(x)+"/"+str(times)+" : "+ str(f1))
        
            f1_max = max(f1_prob_dict.values())
            prob_max = max(f1_prob_dict, key=f1_prob_dict.get)
            return prob_max
            
         #二分类
    def get_predict(self,X,pro=0.5):
        model_proba = self.model_lgb.predict(X)  # 猜一类的机率
        prob_max_pred = [1 if y >= pro else 0 for y in model_proba]
        return prob_max_pred
    
    #二分类
    def get_best_benefit(self,X,y,tp=1,fp=1):
        if y.nunique()>2:
            return 0
        else:
            model_train = pd.DataFrame()
            model_train['correct'] = y  # y_train存在index 合并会出错
            model_train['yes_prob'] = self.model_lgb.predict(X)
            model_train.sort_values(by='yes_prob', ascending=False, inplace=True)  # ascending=False 倒叙
            model_train.reset_index(drop=True, inplace=True)
            pred = [0] * model_train.shape[0]
            f1_prob_dict = dict()
            benefit_max =0
            index =0
            benefit =0
            for i in range(0, model_train.shape[0] - 1):
                if model_train['correct'][i]==1:
                    benefit += tp
                else:
                    benefit -= fp
                if benefit > benefit_max:
                    benefit_max = benefit
                    index = i
                
            prob_max = model_train['yes_prob'][index]
            return prob_max 

    def get_model_report(self,y_pre,y_true):
        model_name = 'lightgbm'
        pred = y_pre #Threshold = 0.5
        y_true = y_true
        f1 = f1_score(y_pred=pred, y_true=y_true, average='binary', pos_label=1)
        recall = recall_score(y_pred=pred, y_true=y_true, average='binary', pos_label=1)
        precision = precision_score(y_pred=pred, y_true=y_true, average='binary', pos_label=1)
        accuracy = accuracy_score(y_pred=pred, y_true=y_true)
        print('result %s: f1=%.3f, recall=%.3f, precision=%.3f, accuracy=%.3f \n' % (
          model_name, f1, recall, precision, accuracy))
        
        print(' train\nconfusion_matrix\n', confusion_matrix(y_true=y_true, y_pred=pred))
        print('classification report\n',classification_report(y_true=y_true, y_pred=pred))
        return None
        
        
        
        
        