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

def solve(k, data_len):
    d = DataGenerator()
    q = qq() # Queue.Queue()
    s = 0
    cnt = 0 
    for _ in xrange(data_len):
        current = d.Next()
        q.put(current)
        s += current
        while s >= k:
            if s == k:
                cnt += 1
            s -= q.get()
            #print _, s, q.qsize(), current
    return cnt


def main():
    n = int(rl())
    for i in range(n):
        (k, data_len) = map(int, rl().split())
        print solve(k, data_len)

if __name__ == "__main__":
    main()
    if IS_DEBUG and type(f) == file:
        f.close()

