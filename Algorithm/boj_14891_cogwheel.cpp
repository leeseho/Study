#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

vector <string> cogwheel_state(5, ""); // 0¹ø ¹«½Ã

int scores[5] = { 0, 1, 2, 4, 8 };


int Rotate_One(int cogNum, int dir)
{
	switch (dir)
	{
	case -1:
	{
		int first_element = cogwheel_state[cogNum][0];
		for (int i = 0; i < 7; ++i)
		{
			cogwheel_state[cogNum][i] = cogwheel_state[cogNum][i + 1];
		}
		cogwheel_state[cogNum][7] = first_element;
		break;
	}
	case 1:
	{
		int last_element = cogwheel_state[cogNum][7];
		for (int i = 7; i > 0; --i)
		{
			cogwheel_state[cogNum][i] = cogwheel_state[cogNum][i-1];
		}
		cogwheel_state[cogNum][0] = last_element;
		break;
	}
	}

	return 0;
}



int Rotate_Every(int cogNum, int dir, int rl)
{
	int right_cognum, left_cognum;
	right_cognum = cogNum + 1;
	left_cognum = cogNum - 1;
	
	if (right_cognum <= 4 && (rl == 0 || rl == 1))
	{
		if (cogwheel_state[cogNum][2] != cogwheel_state[right_cognum][6])
		{
			Rotate_Every(right_cognum, -dir, 1);
		}
	}

	if(left_cognum >= 1 && (rl == 0 || rl == 2))
	{
		if (cogwheel_state[cogNum][6] != cogwheel_state[left_cognum][2])
			Rotate_Every(left_cognum, -dir, 2);
	}

	Rotate_One(cogNum, dir);

	return 0;
}


int main()
{
	for (int num = 1; num <= 4; ++num)
	{
		cin >> cogwheel_state[num];
	}

	int N;
	cin >> N;
	for (int i = 0; i < N; ++i) 
	{
		int cogNum, dir;
		cin >> cogNum >> dir;
		Rotate_Every(cogNum, dir, 0);
	}

	int score = 0;
	size_t zero = 1;
	for (int i = 1; i <= 4; ++i)
	{
		score += (cogwheel_state[i][0] - '0') * scores[i]; // !!!!
	}

	cout << score;

	return 0;
}