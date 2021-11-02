# -*- coding: utf-8 -*-
"""
Created on Sun Oct 31 13:54:20 2021

@author: prof_fl
"""

import numpy as np


class Perceptron(object):
    """
    Perceptron for sloving classification problem
    @attr eta: learning rate default 0.01
    @attr n_iter: epoches that the perceptron will iterate
    @attr random_state: seed value for generating random initial values of w_
    @attr w_ parameters in perceptron which have size of X.shape[1] + 1, w[0] as b for changing from > b to > 0
    @attr errors_ store errors values in every epoch

    """

    def __init__(self, eta=0.01, n_iter=50, random_state=1):
        """
        construct
        """
        self.eta = eta
        self.n_iter = n_iter
        self.random_state = random_state
        self.w_ = []
        self.errors_ = []

    def fit(self, X, y):
        """
        fit the model by giving X and y.
        In each epoch w_ will be updated by errors multi X(x0=1)
        @attr X: input array
        @attr y: target
        """

        rs = np.random.RandomState(self.random_state)
        self.w_ = rs.normal(loc=0.0, scale=0.01, size=1 + X.shape[1])
        self.errors_ = []

        for epoch in range(self.n_iter):
            errors = 0
            for (xi, y) in zip(X, y):
                update = self.eta * (y - self.predict(xi))
                self.w_[1:] += update * xi
                self.w_[0] += update
                errors += int(update != 0.0)
            self.errors_.append(errors)

        return self

    def net_input(self, xi):
        """
        calculate net input
        """
        return np.dot(xi, self.w_[1:]) + self.w_[0]

    def predict(self, xi):
        """
        predict xi by current w_.
        """
        return 1 if self.net_input(xi) > 0 else -1
