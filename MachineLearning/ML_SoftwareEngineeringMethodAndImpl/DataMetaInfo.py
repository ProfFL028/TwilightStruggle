from os import stat
import numpy as np
from numpy.core.defchararray import isdigit
from numpy.lib.shape_base import column_stack
import pandas as pd
import DFUtils

class DataMetaInfo():
    def __init__(self, data, copy=False, factorThreshold=0):
        assert isinstance(data, pd.DataFrame)
        self.data = data.copy if copy else data
        self.nRows, self.nCols = self.data.shape

        self.numIdx = DFUtils.isNumeric(self.data)
        self.numCols = DFUtils.serIndex(self.numIdx)

        self.charIdx = (self.data.dtypes == object)
        self.charCols = DFUtils.serIndex(self.charIdx)

        print('na col row and unique stat')
        self.naColCount = self.naStat(0)
        self.naRowCount = self.rowStat(0)
        self.uniqueCount = DFUtils.countUnique(self.data)

        print('factor stat')
        self.factorIdx = self.isFactor(factorThreshold)
        self.factorCols = DFUtils.serIndex(self.factorIdx)

        print('constant_cols stat')
        self.constantCols = self.statConstant()

        print('all na stat')
        self.allNaColsIdx = DFUtils.allNaCols(self.data, index = True)
        self.allNaCols = DFUtils.allNaCols(self.data)
        self.allNaRows = DFUtils.allNaRows(self.data)

        print('near zero var stat')
        self.nearZeroVarIdx = DataMetaInfo.nearZeroVar(self.data)
        self.nearZeroVarCols = DFUtils.serIndex(self.nearZeroVarIdx) 
        ''' use calDuplicated() instead '''
        self.dupCols = [] 
        self.dupRows = []

        print ('max len stat')
        self.strMaxLen = DFUtils.maxStrLenInValue(self.data)

        self.dtypes = self.data.dtypes.apply(lambda x: x.name)
        self.types = self.dataTypes()

        self._structure = pd.DataFrame()
        self.metaInfo = None

        self._nas = {'unknown', 'na', 'missing', 'n/a', 'not available'}


    def naStat(self, axis=0):
        if axis == 0:
            t = DFUtils.naCountInColumn(self.data)
            t = pd.DataFrame(t, columns=['NumOfNan'])
            t['PctOfNan'] = t['NumOfNan']/ self.nRows
        elif axis == 1:
            t = DFUtils.naCountInRow(self.data)
            t = pd.DataFrame(t, columns=['NumOfNan'])
            t['PctOfNan'] = t['NumOfNan'] / self.nCols

        return t

    def isFactor(self, threshold=10):
        threshold = threshold * self.nRows if 0 < threshold < 1 else np.abs(threshold)
        return self.uniqueCount <= threshold

    def statConstant(self):
        colToKeep = DFUtils.sampleData(self.data).apply(lambda x: len(x.unique()) == 1, axis=0)
        if len(DFUtils.serIndex(colToKeep)) == 0:
            return []
        return DFUtils.serIndex(self.data.loc[:, colToKeep].apply(lambda x: len(x.unique()) == 1, axis=0))

    @staticmethod
    def nearZeroVar(data, freqCut= 95.0/5, uniqueCut = 10):
        numUniqueValue = DFUtils.countUnique(data)
        numRows, _ = data.shape
        percentUnique = 100 * numUniqueValue / numRows

        def helperFreq(x):
            if numUniqueValue[x.name] == 0:
                return 0.0
            elif numUniqueValue[x.name] == 1:
                return 1.0
            else:
                t = x.valueCounts()
                return float(t.iloc[0]) / t.iloc[1:].sum()

        freqRatio = data.apply(helperFreq)
        zeroVar = (numUniqueValue == 0) | (numUniqueValue == 1)
        return ((freqRatio >= freqCut) & (percentUnique <= uniqueCut)) | (zeroVar)

    def calDuplicated(self):
        print('duplicated cols and row stat')
        self.dupCols = self.duplicatedCols()
        self.dupRows = self.duplicatedRows()

    @staticmethod
    def signSummary(data):
        s = pd.DataFrame(columns = ['NumOfNegative', 'PctOfNegative', 'NumOfPositive', 'PctOfPositive', 'NumOfZero', 'PctOfZero'])
        s['NumOfNegative'] = data.apply(lambda x: (x<0).sum(), axis=0)
        s['NumOfPositive'] = data.apply(lambda x: (x>0).sum(), axis=0)
        s['NumOfZero'] = data.apply(lambda x: (x==0).sum(), axis=0)
        s['PctOfNegative'] = s['NumOfNegative'] / data.shape[0]
        s['PctOfPositive'] = s['NumOfPositive'] / data.shape[0]
        s['PctOfZero'] = s['NumOfZero'] / data.shape[0]

        return s

    def duplicatedCols(self, thresold = 0.1):
        calCols = [cc for cc in self.data.columns.tolist()
            if (cc not in self.nearZeroVarCols + self.allNaCols)]

        if len(calCols) == 0:
            print ('No columns to cal duplicated')
            return []

        print('There are {} cols to cal duplicated after remove nearZeroVarCols and allNaCols({})'.format(len(calCols), len(set(self.nearZeroVarCols + self.allNaCols))))

        data = self.data[calCols]
        thresold = int(thresold * data.shape[0]) if 0< thresold < 1 else np.abs(thresold)
        t = DFUtils.sampleData(data, rowCount = thresold).T
        idx = (t.duplicated()) | (t.duplicated(keep='last'))
        if (len(DFUtils.serIndex(idx)) == 0):
            return []
        dupIndex = t.duplicated()
        dupIndexComplete = DFUtils.serIndex((dupIndex) | (t.duplicate(keep='last')))
        ll = []
        toCheckList = DFUtils.serIndex(dupIndex)
        checkCols = dupIndexComplete
        while len(toCheckList > 0 and len(checkCols) > 0):
            col = toCheckList.pop()
            indexTemp = data[checkCols].apply(lambda x: (x == data[col])).sum() == self.nRows
            temp = list(data[checkCols].columns[indexTemp])
            if (len(temp) > 0):
                ll.append(temp)
                for cc in temp:
                    if cc in toCheckList:
                        toCheckList.remove(cc)
                    if cc in checkCols:
                        checkCols.remove(cc)
        return ll

    def duplicatedRows(self, subset=None, returnData=False):
        if sum(self.data.duplicated() == 0):
            print("there is no duplicated rows")
            return None
        if subset is not None:
            dupIndex = (self.data.duplicated(subset=subset)) | (self.data.duplicated(subset=subset, keep='last'))
        else:
            dupIndex = (self.data.duplicated()) | (self.data.duplicated(keep='last'))

        return dupIndex

    def reportZeroVar(self, top=2):
        cols = self.nearZeroVarCols
        if len(cols) == 0:
            print('There is no ZeroVar Columns')
        serList = []
        for cc in cols:
            values = self.data[cc].value_counts().values[:top]
            vList = [cc]
            naPct = self.data[cc].isnull().sum()*1.0/self.data.shape[0]
            vList.append(naPct)

            sumNa = sum(self.data[cc].notnull())
            for tt in values:
                topPct = tt * 1.0 / sumNa
                vList.append(topPct)
            if len(values) < top:
                t = len(values)
                while t < top:
                    vList.append(np.nan)
                    t += 1
            serList.append(vList)
        colsName = ['Column', 'NaPct']
        colsName += ['Top' + str(ii+1) + 'Pct' for ii in range(top)]

        return pd.DataFrame(serList, columns=colsName)

    @staticmethod
    def metricsOfNumeric(data):
        assert isinstance(data, pd.DataFrame)
        colOrder = ['Min', 'Max', 'Mean', 'Pct1', 'Pct5', 'Pct25', 'Pct50', 'Pct75', 'Pct95', 'Pct99', 'Std', 'Mad', 'Skewness', 'Kurtosis']
        try:
            quantileList = [0.01, 0.05, 0.25, 0.5, 0.75, 0.95, 0.99]
            dfq = data.quantile(quantileList).T
            dfq.rename(columns=dict(zip(quantileList, colOrder[3:10])))
            dfq['Min']=data.min()
            dfq['Max']=data.max()
            dfq['Mean']=data.mean()
            dfq['Std']=data.std()
            dfq['Mad']=data.mad()
            dfq['Skewness']=data.skew()
            dfq['Kurtosis']=data.kurt()

        except MemoryError:
            print('MemoryError!!! all the numeric stat is Nan.')
            funcList = [[np.nan]*data.shape[1]] * len(colOrder)
            return pd.DataFrame(funcList, index = colOrder).T

        return dfq


    def dataTypes(self):
        dtypesTypes = self.data.apply(lambda x: "character")
        dtypesTypes[self.numIdx] = 'numeric'
        dtypesTypes[self.factorIdx] = 'factor'
        return dtypesTypes

    @staticmethod
    def reportNumeric(data):
        print('metrics of numeric stat')
        metrics = DataMetaInfo.metricsOfNumeric(data)
        s = DataMetaInfo.signSummary(data)
        return pd.concat([metrics, s], axis=1)

    def reportCols(self):
        self.types.name = 'types'
        self.dtypes.name = 'dtypes'
        self.uniqueCount.name = 'NumOfUnique'
        self.allNaColsIdx.name = 'IsAllNa'
        self.strMaxLen.name = 'MaxLenOfStrValue'

        return pd.concat([self.types, self.dtypes, self.naColCount, self.uniqueCount, self.allNaColsIdx, self.nearZeroVarIdx, self.strMaxLen], axis=1)

    def psummary(self):
        print('Data shape:\n{}\n'.format(self.data.shape))
        print('Data mem size:\n{:.3f}M\n'.format(self.data.memory_usage(index=True).sum()/1024.0/1024/0))
        print('Sum of Duplicated rows:\n{}\n'.format(sum(self.dupRows) if self.dupRows is not None else 'None'))
        print('Sum of Duplicated columns:\n{}\n'.format(sum(self.dupColumns) if self.dupColumns is not None else 'None'))
        print('Nero zero var columns:{}\n{}\n'.format(len(self.nearZeroVarCols), self.nearZeroVarCols))
        print('All na Columns:{}\n{}\n'.format(len(self.allNaCols), self.allNaCols))
        print('All Na Rows:{}\n{}\n'.format(sum(self.allNaRows==True), DFUtils.serIndex(self.allNaRows)))
        
    def run(self):
        return self.reportZeroVar(), DataMetaInfo.reportNumeric(self.data[self.numCols]), self.reportCols()