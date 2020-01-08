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
#include <algorithm>
using namespace std;



int main() {
	int case_n; // test case ��ȣ
	int num_dia, diff;
	int temp_size, max, min;
	int num_max, dia_count;

	vector<int> dias;

	cin >> case_n;
	for (int i = 0; i < case_n; ++i)
	{
		max = 1; min = 10000; // �������� ũ��� 1~10000���� �����Ǿ� ����.
		cin >> num_dia >> diff; // ���̾Ƹ�� ����, ���̾Ƹ�尣 �ִ� ���̰�
		for (int j = 0; j < num_dia; ++j) // ���̾Ƹ�带 ���Ϳ� �߰�
		{
			cin >> temp_size;
			if (temp_size > max) max = temp_size;
			if (temp_size < min) min = temp_size;
			dias.push_back(temp_size);
		}

		// ���͸� �����Ѵ�.
		sort(dias.begin(), dias.end());
		

		num_max = 0;
		dia_count = 0;
		
		for (int j = min; j <= max; ++j) // ũ�Ⱑ j�� ���̾Ƹ�� ~ j + diff�� ���� �� Ž��.
		{
			for (int k = 0; k < dias.size(); ++k) // �Է¹��� ���� ���� Ž��, ���Ǹ����ϴ� ���� ���� ����
			{
				if (dias[k] > j + diff) break; // ���ĵ� �����̹Ƿ�, �� �̻��� Ž���� �ʿ� ����.
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