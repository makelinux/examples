#!/usr/bin/env python3.7

# https://docs.python.org/3/whatsnew/3.7.html

from contextvars import *
import dataclasses
import importlib.resources

var: ContextVar[int] = ContextVar('var', default=1)
assert(var.get() == 1)

var.set(2)
assert(var.get() == 2)

from sys import *
print("passed", version)
