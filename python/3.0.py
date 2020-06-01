#!/usr/bin/env python3.1

# https://docs.python.org/3.10/whatsnew/3.0.html

import sys
import io

buff = io.StringIO()

# https://docs.python.org/3.10/whatsnew/3.0.html#print-is-a-function
print(1,2,3, sep=",", end="!", file=buff)

assert(buff.getvalue() == "1,2,3!")

class Meta(type):
    pass

class Foo(metaclass=Meta):
    pass

import passed
