#include<iostream>
#include<string>
#include<fstream>
#include<array>
#include<vector>

using namespace std;

istream& in = cin;

struct block {
	int x, y;
};

array<block, 4> blocks = { 1, 1,
1, -1,
-1, 1,
-1, -1 };

enum Tile { empty = 0, wall = 1, tile = 3 };

int BoardCover(vector< vector < Tile> > & tiles, int BaseX, int BaseY, int MaxX, int MaxY);

int main() {

	int tCase;
	in >> tCase;
	while (tCase--) {
		int row, col;
		in >> row >> col;
		vector< vector < Tile> > tiles(col + 2, vector<Tile> (row + 2, wall));
		char t;
		for (int y = 1; y < row +1; y++) {
			for (int x = 1; x < col+1; x++) {
				in >> t;
				if (t == '.') {
					tiles[x][y] = empty;
				}

			}

		}
		cout << BoardCover(tiles, 1, 1,col, row) << endl;

	}
	return 0;
}

int BoardCover(vector< vector < Tile> > & tiles, int BaseX, int BaseY, int MaxX, int MaxY) {

	bool failed = true;
	int result = 0;
	if (BaseX == MaxX && BaseY == MaxY && tiles[BaseX][BaseY] != empty) {
		return 1;
	}

	if (tiles[BaseX][BaseY] != empty) {
		if (BaseX == MaxX) {
			result += BoardCover(tiles, 1, BaseY+1, MaxX, MaxY);
		}
		else {
			result += BoardCover(tiles, BaseX+1, BaseY, MaxX, MaxY);
		}
	}
	else {
		for (int i = 0; i < 4; i++) {
			int x1, y1, x2, y2;
			x1 = BaseX + blocks[i].x;
			y1 = BaseY;
			x2 = BaseX;
			y2 = BaseY + blocks[i].y;
			if (tiles[x1][y1] == empty && tiles[x2][y2] == empty) {
				failed = false;
				tiles[BaseX][BaseY] = tiles[x1][y1] = tiles[x2][y2] = tile;
				if (BaseX == MaxX) {
					result += BoardCover(tiles, 1, BaseY + 1, MaxX, MaxY);
				}
				else {
					result += BoardCover(tiles, BaseX + 1, BaseY, MaxX, MaxY);
				}
				tiles[BaseX][BaseY] = tiles[x1][y1] = tiles[x2][y2] = empty;
			}

		}
		int x1, y1, x2, y2;

		/////////
		x1 = BaseX;
		y1 = BaseY + 1;
		x2 = BaseX + 1;
		y2 = BaseY + 1;
		if (tiles[x1][y1] == empty && tiles[x2][y2] == empty) {
			failed = false;
			tiles[BaseX][BaseY] = tiles[x1][y1] = tiles[x2][y2] = tile;
			if (BaseX == MaxX) {
				result += BoardCover(tiles, 1, BaseY + 1, MaxX, MaxY);
			}
			else {
				result += BoardCover(tiles, BaseX + 1, BaseY, MaxX, MaxY);
			}
			tiles[BaseX][BaseY] = tiles[x1][y1] = tiles[x2][y2] = empty;
		}

		/////////
		x1 = BaseX + 1;
		y1 = BaseY;
		x2 = BaseX + 1;
		y2 = BaseY + 1;
		if (tiles[x1][y1] == empty && tiles[x2][y2] == empty) {
			failed = false;
			tiles[BaseX][BaseY] = tiles[x1][y1] = tiles[x2][y2] = tile;
			if (BaseX == MaxX) {
				result += BoardCover(tiles, 1, BaseY + 1, MaxX, MaxY);
			}
			else {
				result += BoardCover(tiles, BaseX + 1, BaseY, MaxX, MaxY);
			}
			tiles[BaseX][BaseY] = tiles[x1][y1] = tiles[x2][y2] = empty;
		}
		////////
		x1 = BaseX - 1;
		y1 = BaseY + 1;
		x2 = BaseX;
		y2 = BaseY + 1;
		if (tiles[x1][y1] == empty && tiles[x2][y2] == empty) {
			failed = false;
			tiles[BaseX][BaseY] = tiles[x1][y1] = tiles[x2][y2] = tile;
			if (BaseX == MaxX) {
				result += BoardCover(tiles, 1, BaseY + 1, MaxX, MaxY);
			}
			else {
				result += BoardCover(tiles, BaseX + 1, BaseY, MaxX, MaxY);
			}
			tiles[BaseX][BaseY] = tiles[x1][y1] = tiles[x2][y2] = empty;
		}
		if (failed) {
			return 0;
		}

	}

	return result;

}