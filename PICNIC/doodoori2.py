#!/usr/bin/env python
import sys
rl = lambda: sys.stdin.readline()

n = int(rl())

def check(n, matched, matches, student_num):
    if n == student_num:
        return 1
    current_sum = 0
    if matched[n] != -1:
        return check(n+1, matched, matches, student_num)
    for target in matches[n]:
        if matched[target] != -1:
            continue
        _matched = [x for x in matched]
        _matched[n] = target
        _matched[target] = n
        current_sum += check(n+1, _matched, matches, student_num)
    return current_sum

for i in range(n):
    student_num, match_num = [int(x) for x in rl().split()]
    current_sum = 0
    line = rl().split()
    matches = [[] for x in range(student_num)]
    for k in range(match_num):
        m = [int(line[k*2]), int(line[k*2+1])]
        m.sort()
        matches[m[0]].append(m[1])
    matched = [-1] * student_num
    current_sum += check(0, matched, matches, student_num)
    print current_sum