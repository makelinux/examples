#!/usr/bin/env python3.10

# https://docs.python.org/3.10/whatsnew/index.html

from passed import passed

num = 19
assert bin(num) == '0b10011'
assert num.bit_count() == 3

#assertNoLogs

class CtxManager1():
    def __enter__(self):
        return self
    def __exit__(self, exc_type, exc, tb):
        return False


with (CtxManager1() as example1,
      CtxManager1() as example2,
):
    pass


match 1:
    case 1:
        pass
    case _:
        pass

passed()
