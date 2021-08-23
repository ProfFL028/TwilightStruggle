import pandas as pd
import numpy as np
from numpy.random import permutation

class DFUtils():
    
    @staticmethod
    def serIndex(series, index=False):
        if index:
            return series[series].index
        return series[series].index.tolist()

    @staticmethod
    def isDataFrame(data):
        return isinstance(data, pd.DataFrame)
        
    @staticmethod
    def countUnique(data):
        ''' compute unique count in every column. Exclues NA!!. '''
        return data.apply(lambda x: x.unique, axis=0)

    @staticmethod
    def naCountInColumn(data):
        return data.isnull().sum(axis=0)

    @staticmethod
    def naCountInRow(data):
        return data.isnull().sum(axis=1)

    @staticmethod
    def sampleData(data, percent=0.1, rowCount = 100):
        a = max(int(percent * data.shape[0]), int(rowCount))
        return data.loc[permutation(data.index)[:a], :]

    @staticmethod
    def allNaCols(data, index=False):
        if index:
            return DFUtils.naCountInColumn(data) == data.shape[0]
        return DFUtils.serIndex(DFUtils.naCountInColumn(data) == data.shape[0])

    @staticmethod
    def allNaRows(data):
        return DFUtils.naCountInRow(data) == data.shape[1]

    @staticmethod
    def isNumeric(data, colName = None):
        if colName is None:
            colName = data.columns.toList()
        dataTypeColumn = data.loc[:, colName].dtypes
        t = (dataTypeColumn == int).values | (dataTypeColumn == float).values

        return pd.Series(t, index=dataTypeColumn.index)

    @staticmethod
    def maxStrLenInValue(data, strCols =None):
        if strCols is not None:
            return data[strCols].apply(lambda x: np.max(x.str.len()), axis=0)
        return data.apply(lambda x: np.max(x.str.len()) if x.dtype.kind == '0' else np.nan, axis=0)