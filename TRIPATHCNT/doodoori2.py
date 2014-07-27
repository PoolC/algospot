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


def solve(paths, path_size):
    path_max={}
    path_num={}
    for level in range(path_size):
        path = paths[level]
        if level == 0:
            path_max[0] = path[0]
            path_num[0] = 1
            continue
        next_path_max = {}
        next_path_num = {}
        for i in xrange(level + 1):
            p = path[i]
            if i == 0:
                next_path_max[i] = path_max[i] + p
                next_path_num[i] = 1
                continue
            if i == level:
                next_path_max[i] = path_max[i-1] + p
                next_path_num[i] = 1
                continue
            lv = path_max[i - 1]
            rv = path_max[i]
            if lv == rv:
                next_path_max[i] = lv + p 
                next_path_num[i] = path_num[i - 1] + path_num[i]
            elif lv > rv:
                next_path_max[i] = lv + p 
                next_path_num[i] = path_num[i - 1]
            else:
                next_path_max[i] = rv + p 
                next_path_num[i] = path_num[i]
        path_max = next_path_max
        path_num = next_path_num
    
    last_max_path_val = 0
    path_cnt = 0
    for k in range(path_size):
        path_val = path_max[k]
        if last_max_path_val == path_val:
            path_cnt += path_num[k]
        elif last_max_path_val < path_val:
            last_max_path_val = path_val
            path_cnt = path_num[k]
    return path_cnt


def main():
    n = int(rl())
    for i in range(n):
        path_size = int(rl())
        paths = []
        for j in range(path_size):
            paths.append(map(int, rl().split()))
        print solve(paths, path_size)


if __name__ == "__main__":
    main()
    if IS_DEBUG and type(f) == file:
        f.close()

