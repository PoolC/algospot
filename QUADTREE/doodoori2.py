#!/usr/bin/env python
import sys

IS_DEBUG = False
#IS_DEBUG = True
if IS_DEBUG:
    f = open('input.dat' ,'r')
    rl = lambda: f.readline()
    import pdb
    pdb.set_trace()
else:
    rl = lambda: sys.stdin.readline()

class NodeType:
    X = 0
    W = 1
    B = 2
    E = -1

class Stream():
    _input_list = None
    _current_position = 0
    def __init__(self, _input):
        self._input_list = [NodeType.X if x == 'x' else NodeType.W if x == 'w' else NodeType.B if x == 'b' else NodeType.E for x in _input]
        self._current_position = 0
        self._str_length = len(_input)

    def getNext(self):
        if self._str_length <= self._current_position:
            return None
        c = self._current_position
        self._current_position += 1
        return self._input_list[c]

class Node():
    _current = None
    _A = None
    _B = None
    _C = None
    _D = None
    def __init__(self, stream):
        self._current = stream.getNext()
        if self._current == NodeType.X:
            self._A = Node(stream)
            self._B = Node(stream)
            self._C = Node(stream)
            self._D = Node(stream)
    def printReverse(self):
        if self._current == NodeType.X:
            ret_str = 'x'
            ret_str += self._C.printReverse()
            ret_str += self._D.printReverse()
            ret_str += self._A.printReverse()
            ret_str += self._B.printReverse()
            return ret_str
        elif self._current == NodeType.W:
            return 'w'
        elif self._current == NodeType.B:
            return 'b'
        else:
            return None

def main():
    n = int(rl())
    for i in range(n):
        s = Stream(rl())
        tree = Node(s)
        print tree.printReverse()

if __name__ == "__main__":
    main()
    if IS_DEBUG and type(f) == file:
        f.close()



