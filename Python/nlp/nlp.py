def get_stop_words(f, encoding='utf-8'):
    """
    @param f: stop_words file path
    @param encoding: encoding, utf-8, gbk
    It will print stop_words count
    @return stop_words <set>: remove duplicated, remove \r\n  and remove leading and tailing blank space.
    """

    stop_words = []
    with open(f, "r", encoding=encoding) as f_stopwords:
        for line in f_stopwords:
            line = remove_strip(line)
            stop_words.append(line)
    stop_words = set(stop_words)
    print("total counts: ", len(stop_words))

    return stop_words


def split_word(document, stop_words, words=[]):
    import jieba
    import re
    if document is None or type(document) is float:
        return ""
    chinese_regular = u"([\u4e00-\u9fa5]+)"
    pattern = re.compile(chinese_regular)
    for word in words:
        jieba.add_word(word)
    li = " ".join(jieba.cut(document))
    vocabulary = []
    chinese_only = pattern.findall(li)
    if chinese_only is not None and len(chinese_only) >= 1:

        for word in chinese_only:
            if word not in stop_words:
                vocabulary.append(word)
    return " ".join(vocabulary)


def remove_strip(str):
    """
    @param str
    @return remove \r\n  and remove leading and tailing blank space in `str`
    """
    return str.replace("\r", "").replace("\n", "").strip()


def tfidf(data, min_df=5, output_dimension=50):
    from sklearn.feature_extraction.text import TfidfVectorizer
    import pandas as pd
    from sklearn.decomposition import PCA

    tfidf_vec = TfidfVectorizer(min_df=min_df)
    x = tfidf_vec.fit_transform(data)
    df = pd.DataFrame(x.toarray(), columns=tfidf_vec.get_feature_names_out())

    pca = PCA(n_components=output_dimension)
    x_pca = pca.fit_transform(df)
    return pd.DataFrame(x_pca), tfidf_vec, pca


def read_corpus(fname, tokens_only=False, encoding='utf-8'):
    import gensim
    import smart_open
    with smart_open.open(fname, encoding=encoding) as f:
        for i, line in enumerate(f):
            tokens = gensim.utils.simple_preprocess(line)
            if tokens_only:
                yield tokens
            else:
                # For training data, add tags
                yield gensim.models.doc2vec.TaggedDocument(tokens, [i])


def sentence_to_vector(sentence, model, stop_words, vec_size=50):
    import numpy as np
    sum_words = np.zeros(vec_size)
    word_count = 0
    for word in split_word(sentence, stop_words):
        if model.wv.__contains__(word):
            sum_words = model.wv[word] + sum_words
            word_count += 1
    sum_words = sum_words / word_count
    return sum_words

