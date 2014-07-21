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
        last = 0
        cont = 0
        max_cont = 1
        for a in input_list:
            if a > last:
                cont += 1
                max_cont = max(max_cont, cont)
            else:
                cont = 1
            last = a
        print max_cont


if __name__ == "__main__":
    main()
    if IS_DEBUG and type(f) == file:
        f.close()

