#!/usr/bin/env python2

import operator
import sys
from random import getrandbits
from commands import getoutput


def test_stringify():
    '''Test conversion to and from string to bignum in base 2.'''
    for i in range(1, 20):
        for j in range(20):
            x = getrandbits(32 * i)
            cmd = './test stringify {} {}'.format(bin(x)[2:], 2)
            result = getoutput(cmd)
            assert x == eval(result) and bin(x) == result, x

def test_add():
    '''Test arbitrary precision addition.'''
    for i in range(1, 20):
        for j in range(20):
            x = getrandbits(32*i)
            y = getrandbits(32*i)
            cmd = './test add {} {}'.format(bin(x)[2:], bin(y)[2:])
            assert x + y== eval(getoutput(cmd))

def test_ops():
    '''Test some arbitrary pairs of 32 bit numbers to test arithmetic.'''
    for opname in 'add mul'.split():
        op = getattr(operator, opname)
        for i in range(20):
            for j in range(20):
                x = getrandbits(32)
                y = getrandbits(32)
                xy = op(x, y)
                cmd = './test {}_op {} {}'.format(opname, x, y)
                assert xy == eval(getoutput(cmd)), (x, y)


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
