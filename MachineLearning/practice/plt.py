import numpy as np
import matplotlib.pyplot as plt
from sklearn.metrics import confusion_matrix


def draw_confusion_matrix(y_test, y_pred):
    con_fmt = confusion_matrix(y_true=y_test, y_pred=y_pred)
    fig, ax = plt.subplots(figsize=(2.5, 2.5))
    ax.matshow(con_fmt, cmap=plt.cm.Blues, alpha=0.3)
    for i in range(con_fmt.shape[0]):
        for j in range(con_fmt.shape[1]):
            ax.text(x=j, y=i, s=con_fmt[i, j], va='center', ha='center')
    plt.xlabel("predicted label")
    plt.ylabel("true label")
    plt.show()


def draw_validation_curve(train_scores, test_scores, param_range, y_range):
    train_mean = np.mean(train_scores, axis=1)
    train_std = np.std(train_scores, axis=1)
    test_mean = np.mean(test_scores, axis=1)
    test_std = np.std(test_scores, axis=1)
    plt.plot(param_range, train_mean, color='blue', marker='o', markersize=5, label='Training Accuracy')
    plt.fill_between(param_range, train_mean + train_std, train_mean - train_std, alpha=0.15, color='blue')
    plt.plot(param_range, test_mean, color='green', marker='s', linestyle='--', markersize=5,
             label='Validation Accuracy')
    plt.fill_between(param_range, test_mean + test_std, test_mean - test_std, alpha=0.15, color='green')
    plt.grid()
    plt.xscale("log")
    plt.xlabel("Parameter C")
    plt.ylabel("Accuracy")
    plt.legend(loc='lower right')
    plt.ylim(y_range)
    plt.show()
