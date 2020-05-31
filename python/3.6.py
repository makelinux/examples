#!/usr/bin/env python3.6

# https://docs.python.org/3.6/whatsnew/3.6.html

# https://docs.python.org/3.6/whatsnew/3.6.html#pep-498-formatted-string-literals

i = 1
assert(f'{i}' == '1')
assert(f'i={i:02}' == 'i=01')
assert(f"{i:#0x}" == "0x1")  # using integer format specifier

r = 1.23
assert(f'{r}' == '1.23')
assert(f'r={r:1.2}' == 'r=1.2')

str = 'a'
assert(f'{str}' == 'a')
assert(f'{str!r}' == "'a'")

# https://docs.python.org/3.6/whatsnew/3.6.html#pep-526-syntax-for-variable-annotations

string: str
i: int

from sys import *
print("passed", version)
