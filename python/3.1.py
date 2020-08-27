#!/usr/bin/env python3.1

# https://docs.python.org/3.10/whatsnew/3.1.html

from decimal import *

assert format(1000, ',d') == '1,000'

assert format(Decimal('1.23'), '.3f') == '1.230'

import passed
