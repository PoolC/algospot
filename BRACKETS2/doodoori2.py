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

cmap = {}
cmap["("] = 1
cmap["{"] = 2
cmap["["] = 3
cmap[")"] = 4
cmap["}"] = 5
cmap["]"] = 6

def solve(input_str):
    stack = []
    for char in input_str:
        cnum = cmap[char]
        if cnum == 1 or cnum == 2 or cnum == 3:
            stack.append(cnum)
        else:
            if len(stack) == 0:
                return "NO"
            last = stack[-1]
            if cnum == last + 3:
                stack.pop()
            else:
                return "NO"
    if len(stack) == 0:
        return "YES"
    return "NO"


def main():
    n = int(rl())
    for i in range(n):
        print solve(rl().strip())

if __name__ == "__main__":
    main()
    if IS_DEBUG and type(f) == file:
        f.close()

