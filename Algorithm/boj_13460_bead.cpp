#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#define MAXBOARD 100;

using namespace std;

class position {
public:
	int height;
	int width;
};

vector<string> game_board;
position hole;

vector<int> Possible_dir(position red)
{
	vector<int> possible_dir;
	if (game_board[red.height][red.width + 1] == '.' ||
		(game_board[red.height][red.width + 1] == 'B' && game_board[red.height][red.width + 2] == '.') ||
		game_board[red.height][red.width + 1] == 'O')
		possible_dir.push_back(0);

	if (game_board[red.height][red.width - 1] == '.' ||
		(game_board[red.height][red.width - 1] == 'B' && game_board[red.height][red.width - 2] == '.') ||
		game_board[red.height][red.width - 1] == 'O')
		possible_dir.push_back(1);

	if (game_board[red.height + 1][red.width] == '.' ||
		(game_board[red.height + 1][red.width] == 'B' && game_board[red.height + 2][red.width] == '.') ||
		game_board[red.height + 1][red.width] == 'O')
		possible_dir.push_back(2);

	if (game_board[red.height - 1][red.width] == '.' ||
		(game_board[red.height - 1][red.width] == 'B' && game_board[red.height - 2][red.width] == '.') ||
		game_board[red.height - 1][red.width] == 'O')
		possible_dir.push_back(3);

	if (possible_dir.size() == 0)
		possible_dir.push_back(-1);

	return possible_dir;
}

int moveBead(position& bead, int dir)
{
	int boardsize = MAXBOARD;
	int bh = bead.height; int bw = bead.width;

	switch (dir)
	{
	case 0:
	{
		for (int i = 1; i < boardsize; ++i)
		{
			if (game_board[bh][bw + i] == '.')
				continue;
			else if (game_board[bh][bw + i] == 'O')
			{
				bead.width = bw + i;
				break;
			}
			else if (game_board[bh][bw + i] == '#' || game_board[bh][bw + i] == 'R' || game_board[bh][bw + i] == 'B')
			{
				bead.width = bw + i - 1;
				break;
			}
		}
		break;
	}
	case 1:
	{
		for (int i = 1; i < boardsize; ++i)
		{
			if (game_board[bh][bw - i] == '.')
				continue;
			else if (game_board[bh][bw - i] == 'O')
			{
				bead.width = bw - i;
				break;
			}
			else if (game_board[bh][bw - i] == '#' || game_board[bh][bw - i] == 'R' || game_board[bh][bw - i] == 'B')
			{
				bead.width = bw - i + 1;
				break;
			}
		}
		break;
	}

	case 2:
	{
		for (int i = 1; i < boardsize; ++i)
		{
			//if (bh + i > 6)
			//	cout << "????";
			if (game_board[bh + i][bw] == '.')
				continue;
			else if (game_board[bh + i][bw] == 'O')
			{
				bead.height = bh + i;
				break;
			}
			else if (game_board[bh + i][bw] == '#' || game_board[bh + i][bw] == 'R' || game_board[bh + i][bw] == 'B')
			{
				bead.height = bh + i - 1;
				break;
			}
		}
		break;
	}

	case 3:
	{
		for (int i = 1; i < boardsize; ++i)
		{
			if (game_board[bh - i][bw] == '.')
				continue;
			else if (game_board[bh - i][bw] == 'O')
			{
				bead.height = bh - i;
				break;
			}
			else if (game_board[bh - i][bw] == '#' || game_board[bh - i][bw] == 'R' || game_board[bh - i][bw] == 'B')
			{
				bead.height = bh - i + 1;
				break;
			}
		}
		break;
	}
	}

	return 2;
}



