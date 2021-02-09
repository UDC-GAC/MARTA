
def inv_dict(d):
    """
    Invert string dictionary, and lowercase all keys and values

    :param d: String dictionary
    :type d: [type]
    :raises TypeError: Input is not a dictionary, or keys are not strings, or
    values are not in a list
    :return: Inverted string dictionary
    :rtype: dict
    """
    new_dict = {}
    if type(d) != dict():
        return new_dict
    for k in d.keys():
        if type(k) != str or type(d[k]) != list:
            raise TypeError
        for v in d[k]:
            if type(v) != str:
                raise TypeError
            new_dict[v.lower()] = k.lower()
    return new_dict
