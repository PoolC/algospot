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

clockswitch={}
clockswitch[0] = [0, 1, 2]
clockswitch[1] = [3, 7, 9, 11]
clockswitch[2] = [4, 10, 14, 15]
clockswitch[3] = [0, 4, 5, 6, 7]
clockswitch[4] = [6, 7, 8, 10, 12]
clockswitch[5] = [0, 2, 14, 15]
clockswitch[6] = [3, 14, 15]
clockswitch[7] = [4, 5, 7, 14, 15]
clockswitch[8] = [1, 2, 3, 4, 5]
clockswitch[9] = [3, 4, 5, 9, 13]


class Clock:
    def __init__(self, clock_list):
        self.clock = [(int(x)/3) %4  for x in clock_list]

    def getClockNum(self, i):
        return self.clock[i]

    def press(self, si, num_to_press):
        sw = clockswitch[si]
        for s in sw:
            v = self.clock[s]
            self.clock[s] = (v + num_to_press) % 4

    def initClockSwitchMapper(self):
        csmap = {}
        for si in clockswitch:
            for ci in clockswitch[si]:
                if not ci in csmap:
                    csmap[ci] = set()
                csmap[ci].add(si)
        return csmap

    def check(self):
        csmap = self.initClockSwitchMapper()
        press_cnt = 0
        while len(csmap) > 0:
            remove_csmap = set()
            for ci in csmap:
                switch_set = csmap[ci]
                if len(switch_set) == 1:
                    sw = switch_set.pop()
                    num_to_press = (4 - self.getClockNum(ci)) % 4
                    self.press(sw, num_to_press)
                    press_cnt += num_to_press
                    for cj in csmap:
                        if sw in csmap[cj]:
                            csmap[cj].remove(sw)
                        if len(csmap[cj]) == 0:
                            remove_csmap.add(cj)
            for ci in remove_csmap:
                csmap.pop(ci)
            
        if sum(self.clock) != 0:
            return -1
        return press_cnt


def main():
    n = int(rl())
    for i in range(n):
        clock = Clock(rl().split())
        print clock.check()


if __name__ == "__main__":
    main()
    if IS_DEBUG and type(f) == file:
        f.close()

