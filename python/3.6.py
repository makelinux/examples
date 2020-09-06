#!/usr/bin/env python3.6

# https://docs.python.org/3.6/whatsnew/3.6.html

# https://docs.python.org/3.6/whatsnew/3.6.html#pep-498-formatted-string-literals

import asyncio
from passed import passed

an_int = 1
assert f'{an_int}' == '1'
assert f'an_int={an_int:02}' == 'an_int=01'
assert f"{an_int:#0x}" == "0x1"  # using integer format specifier

a_real = 1.23
assert f'{a_real}' == '1.23'
assert f'a_real={a_real:1.2}' == 'a_real=1.2'

a_str = 'a'
assert f'{a_str}' == 'a'
assert f'{a_str!r}' == "'a'"

# https://docs.python.org/3.6/whatsnew/3.6.html#pep-526-syntax-for-variable-annotations

a_str: str
an_int: int


async def main():
    print('hello')
    await asyncio.sleep(1)
    print('world')

# asyncio.run(main())

passed()
