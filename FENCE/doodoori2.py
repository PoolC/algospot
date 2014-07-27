#!/usr/bin/env python
import sys
from Queue import Queue

IS_DEBUG = False
#IS_DEBUG = True
if IS_DEBUG:
    f = open('input.dat' ,'r')
    rl = lambda: f.readline()
    import pdb
    pdb.set_trace()
else:
    rl = lambda: sys.stdin.readline()

class Fences():
    def __init__(self, fence_list):
        self.fence_list_ = [int(x) for x in fence_list]

    def solve(self, left, right):
        c_max = 0
        if left == right:
            return self.fence_list_[left]
        else:
            mid = int((right + left) / 2)
            lo = mid
            hi = mid+1
            height  = min(self.fence_list_[lo], self.fence_list_[hi])
            c_max = max(c_max, self.solve(left, mid), self.solve(mid + 1, right), height * 2)
            while (left < lo or hi < right):
                if (hi < right and (lo == left or self.fence_list_[lo-1] < self.fence_list_[hi+1])):
                    hv = self.fence_list_[hi+1]
                    hi += 1
                    height = min(height, hv)
                    while hi < right and hv <= self.fence_list_[hi+1]:
                        hi += 1
                else:
                    lv = self.fence_list_[lo-1]
                    lo -= 1
                    height = min(height, lv)
                    while lo > left and lv <= self.fence_list_[lo-1]:
                        lo -= 1
                c_max = max(c_max, height * (hi - lo + 1))
            return c_max

def main():
    n = int(rl())
    for i in range(n):
        fence_cnt = int(rl())
        fence_input = rl().split()
        fences = Fences(fence_input)
        print fences.solve(0, len(fences.fence_list_)-1)

if __name__ == "__main__":
    main()
    if IS_DEBUG and type(f) == file:
        f.close()


