

def balance_down_sample(X, y, less=1, more=0):
    import numpy as np
    from sklearn.utils import resample

    X_unsampled, y_unsampled = resample(X[y==more], y[y==more], replace=True, n_samples=X[y==less].shape[0])
    X_bal = np.vstack((X[y==less], X_unsampled))
    y_bal = np.hstack((y[y==less], y_unsampled))

    return X_bal, y_bal


def balance_up_sample(X, y, less=1, more=0):
    import numpy as np
    from sklearn.utils import resample

    X_unsampled, y_unsampled = resample(X[y==less], y[y==less], replace=True, n_samples=X[y==more].shape[0])
    X_bal = np.vstack((X[y==more], X_unsampled))
    y_bal = np.hstack((y[y==more], y_unsampled))

    return X_bal, y_bal