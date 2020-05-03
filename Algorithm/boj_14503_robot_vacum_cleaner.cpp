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
		clean_complete++; // ����ġ û��
		map[call_y][call_x] = 2; // û�ҿϷ� ���� == 2;
	}
	
	while (1)
	{
		if (map[check_y + LeftY[check_dir]][check_x + LeftX[check_dir]] == 0)
		{ // ������ �����ϸ� �ϰ� ���ƿͼ�, �ٽ� Ž���ϴ� ���� �ƴ϶� �� ������ �ٸ� ������ ����.
			clean_complete += CleanRoom(check_y + LeftY[check_dir], check_x + LeftX[check_dir], RotateDirLeft[check_dir]);
			return clean_complete;
		}
		else if (RotateDirLeft[check_dir] == call_dir) // + ���� ���� : ������ �̹� û�һ��� + ��� ���� û�� �Ϸ�.
		{
			if (map[check_y + BackCheckY[call_dir]][check_x + BackCheckX[call_dir]] != 1)// ��������?
			{
				// ȣ�� ���� �״�� ���� ��, ȣ��
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