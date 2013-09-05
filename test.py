#!/usr/bin/env python2

import sys
from commands import getoutput


def test_mul():
    '''Test some arbitrary pairs of 32 bit numbers to multiply.'''
    for x in xrange(1, 0xffffffff, 37**5):
        for y in xrange(1, 0xffffffff, 53**5):
            cmd = './test mul {} {}'.format(x, y)
            assert x * y == eval(getoutput(cmd)), (x, y)


if __name__ == '__main__':
    g = globals()
    for name, value in g.items():
        if name.startswith('test'):
            try:
                sys.stdout.write(name + '\t')
                sys.stdout.flush()
                value()
                sys.stdout.write('PASSED\n')
            except AssertionError:
                sys.stdout.write('FAILED\n')
            except:
                sys.stdout.write('ERROR\n')
