#!/usr/bin/env python3.7

# https://docs.python.org/3/whatsnew/3.7.html

from contextvars import *
import dataclasses
import importlib.resources

var: ContextVar[int] = ContextVar('var', default=1)
assert(var.get() == 1)

var.set(2)
assert(var.get() == 2)

import asyncio

buf = ''

async def corutine():
    global buf
    buf += '3'
    pass

async def test_task():
    global buf
    buf += '1'
    # Before:
    #task = asyncio.ensure_future(corutine())
    task = asyncio.create_task(corutine())
    buf += '2'
    await task
    buf += '4'

asyncio.run(test_task())
assert(buf == '1234')

import passed
