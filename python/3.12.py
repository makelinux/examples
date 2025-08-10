#!/usr/bin/env python3.12

# https://docs.python.org/3.12/whatsnew/3.12.html

from passed import passed

import sys
from itertools import batched
from typing import override


# PEP 695: Type parameter syntax for generics
def identity[T](value: T) -> T:
    return value


class Box[T]:
    def __init__(self, value: T):
        self.value = value


assert identity(10) == 10
assert Box[int](1).value == 1


# PEP 701: f-strings improvements (kept simple for parser compatibility here)
fstring_demo = f"sum = {(1 + 2)}"
assert fstring_demo == "sum = 3"


# itertools.batched added to the standard library
assert list(batched([1, 2, 3, 4, 5], 2)) == [(1, 2), (3, 4), (5,)]


# PEP 698: typing.override decorator
class Base:
    def method(self) -> str:
        return "base"


class Child(Base):
    @override
    def method(self) -> str:
        return "child"


assert Child().method() == "child"


# PEP 669: sys.monitoring (presence check)
assert hasattr(sys, "monitoring")


passed()


