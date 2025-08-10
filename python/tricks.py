#!/usr/bin/env python3

from collections import Counter, defaultdict
from contextlib import suppress
from dataclasses import dataclass
from functools import lru_cache
from pathlib import Path
import sys

from passed import passed

def multi_args(a, b, c,):
    assert(a == 1)
    assert(b == 2)
    assert(c == 3)
    pass

args = { 'a': 1, 'b': 2, 'c': 3 }

multi_args(**args)

args = [ 1, 2, 3 ]

multi_args(*args)


# Sequence unpacking with a starred target
nums = [1, 2, 3, 4]
first, *middle, last = nums
assert first == 1 and middle == [2, 3] and last == 4

# Swap without a temp
x, y = 10, 20
x, y = y, x
assert x == 20 and y == 10

# enumerate with a custom start
letters = ["a", "b"]
assert list(enumerate(letters, start=1)) == [(1, "a"), (2, "b")]

# zip and unzip
names = ["alice", "bob"]
scores = [3, 4]
pairs = list(zip(names, scores))
assert pairs == [("alice", 3), ("bob", 4)]
unzipped_names, unzipped_scores = zip(*pairs)
assert list(unzipped_names) == names and list(unzipped_scores) == scores

# Comprehensions
squares = [n * n for n in range(5)]
assert squares == [0, 1, 4, 9, 16]

codepoints = {c: ord(c) for c in "ab"}
assert codepoints == {"a": 97, "b": 98}

parities = {n % 2 for n in range(5)}
assert parities == {0, 1}

# any/all
assert any([0, "", 3]) is True
assert all([1, True, "x"]) is True

# Chained comparisons
z = 5
assert 1 < z < 10

# Slicing tricks
s = "abcd"
assert s[::-1] == "dcba"
assert s[::2] == "ac"

# Join strings
assert "-".join(["a", "b", "c"]) == "a-b-c"

# dict.get and setdefault
lookup: dict[str, list[int]] = {}
assert lookup.get("missing", 42) == 42
lookup.setdefault("items", []).append(1)
lookup.setdefault("items", []).append(2)
assert lookup["items"] == [1, 2]

# defaultdict for grouping
data = [("a", 1), ("b", 2), ("a", 3)]
grouped: defaultdict[str, list[int]] = defaultdict(list)
for key, value in data:
    grouped[key].append(value)
assert grouped["a"] == [1, 3] and grouped["b"] == [2]

# Counter for frequencies
cnt = Counter("abca")
assert dict(cnt) == {"a": 2, "b": 1, "c": 1}

# pathlib basics
assert Path(__file__).name == "tricks.py"

# lru_cache for memoization
@lru_cache(maxsize=None)
def fib(n: int) -> int:
    return n if n < 2 else fib(n - 1) + fib(n - 2)

assert fib(10) == 55

# dataclass for simple value objects
@dataclass
class Point:
    x: int
    y: int


p1 = Point(1, 2)
p2 = Point(1, 2)
assert p1 == p2 and repr(p1).startswith("Point(")

# Context manager that ignores specific errors
with suppress(ZeroDivisionError):
    1 / 0

# Guarded examples for newer syntax/features
if sys.version_info >= (3, 9):
    d1 = {"a": 0, "b": 2}
    d2 = {"a": 1, "c": 3}
    merged = d1 | d2  # dict merge operator (3.9+)
    assert merged == {"a": 1, "b": 2, "c": 3}

if sys.version_info >= (3, 10):
    # Structural pattern matching (3.10+)
    match (1, 0):
        case (1, 0):
            matched = True
        case _:
            matched = False
    assert matched

passed()