int MoveRB(position& red, position& blue, int this_dir)
{
	int boardsize = game_board.size();
	int stoppos;
	switch (this_dir)
	{
	case 0:
	{
		if (red.width < blue.width)
		{
			game_board[blue.height][blue.width] = '.';
			moveBead(blue, this_dir);
			game_board[blue.height][blue.width] = 'B';

			game_board[red.height][red.width] = '.';
			moveBead(red, this_dir);
			game_board[red.height][red.width] = 'R';
		}
		else {
			game_board[red.height][red.width] = '.';
			moveBead(red, this_dir);
			if (red.height == hole.height && red.width == hole.width)
				game_board[red.height][red.width] = 'O';
			else {
				game_board[red.height][red.width] = 'R';
			}

			game_board[blue.height][blue.width] = '.';
			moveBead(blue, this_dir);
			game_board[blue.height][blue.width] = 'B';
		}
		break;
	}


	case 1:
	{
		if (red.width < blue.width)
		{
			game_board[red.height][red.width] = '.';
			moveBead(red, this_dir);
			if (red.height == hole.height && red.width == hole.width)
				game_board[red.height][red.width] = 'O';
			else {
				game_board[red.height][red.width] = 'R';
			}

			game_board[blue.height][blue.width] = '.';
			moveBead(blue, this_dir);
			game_board[blue.height][blue.width] = 'B';
		}
		else {
			game_board[blue.height][blue.width] = '.';
			moveBead(blue, this_dir);
			game_board[blue.height][blue.width] = 'B';

			game_board[red.height][red.width] = '.';
			moveBead(red, this_dir);
			game_board[red.height][red.width] = 'R';
		}
		break;
	}
	case 2:
	{
		if (red.height < blue.height)
		{
			game_board[blue.height][blue.width] = '.';
			moveBead(blue, this_dir);
			game_board[blue.height][blue.width] = 'B';

			game_board[red.height][red.width] = '.';
			moveBead(red, this_dir);
			game_board[red.height][red.width] = 'R';
		}
		else
		{
			game_board[red.height][red.width] = '.';
			moveBead(red, this_dir);
			if (red.height == hole.height && red.width == hole.width)
				game_board[red.height][red.width] = 'O';
			else {
				game_board[red.height][red.width] = 'R';
			}

			game_board[blue.height][blue.width] = '.';
			moveBead(blue, this_dir);
			game_board[blue.height][blue.width] = 'B';
		}
		break;
	}
	case 3:
	{
		if (red.height < blue.height)
		{
			game_board[red.height][red.width] = '.';
			moveBead(red, this_dir);
			if (red.height == hole.height && red.width == hole.width)
				game_board[red.height][red.width] = 'O';
			else {
				game_board[red.height][red.width] = 'R';
			}

			game_board[blue.height][blue.width] = '.';
			moveBead(blue, this_dir);
			game_board[blue.height][blue.width] = 'B';
		}
		else
		{
			game_board[blue.height][blue.width] = '.';
			moveBead(blue, this_dir);
			game_board[blue.height][blue.width] = 'B';

			game_board[red.height][red.width] = '.';
			moveBead(red, this_dir);
			game_board[red.height][red.width] = 'R';
		}
		break;
	}
	} // switch end

	return 0;
}

bool isBacktracking(int thisdir, int prev)
{
	if (thisdir == 0 && prev == 1)
		return true;
	if (thisdir == 1 && prev == 0)
		return true;
	if (thisdir == 2 && prev == 3)
		return true;
	if (thisdir == 3 && prev == 2)
		return true;

	return false;
}



int MinimumMove(position& red, position& blue, int moveNum, int prevdir)
{
	if (moveNum > 10)
	{
		return 11;
	}
	else if (blue.height == hole.height && blue.width == hole.width) // blue가 hole에 들어가는 경우
	{
		return 99;
	}
	else if (red.height == hole.height && red.width == hole.width) // red만 들어가는 경우
	{
		return moveNum;
	}

	else
	{

		//possible_dir = Possible_dir(red); // RED가 갈수없더라도, 제한시켜버리면 Blue가 변할 여지를 없애버림..
		position tempred, tempblue;
		tempred.height = red.height; tempred.width = red.width;
		tempblue.height = blue.height; tempblue.width = blue.width;

		int min = 999;
		for (int i = 0; i < 4; ++i)
		{

			int temp_min;
			MoveRB(red, blue, i);
			temp_min = MinimumMove(red, blue, ++moveNum, i);
			--moveNum;


			game_board[blue.height][blue.width] = '.';
			game_board[red.height][red.width] = '.';
			game_board[hole.height][hole.width] = 'O';
			red = tempred;
			blue = tempblue;
			game_board[blue.height][blue.width] = 'B';
			game_board[red.height][red.width] = 'R';
			if (temp_min < min) min = temp_min;
		}
		
		return min;



	}
}



int main()
{

	int width, height; // 3 < h,w < 10 	

	string templine;
	position red, blue;

	while (1)
	{
		cin >> height >> width;
		for (int i = 0; i < height; ++i)
		{
			cin >> templine;
			game_board.push_back(templine);
		}


		for (int i = 0; i < height; ++i)
		{
			for (int j = 0; j < width; ++j)
			{
				if (game_board[i][j] == 'R')
				{
					red.height = i; red.width = j;
				}
				if (game_board[i][j] == 'B')
				{
					blue.height = i; blue.width = j;
				}
				if (game_board[i][j] == 'O')
				{
					hole.height = i; hole.width = j;
				}
			}
		}

		int min = MinimumMove(red, blue, 0, -1);

		if (!(min <= 10 && min >= 0)) cout << -1;
		else cout << min;

		game_board.clear();
	}

	return 0;
}

/*
5 5
#####
#.R##
#####
#B.O#
#####

10 6
######
#....#
#.#..#
#..#R#
##.#.#
#....#
#.#.B#
#..#O#
#.#..#
######



5 9
#########
#.......#
##.#OR.B#
#...#.#.#
#########
1

*/