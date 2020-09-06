#!/usr/bin/env python2.4

from passed import passed

# https://docs.python.org/3.10/whatsnew/2.4.html#pep-218-built-in-set-objects

assert 1 in set([1, 2])

s = set('ab')
assert 'b' in s
s.add('c')
assert 'c' in s
s.update('d')
assert 'd' in s
s.remove('a')
assert 'a' not in s


# https://docs.python.org/3.10/whatsnew/2.4.html#pep-289-generator-expressions

generator_expression = (c for c in 'ef' if c > 'e')

for c in generator_expression:
    s.add(c)

assert 'e' not in s
assert 'f' in s


# https://docs.python.org/3.10/whatsnew/2.4.html#pep-292-simpler-string-substitutions

import string

t = string.Template('a=$a')
assert t.substitute({'a': 1}) == 'a=1'


# https://docs.python.org/3.10/whatsnew/2.4.html#pep-318-decorators-for-functions-and-methods

def decoration(func):
    def wrapper(arg):
        return 'decorated' + func(arg)
    wrapper.attr = 'decorated'
    return wrapper


@decoration
def decorated(a):
    return a


assert decorated.attr
assert decorated('1') == 'decorated1'

# https://docs.python.org/3.10/whatsnew/2.4.html#pep-322-reverse-iteration

assert list(reversed(xrange(1, 4))) == [3, 2, 1]

# https://docs.python.org/3.10/whatsnew/2.4.html#pep-324-new-subprocess-module

import subprocess

passed()
