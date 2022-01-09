import numpy as np
import pandas as pd
import os
import warnings

from sklearn.preprocessing import OneHotEncoder
from sklearn.impute import SimpleImputer

pd.set_option("expand_frame_repr", False)
warnings.filterwarnings("ignore")
pd.set_option('display.float_format', lambda x: '%.2f' % x)  # 数值不显示科学计数法，保留两位小数
np.set_printoptions(suppress=True)


def column_mapping_str(col_value_counts, begin_idx=0):
    """
    根据指定列的值，生成mapping字符串
    """
    label_str = "{"
    for idx, key in enumerate(col_value_counts.keys()):
        label_str = "".join([label_str, "'", str(key), "'", ": ", str(idx + begin_idx), ", "])
    label_str = label_str[0:-2]
    label_str = "".join([label_str, "}"])
    return label_str


class DataPreprocessing(object):
    """
    数据预处理
    """

    def __init__(self):
        self.data = None
        self.test_data = None
        self.nRows = 0
        self.nCols = 0
        self.features = []
        self.test_features = []

        self.column_transformers = {}

    def load_data(self, train_path="train.csv", test_path="test.csv", sep=",", encoding="gbk", index_col=None,
                  header=0):
        """
        加载数据。
        @param train_path 训练文件的路径
        @param test_path 测试文件路径
        @param sep 字段分隔符。默认'，'，查看文件，也可能是';', ' '等。
        @param encoding 编码集。默认是'gbk'，也可能是'utf-8', 'ansi'等。如果查看的数据是乱码，试试用其他编码集。
        @param index_col 索引列。默认没有索引，通常为第一列，或者为"ID"等。
        @param header 标题行。通常第一行为标题行，也可能没有
        """
        if train_path.endswith(".csv") or train_path.endswith(".txt"):
            self.data = pd.read_csv(train_path, sep=sep, encoding=encoding, index_col=index_col, header=header)
            self.test_data = pd.read_csv(test_path, sep=sep, encoding=encoding, index_col=index_col, header=header)
        elif train_path.endswith(".xls") or train_path.endswith(".xlsx"):
            self.data = pd.read_excel(train_path, index_col=index_col, header=header)
            self.test_data = pd.read_excel(test_path, index_col=index_col, header=header)

        print("加载数据\n---------------------------------\n如果报错，请检查文件相对路径:")
        print(os.getcwd() + "/" + train_path)
        self.nRows = self.data.shape[0]
        self.nCols = self.data.shape[1]
        if self.nRows > 0:
            print("合计：%d行， %d列" % (self.nRows, self.nCols))
            print("前五行数据为（如果显示乱码，用dp.load_data(..., encoding='utf-8')等重新尝试：")
            print(self.data.head(5))
        else:
            print("！！！加载数据出错，请检查文件路径是否正确！！！")
        return self.data.shape

    def explore(self, row_null_threshold=10, num_txt_threshold=30):
        """
        数据探索：数据类型检查，给出常规预处理方案，检查空值。
        @param num_txt_threshold 如果某列数据不同值的个数大于num_txt_threshold，则认为此列为数字或文本。
        @param row_null_threshold 如果某行的空值数大于row_null_threshold, 则认为此行为无效数据，删除。
        """
        print("----------------行空值检查：-------------------")
        row_nulls = self.data

        if len(row_nulls[row_nulls > row_null_threshold]) > 0:
            print("将删除第 ", row_nulls[row_nulls > row_null_threshold].index, " 的数据")
            self.data.drop(labels=row_nulls[row_nulls > row_null_threshold].index, axis=0, inplace=True)

        print("----------------列值检查：------------------")
        col_nulls = self.data.isnull().sum(axis=0)
        col_nulls = col_nulls[col_nulls > 0]
        print("列空值检查，以下列包含空值：", col_nulls.keys)

        for column in self.data.columns:
            print("--------------- %s 处理--------------" % column)
            if "id" in column.lower():
                print("此列可能为id列，不建议加入特征中")
                continue

            col_value_counts = self.data[column].value_counts()
            if len(col_value_counts) == 1:
                print("%s 列是常数列，不建议加入到特征中。" % column)
            elif len(col_value_counts) <= num_txt_threshold:
                print("%s 列共有 %d个不同的值，当做 类型 字段处理." % (column, len(col_value_counts)))
                print("每个类型的分布情况如下：")
                print(col_value_counts)
                print()
                print("可以参考以下代码(列名如果是中文，请修改成英文。合并小类到大类中)：")
                print("````````````````````````````````````````````")
                print("%s_mapping = %s" % (column, column_mapping_str(col_value_counts)))
                if len(col_value_counts) == 2:
                    print("#%s 列只有两个值，直接二值化。" % column)
                    print("data_%s = data['%s'].map(%s_mapping)" % (column, column, column))
                else:
                    print("#添加空值处理的逻辑")
                    print("si_%s = SimpleImputer(strategy='most_frequent')" % column)
                    print("dp.impute(%s, si_%s)" % (column, column))
                    print("dp.ohe_col('%s', %s_mapping, fill_na=0)" % (column, column))
                print("````````````````````````````````````````````")

                if self.data[column].dtype == object:
                    col_len = self.data[column].apply(lambda content: len(str(content).strip()))
                    if col_len[col_len > 20].count() < 10:
                        print("dp")

    def impute(self, column_name, impute):
        data_imputed = impute.fit_transform(self.data['column_name'].values.reshape(-1, 1))
        data_imputed

    def ohe_col(self, column_name, label_mapping, fill_na=0):
        """
        根据label_mapping,将某列转换成one-hot编码（drop='first')
        """
        mapped_df = self.data[column_name].map(label_mapping).fillna(fill_na).astype(int)
        ohe_encoder = OneHotEncoder(drop='first')
        ohe_arr = ohe_encoder.fit_transform(mapped_df.values.reshape(-1, 1))
        column_names = ["_".join([column_name, str(i)]) for i in range(0, label_mapping.keys())]
        ohe_df = pd.DataFrame(ohe_arr.toarray(), columns=column_names, index=self.data.index)
        self.features.append(ohe_df)
        """
        对测试集进行同样的处理
        """
        mapped_df = self.test_data[column_name].map(label_mapping).fillna(fill_na).astype(int)
        test_ohe_arr = ohe_encoder.fit_transform(mapped_df.values.reshape(-1, 1))
        test_df = pd.DataFrame(test_ohe_arr.toarray(), columns=column_names, index=self.test_data.index)
        self.test_features.append(test_df)


if __name__ == '__main__':
    dp = DataPreprocessing()
    dp.load_data("./data/1_train.xlsx", "./data/1_test.xlsx")
    dp.explore()
