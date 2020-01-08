/*
#include <iostream>
#include <vector>
using namespace std;

int main() {
	int case_n; // test case 번호

	cin >> case_n;
	for (int i = 0; i < case_n; ++i)
	{
		

	}

	return 0;
}
*/


#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;



int main() {
	int case_n; // test case 번호
	int num_dia, diff;
	int temp_size, max, min;
	int num_max, dia_count;

	vector<int> dias;

	cin >> case_n;
	for (int i = 0; i < case_n; ++i)
	{
		max = 1; min = 10000; // 문제에서 크기는 1~10000으로 한정되어 있음.
		cin >> num_dia >> diff; // 다이아몬드 개수, 다이아몬드간 최대 차이값
		for (int j = 0; j < num_dia; ++j) // 다이아몬드를 벡터에 추가
		{
			cin >> temp_size;
			if (temp_size > max) max = temp_size;
			if (temp_size < min) min = temp_size;
			dias.push_back(temp_size);
		}

		// 벡터를 정렬한다.
		sort(dias.begin(), dias.end());
		

		num_max = 0;
		dia_count = 0;
		
		for (int j = min; j <= max; ++j) // 크기가 j인 다이아몬드 ~ j + diff의 개수 합 탐색.
		{
			for (int k = 0; k < dias.size(); ++k) // 입력받은 벡터 내부 탐색, 조건만족하는 것의 원소 개수
			{
				if (dias[k] > j + diff) break; // 정렬된 상태이므로, 그 이상은 탐색할 필요 없음.
				else if (dias[k] <= j + diff && dias[k] >= j)
					++dia_count;
			}

			if (dia_count > num_max) num_max = dia_count;
			dia_count = 0;
		}


		cout << "#" << i + 1 << " " << num_max << endl;

		dias.clear();
	}

	return 0;
}