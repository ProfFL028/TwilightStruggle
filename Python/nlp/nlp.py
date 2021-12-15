def get_stop_words(f):
    """
    @param f: stop_words file path
    It will print stop_words count
    @return stop_words <set>: remove duplicated, remove \r\n  and remove leading and tailing blank space.
    """

    stop_words = []
    with open(f, "r", encoding='utf-8') as f_stopwords:
        for line in f_stopwords:
            line = remove_strip(line)
            stop_words.append(line)
    stop_words = set(stop_words)
    print("total counts: ", len(stop_words))

    return stop_words


def remove_strip(str):
    """
    @param str
    @return remove \r\n  and remove leading and tailing blank space in `str`
    """
    return str.replace("\r", "").replace("\n", "").strip()
