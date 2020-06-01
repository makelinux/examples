#!/usr/bin/env python3.5

# https://docs.python.org/3/whatsnew/3.5.html

from typing import *

def function_with_type_annotation(a: str) -> str:
    return a

# But the Python runtime does not enforce function.
assert(function_with_type_annotation(1.2) == 1.2)

Vector_type_alias = List[float]

def scale(scalar: float, vector: Vector_type_alias) -> Vector_type_alias:
    return [scalar * num for num in vector]

assert(scale(2, [1.1, 3.3]) == [2.2, 6.6])

UserId = NewType('UserId', int)
some_id = UserId(1)

def valid(id:UserId) -> bool:
    return True

def feeder(get_next_item: Callable[[], str]) -> None:
    pass

def async_query(on_success: Callable[[int], None],
                on_error: Callable[[int, Exception], None]) -> None:
    pass

import asyncio

async def coroutine():
    return 1

loop = asyncio.get_event_loop()
try:
    r = loop.run_until_complete(coroutine())
finally:
    loop.close()

assert(r == 1)

import passed
