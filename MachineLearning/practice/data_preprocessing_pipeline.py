import xgboost as xgb
import pandas as pd
import numpy as np
import logging
from sklearn.pipeline import Pipeline, make_pipeline, FeatureUnion
from sklearn.base import BaseEstimator, TransformerMixin
from sklearn.tree import DecisionTreeClassifier
from sklearn.metrics import confusion_matrix
from collections import defaultdict
from sklearn.preprocessing import StandardScaler
from sklearn.preprocessing import OneHotEncoder
import matplotlib.pyplot as plt
from sklearn.preprocessing import MinMaxScaler

logging.basicConfig(level=logging.INFO,
                    format='%(asctime)s %(levelname)s %(message)s',
                    datefmt='%Y %H:%M:%S')


def get_kind(x: pd.Series, diff_limit: int = 8):
    x = x.astype('str')
    x = x.str.extract(r'(^(\-|)(?=.*\d)\d*(?:\.\d*)?$)')[0]
    x.dropna(inplace=True)
    if x.nunique() > diff_limit:
        kind = 'numeric'
    else:
        kind = 'categorical'
    return kind


def check_data_y(X):
    """
    检查数据结构，数据预测变量为 0,1，并以“y”命名
    """
    if 'y' not in X.columns:
        logging.error('未检测到"y"变量，请将预测变量命名改为"y"')


class wrong_value_fillna(BaseEstimator, TransformerMixin):
    def __init__(self,
                 num_list: list = None,
                 cate_list: list = None,
                 wrong_value: list = None,
                 diff_num: int = 10):
        self.num_list = num_list
        self.cate_list = cate_list
        self.diff_num = diff_num
        self.wrong_value = wrong_value

    def fit(self, X, y=None):
        X = X.copy()
        if self.num_list is None:
            self.num_list = []
            for col in X.columns:
                kind = get_kind(x=X[col], diff_limit=self.diff_num)
                if kind == 'numeric':
                    self.num_list.append(col)
        if self.cate_list is None:
            self.cate_list = []
            for col in X.columns:
                kind = get_kind(x=X[col], diff_limit=self.diff_num)
                if kind == 'categorical':
                    self.cate_list.append(col)
        return self

    def transform(self, X):
        X = X.copy()
        X.replace(self.wrong_value, np.nan, inplace=True)
        for col in self.num_list:
            # if get_kind(X[col]) == 'numeric':
            X[col] = X[col].astype('float')
        logging.info('wrong values already fill as np.nan!')
        return X


class base_fill(BaseEstimator, TransformerMixin):
    def __init__(self,
                 num_list: list = None,
                 cate_list: list = None,
                 diff_num: int = 10,
                 cate_method: str = 'self_value',
                 cate_value: str = 'Unknown',
                 num_method: str = 'self_value',
                 num_value: float = 0,
                 self_fill_dict: dict = None
                 ):
        self.num_list = num_list
        self.cate_list = cate_list
        self.diff_num = diff_num
        self.cate_method = cate_method
        self.cate_value = cate_value
        self.num_method = num_method
        self.num_value = num_value
        self.self_fill_dict = self_fill_dict

    def fit(self, X, y=None):
        from tqdm import tqdm
        X = X.copy()
        if self.self_fill_dict is not None:
            return self
        else:
            '''get num_list and cate_list'''
            if self.num_list is None and self.cate_list is None:
                self.num_list, self.cate_list = [], []
                for col in X.columns:
                    kind = get_kind(x=X[col], diff_limit=self.diff_num)
                    if kind == 'numeric':
                        self.num_list.append(col)
                    else:
                        self.cate_list.append(col)
            elif self.num_list is not None and self.cate_list is not None:
                pass
            else:
                if self.num_list is not None:
                    self.cate_list = list(set(X.columns).difference(set(self.num_list)))
                else:
                    self.num_list = list(set(X.columns).difference(set(self.cate_list)))
            '''fill nan'''
            self.self_fill_dict = {}
            for col in self.num_list:
                if self.num_method == 'self_value':
                    self.self_fill_dict[col] = self.num_value
                elif self.num_method == 'mean':
                    self.self_fill_dict[col] = X[col].mean()
                elif self.num_method == 'median':
                    self.self_fill_dict[col] = X[col].median()
                else:
                    logging.error('Do not find this num_method. Please input "self_value"/"median"/"mean". ')
            for col in self.cate_list:
                if self.cate_method == 'self_value':
                    self.self_fill_dict[col] = self.cate_value
                elif self.cate_method == 'mode':
                    self.self_fill_dict[col] = X[col].mode()[0]
                else:
                    logging.error('Do not find this cate_method. Please input "self_value"/"mode". ')

            return self

    def transform(self, X):
        X = X.copy()
        from tqdm import tqdm
        for key in tqdm(self.self_fill_dict):
            X[key] = X[key].fillna(self.self_fill_dict[key])
        logging.info('base fillNa success!')
        return X


