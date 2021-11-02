import numpy as np


class AdalineGD(object):
    def __init__(self, eta=0.01, n_iter=50, random_state=1, shuffle=True):
        self.eta = eta
        self.n_iter = n_iter
        self.random_state = random_state
        self.w_ = []
        self.costs_ = []
        self.shuffle = shuffle
        self.w_initialized = False

    def fit(self, X, y):
        self._init_weights(X.shape[1] + 1)
        self.costs_ = []

        for epoch in range(self.n_iter):
            if self.shuffle:
                self._shuffle(X, y)

            cost = []
            for xi, target in zip(X, y):
                cost.append(self._update_weights(xi, target))

            avg_cost = sum(cost) / len(y)
            self.costs_.append(avg_cost)

        return self

    def partial_fit(self, X, y):
        if not self.w_initialized:
            self._init_weights(X.shape[1])

        if y.ravel().shape[0] > 1:
            for xi, target in zip(X, y):
                self._update_weights(xi, target)
        else:
            self._update_weights(X, y)
        return self

    def _shuffle(self, X, y):
        r = self.rs.permutation(len(y))
        return X[r], y[r]

    def _init_weights(self, m):
        self.rs = np.random.RandomState(self.random_state)
        self.w_ = self.rs.normal(loc=0.0, scale=0.01, size=m)
        self.w_initialized = True

    def _update_weights(self, xi, target):
        output = self.activation(self.net_input(xi))
        error = target - output
        self.w_[1:] += self.eta * xi.dot(error)
        self.w_[0] += self.eta * error
        cost = 0.5 * error ** 2
        return cost

    def net_input(self, X):
        return np.dot(X, self.w_[1:]) + self.w_[0]

    def activation(self, X):
        return X

    def predict(self, X):
        return np.where(self.activation(self.net_input(X)) >= 0.0, 1, -1)

