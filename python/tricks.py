#!/usr/bin/env python

def multi_args(a, b, c,):
    assert(a == 1)
    assert(b == 2)
    assert(c == 3)
    pass

args = { 'a': 1, 'b': 2, 'c': 3 }

multi_args(**args)

args = [ 1, 2, 3 ]

multi_args(*args)
