#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main()
{
	string check_string = "abcabcabcabcdededededede";

	int slice_unit;
	int temp_min = 999, real_min = 999;

	for (slice_unit = 1; slice_unit <= check_string.size(); ++slice_unit)
	{
		int sp = 0;
		int temp_count = 1;

		vector<int> same_count;

		while (sp < check_string.size()- slice_unit) { // sp는 index이고 + 마지막 전 index까지
			check_string.substr(sp, slice_unit); // slice unit만큼 자른다.
			// 다음 slice랑 같은지 확인
			if (check_string.substr(sp, slice_unit) == check_string.substr(sp + slice_unit, slice_unit))
			{//같으면 압축
				cout << check_string.substr(sp, slice_unit) << " = " << check_string.substr(sp + slice_unit, slice_unit) << endl;
				temp_count++;
			}
			else {
				if (temp_count != 1) same_count.push_back(temp_count);
				temp_count = 1; // 1로 초기화
			}
			sp += slice_unit; 
		}

		if (temp_count != 1) same_count.push_back(temp_count);


		// 압축된 string 길이 계산
		int compressed_size;
		int number_hight_sum = 0;
		for (int i = 0; i < same_count.size(); ++i)
		{
			int test_count = same_count[i];
			int high = 1;
			// 자릿수 합
			while (1) {
				if ((test_count / 10) > 0)
				{
					high++; // 자리수 증가
					test_count /= 10;
				}
				else break;
			}
			number_hight_sum += high;
		}

		compressed_size = number_hight_sum + same_count.size() * slice_unit;

		int uncompressed;
		// 압축 안된 string 길이 계산
		int before_comp_size = 0;
		for (int i = 0; i < same_count.size(); ++i)
		{
			before_comp_size += same_count[i] * slice_unit;
		}
		
		uncompressed = check_string.size() - before_comp_size;

		int partial_min;
		partial_min = compressed_size + uncompressed;
		
		if (partial_min < real_min)
			real_min = partial_min;
		
		same_count.clear();
	}

	cout << "minimum compressed string length : " << real_min << endl;


	return 0;
}