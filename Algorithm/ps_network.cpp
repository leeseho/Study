#include <iostream>
#include <vector>

using namespace std;

vector<int> visit; // �湮����..
int network_count; // ��Ʈ��ũ ����


int my_dfs(vector<vector<int> > computers, int s)
{
    int i;

    visit[s] = 1; // s�� �湮

    for (i = 0; i < computers[0].size(); ++i) // s�� ����� ��� ã��
    {
        if (computers[s][i] == 1 && visit[i] == 0) // s�� i�� ����Ǿ��ְ�, �湮���� ���� ���
            my_dfs(computers, i); // ã���� ȣ��
    }
    return 0;
}


int find_network(vector<vector<int> > computers) {
    
    for (int i = 0; i < computers[0].size(); ++i)
    {
        if (visit[i] != 1)
        {
            network_count++;
            my_dfs(computers, i);
        }
    }

    return 0;
}



int solution(int n, vector<vector<int>> computers) {
    

    



    return answer;
}



int main()
{
    int test_n;
    vector< vector<int> > test_com;
    
}