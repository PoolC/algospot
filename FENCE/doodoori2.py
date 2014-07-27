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
        #print fence_list
        self.fence_list_ = [int(x) for x in fence_list]
        self.fence_list_len_ = len(fence_list)

    def _divide(self, left, right):
        lv = 0
        rv = 0
        if left == right:
            return self.fence_list_[left]
        else:
            mid = int((right + left) / 2)
            c_max = max(self._divide(left, mid), self._divide(mid + 1, right))
            lo = mid
            hi = mid+1
            height  = min(self.fence_list_[lo], self.fence_list_[hi])
            c_max = max(c_max, height * 2)

            while (left < lo or hi < right):
                if (hi < right and (lo == left or self.fence_list_[lo-1] < self.fence_list_[hi+1])):
                    hi += 1
                    height = min(height, self.fence_list_[hi])
                else:
                    lo -= 1
                    height = min(height, self.fence_list_[lo])
                c_max = max(c_max, height * (hi - lo + 1))

            return c_max

    def getMaxArea(self):
        return self._divide(0, len(self.fence_list_)-1)


def main():
    n = int(rl())
    for i in range(n):
        fence_cnt = int(rl())
        fence_input = rl().split()
        fences = Fences(fence_input)
        print fences.getMaxArea()

if __name__ == "__main__":
    main()
    if IS_DEBUG and type(f) == file:
        f.close()


