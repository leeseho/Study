#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main()
{
	int case_n;
	int string_len;
	

	cin >> case_n;
	for (int i = 0; i < case_n; ++i)
	{
		cin >> string_len;
		string answer;
		string submit;
		int right_char = 0;
		

		cin >> answer >> submit;
		
		for (int j = 0; j < string_len; ++j)
		{
			if (answer.at(j) == submit.at(j))
			{
				++right_char;
			}
		}

		cout << right_char << endl;
			   		
	}



	return 0;
}