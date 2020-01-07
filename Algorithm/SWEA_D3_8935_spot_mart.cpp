#include <iostream>
#include <vector>
using namespace std;

int Find_Max_weight(vector<int>& snack, int case_MAX)
{
	int len, max, sum;
	len = snack.size(); // ������ ����

	max = 0;
	for (int i = 0; i < len; ++i)
	{
		for (int j = i + 1; j < len; ++j)
		{
			sum = snack[i] + snack[j]; // �� ���� ������ ��
			if (sum > case_MAX) continue;
			else if (max < sum) max = sum;
			if (max == case_MAX) return max; // �ش� ���̽��� �ִ밪�̶�� �ٷ� return
		}
	}
	
	if (max == 0) return -1;
	
	return max;
}



int main() {
	int case_n; // test case ��ȣ
	int N, M, max; // N: ���ں��� ����, M�� �� �� �ִ� �ִ� ����
	vector<int> snacks;

	cin >> case_n;
	for (int i = 0; i < case_n; ++i)
	{
		cin >> N >> M;
		for (int j = 0; j < N; ++j) // �� ���ں����� ���Ը� �Է¹���.
		{
			int snack_temp;
			cin >> snack_temp;
			snacks.push_back(snack_temp); // vector�� �߰�
		}
		// ====== vector�� ���� �Ϸ�...

		max = Find_Max_weight(snacks, M);

		cout << "#" << i + 1 << " " << max << endl;


		snacks.clear(); // �� case�� �������� ���� vector �ʱ�ȭ
	}


	return 0;
}