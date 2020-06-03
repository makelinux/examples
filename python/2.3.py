#!/usr/bin/env python2.3
# -*- coding: UTF-8 -*-

# before 2.4

comprehension = [c for c in 'ab' if c > 'a']
assert('a' not in comprehension)
assert('b' in comprehension)

'%(page)i: %(title)s' % {'page': 2, 'title': 'The Best of Times'}

# https://docs.python.org/3.10/whatsnew/2.3.html


def sipmple_generator(N):
    for i in range(N):
        yield i


gen = sipmple_generator(3)
assert(gen.next() == 0)
assert(gen.next() == 1)
assert(gen.next() == 2)

assert(list(enumerate(['a', 'b', 'c'])) == [(0, 'a'), (1, 'b'), (2, 'c')])

assert(bool(1) is True)
assert(bool([]) is False)
assert(range(5)[::2] == [0, 2, 4])

import logging
import csv

import passed
