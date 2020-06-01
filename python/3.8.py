#!/usr/bin/env python3.8

# https://www.geeksforgeeks.org/awesome-new-features-in-python-3-8/
#
# https://docs.python.org/3/whatsnew/3.8.html

from datetime import *

# Arguments before / are considered as positional arguments only
#
# https://docs.python.org/3/whatsnew/3.8.html#positional-only-parameters

def add(x, y, /, z = 0):
    a = x + y + z
    return a

try:
    add(x = 2, y = 5)
except:
    res = add(1, 2, 3)
assert(res == 6)

# Assignment Expression
# https://docs.python.org/3/whatsnew/3.8.html#assignment-expressions

assert(b := 2 > 1)

# https://docs.python.org/3/whatsnew/3.8.html#f-strings-support-for-self-documenting-expressions-and-debugging

i = 1

assert(f'{i=}' == 'i=1')

# The usual f-string format specifiers allow more control over how the result of the expression is displayed:

assert(f'{i=:.3f}' == 'i=1.000')

assert(f'{i+i=}' == 'i+i=2')

import asyncio
# get_coro get_name set_name

import passed
