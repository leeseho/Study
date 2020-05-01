#include <iostream>
#include <vector>

using namespace std;

class dir {
public:
	int y_dir;
	int x_dir;
};

vector< vector<int> > map;
vector< vector<int> > rampmap;
dir direction[2] = {1, 0, 0, 1}; // direction[0]:아랫방향, direction[1] : 오른쪽방향
int map_size;

bool isRampAvailable(int y, int x, int ramp_length, int caseud)
{
	bool avail = true;

	switch (caseud)
	{
	case 0: // 아랫방향으로 ramp 설치
	{
		if (rampmap[y + 1][x] == 1) { avail = false; break; }
		for (int i = 1; i < ramp_length; ++i)
		{
			if (y + i + 1 <= map_size - 1 && map[y + i + 1][x] == map[y + i][x]) continue;
			else { avail = false; break; }
		}

		if (avail == true) // ramp 설치
		{
			for (int i = 1; i <= ramp_length; ++i)
			{
				rampmap[y + i][x] = 1;
			}
		}
		break;
	}
	case 1: //윗방향으로 설치
	{
		if (rampmap[y][x] == 1) { avail = false; break; }
		for (int i = 0; i < ramp_length - 1; ++i)
		{
			if (y - i - 1 >= 0 && map[y - i - 1][x] == map[y - i][x] &&
				rampmap[y-i][x] != 1 && rampmap[y - i - 1][x] != 1) continue; // 기존 ramp도 없어야 함
			else { avail = false; break; }
		}
		if (avail == true) // ramp 설치
		{
			for (int i = 0; i < ramp_length; ++i)
			{
				rampmap[y - i][x] = 1;
			}
		}
		break;
	}
	case 2: // 오른쪽
	{
		if (rampmap[y][x + 1] == 1) { avail = false; break; }
		for (int i = 1; i < ramp_length; ++i)
		{
			if (x + i + 1 <= map_size - 1 && map[y][x + i + 1] == map[y][x + i]) continue;
			else { avail = false; break; }
		}

		if (avail == true) // ramp 설치
		{
			for (int i = 1; i <= ramp_length; ++i)
			{
				rampmap[y][x + i] = 1;
			}
		}
		break;
	}
	case 3:
	{
		if (rampmap[y][x] == 1) { avail = false; break; }

		for (int i = 0; i < ramp_length - 1; ++i)
		{
			if (x - i - 1 >= 0 && map[y][x - i - 1] == map[y][x - i] &&
				rampmap[y][x - i] != 1 && rampmap[y][x - i - 1] != 1) continue; // 기존 ramp도 없어야 함
			else { avail = false; break; }
		}
		if (avail == true) // ramp 설치
		{
			for (int i = 0; i < ramp_length; ++i)
			{
				rampmap[y][x - i] = 1;
			}
		}
		break;
	}
	}
	
	
	return avail;
}

