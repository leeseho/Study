#include <iostream>
#include <vector>

using namespace std;

vector <vector <int> > ladder_map;
vector <vector <int> > ladder_used;

int Vnum, Mnum, Hnum;
int minimum_ladder;

int BuildNAndSim(int N, int curr_n);
int Simulation_ladder(int cy, int cx);

int main()
{
	cin >> Vnum >> Mnum >> Hnum;
	minimum_ladder = 99999;

	ladder_map.assign(Hnum + 1, vector<int>(Vnum + 1, 0)); // 1~V, 1~H
	ladder_used.assign(Hnum + 1, vector<int>(Vnum + 1, 0)); // 1~V, 1~H

	int i; int y_temp, x_temp;
	for (i = 1; i <= Mnum; ++i)
	{
		cin >> y_temp >> x_temp;
		ladder_map[y_temp][x_temp] = 1; // 사다리 존재
	}

	for (i = 0; i <= 3; ++i)
	{
		BuildNAndSim(i, 0);
		if(minimum_ladder != 99999)
		{
			break; // 가장 빠른 성공에서 탈출 
		}
	}

	if (minimum_ladder != 99999) cout << minimum_ladder;
	else cout << -1;

	return 0;
}


int BuildNAndSim(int N, int curr_n) {
	if (curr_n == N)
	{
		int isItoI = true;
		//Sim
		for (int s = 1; s <= Vnum; ++s)
		{
			int sim_return;
			sim_return = Simulation_ladder(1, s);
			ladder_used.assign(Hnum + 1, vector<int>(Vnum + 1, 0)); // 매 번호에 대한 Simulation 전 초기화 -> 순서 주의! 빠져나가기 전에 하면 다음에..
			if (sim_return != s)
			{
				isItoI = false;
				break; // 그 뒤는 볼것도 없음.
			}
		}
		if (isItoI == true) minimum_ladder = curr_n; // 성공 종료
		// 실패 종료

		return 0;
	}
	else
	{
		for (int h = 1; h <= Hnum; ++h)
		{
			for (int v = 1; v <= Vnum - 1; ++v) // !!! Vunm 까지로하면 안됨.. Vnum - Vnum +1을 이어주는 선이기 때문
			{
				if (ladder_map[h][v] == 0 && ladder_map[h][v+1] != 1 && ladder_map[h][v - 1] != 1)
				{
					ladder_map[h][v] = 1;
					BuildNAndSim(N, curr_n + 1);
					ladder_map[h][v] = 0;
				}
			}
		}

	}
}


int Simulation_ladder(int cy, int cx) // 종료시 cx 좌표 리턴
{
	if (cy > Hnum)
	{
		return cx;
	}
	else
	{
		int check_cy = cy, check_cx = cx;
		if (ladder_map[cy][cx] == 1 && ladder_used[cy][cx] == 0)
		{
			ladder_used[cy][cx] = 1;
			return Simulation_ladder(cy, cx + 1);
		}
		else if (check_cx - 1 >= 1 && ladder_map[cy][cx - 1] == 1 && ladder_used[cy][cx - 1] == 0) 
			// 0부터 잡았기 때문에 check_cx - 1 >= 1는 없어도 되지만, 항상 주의!!!
		{
			ladder_used[cy][cx - 1] = 1;
			return Simulation_ladder(cy, cx - 1);
		}
		else
		{
			return Simulation_ladder(cy + 1, cx);
		}
	}
}