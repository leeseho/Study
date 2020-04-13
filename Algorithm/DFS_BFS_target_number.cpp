#include <iostream>
#include <vector>

using namespace std;

int target_count = 0;


int addsub(vector<int> numbers, int cur_sum, int depth, int len, int target)
{
    depth++; // ȣ��� Ƚ���� ���� : ���ڰ� 5���ΰ�� depth == 4���Ǹ� ������ ����
    if (depth == len - 1) // base case
    {
        if (cur_sum + numbers[depth] == target) ++target_count;
        if (cur_sum - numbers[depth] == target) ++target_count;
    }
    else
    {
        addsub(numbers, cur_sum + numbers[depth], depth, len, target);
        addsub(numbers, cur_sum - numbers[depth], depth, len, target);
    }

    return 0;
}

int solution(vector<int> numbers, int target) {
    int depth = 0;

    int len = numbers.size();
    cout << "len = " << len << endl;

    addsub(numbers, numbers[0], depth, len, target);
    addsub(numbers, -numbers[0], depth, len, target);
    
    cout << "result = " << target_count << endl;

    return 0;
}


int main()
{
    int test;
    vector<int> v_test{ 1, 1, 1, 1, 1 }; // !!! vector �����ϰ� �ʱ�ȭ

    test = solution(v_test, 3);

    cout << "non " << test << endl;
}


