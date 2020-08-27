#!/usr/bin/env python2.5

# https://docs.python.org/3.10/whatsnew/2.5.html

assert (1 if False else 2) == 2

try:
    pass
except TypeError:
    pass
except AttributeError:
    pass
else:
    pass
finally:
    pass


import passed
