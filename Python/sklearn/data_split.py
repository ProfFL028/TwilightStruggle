

def balance_sample(X, y, op_set=1, ref_set=0):
    """
    balance subset y[op_set] size to y[ref_set]
    @param X X inputs
    @param y y output
    @param op_set mutable set
    @param ref_set reference set

    @return X_bal,y_bal, where len(y_bal[op_set])=len(y_bal[ref_set])
    """
    import numpy as np
    from sklearn.utils import resample

    X_unsampled, y_unsampled = resample(X[y == op_set], y[y == op_set], replace=True, n_samples=X[y == ref_set].shape[0])
    X_bal = np.vstack((X[y == ref_set], X_unsampled))
    y_bal = np.hstack((y[y == ref_set], y_unsampled))

    return X_bal, y_bal

