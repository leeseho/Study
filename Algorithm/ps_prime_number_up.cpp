#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> CheckComplete;

bool isPrimeNumber(string SelectedNumber) {
	int IntNumber = atoi(SelectedNumber.c_str()); 


	bool isPrime = true;
	if (IntNumber == 1 || IntNumber == 0)
	{
		return false;
	}
	else {
		for (int divisor = 2; divisor < IntNumber; ++divisor)
		{
			if (IntNumber % divisor == 0)
			{
				return false;
			}
		}
	}



	vector<int>::iterator IntNumberPosition;
	IntNumberPosition = find(CheckComplete.begin(), CheckComplete.end(), IntNumber);

	if(IntNumberPosition != CheckComplete.end()) 
	{
		isPrime = false; 
	}
	else
	{
		isPrime = true;
		CheckComplete.push_back(IntNumber);
	}



	return isPrime;
}

string getRemainingString(string Remaining_string, int Select)
{
	string New_remaining;
	if (Select == 0) 
	{
		 
		New_remaining = Remaining_string.substr(1, Remaining_string.size() - 1); 
	}
	else if (Select == Remaining_string.size() -1 )
	{
		 
		New_remaining = Remaining_string.substr(0, Remaining_string.size() - 1);
	}
	else
	{
		New_remaining = Remaining_string.substr(0, Select) + 
			Remaining_string.substr(Select + 1, Remaining_string.size() - 1 - Select);
	}

	return New_remaining;
}

int GetPermutationAndCheckPrime(string Remaining_string, int Number_position, string Select_so_far)
{
	int Prime_count_below = 0; 
	string New_remaing_string;

	
	if (Select_so_far.size() == Number_position)
	{
		if (isPrimeNumber(Select_so_far) == true)
		{
			return 1;
		}
		return 0;
	}
	else
	{
		for (int select_in_this_recursion = 0; select_in_this_recursion < Remaining_string.size(); select_in_this_recursion++)
		{
			Select_so_far = Select_so_far + Remaining_string[select_in_this_recursion]; 
			New_remaing_string = getRemainingString(Remaining_string, select_in_this_recursion);
			Prime_count_below += GetPermutationAndCheckPrime(New_remaing_string, Number_position, Select_so_far);
			Select_so_far = Select_so_far.substr(0, Select_so_far.size() - 1); 
		} 
		return Prime_count_below; 
		
	}
}



int main()
{
	int Prime_Count = 0;
	string Input_number = "17";
	
	int String_length = Input_number.size();
	//if (String_length == NULL) cout << "SL_error" << endl;
	
	
	for (int Number_position = 1; Number_position <= String_length; ++Number_position) 	
	{
		string Select_so_far = "";
		Prime_Count += GetPermutationAndCheckPrime(Input_number, Number_position, Select_so_far);
			
	}

	cout << Prime_Count << endl;

	
	return 0;
			
}