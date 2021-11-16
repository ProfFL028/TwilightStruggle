import pandas as pd


def column_to_dummies(data, column_name, ohe=None):
    from sklearn.preprocessing import OneHotEncoder
    if ohe is None:
        ohe = OneHotEncoder(drop='first')
    dummies = ohe.fit_transform(data[[column_name]])
    dummies = pd.DataFrame(dummies.toarray())
    dummies.columns = [column_name + '-' + str(i) for i in range(len(dummies.columns))]
    for c_name in dummies.columns:
        if c_name in data.columns:
            data.drop(columns=c_name, inplace=True)
    data = data.join(dummies)
    data.drop(columns=[column_name], inplace=True)
    return data, ohe


def predict(X_train, X_test, y_train, y_test, classifier, score):
    classifier.fit(X_train, y_train)
    y_pred = classifier.predict(X_test)

    print("score ->", score(y_test, y_pred))
    return y_pred


def plot_confusion_matrix(y_true, y_pred):
    import matplotlib.pyplot as plt
    from sklearn.metrics import confusion_matrix
    con_matrix = confusion_matrix(y_true=y_true, y_pred=y_pred)
    print(con_matrix)
    fig, ax = plt.subplots(figsize=(2.5, 2.5))
    ax.matshow(con_matrix, cmap=plt.cm.Blues, alpha=0.3)
    for i in range(con_matrix.shape[0]):
        for j in range(con_matrix.shape[1]):
            ax.text(x=j, y=i, s=con_matrix[i, j], va='center', ha='center')
    plt.xlabel('Predict Label')
    plt.ylabel('true label')
    plt.show()

