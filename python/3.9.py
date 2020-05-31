#!/usr/bin/env python3.9

# https://docs.python.org/3.9/whatsnew/3.9.html

from datetime import *

# https://docs.python.org/3.9/whatsnew/3.9.html#dictionary-merge-update-operators

d1 = {'a':0, 'b':2}
d2 = {'a':1, 'c':3}

assert(d1 | d2 == {'a': 1, 'b': 2, 'c': 3})

d1 |= d2

assert(d1 == {'a': 1, 'b': 2, 'c': 3})

# https://docs.python.org/3.9/whatsnew/3.9.html#pep-585-builtin-generic-types

def sum(l: list[int]) -> int:
    s = 0
    for i in l:
        s+=i
    return s

assert(sum([1,2,3]) == 6)

from sys import *
print("passed", version)
