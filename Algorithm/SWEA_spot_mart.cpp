#include <iostream>
#include <vector>
using namespace std;


int main() {
	int case_n; // test case 번호
	int N, M; // N: 과자봉지 개수, M는 들 수 있는 최대 무게
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

		




		snacks.clear(); // 각 case가 끝났을때 과자 vector 초기화
	}


	return 0;
}