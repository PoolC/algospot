#!/usr/bin/env python
import sys

IS_DEBUG = False
#IS_DEBUG = True
if IS_DEBUG:
    f = open('input.dat', 'r')
    rl = lambda: f.readline()
    import pdb
    pdb.set_trace()
else:
    rl = lambda: sys.stdin.readline()


fmap = {}
fmap[0] = 1
fmap[1] = 1

def fib(n):
    if n in fmap:
        return fmap[n]
    for i in xrange(n+1):
        if i < 2:
            continue
        fmap[i] = fmap[i-1] + fmap[i-2]
    return fmap[n]


def main():
    n = int(rl())
    for i in range(n):
        target = int(rl())
        print fib(target) % 1000000007


if __name__ == "__main__":
    main()
    if IS_DEBUG and type(f) == file:
        f.close()

