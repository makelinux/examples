#!/usr/bin/env python2.3
# -*- coding: UTF-8 -*-

from passed import passed


try:
    raise "Ex"
except:
    pass


# https://docs.python.org/3.10/whatsnew/2.0.html


comprehension = [c for c in 'ab' if c > 'a']
assert 'a' not in comprehension
assert 'b' in comprehension

# https://docs.python.org/3.10/whatsnew/2.1.html


def function():
    def closure():
        pass
    closure()


# https://docs.python.org/3.10/whatsnew/2.2.html


class C(object):
    def __init__(self):
        pass


assert C.__name__ == 'C'


# https://docs.python.org/3.10/whatsnew/2.0.html


comprehension = [c for c in 'ab' if c > 'a']
assert 'a' not in comprehension
assert 'b' in comprehension


assert C.__name__ == 'C'



import logging
import csv


# before 2.4

comprehension = [c for c in 'ab' if c > 'a']
assert 'a' not in comprehension
assert 'b' in comprehension

'%(page)i: %(title)s' % {'page': 2, 'title': 'The Best of Times'}

# https://docs.python.org/3.10/whatsnew/2.3.html


def sipmple_generator(N):
    for i in range(N):
        yield i


gen = sipmple_generator(3)
assert gen.next() == 0
assert gen.next() == 1
assert gen.next() == 2

assert list(enumerate(['a', 'b', 'c'])) == [(0, 'a'), (1, 'b'), (2, 'c')]

assert bool(1) is True
assert bool([]) is False
assert range(5)[::2] == [0, 2, 4]

# older

assert([0, 1].pop() == 1)
l = list().append(2)
assert(l.pop() == 1)

passed()