class fill_default_rate(BaseEstimator, TransformerMixin):

    def __init__(self,
                 columns: list = None,
                 pos_label: int = 1,
                 ):
        self.columns = columns
        self.pos_label = pos_label
        self.rate_dict = defaultdict(defaultdict)

    def fit(self, X, y=None):
        X = X.copy()
        X['y'] = y
        for col in self.columns:
            for fea in list(X[col].unique()):
                self.rate_dict[col][fea] = (X[(X['y'] == self.pos_label) & (X[col] == fea)].shape[0]) / (
                X[X[col] == fea].shape[0])
        # print(self.rate_dict)
        return self

    def transform(self, X):
        X = X.copy()
        for col in self.columns:
            for fea in list(X[col].unique()):
                X[col].replace(fea, self.rate_dict[col][fea], inplace=True)
        return X


class xgb_fill(BaseEstimator, TransformerMixin):

    def __init__(self,
                 num_list: list = None,
                 cate_list: list = None,
                 diff_num: int = 10,
                 random_state: int = 0):
        self.num_list = num_list
        self.cate_list = cate_list
        self.diff_num = diff_num
        self.random_state = random_state
        self.xgb_cla_dict = {}
        self.xgb_reg_dict = {}

    def fit(self, X, y=None):
        from tqdm import tqdm
        X = X.copy()
        if self.num_list is None:
            self.num_list = []
            for col in X.columns:
                kind = get_kind(x=X[col], diff_limit=self.diff_num)
                if kind == 'numeric':
                    self.num_list.append(col)
        if self.cate_list is None:
            self.cate_list = []
            for col in X.columns:
                kind = get_kind(x=X[col], diff_limit=self.diff_num)
                if kind == 'categorical':
                    self.cate_list.append(col)
        for col in tqdm(self.cate_list):
            file = X.copy()
            if file[col].isnull().any():
                df = pd.get_dummies(file, columns=[i for i in self.cate_list if i != col],
                                    prefix=[i for i in self.cate_list if i != col],
                                    dummy_na=True)
                not_null = df.dropna(subset=[col])
                x_ = not_null.drop([col], axis=1)
                y_ = not_null[col]
                xgb_cla = xgb.XGBClassifier(random_state=self.random_state)
                xgb_cla.fit(x_, y_)
                self.xgb_cla_dict[col] = xgb_cla

        for col in tqdm(self.num_list):
            file = X.copy()
            if file[col].isnull().any():
                df = pd.get_dummies(file, columns=self.cate_list, dummy_na=True, prefix=self.cate_list)
                not_null = df.dropna(subset=[col])
                x_ = not_null.drop([col], axis=1)
                y_ = not_null[col]
                xgb_reg = xgb.XGBRegressor(random_state=self.random_state, objective='reg:squarederror')
                xgb_reg.fit(x_, y_)
                self.xgb_reg_dict[col] = xgb_reg
        logging.info('fit xgb fill the Na success!')
        return self

    def transform(self, X):
        X = X.copy()
        from tqdm import tqdm
        for col in tqdm(self.cate_list):
            file = X.copy()
            if file[col].isnull().any():
                df = pd.get_dummies(file, columns=[i for i in self.cate_list if i != col],
                                    prefix=[i for i in self.cate_list if i != col],
                                    dummy_na=True)
                not_null = df.dropna(subset=[col])
                null = df.drop(not_null.index)
                null[col] = self.xgb_cla_dict[col].predict(null.drop([col], axis=1))
                X[col] = pd.concat([null, not_null], axis=0)[col]
            else:
                X[col] = file[col]

        for col in tqdm(self.num_list):
            file = X.copy()
            if file[col].isnull().any():
                df = pd.get_dummies(file, columns=self.cate_list, dummy_na=True, prefix=self.cate_list)
                not_null = df.dropna(subset=[col])
                null = df.drop(not_null.index)
                null[col] = self.xgb_reg_dict[col].predict(null.drop([col], axis=1))
                X[col] = pd.concat([null, not_null], axis=0)[col]
            else:
                X[col] = file[col]
        logging.info('transform xgb fill the NA success!')
        return X


