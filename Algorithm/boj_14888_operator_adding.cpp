#include <iostream>
#include <vector>

using namespace std;
vector<int> numbers;
vector<int> remaing_operator(4, 0);
int total_max = -1000000000, total_min = 1000000000;

int OperateAndGetMinMax(int numNum, int partial_result)
{
	if (numNum == numbers.size() - 1) //
	{
		if (partial_result > total_max)
			total_max = partial_result;
		if (partial_result < total_min)
			total_min = partial_result;
		return 0;
	}
	else {
		for (int i = 0; i < 4; ++i)
		{
			if (remaing_operator[i] > 0)
			{
				--remaing_operator[i];
				switch (i)
				{
				case 0: // µ¡¼À
				{
					OperateAndGetMinMax(numNum + 1, partial_result + numbers[numNum + 1]);
					break;
				}
				case 1:
				{
					OperateAndGetMinMax(numNum + 1, partial_result - numbers[numNum + 1]);
					break;
				}
				case 2:
				{
					OperateAndGetMinMax(numNum + 1, partial_result * numbers[numNum + 1]);
					break;
				}
				case 3:
				{
					OperateAndGetMinMax(numNum + 1, partial_result / numbers[numNum + 1]);
					break;
				}
				}
				++remaing_operator[i];
			}
		}

	}
	
	return 0;
}

int main()
{
	int N, temp;
	cin >> N;

	for (int i = 0; i < N; ++i)
	{
		cin >> temp;
		numbers.push_back(temp);
	}

	for (int i = 0; i < 4; ++i)
	{
		cin >> remaing_operator[i];
	}

	//cout << "-6 / 5 = " << -6 / 5 << endl;

	OperateAndGetMinMax(0, numbers[0]);

	cout << total_max << endl;
	cout << total_min;


	return 0;
}