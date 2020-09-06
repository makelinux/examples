#!/usr/bin/env python2.7

from passed import passed

# https://docs.python.org/3.10/whatsnew/2.7.html

assert {1, 2} == set([1, 2])
assert {x: x * x for x in range(3)} == {0: 0, 1: 1, 2: 4}

from collections import OrderedDict

# https://docs.python.org/3.10/whatsnew/2.7.html#pep-372-adding-an-ordered-dictionary-to-collections

d = OrderedDict([('a', 1), ('b', 2), ('c', 3)])
d['b'] = 4

assert d == OrderedDict([('a', 1), ('b', 4), ('c', 3)])

assert d.popitem(last=False) == ('a', 1)

import argparse

import logging
import logging.config
import importlib

passed()