class fix_outlier(BaseEstimator, TransformerMixin):#已修改
    def __init__(self,
                 num_list=None,
                 diff_num: int = 10,
                 pmin: float = None,
                 pmax: float = None,
                 fmin_: float = None,
                 fmax_: float = None,
                 how: str = 'quartile'):
        self.num_list = num_list
        self.diff_num = diff_num
        self.pmin = pmin
        self.pmax = pmax
        self.fmin_ = fmin_
        self.fmax_ = fmax_
        self.how = how
        

    def fit(self, X, y=None):
        X = X.copy()
        if self.num_list is None:
            self.num_list = []
            for col in X.columns:
                kind = get_kind(x=X[col], diff_limit=self.diff_num)
                if kind == 'numeric':
                    self.num_list.append(col)
        for col in self.num_list:
            describe_ = X[col].describe()
            fmin_, fmax_ = 0.0, 0.0
            if self.how == 'quartile':
                IQR = round(describe_['75%'] - describe_['25%'], 2)
                self.fmin_ = round(describe_['25%'] - 1.5 * IQR, 2)
                self.fmax_ = round(describe_['75%'] + 1.5 * IQR, 2)
            elif self.how == 'self_percent':
                self.fmin_ = round(X[col].quantile(self.pmin), 2)
                self.fmax_ = round(X[col].quantile(self.pmax), 2)
            elif self.how == 'cap':
                self.fmin_ = round(describe_['mean'] - 3 * describe_['std'], 2)
                self.fmax_ = round(describe_['mean'] + 3 * describe_['std'], 2)
            else:
                logging.error("don't have that method!")
        return self

    def transform(self, X):
        X = X.copy()
        for col in self.num_list:
            logging.info('deal with "' + col + '" lower fmin size: ' + str(X.loc[X[col] < self.fmin_, col].shape[0]))
            logging.info('deal with "' + col + '" higher fmax size: ' + str(X.loc[X[col] > self.fmax_, col].shape[0]))
            X.loc[X[col] < self.fmin_, col] = self.fmin_
            X.loc[X[col] > self.fmax_, col] = self.fmax_
        logging.info('fix outlier success!')
        return X


