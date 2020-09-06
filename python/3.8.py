#!/usr/bin/env python3.8

from passed import passed

# https://www.geeksforgeeks.org/awesome-new-features-in-python-3-8/
#
# https://docs.python.org/3/whatsnew/3.8.html


# https://docs.python.org/3/whatsnew/3.8.html#positional-only-parameters

# Arguments before / are considered as positional arguments only

def pos_only_arg_demo(pos_only_arg, /):
    return pos_only_arg


try:
    res = pos_only_arg_demo(pos_only_arg='Fail')
except TypeError:
    res = pos_only_arg_demo('Passed')
assert res == 'Passed'

# Assignment Expression
# https://docs.python.org/3/whatsnew/3.8.html#assignment-expressions

assert (an_int := 2) > 1

# https://docs.python.org/3/whatsnew/3.8.html#f-strings-support-for-self-documenting-expressions-and-debugging

an_int = 1

assert f'{an_int=}' == 'an_int=1'

# The usual f-string format specifiers allow more control over how the result
# of the expression is displayed:

assert f'{an_int=:.3f}' == 'an_int=1.000'

assert f'{an_int+an_int=}' == 'an_int+an_int=2'

# get_coro get_name set_name

passed()
