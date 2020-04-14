#include <iostream>
#include <vector>

using namespace std;

vector<int> visit; // 방문여부..
int network_count; // 네트워크 개수


int my_dfs(vector<vector<int> > computers, int s)
{
    int i;

    visit[s] = 1; // s를 방문

    for (i = 0; i < computers[0].size(); ++i) // s와 연결된 요소 찾기
    {
        if (computers[s][i] == 1 && visit[i] == 0) // s와 i가 연결되어있고, 방문하지 않은 경우
            my_dfs(computers, i); // 찾으면 호출
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