int main()
{
	int x = 0; int y = 0;
	int road_count = 0;
	int ramp_length;
	cin >> map_size;
	cin >> ramp_length;
	map.assign(map_size, vector<int>(map_size, 0));
	rampmap.assign(map_size, vector<int>(map_size, 0));

	for (int i = 0; i < map_size; ++i)
	{
		for (int j = 0; j < map_size; ++j)
		{
			int temp;
			cin >> temp;
			map[i][j] = temp;
			cout << map[i][j] << "\t";
		}
		cout << endl;
	}

	x = 0; y = 0;
	// 한 방향 : 상하방향만 검사
	while (1)
	{
		bool available = true;
		if (y + ramp_length < map_size && map[y][x] - 1 == map[y + 1][x]) // 아랫칸이 1 더 낮고, 남은 칸이 ramp_length 이상인 경우
		{
			// ramp_length만큼 앞으로의 칸이 높이가 같은지 검사하고 가능하면 그 칸만큼 ramp 설치
			// 불가능하면 false 리턴
			if (isRampAvailable(y, x, ramp_length, 0)) // 높이가 같은 경우
			{
				// ramp_map이 이미 1인지 검사 필요 없음 : 아래방향으로 검사하기 때문에
				// ramp 설치만 하면됨
				// ok : 여기서는 아무 것도 안함(if문 밖에서 다음칸 이동)

			}
			else { // 경사로 설치 불가
				available = false;
			}
		}
		else if (y + 1 - ramp_length >= 0 && map[y][x] + 1 == map[y + 1][x]) // 아랫칸이 1 더 높은 경우
		{ 
			
			if (isRampAvailable(y, x, ramp_length, 1)) // ramp를 놓을수 있다면 가능, 1은 윗방향 설치를 의미
			{
				// ok
			}
			else
			{
				available = false;
			}
		}
		else if (y + 1 < map_size && map[y][x] == map[y + 1][x])// 같은 경우 (ramp lenth 길이보다 적게 남은 경우)
		{
			// ok (ramp 놓을 필요 없음)
		}
		else // 높이 차이가 2이상인 경우 or 남은 칸이 부족한 경우 등  : 불가능. -> 바로 다음 열로 이동.
		{
			available = false;
		}

		// 다음칸으로 이동
		x += direction[0].x_dir; // ###
		y += direction[0].y_dir;

		cout << endl << " checking .. (" << y << " , " << x << ")" << endl;

		// 위 조건문에서 하나라도 false 발생시 다음 칸으로 이동 또는 y 초과
		if (y >= map_size - 1 || available == false)  // 마지막칸은 검사 안해도 됨
		{
			if (available == true) ++road_count;
			// available == false인 경우 x방향으로 증가
			y = 0;
			x += direction[1].x_dir;
			y += direction[1].y_dir;

			if (x >= map_size) break;// x축으로 범위 초과한 경우 끝.
		}
	}

	x = 0; y = 0;
	rampmap.assign(map_size, vector<int>(map_size, 0));
	
	while (1) // 좌우 방향
	{
		bool available = true;
		if (x + ramp_length < map_size && map[y][x] - 1 == map[y][x + 1]) // 오른칸이 1 더 낮고, 남은 칸이 ramp_length 이상인 경우
		{
			if (isRampAvailable(y, x, ramp_length, 2)) // 2는 오른쪽으로.. 
			{
				// ok 
			}
			else { // 경사로 설치 불가
				available = false;
			}
		}
		else if (x + 1 - ramp_length >= 0 && map[y][x] + 1 == map[y][x + 1]) // 오른칸이 1 더 높은 경우 + ramp lenth이상 칸이 남은 경우
		{
			if (isRampAvailable(y, x, ramp_length, 3)) // 3은 왼쪽방향 : 현재칸 포함 ramp칸 검사주의
			{
				// ok
			}
			else
			{
				available = false;
			}
		}
		else if (x + 1 < map_size && map[y][x] == map[y][x + 1])// 같은 경우 (ramp lenth 길이보다 적게 남은 경우)
		{
			// ok (ramp 놓을 필요 없음)
		}
		else // 높이 차이가 2이상인 경우 or 남은 칸이 부족한 경우 등  : 불가능. -> 바로 다음 열로 이동.
		{
			available = false;
		}

		// 다음칸으로 이동
		x += direction[1].x_dir; // ###
		y += direction[1].y_dir;

		cout << endl << " checking .. (" << y << " , " << x << ")" << endl;

		// 위 조건문에서 하나라도 false 발생시 다음 칸으로 이동 또는 y 초과
		if (x >= map_size - 1 || available == false)  // 마지막칸은 검사 안해도 됨
		{
			if (available == true) ++road_count;
			// available == false인 경우 x방향으로 증가
			x = 0;
			x += direction[0].x_dir;
			y += direction[0].y_dir;

			if (y >= map_size) break;// x축으로 범위 초과한 경우 끝.
		}
	}
	
	cout << road_count;


	return 0;
}