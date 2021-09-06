import numpy as np

X = np.array([1,2,3,4,5])

"""
Standard Scaler
"""
from sklearn.preprocessing import StandardScaler
s = StandardScaler()
X2 = s.fit_transform(X.reshape(-1, 1))
X2.mean(), X2.std()

"""
MinMax Scaler
"""
from sklearn.preprocessing import MinMaxScaler

s2 = MinMaxScaler()
X3 = s2.fit_transform(X.reshape(-1, 1))
X3.mean(), X3.std()

"""
normalize 
"""
from sklearn.preprocessing import normalize
X4 = np.array([1, -1, 2], [2, 1, 0], [0, 1, -1])
X4_normalized = normalize(X4, norm="l2")
np.square(X4_normalized[0,:]).sum()

"""
log transformer
"""
X_log = np.log(X)

"""
power transformer
"""
from sklearn.preprocessing import PowerTransformer
pt = PowerTransformer()
X_powered = pt.fit_transform(X)

"""
two sperate
"""
X5 = (X>3).astype(int)

"""
label encoder
"""
X6 = ['b','a', 'b', 'c', 'b']
from sklearn.preprocessing import LabelEncoder
l = LabelEncoder()
X7 = l.fit_transform(X6)

"""
OneHot Encoder
"""
from sklearn.preprocessing import OneHotEncoder
oneHotEncoder = OneHotEncoder(sparse=False)
X8 = oneHotEncoder.fit_transform(X7.reshpae(-1, 1))

"""
LabelBinarizer works like OneHotEncoder.
"""
from sklearn.preprocessing import LabelBinarizer
X9 = LabelBinarizer().fit_transform(X6)