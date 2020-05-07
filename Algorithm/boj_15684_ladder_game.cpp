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
		ladder_map[y_temp][x_temp] = 1; // ��ٸ� ����
	}

	for (i = 0; i <= 3; ++i)
	{
		BuildNAndSim(i, 0);
		if(minimum_ladder != 99999)
		{
			break; // ���� ���� �������� Ż�� 
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
			ladder_used.assign(Hnum + 1, vector<int>(Vnum + 1, 0)); // �� ��ȣ�� ���� Simulation �� �ʱ�ȭ -> ���� ����! ���������� ���� �ϸ� ������..
			if (sim_return != s)
			{
				isItoI = false;
				break; // �� �ڴ� ���͵� ����.
			}
		}
		if (isItoI == true) minimum_ladder = curr_n; // ���� ����
		// ���� ����

		return 0;
	}
	else
	{
		for (int h = 1; h <= Hnum; ++h)
		{
			for (int v = 1; v <= Vnum - 1; ++v) // !!! Vunm �������ϸ� �ȵ�.. Vnum - Vnum +1�� �̾��ִ� ���̱� ����
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


int Simulation_ladder(int cy, int cx) // ����� cx ��ǥ ����
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
			// 0���� ��ұ� ������ check_cx - 1 >= 1�� ��� ������, �׻� ����!!!
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