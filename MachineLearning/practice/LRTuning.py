import numpy as np
import pandas as pd
from sklearn.linear_model import LogisticRegression
from sklearn.model_selection import GridSearchCV
from sklearn.metrics import f1_score
import warnings
from plt import *

pd.set_option("expand_frame_repr", False)
warnings.filterwarnings("ignore")
pd.set_option('display.float_format', lambda x: '%.2f' % x)  # 数值不显示科学计数法，保留两位小数
np.set_printoptions(suppress=True)


class LRTuning(object):
    def __init__(self, X_train, X_test, y_train, y_test, scoring='f1_weighted', cv=10, random_seed=42):
        self.X_train = X_train
        self.X_test = X_test
        self.y_train = y_train
        self.y_test = y_test
        self.scoring = scoring
        self.cv = cv
        self.random_seed = random_seed

        self.gs = None

    def fit_transform(self):
        param_grid = {
            'C': [0.1, 0.01, 0.001, 1, 10, 100]
        }
        model = LogisticRegression(random_state=self.random_seed)
        gs = GridSearchCV(estimator=model, param_grid=param_grid, scoring=self.scoring, cv=self.cv)
        gs.fit(self.X_train, self.y_train)
        print("best score: %.4f, and best params: %s" % (gs.best_score_, gs.best_params_))
        y_pred = gs.predict(self.X_test)
        print("LR f1_score: %.4f%%" % (f1_score(self.y_test, y_pred) * 100))

        draw_confusion_matrix(self.y_test, y_pred)
        return y_pred

    def predict(self, X):
        return self.gs.predict(X)