class feature_select(BaseEstimator, TransformerMixin):
    def __init__(self,
                 num_list: list = None,
                 cate_list: list = None,
                 num_method: str = 'sys',
                 cate_method: str = 'sys',
                 diff_num: int = 10,
                 pos_label: str = 1,
                 show_df: bool = False):
        self.num_list = num_list
        self.cate_list = cate_list
        self.num_method = num_method
        self.cate_method = cate_method
        self.diff_num = diff_num
        self.pos_label = pos_label
        self.show_df = show_df
        self.select_list = []

    def fit(self, X, y=None):
        X = X.copy()
        from scipy import stats
        if self.num_list is None:
            self.num_list = []
            for col in X.columns:
                kind = get_kind(x=X[col], diff_limit=self.diff_num)
                if kind == 'numeric':
                    self.num_list.append(col)
        if self.cate_list is None:
            self.cate_list = []
            for col in X.columns:
                kind = get_kind(x=X[col], diff_limit=self.diff_num)
                if kind == 'categorical':
                    self.cate_list.append(col)
        X['y'] = y
        yes = X[X['y'] == self.pos_label]
        yes.reset_index(drop=True, inplace=True)
        no = X[X['y'] != self.pos_label]
        no.reset_index(drop=True, inplace=True)
        del X['y']
        sys_cate_list, kf_list, kf_p_list = [], [], []
        sys_num_list, t_list, p_value_list, anova_f_list, anova_p_list = [], [], [], [], []
        if self.cate_method == 'sys' or self.show_df is True:
            for obj in self.cate_list:
                value_list = list(X[obj].unique())
                value_sum = 0
                for value in value_list:
                    support_yes = (yes[yes[obj] == value].shape[0] + 1) / (yes.shape[0] + 1)
                    support_no = (no[no[obj] == value].shape[0] + 1) / (no.shape[0] + 1)
                    confidence_yes = support_yes / (support_yes + support_no)
                    value_sum += abs(2 * confidence_yes - 1) * (X[X[obj] == value].shape[0] / X.shape[0])
                sys_cate_list.append(value_sum)
                if value_sum >= 0.09 and self.cate_method == 'sys':
                    self.select_list.append(obj)

        if self.cate_method == 'kf' or self.show_df is True:
            for obj in self.cate_list:
                df_obj = pd.get_dummies(X[obj], prefix=obj)
                df_obj['result'] = y
                df_obj = df_obj.groupby('result').sum()
                obs = df_obj.values
                kf = stats.chi2_contingency(obs)
                '''
                chi2: The test statistic
                p: p-value
                dof: Degrees of freedom
                expected: The expected frequencies, based on the marginal sums of the table.
                '''
                chi2, p, dof, expect = kf
                kf_list.append(chi2)
                kf_p_list.append(p)

                if p < 0.05 and self.cate_method == 'kf':
                    self.select_list.append(obj)

        if self.num_method == 'sys' or self.show_df is True:
            for num in self.num_list:
                mean_c1 = no[num].mean()
                std_c1 = no[num].std()
                mean_c2 = yes[num].mean()
                std_c2 = yes[num].std()
                value_sum = abs(mean_c1 - mean_c2) / (std_c1 + std_c2) * 2
                sys_num_list.append(value_sum)
                if value_sum >= 0.09 and self.num_method == 'sys':
                    self.select_list.append(num)

        if self.num_method == 't' or self.show_df is True:
            for num in self.num_list:
                t_t, t_p = stats.ttest_ind(yes[num], no[num], equal_var=False, nan_policy='omit')  # 'omit'忽略nan值执行计算
                t_list.append(t_t)
                p_value_list.append(t_p)
                if t_p < 0.05 and self.num_method == 't':
                    self.select_list.append(num)
                # print('attr=%s, t=%.5f, p=%.5f' % (num, t, p_value))
        if self.num_method == 'anova' or self.show_df is True:
            for num in self.num_list:
                anova_f, anova_p = stats.f_oneway(yes[num], no[num])
                anova_f_list.append(anova_f)
                anova_p_list.append(anova_p)
                # print('attr=%s, anova_f=%.5f, anova_p=%.5f' % (num, anova_f, anova_p))
                if anova_p < 0.05 and self.num_method == 'anova':
                    self.select_list.append(num)
        if self.show_df is True:
            dic1 = {'categorical': self.cate_list, 'importance_': sys_cate_list, 'Kf-Value': kf_list,
                    'Kf-P-Value': kf_p_list}
            df = pd.DataFrame(dic1, columns=['categorical', 'importance_', 'Kf-Value', 'Kf-P-Value'])
            df.sort_values(by='Kf-P-Value', inplace=True)
            print(df)
            dic2 = {'numeric': self.num_list, 'importance_': sys_num_list, 'T-Value': t_list, 'P-value': p_value_list,
                    'Anova-F-Value': anova_f_list, 'Anova-P-value': anova_p_list}
            df = pd.DataFrame(dic2,
                              columns=['numeric', 'importance_', 'T-Value', 'P-value', 'Anova-F-Value',
                                       'Anova-P-value'])
            df.sort_values(by='Anova-P-value', inplace=True)
            print(df)
        self.select_list = list(set(self.select_list))
        print('After select attr:', self.select_list)
        return self

    def transform(self, X):
        X = X.copy()
        logging.info('attr select success!')
        return X[self.select_list]


