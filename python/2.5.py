#!/usr/bin/env python2.5

# https://docs.python.org/3.10/whatsnew/2.5.html

assert((1 if False else 2) == 2)

try:
    pass
except Exception1:
    pass
except Exception2:
    pass
else:
    pass
finally:
    pass


import passed
