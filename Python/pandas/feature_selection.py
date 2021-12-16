
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
