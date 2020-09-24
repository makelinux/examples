#!/usr/bin/env python3.7

# https://docs.python.org/3/whatsnew/3.7.html
# https://realpython.com/python37-new-features/

import asyncio
import sys
from contextvars import ContextVar
import dataclasses
import importlib.resources
from passed import passed

var: ContextVar[int] = ContextVar('var', default=1)
assert var.get() == 1

var.set(2)
assert var.get() == 2

buf = ''


async def corutine():
    global buf
    buf += '3'


async def test_task():
    global buf
    buf += '1'
    # Before:
    # task = asyncio.ensure_future(corutine())
    task = asyncio.create_task(corutine())
    buf += '2'
    await task
    buf += '4'

asyncio.run(test_task())
assert buf == '1234'

breakpoint_passed = False

sys.breakpointhook = lambda: globals().update(breakpoint_passed=True)
breakpoint()

assert breakpoint_passed

passed()
