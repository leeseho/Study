#include <iostream>
#include <vector>

using namespace std;


int cleaned = 0;
vector< vector <int> > map;

int LeftX[4] = { -1, 0, 1, 0 };
int LeftY[4] = { 0, -1, 0, 1 };

int RotateDirLeft[4] = { 3, 0, 1, 2 };

int BackCheckX[4] = { 0, -1, 0, 1 };
int BackCheckY[4] = { 1, 0, -1, 0 };

int CleanRoom(int call_y, int call_x, int call_dir)
{
	cout << "Curr Y : " << call_y << " Curr X : " << call_x << " Curr dir : " << call_dir << endl;
	int clean_complete = 0;
	int check_y = call_y;
	int check_x = call_x;
	int check_dir = call_dir;

	if (map[call_y][call_x] != 2) {
		clean_complete++; // 현위치 청소
		map[call_y][call_x] = 2; // 청소완료 상태 == 2;
	}
	
	while (1)
	{
		if (map[check_y + LeftY[check_dir]][check_x + LeftX[check_dir]] == 0)
		{ // 왼쪽이 가능하면 하고 돌아와서, 다시 탐색하는 것이 아니라 이 구간의 다른 방향은 버림.
			clean_complete += CleanRoom(check_y + LeftY[check_dir], check_x + LeftX[check_dir], RotateDirLeft[check_dir]);
			return clean_complete;
		}
		else if (RotateDirLeft[check_dir] == call_dir) // + 위에 의해 : 왼쪽이 이미 청소상태 + 모든 방향 청소 완료.
		{
			if (map[check_y + BackCheckY[call_dir]][check_x + BackCheckX[call_dir]] != 1)// 후진가능?
			{
				// 호출 방향 그대로 후진 후, 호출
				clean_complete += CleanRoom(check_y + BackCheckY[call_dir], check_x + BackCheckX[call_dir], call_dir);
			}
			return clean_complete;
		}
		else
		{
			check_dir = RotateDirLeft[check_dir];
		}
	}

}

int main()
{
	int H, W; // size : not max index
	int start_y, start_x, start_dir;
	cin >> H >> W;
	cin >> start_y >> start_x >> start_dir;

	map.assign(H, vector<int>(W, 0));
	for (int i = 0; i < H; ++i)
	{
		for (int j = 0; j < W; ++j)
		{
			cin >> map[i][j];
		}
	}

	cleaned = CleanRoom(start_y, start_x, start_dir);
	
	/*for (int i = 0; i < H; ++i)
	{
		for (int j = 0; j < W; ++j)
		{
			cout << map[i][j] << " ";
		}
		cout << endl;
	}*/


	cout << cleaned;

	return 0;
}