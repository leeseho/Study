#include <iostream>
#include <vector>

using namespace std;

vector < vector<int> > dragon_curve(101, vector<int>(101, 0)); // 100x100 격자칸

vector <int> past_dir;


int movex[4] = { 1,0,-1,0 };
int movey[4] = { 0,-1,0,1 };

// 0 -> 1, 1 -> 2, 2 -> 3, 3 -> 0
int thisdir[4] = { 1, 2, 3, 0 };

// 시작점, 방향, 세대
int DrawDragonCurve(int& x, int & y) 
{
	for (int i = past_dir.size() - 1; i >= 0; --i)
	{
		x = x + movex[thisdir[past_dir[i]]];
		y = y + movey[thisdir[past_dir[i]]];
		//cout << "x : " << x << " y : " << y << endl;;
		dragon_curve[x][y] = 1; // draw

		past_dir.push_back(thisdir[past_dir[i]]);
	}

	return 0;
}

int main()
{
	int N;
	cin >> N;

	for (int i = 0; i < N; ++i) // N개의 dragon curve 그리기
	{
		int x, y, dir, generation;
		cin >> x >> y >> dir >> generation;
		dragon_curve[x][y] = 1;
		past_dir.push_back(dir);

		// start to dir
		x += movex[dir];
		y += movey[dir];
		dragon_curve[x][y] = 1;

		//cout << "x : " << x << " y : " << y << endl;;

		for (int j = 0; j < generation; ++j) {	
			DrawDragonCurve(x, y);
		}

		//cout << endl << endl;
		past_dir.clear();
	}
	// dragon curve draw 끝

	for (int i = 0; i < 10; ++i)
	{
		for (int j = 0; j < 10; ++j)
		{
			cout << dragon_curve[j][i] << " ";
		}
		cout << endl;
	}

	int sqaures = 0;
	for (int i = 0; i < 101; ++i)
	{
		for (int j = 0; j < 101; ++j)
		{
			if (dragon_curve[j][i] == 1 &&
				dragon_curve[j + 1][i] == 1 &&
				dragon_curve[j][i + 1] == 1 &&
				dragon_curve[j + 1][i + 1] == 1
				)
			{
				sqaures++;
			}
		}
	}

	cout << sqaures;
	

	return 0;
}
