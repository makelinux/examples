#!/usr/bin/env python2.3

# https://docs.python.org/3.10/whatsnew/2.0.html

comprehension = [c for c in 'ab' if c > 'a']
assert('a' not in comprehension)
assert('b' in comprehension)

import passed
