#!/usr/bin/env python3.11

# https://docs.python.org/3.11/whatsnew/3.11.html

from passed import passed

import asyncio
import enum
import tomllib


# ExceptionGroup and except* (PEP 654)
def _raise_exception_group() -> None:
    raise ExceptionGroup(
        "demo",
        [ValueError("bad value"), TypeError("bad type")],
    )


handled_value_error = False
handled_type_error = False

try:
    _raise_exception_group()
except* ValueError as eg:
    handled_value_error = True
    # Each subgroup only contains the matched exception type
    assert all(isinstance(e, ValueError) for e in eg.exceptions)
except* TypeError as eg:
    handled_type_error = True
    assert all(isinstance(e, TypeError) for e in eg.exceptions)

assert handled_value_error and handled_type_error


# tomllib in the standard library (PEP 680)
toml_text = """
name = "alice"
age = 42
"""
data = tomllib.loads(toml_text)
assert data == {"name": "alice", "age": 42}

# enum.StrEnum (bakes in str behavior)
class Color(enum.StrEnum):
    RED = "red"
    BLUE = "blue"

assert Color.RED == "red"
assert isinstance(Color.BLUE, str)

# asyncio.TaskGroup (structured concurrency)
async def _tg_demo() -> int:
    async with asyncio.TaskGroup() as tg:
        task_one = tg.create_task(asyncio.sleep(0.01, result=1))
        task_two = tg.create_task(asyncio.sleep(0.01, result=2))
    return task_one.result() + task_two.result()

assert asyncio.run(_tg_demo()) == 3

passed()
