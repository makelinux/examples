#!/usr/bin/env python3.1

from passed import passed

# https://docs.python.org/3.10/whatsnew/3.0.html

assert 3 / 2 == 1.5
assert isinstance(range(3), range)

import io

buff = io.StringIO()

# https://docs.python.org/3.10/whatsnew/3.0.html#print-is-a-function

print(1, 2, 3, sep=", ", end="!", file=buff)

assert buff.getvalue() == "1, 2, 3!"


class Meta(type):
    pass


class Foo(metaclass=Meta):
    pass


passed()
