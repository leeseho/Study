#include <iostream>
#include <vector>
using namespace std;


int main() {
	int case_n; // test case ��ȣ
	int N, M; // N: ���ں��� ����, M�� �� �� �ִ� �ִ� ����
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

		




		snacks.clear(); // �� case�� �������� ���� vector �ʱ�ȭ
	}


	return 0;
}