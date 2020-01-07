#include <iostream>
#include <vector>
using namespace std;

int Find_Max_weight(vector<int>& snack, int case_MAX)
{
	int len, max, sum;
	len = snack.size(); // 과자의 개수

	max = 0;
	for (int i = 0; i < len; ++i)
	{
		for (int j = i + 1; j < len; ++j)
		{
			sum = snack[i] + snack[j]; // 두 과자 무게의 합
			if (sum > case_MAX) continue;
			else if (max < sum) max = sum;
			if (max == case_MAX) return max; // 해당 케이스의 최대값이라면 바로 return
		}
	}
	
	if (max == 0) return -1;
	
	return max;
}



int main() {
	int case_n; // test case 번호
	int N, M, max; // N: 과자봉지 개수, M는 들 수 있는 최대 무게
	vector<int> snacks;

	cin >> case_n;
	for (int i = 0; i < case_n; ++i)
	{
		cin >> N >> M;
		for (int j = 0; j < N; ++j) // 각 과자봉지의 무게를 입력받음.
		{
			int snack_temp;
			cin >> snack_temp;
			snacks.push_back(snack_temp); // vector에 추가
		}
		// ====== vector에 저장 완료...

		max = Find_Max_weight(snacks, M);

		cout << "#" << i + 1 << " " << max << endl;


		snacks.clear(); // 각 case가 끝났을때 과자 vector 초기화
	}


	return 0;
}