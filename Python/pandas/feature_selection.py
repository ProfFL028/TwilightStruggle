import pandas as pd


def age_to_int(age, step=5, young_age=20, old_age=60, default=0, old_age_value=99):
    """
    separate `age` to age intervals by `step`.
    notice it will convert age to int automatically, for that is not numeric it will return `default`
    and for these small than 0 and greater than 120, it will return `default` too.
    for age like '33.99' it will treat as 33 instead of `default`

    usage: data_age = data['age'].apply(lambda age: age_to_int(age)

    @param age age value in columns
    @param step interval size
    @param young_age set `age` smaller than it be 1
    @param old_age set `age` greater than it be `old_age_value`
    """
    if age is None:
        return default
    if str(age).isnumeric():
        int_age = int(age)
        if int_age <= 0 or int_age >= 120:
            return default
        if int_age < young_age:
            return 1
        if int_age >= old_age:
            return old_age_value
        return (int_age - young_age + 1) // step + 1
    return default


def column_mapping_str(str_list, begin_idx=0):
    """
    giving a string list, return a mapping string.
    usage1: str_list=['a', 'b', 'c'] returns {'a': 0, 'b': 1, 'c': 2}
    usage2: column_mapping_str(data['column_name'].unique())
    """
    label_str = "{"
    for idx, key in enumerate(str_list):
        label_str = "".join([label_str, "'", str(key), "'", ": ", str(idx + begin_idx), ", "])
    label_str = label_str[0:-2]
    label_str = "".join([label_str, "}"])
    return label_str


def one_hot_encoder_column(input_df, column_name, label_mapping, fill_na=0, column_names=None):
    """
    given a dataframe and column_name, return one-hot encoded dataframe(it always drop first)
    """
    from sklearn.preprocessing import OneHotEncoder
    mapped_df = input_df[column_name].map(label_mapping).fillna(fill_na).astype(int)
    ohe_encoder = OneHotEncoder(drop='first')
    ohe_arr = ohe_encoder.fit_transform(mapped_df.values.reshape(-1, 1))
    if column_names is None:
        column_names = ["_".join([column_name, str(i)]) for i in range(0, ohe_arr.shape[1])]
    if ohe_arr.shape[1] != len(column_names):
        print("column_names.len doesn't equals to one-hot-encoded shape, use default:")
        column_names = ["_".join([column_name, str(i)]) for i in range(0, ohe_arr.shape[1])]
    ohe_df = pd.DataFrame(ohe_arr.toarray(), columns=column_names, index=input_df.index)
    return ohe_df, ohe_encoder


def object_feature_helper(data, by='y', label_mapping_count=10, threshold=0.1, plot=False):
    """
    given a dataframe, print some advices for object columns feature selection.
    for column classification counts are less(eq) than `label_mapping_count`, it will output label_mapping string.
    for that are great than `label_mapping_count`, it needs further work. It will advice you to convert seldom
    values(threshold * total_count / classification_count) to some other values
    """
    row_counts = data.shape[0]
    print("---------------------------------------------")
    print("data contains [ %d ] records " % row_counts)

    for column in data.columns:
        null_counts = row_counts - data[column].count()
        if null_counts > 0:
            print("%s have %d null values:\n" % (column, null_counts))
        else:
            print("%s do not have any null values." % column)

        if data[column].dtype == object:
            col_value_counts = data[column].value_counts()
            if len(col_value_counts) <= label_mapping_count:
                print(col_value_counts)
                print("use following code to generate features from label mapping:")
                print("%s_mapping = %s" % (column, column_mapping_str(col_value_counts.keys().values)))

                if len(col_value_counts) == 2:
                    print("binary value can use simple binary classification only:")
                    print("data_%s = data['%s'].map(%s_mapping)" % (column, column, column))
                else:
                    print("#TODO: add your logic to handle None")
                    print("data_%s, %s_ohe = one_hot_encoder_column(data, '%s', %s_mapping, fill_na=99)" % (
                        column, column, column, column))
                if plot:
                    data.groupby(column)[by].value_counts().unstack().plot.bar(width=1, stacked=True)
                print("\n\n")
            else:
                print(column, " has [", len(col_value_counts), "] different values, please create features yourself!")
                value_counts = data[column].value_counts()
                seldom_indexes = value_counts[value_counts <= row_counts * threshold / len(col_value_counts)].index
                print("please notice here are some seldom_indexes: ", seldom_indexes)
                print("\n\n")
        else:
            print(column, " is numeric column:")
            print(data[column].describe())
            print("\n\n")
        print("---------------------------------------------")


def fill_na(data, non_list=[], na_value=0):
    """
    fill `data` values in `non_list` with `na_value`
    """
    data_filled = data.fillna(na_value)
    data_filled[data_filled.isin(non_list)] = na_value
    data_filled = data_filled.astype(int)
    return data_filled
