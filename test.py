#!/usr/bin/env python2

import sys
from random import getrandbits
from commands import getoutput


def test_mul():
    '''Test some arbitrary pairs of 32 bit numbers to multiply.'''
    for i in range(20):
        for j in range(20):
            x = getrandbits(32)
            y = getrandbits(32)
            cmd = './test mul {} {}'.format(x, y)
            assert x * y == eval(getoutput(cmd)), (x, y)

def test_stringify():
    '''Test conversion to and from string to bignum in base 2.'''
    for i in range(1, 20):
        for j in range(20):
            x = getrandbits(32 * i)
            cmd = './test stringify {} {}'.format(bin(x)[2:], 2)
            result = getoutput(cmd)
            assert x == eval(result) and bin(x) == result, x


if __name__ == '__main__':
    g = globals()
    for name, value in g.items():
        if name.startswith('test'):
            try:
                sys.stdout.write(name + '\t')
                sys.stdout.flush()
                value()
                sys.stdout.write('PASSED\n')
            except AssertionError as e:
                sys.stdout.write('FAILED\n')
            except Exception as e:
                sys.stdout.write('ERROR\n')
