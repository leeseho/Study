#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class position {
public:
	int y;
	int x;
};

position dir[4] = { 0,1,0,-1, 1,0, -1,0 }; // !!!

int height, width, time;
queue<position> qu;
vector< vector<int> > map;
vector< vector<int> > addmap;
position upper_airpurifier, under_airpurifier;


// 
int SpreadAndClean(int t)
{
	// �� ������ ��ġ�� ã�´�.
	// �ش� ��ġ���� Ȯ�� ��Ű��, ����û���� �������� ȸ���Ѵ�.

	// base case : time��ŭ �ð��� ������ ��.
	if (t == time)
	{
		cout << endl;
		int dustsum = 0;
		// map���� �̼������� ������ ���� �����Ѵ�.
		for (int h = 0; h < height; ++h)
		{
			for (int w = 0; w < width; ++w)
			{
				cout << map[h][w] << "\t";
				if (map[h][w] != -1 && map[h][w] != 0)
				{
					dustsum += map[h][w];
				}
			}
			cout << endl;
		}

		return dustsum;
	}
	else
	{
		// 1. ����Ȯ��
		vector<position> dustpos;
		for (int h = 0; h < height; ++h)
		{
			for (int w = 0; w < width; ++w)
			{
				if (map[h][w] != 0 && map[h][w] != -1) {
					for (int dirindex = 0; dirindex < 4; ++dirindex)
					{
						if (h + dir[dirindex].y >= 0 && h + dir[dirindex].y < map.size() &&
							w + dir[dirindex].x >= 0 && w + dir[dirindex].x < map[0].size() &&
							map[h + dir[dirindex].y][w + dir[dirindex].x] != -1) // ���� �� index�̰�, ����û���Ⱑ �ƴѰ�� ����ġ�� Ȯ��
						{
							addmap[h + dir[dirindex].y][w + dir[dirindex].x] += (int)(0.2 * map[h][w]);
							addmap[h][w] -= (int)(0.2 * map[h][w]);
						}
					} // 4�������� ��� Ȯ��
				}
			}
		}

		
		for (int h = 0; h < height; ++h)
		{
			for (int w = 0; w < width; ++w)
			{
				map[h][w] += addmap[h][w];
			}
		}
		addmap.assign(height, vector<int>(width, 0)); // addmap �ʱ�ȭ



		// 2. û��
		for (int i = upper_airpurifier.y - 1; i > 0; --i)
		{
			// ������ �Ʒ���
			map[i][0] = map[i - 1][0];
		}
		for (int i = 0; i < width - 1; ++i)
		{// �����ʿ��� ��������
			map[0][i] = map[0][i + 1];
		}
		for (int i = 0; i < upper_airpurifier.y; ++i)
		{// �Ʒ����� ����
			map[i][width - 1] = map[i + 1][width - 1];
		}
		for (int i = width - 1; i >= 2; --i)
		{// ��-> ��
			map[upper_airpurifier.y][i] = map[upper_airpurifier.y][i - 1];
		}
		map[upper_airpurifier.y][1] = 0;



		for (int i = under_airpurifier.y + 1; i < height - 1; ++i)
		{
			map[i][0] = map[i + 1][0];
		}
		for (int i = 0; i < width - 1; ++i)
		{
			map[height - 1][i] = map[height - 1][i + 1];
		}
		for (int i = height - 1; i >= under_airpurifier.y + 1; --i)
		{
			map[i][width - 1] = map[i - 1][width - 1];
		}
		for (int i = width - 1; i >= 2; --i)
		{
			map[under_airpurifier.y][i] = map[under_airpurifier.y][i - 1];
		}
		map[under_airpurifier.y][1] = 0;

		return SpreadAndClean(++t);
	}
	
}

/*
5 5 1
1 2 1 2 1
-1 0 0 0 2
-1 0 0 0 1
1 0 0 0 2
2 1 2 1 2
*/


int main()
{
	cin >> height >> width >> time;
	
	map.assign(height, vector<int>(width, 0));
	addmap.assign(height, vector<int>(width, 0));


	bool find = false;
	for (int h = 0; h < height; ++h)
	{
		for (int w = 0; w < width; ++w)
		{
			int temp;
			cin >> temp;
			if (temp == -1 && find == false) // ����û������ ��ġ
			{
				find = true;
				upper_airpurifier.y = h;
				upper_airpurifier.x = w;

				under_airpurifier.y = h + 1;
				under_airpurifier.x = w;
			}
			map[h][w] = temp;
		}
	}

	int dust = SpreadAndClean(0);

	cout << dust;

	return 0;
}