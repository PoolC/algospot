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

def main():
    n = int(rl())
    for i in range(n):
        input_cnt = int(rl())
        input_list = rl().split()
        cont = {}
        for a in input_list:
            a = int(a)
            if not a in cont:
                cont[a] = 1
            for ta in xrange(a-1, 0, -1):
                if ta in cont:
                    cont[a] = max(cont[a], cont[ta] + 1)
                    break
        max_cont = max([cont[x] for x in cont])


if __name__ == "__main__":
    main()
    if IS_DEBUG and type(f) == file:
        f.close()

