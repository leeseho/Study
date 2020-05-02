#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int N, x, y, d1, d2;
vector< vector<int> > population_map;
vector< vector<int> > boundary_map;


bool IsInFiveArea(int in_r, int in_c)
{
	bool isinfive = false;

	bool d1_check = false;
	bool d2_check = false;

	// 1번, 3번 경계선 check
	for (int i = 0; i <= d1; ++i)
	{
		if (in_r >= x + i && in_c >= y - i &&
			in_r <= x + d2 + i && in_c <= y + d2 - i)
			d1_check = true;
	}

	for (int i = 0; i <= d2; ++i)
	{
		if (in_r >= x + i && in_c <= y + i &&
			in_r <= x + d1 + i && in_c >= y - d1 + i)
			d2_check = true;
	}
	
	if (d1_check && d2_check) isinfive = true;


	return isinfive;
}


int DivideDistrict()
{
	vector<int> comp; // 벡터를 처음 할당해버림
	int p1 = 0, p2 = 0, p3 = 0, p4 = 0, p5 = 0;

	int dmax = 0;
	int dmin = 9999;
	// 구역나누고
	for (int i = 1; i <= N; ++i)
	{
		for (int j = 1; j <= N; ++j)
		{
			boundary_map[i][j] = 5;
			p5 += population_map[i][j]; // 전체 인원 수
		}
	}

	for (int i = 1; i < x+d1; ++i) // 1번 구역
	{
		for (int j = 1; j <= y; ++j)
		{
			if (!IsInFiveArea(i, j))
			{
				boundary_map[i][j] = 1;
				p1 += population_map[i][j]; // 1번구역 인구 모두 더함
				p5 -= population_map[i][j];
			}
		}
	}

	for (int i = 1; i <= x+d2; ++i) // 2번 구역
	{
		for (int j = y + 1; j <= N; ++j)
		{
			if (!IsInFiveArea(i, j))
			{
				boundary_map[i][j] = 2;
				p2 += population_map[i][j];
				p5 -= population_map[i][j];
			}
		}
	}

	for (int i = x+d1; i <= N; ++i) // 3번 구역
	{
		for (int j = 1; j < y-d1+d2; ++j)
		{
			if (!IsInFiveArea(i, j))
			{
				boundary_map[i][j] = 3;
				p3 += population_map[i][j];
				p5 -= population_map[i][j];
			}
		}
	}

	for (int i = x + d2 + 1; i <= N; ++i) // 4번 구역
	{
		for (int j = y - d1 + d2; j <= N; ++j)
		{
			if (!IsInFiveArea(i, j))
			{
				boundary_map[i][j] = 4;
				p4 += population_map[i][j];
				p5 -= population_map[i][j];
			}
		}
	}

	comp.push_back(p1); 
	comp.push_back(p2);
	comp.push_back(p3); 
	comp.push_back(p4); 
	comp.push_back(p5); 

	dmax = *max_element(comp.begin(), comp.end()); // 함수는 주소를 반환함!!!
	dmin = *min_element(comp.begin(), comp.end());
	

	return dmax - dmin;
}

int PrintBoundaryMap()
{
	for (int i = 1; i <= N; ++i) {
		for (int j = 1; j <= N; ++j)
			cout << boundary_map[i][j] << "\t";
		cout << endl;
	}

	cout << " x: " << x << " y: " << y << " d1: " << d1 << " d2: " << d2;
	cout << endl << endl;

	return 0;
}


int main()
{
	int whole_minimum = 9999, temp_minimum = 9999;
	cin >> N;
	population_map.assign(N+1, vector<int>(N+1, 0)); // index 0은 없는걸로..
	boundary_map.assign(N+1, vector<int>(N+1, 0));

	for (int i = 1; i <= N; ++i)
	{
		for (int j = 1; j <= N; ++j)
		{
			int temp;
			cin >> temp;
			population_map[i][j] = temp;
		}
	}

	for (d1 = 1; d1 < N; ++d1)
	{
		for (d2 = 1; d2 < N; ++d2)
		{
			for (x = 1; x < N; ++x)
			{
				for (y = 1; y < N; ++y)
				{
					if (x + d1 + d2 > N || y - d1 < 1 || y + d2 > N) continue; // 범위이탈
					else // 범위내이면 구역 나누고, 최대 - 최소 
					{
						temp_minimum = DivideDistrict();

						if (temp_minimum < whole_minimum)
						{
							whole_minimum = temp_minimum;
							//PrintBoundaryMap();
						}
					}
				}
			}
		}
	}




	cout << whole_minimum;

	return 0;
}