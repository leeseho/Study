/*
#include <iostream>
#include <vector>
using namespace std;

int main() {
	int case_n; // test case ��ȣ

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
	int case_n; // test case ��ȣ
	int num_dia, diff;
	int temp_size;

	vector<int> dias;
	vector<int> bundle_dia;

	cin >> case_n;
	for (int i = 0; i < case_n; ++i)
	{
		cin >> num_dia >> diff; // ���̾Ƹ�� ����, ���̾Ƹ�尣 �ִ� ���̰�
		for (int j = 0; j < num_dia; ++j) // ���̾Ƹ�带 ���Ϳ� �߰�
		{
			cin >> temp_size;
			dias.push_back(temp_size);
		}



		dias.clear();
	}

	return 0;
}


