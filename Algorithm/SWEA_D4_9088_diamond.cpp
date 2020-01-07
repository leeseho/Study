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
using namespace std;

int main() {
	int case_n; // test case 번호
	int num_dia, diff;
	int temp_size;

	vector<int> dias;
	vector<int> bundle_dia;

	cin >> case_n;
	for (int i = 0; i < case_n; ++i)
	{
		cin >> num_dia >> diff; // 다이아몬드 개수, 다이아몬드간 최대 차이값
		for (int j = 0; j < num_dia; ++j) // 다이아몬드를 벡터에 추가
		{
			cin >> temp_size;
			dias.push_back(temp_size);
		}



		dias.clear();
	}

	return 0;
}


