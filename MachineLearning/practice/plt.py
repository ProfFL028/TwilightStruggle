
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