#!/usr/bin/env python3.13

# https://docs.python.org/3.13/whatsnew/3.13.html

from passed import passed

import typing as _typing
from warnings import deprecated, catch_warnings, simplefilter
from typing import TypeIs, ReadOnly, TypedDict


# PEP 742: typing.TypeIs for intuitive type narrowing
def is_str(value: object) -> TypeIs[str]:
    return isinstance(value, str)


unknown: object = "hello"
if is_str(unknown):
    assert unknown.upper() == "HELLO"


# PEP 705: typing.ReadOnly for immutable fields in TypedDict
class Config(TypedDict):
    env: ReadOnly[str]


cfg: Config = {"env": "production"}
assert cfg["env"] == "production"


# PEP 702: deprecation decorator – pick from typing or warnings; fallback to no-op
@deprecated("use 'new_api' instead")
def old_api() -> int:
    return 1


passed()