class binning(BaseEstimator, TransformerMixin):#可使用等宽、决策树、momo分箱，等频不知道怎么改
    def __init__(self,
                 num_list: list = None,
                 diff_num: int = 10,
                 how: str = 'dtc',
                 q=5,
                 include_y: bool = True,
                 random_state: int = None
                 ):
        self.num_list = num_list
        self.diff_num = diff_num
        self.how = how
        self.q = q  # just for equal_size and equal_width method
        self.include_y = include_y
        self.random_state = random_state
        self.cut_dict = None

    def fit(self, X, y=None):
        X = X.copy()

        if self.num_list is None:
            self.num_list = []
            for col in X.columns:
                kind = get_kind(x=X[col], diff_limit=self.diff_num)
                if kind == 'numeric':
                    self.num_list.append(col)
            if not self.num_list:
                return self

        if self.include_y:
            X['y'] = y

        if self.how == 'dtc':
            check_data_y(X)
            self.cut_dict = {}
            for num in self.num_list:
                """
                    利用决策树获得最优分箱的边界值列表
                """
                boundary = []  # 待return的分箱边界值列表
                clf = DecisionTreeClassifier(criterion='entropy',  # “信息熵”最小化准则划分
                                             max_leaf_nodes=6,  # 最大叶子节点数
                                             min_samples_leaf=0.05,  # 叶子节点样本数量最小占比
                                             random_state=self.random_state)  # 随机种子
                clf.fit(X[num].values.reshape(-1, 1), X['y'])  # 训练决策树

                n_nodes = clf.tree_.node_count
                children_left = clf.tree_.children_left
                children_right = clf.tree_.children_right
                threshold = clf.tree_.threshold

                for i in range(n_nodes):
                    if children_left[i] != children_right[i]:  # 获得决策树节点上的划分边界值
                        boundary.append(threshold[i])

                boundary.sort()

                min_x = np.around(X[num].min() - 1e-2, 3)
                max_x = np.around(X[num].max(), 3)
                boundary = [min_x] + boundary + [max_x]
                self.cut_dict[num] = boundary               
        elif self.how == 'mono':
            self.cut_dict = {}
            check_data_y(X)
            from xverse.transformer import MonotonicBinning
            mono_bin = MonotonicBinning(feature_names=self.num_list)
            mono = mono_bin.fit(X.drop('y', axis=1), X['y'])
            self.cut_dict = mono.bins
            for v in self.cut_dict.values():
                v[0] -= 1e-2
        elif self.how == 'equal_width':
            self.cut_dict = {}
            for num in self.num_list:
                whatever,boundary = pd.cut(x=X[num], bins=self.q,retbins=True)
                self.cut_dict[num] = boundary
        if self.include_y:
            X.drop('y', axis=1, inplace=True)
        return self

    def transform(self, X):
        if not self.num_list:
            return X
        X = X.copy()
        if self.how == 'dtc' or self.how == 'mono':
            for num in self.num_list:
                X[num] = pd.cut(x=X[num], bins=self.cut_dict[num])
                # labels=[chr(i) for i in range(97, 97 + len(self.cut_dict[num]) - 1)])  # 左开右闭
                X[num] = X[num].astype('object')

        elif self.how == 'equal_size':
            for num in self.num_list:
                X[num] = pd.qcut(x=X[num], q=self.q)
                X[num] = X[num].astype('object')

        elif self.how == 'equal_width':
            for num in self.num_list:
                X[num] = pd.cut(x=X[num], bins=self.cut_dict[num])
                X[num] = X[num].astype('object')
        else:
            logging.error("do not have that method, you can use 'dtc'/'mono'/'equal_size' or 'equal_width'")
            return X

        logging.info('bin success!')
        return X


class dummies(BaseEstimator, TransformerMixin): #用onehot，这个就不改了
    def __init__(self,
                 cate_list=None,
                 diff_num: int = 10,
                 dummy_na=True,
                 ):
        self.cate_list = cate_list
        self.diff_num = diff_num
        self.dummy_na = dummy_na

    def fit(self, X, y=None):
        X = X.copy()
        if self.cate_list is None:
            self.cate_list = []
            for col in X.columns:
                kind = get_kind(x=X[col], diff_limit=self.diff_num)
                if kind == 'categorical':
                    self.cate_list.append(col)
        return self

    def transform(self, X):
        import re
        X = X.copy()
        X = pd.get_dummies(X, columns=self.cate_list, dummy_na=self.dummy_na, prefix=self.cate_list)
        logging.info('dummies success!')
        regex = re.compile(r"\(|\]|\[\,", re.IGNORECASE)
        X.columns = [regex.sub("_", col) for col in X.columns.values]
        # if any(x in str(col) for x in {'(', '[', ']', ')', ','}) else col
        return X

