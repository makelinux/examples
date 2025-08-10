#!/usr/bin/env python3.1

import io
from passed import passed

# https://docs.python.org/3.10/whatsnew/3.0.html

assert 3 / 2 == 1.5
assert isinstance(range(3), range)


buff = io.StringIO()

# https://docs.python.org/3.10/whatsnew/3.0.html#print-is-a-function

print(1, 2, 3, sep=", ", end="!", file=buff)

assert buff.getvalue() == "1, 2, 3!"


class Meta(type):
    pass


class Foo(metaclass=Meta):
    pass

try:
    raise Exception("Ex")
except Exception as inst:
    assert str(type(inst)) == "<class 'Exception'>"
    print(inst.args)
    print(inst)


passed()
