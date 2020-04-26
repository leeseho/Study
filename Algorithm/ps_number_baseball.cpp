#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;


int main()
{
	vector<int> a{123,1,1};
	vector<int> b{356,1,0};
	vector<int> c{327,2,0};
	vector<int> d{489,0,1};

	vector < vector<int> > baseball_result; 
	baseball_result.push_back(a);
	baseball_result.push_back(b);
	baseball_result.push_back(c);
	baseball_result.push_back(d);


	int count = 0;


	for (int checking_number = 123; checking_number < 987; ++checking_number)
	{
		string checking_string_number = to_string(checking_number); 
		bool isAllMatch = true;

		if (checking_string_number[0] == checking_string_number[1] ||
			checking_string_number[0] == checking_string_number[2] ||
			checking_string_number[1] == checking_string_number[2]) 
		{
			//cout << "pass num : " << checking_number << endl;
			continue;
		}

		if (checking_string_number[0] == '0' || checking_string_number[1] == '0' || checking_string_number[2] == '0') { continue; }
	

		
		for (int a_S_B_result = 0; a_S_B_result < baseball_result.size(); a_S_B_result++)
		{
			int Strike = 0; int Ball = 0;
			string result_string_number = to_string(baseball_result[a_S_B_result][0]);
				for (int i = 0; i < checking_string_number.size(); ++i) 
				{
					if (result_string_number[i] == checking_string_number[i])
						++Strike;

					for (int j = 0; j < result_string_number.size(); ++j) { 
						if (j == i) continue; 
						if (checking_string_number[i] == result_string_number[j]) Ball++;
					}
				}
				if (Strike != baseball_result[a_S_B_result][1] || Ball != baseball_result[a_S_B_result][2]) 
				{ 
					isAllMatch = false; break;
				}
		}
		

		if (isAllMatch == true) { cout << checking_number << endl; ++count; }

	}

	cout << count << endl;




	return 0;
}