#!/usr/bin/env python
import sys
#import pdb

rl = lambda: sys.stdin.readline()
#f = open('input.dat', 'r')
#rl = lambda: f.readline()
#pdb.set_trace()

check_tiles = []
check_tiles.append([[0,0], [0,1] , [1, 1]]) 
check_tiles.append([[0,0], [0,1] , [-1, 1]]) 
check_tiles.append([[0,0], [1,0] , [0, 1]]) 
check_tiles.append([[0,0], [1,0] , [1, 1]]) 

class Board:
    board = []
    def __init__(self, max_x, max_y, lines):
        self.board = []
        self.mx = max_x
        self.my = max_y
        for xi in range(self.mx):
            self.board.append([-1] * self.my)
        for yi in range(self.my):
            dx = lines[yi]
            for xi in range(self.mx):
                self.board[xi][yi] = 0 if dx[xi] == '.' else 1

    def checkBoardFull(self):
        for yi in range(self.my):
            for xi in range(self.mx):
                if self.board[xi][yi] == 0:
                    return False
        return True

    def getEmptyPosition(self):
        for yi in range(self.my):
            for xi in range(self.mx):
                if self.board[xi][yi] == 0:
                    return [xi, yi]
        return False

    def isTileAvailable(self, point, tile):
        x = point[0]
        y = point[1]
        for ti in tile:
            tx = x + ti[0]
            ty = y + ti[1]
            if tx < 0 or tx >= self.mx:
                return False
            if ty < 0 or ty >= self.my:
                return False
            if self.board[tx][ty] != 0:
                return False
        return True

    def setTile(self, point, tile, value):
        x = point[0]
        y = point[1]
        for ti in tile:
            tx = x + ti[0]
            ty = y + ti[1]
            if tx < 0 or tx >= self.mx:
                continue
            if ty < 0 or ty >= self.my:
                continue
            self.board[tx][ty] = value


    def checkProcess(self):
        current_sum = 0
        p = self.getEmptyPosition()
        if p == False:
            return 1 if self.checkBoardFull() else 0
        for tile in check_tiles:
            if not self.isTileAvailable(p, tile):
                continue
            self.setTile(p, tile, 1)
            current_sum += self.checkProcess()
            self.setTile(p, tile, 0)
        return current_sum

def main():
    n = int(rl())
    for i in range(n):
        my, mx = [int(x) for x in rl().split()]
        board_lines = []
        for yi in range(my):
            board_lines.append(rl())
        board = Board(mx, my, board_lines)
        print board.checkProcess()



if __name__ == "__main__":
    main()
