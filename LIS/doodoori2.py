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
        input_list = map(int, rl().split())
        cont = {}
        for now in input_list:
            cont_len = len(cont)
            if cont_len == 0:
                cont[1] = now
                continue
            else:
                cont[1] = min(cont[1], now)
            for current_len in xrange(cont_len, 0, -1):
                check = cont[current_len]
                if check > now:
                    continue
                if check == now:
                    break
                next_len = current_len + 1
                if next_len in cont:
                    cont[next_len] = min(now, cont[next_len])
                else:
                    cont[next_len] = now
                #print now, cont
                break
        print len(cont)


if __name__ == "__main__":
    main()
    if IS_DEBUG and type(f) == file:
        f.close()