class one_hotdummies(BaseEstimator, TransformerMixin):# one-hot编码
    def __init__(self,
                 cate_list=None,
                 num_list =None,  
                 diff_num: int = 10,
                 ):
        self.cate_list = cate_list
        self.num_list = num_list
        self.diff_num = diff_num
        self.model_enc=OneHotEncoder()

    def fit(self, X, y=None):
        X = X.copy()
        if self.cate_list is None:
            self.cate_list = []
            for col in X.columns:
                kind = get_kind(x=X[col], diff_limit=self.diff_num)
                if kind == 'categorical':
                    self.cate_list.append(col)
        if self.num_list is None:
            self.num_list = []
            for col in X.columns:
                kind = get_kind(x=X[col], diff_limit=self.diff_num)
                if kind == 'numeric':
                    self.num_list.append(col)
        X_cate = X[[col for col in self.cate_list]]
        self.model_enc.fit(X_cate)
        return self
    
    def transform(self, X):
        X = X.copy()
        X_cate = X[[col for col in self.cate_list]]
        X_num = X[[col for col in self.num_list]]
        x_1 =pd.DataFrame(self.model_enc.transform(X_cate).toarray())
        X_new =pd.concat((X_num,x_1),axis=1)
        return X_new
    
class scaler(BaseEstimator, TransformerMixin): #已修改
    def __init__(self,
                 method: str = 'Standard',
                 num_list: list = None,
                 cate_list: list = None,
                 diff_num: int = 10
                 ):
        self.method = method
        self.num_list = num_list
        self.cate_list = cate_list
        self.diff_num = diff_num
        self.standard = StandardScaler()
        self.minmax =  MinMaxScaler()

    def fit(self, X, y=None):
        if self.num_list is None:
            self.num_list = []
            for col in X.columns:
                kind = get_kind(x=X[col], diff_limit=self.diff_num)
                if kind == 'numeric':
                    self.num_list.append(col)
        if self.cate_list is None:
            self.cate_list = []
            for col in X.columns:
                kind = get_kind(x=X[col], diff_limit=self.diff_num)
                if kind == 'categorical':
                    self.cate_list.append(col)
        if self.method == 'Standard':
            self.standard.fit(X[self.num_list])
        elif self.method == 'MinMax':
            self.minmax.fit(X[self.num_list])      
        return self

    def transform(self, X):
        X = X.copy()
        if self.method == 'Standard':
            X[self.num_list] = self.standard.transform(X[self.num_list])
        elif self.method == 'MinMax':
            X[self.num_list] = self.minmax.transform(X[self.num_list])
        return X
    

class HReport(object): #直方图
    def __init__(self,
                 num_list: list = None,
                 bins: int=20,
                 diff_num: int = 10):
        self.num_list = num_list
        self.diff_num = diff_num
        self.bins=bins

    def show(self, X):
        X = X.copy()
        if self.num_list is None:
            self.num_list = []
            for col in X.columns:
                kind = get_kind(x=X[col], diff_limit=self.diff_num)
                if kind == 'numeric':
                    self.num_list.append(col)
        for col in self.num_list:
            plt.hist(x = X[col], # 指定绘图数据
                            bins = self.bins, # 指定直方图中条块的个数
                              color = 'steelblue', # 指定直方图的填充色
                                 edgecolor = 'black' # 指定直方图的边框色
                          )
            plt.title(col)
            plt.show()
        return self
    
if __name__ == '__main__':
    from sklearn.metrics import f1_score

    # loan = pd.read_csv('small_loan.csv')
    # xf = xgb_fill()
    # loan = xf.fit_transform(loan.drop('response',axis=1),loan['response'])
    # print(loan.head())
    from sklearn.model_selection import train_test_split
    from sklearn.preprocessing import StandardScaler, MinMaxScaler

    data = pd.read_csv('small_loan.csv')
    data.rename(columns={'response': 'y'}, inplace=True)
    X_ = data.drop(['id', 'y'], axis=1)
    y_ = data['y'].values
    x_train, x_test, y_train, y_test = train_test_split(X_, y_, test_size=0.2, random_state=0)

    pipe = Pipeline(
        [('wrong_fillna', wrong_value_fillna(wrong_value=['.', '?'])),
         ('xgb_fillna', xgb_fill()),
         # ('base_fillna', base_fill(cate_method='mode', num_method='median')),
         ('fix', fix_outlier(how='self_percent', pmin=0.05, pmax=0.95)),
         ('fea_select', feature_select()),
         ('monobins', binning(how='mono')),
         ('dummy', dummies()),
         ('ss', MinMaxScaler())
         ])

    x_train = pipe.fit_transform(x_train, y_train)
    x_test = pipe.transform(x_test)
    dtc = DecisionTreeClassifier()
    dtc.fit(x_train, y_train)
    y_hat = dtc.predict(x_test)
    cm = confusion_matrix(y_true=y_test, y_pred=y_hat)
    print(cm)
