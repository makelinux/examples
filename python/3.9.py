#!/usr/bin/env python3.9

from passed import passed

# https://docs.python.org/3.9/whatsnew/3.9.html

# https://docs.python.org/3.9/whatsnew/3.9.html#dictionary-merge-update-operators

dict_1 = {'a': 0, 'b': 2}
dict_2 = {'a': 1, 'c': 3}

# Merging dictionaries

assert dict_1 | dict_2 == {'a': 1, 'b': 2, 'c': 3}

dict_1 |= dict_2

# Updating a dictionary

assert dict_1 | dict_2 == {'a': 1, 'b': 2, 'c': 3}
assert dict_1 == {'a': 1, 'b': 2, 'c': 3}


# In type annotations you can now use built-in collection types such as list
# and dict as generic types instead of importing the corresponding
# capitalized types.
# https://docs.python.org/3.9/whatsnew/3.9.html#pep-585-builtin-generic-types


def is_list(a_list: list[int]) -> bool:
    return isinstance(a_list, list)


assert is_list([1, 2, 3])

assert 'ab'.removeprefix('a') == 'b'
assert 'ab'.removesuffix('b') == 'a'

passed()
