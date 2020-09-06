#!/usr/bin/env python2.4

import subprocess
import string
from passed import passed

# https://docs.python.org/3.10/whatsnew/2.4.html#pep-218-built-in-set-objects

assert 1 in set([1, 2])

a_str = set('ab')
assert 'b' in a_str
a_str.add('c')
assert 'c' in a_str
a_str.update('d')
assert 'd' in a_str
a_str.remove('a')
assert 'a' not in a_str


# https://docs.python.org/3.10/whatsnew/2.4.html#pep-289-generator-expressions

generator_expression = (c for c in 'ef' if c > 'e')

for c in generator_expression:
    a_str.add(c)

assert 'e' not in a_str
assert 'f' in a_str


# https://docs.python.org/3.10/whatsnew/2.4.html#pep-292-simpler-string-substitutions

a_str = string.Template('var=$var')
assert a_str.substitute({'var': 1}) == 'var=1'


# https://docs.python.org/3.10/whatsnew/2.4.html#pep-318-decorators-for-functions-and-methods

def decoration(func):
    def wrapper(arg):
        return 'decorated' + func(arg)
    wrapper.attr = 'decorated'
    return wrapper


@decoration
def decorated(arg):
    return arg


assert decorated.attr
assert decorated('1') == 'decorated1'

# https://docs.python.org/3.10/whatsnew/2.4.html#pep-322-reverse-iteration

assert list(reversed(xrange(1, 4))) == [3, 2, 1]

# https://docs.python.org/3.10/whatsnew/2.4.html#pep-324-new-subprocess-module


passed()
