#!/usr/bin/env python
import sys
import Queue

IS_DEBUG = False
#IS_DEBUG = True
if IS_DEBUG:
    f = open('input.dat', 'r')
    rl = lambda: f.readline()
    import pdb
    pdb.set_trace()
else:
    rl = lambda: sys.stdin.readline()

class qq():
    def __init__(self):
        self.arr = {}
        self.s = 0
        self.e = 0
    def put(self, e):
        self.arr[self.e] = e
        self.e += 1
    def get(self):
        ret = self.arr[self.s]
        del self.arr[self.s]
        self.s += 1
        return ret

class DataGenerator():
    def __init__(self):
        self.i = 1983
    def _Next(self):
        self.i += 1
        arr = [1,4,2,1,4,3,1,6]
        return arr[self.i - 1984]
    def Next(self):
        ret = self.i % 10000 + 1
        self.i = (self.i * 214013 + 2531011) % (4294967296) # ( 2  ** 32)
        return ret

class Problem():
    def __init__(self, k, data_len):
        self.k = k
        self.data_len = data_len
        self.is_solved = False
        self.answer = 0

def solve_once(problems, max_data_len):
    d = DataGenerator()
    for p in problems:
        p.q = qq() # Queue.Queue()
        p.s = 0
        p.cnt = 0
    for l in xrange(max_data_len):
        current = d.Next()
        for p in problems:
            if p.is_solved:
                continue
            if p.data_len == l:
                p.is_solved = True
                p.answer = p.cnt
                continue
            p.q.put(current)
            p.s += current
            while p.s >= p.k:
                if p.s == p.k:
                    p.cnt += 1
                p.s -= p.q.get()
    for p in problems:
        print p.cnt

def main():
    n = int(rl())
    problems = []
    max_data_len = 0
    for i in range(n):
        (k, data_len) = map(int, rl().split())
        problems.append(Problem(k, data_len))
        max_data_len = max(max_data_len, data_len)
    solve_once(problems, max_data_len)

if __name__ == "__main__":
    main()
    if IS_DEBUG and type(f) == file:
        f.close()

