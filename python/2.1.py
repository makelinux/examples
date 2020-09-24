#!/usr/bin/env python2.3

# https://docs.python.org/3.10/whatsnew/2.1.html

from passed import passed


def function():
    def closure():
        pass
    closure()


passed()
