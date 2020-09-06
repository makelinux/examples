#!/usr/bin/env python3.9

from passed import passed

# https://docs.python.org/3.9/whatsnew/3.9.html

# https://docs.python.org/3.9/whatsnew/3.9.html#dictionary-merge-update-operators

d1 = {'a': 0, 'b': 2}
d2 = {'a': 1, 'c': 3}

# Merging dictionaries

assert d1 | d2 == {'a': 1, 'b': 2, 'c': 3}

d1 |= d2

# Updating a dictionary

assert d1 | d2 == {'a': 1, 'b': 2, 'c': 3}
assert d1 == {'a': 1, 'b': 2, 'c': 3}


# In type annotations you can now use built-in collection types such as list
# and dict as generic types instead of importing the corresponding
# capitalized types.
# https://docs.python.org/3.9/whatsnew/3.9.html#pep-585-builtin-generic-types


def is_list(l: list[int]) -> bool:
    return isinstance(l, list)


assert is_list([1, 2, 3])

passed()
