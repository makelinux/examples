#!/usr/bin/env python2.7

from collections import OrderedDict
import logging
import logging.config
import importlib
# import argparse
from passed import passed

# https://docs.python.org/3.10/whatsnew/2.7.html

assert {1, 2} == set([1, 2])
assert {x: x * x for x in range(3)} == {0: 0, 1: 1, 2: 4}

# https://docs.python.org/3.10/whatsnew/2.7.html#pep-372-adding-an-ordered-dictionary-to-collections

a_dict = OrderedDict([('a', 1), ('b', 2), ('c', 3)])
a_dict['b'] = 4

assert a_dict == OrderedDict([('a', 1), ('b', 4), ('c', 3)])

assert a_dict.popitem(last=False) == ('a', 1)


passed()
