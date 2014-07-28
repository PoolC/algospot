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

ites_init = 1983

def generate_ites(prev):
    return (prev * 214013 + 2531011) % 4294967296

def to_seq_number(ites_value):
    return ites_value % 10000 + 1

class problem_context():
    def __init__(self, target_sum, seq_count):
        global ites_init
        self.seq_count = seq_count
        self.case_count = 0
        self.target_sum = target_sum
        self.sum = 0
        self.partial_seq_first_ites = ites_init


def solve_once(problem_contexts, max_seq_count):
    global ites_init
    ites_value = ites_init
    
    for seq_index in xrange(max_seq_count):
        seq_number = to_seq_number(ites_value)
        for ctx in problem_contexts:
            if ctx.seq_count < seq_index:
                continue
            ctx.sum += seq_number
            if (ctx.sum == ctx.target_sum):
                ctx.case_count += 1
            while (ctx.sum > ctx.target_sum):
                ctx.sum -= to_seq_number(ctx.partial_seq_first_ites)
                ctx.partial_seq_first_ites = generate_ites(ctx.partial_seq_first_ites)
                if (ctx.sum == ctx.target_sum):
                    ctx.case_count += 1
        ites_value = generate_ites(ites_value)

    for ctx in problem_contexts:
        print ctx.case_count

def main():
    n = int(rl())
    problem_contexts = []
    max_seq_count = 0
    for i in range(n):
        (target_sum, seq_count) = map(int, rl().split())
        problem_contexts.append(problem_context(target_sum, seq_count))
        max_seq_count = max(max_seq_count, seq_count)
    solve_once(problem_contexts, max_seq_count)

if __name__ == "__main__":
    main()
    if IS_DEBUG and type(f) == file:
        f.close()

