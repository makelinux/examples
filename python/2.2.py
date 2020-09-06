#!/usr/bin/env python2.3

from passed import passed

# https://docs.python.org/3.10/whatsnew/2.2.html


class C(object):
    def __init__(self):
        pass


assert C.__name__ == 'C'


passed()
