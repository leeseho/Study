#include <iostream>
#include <vector>
#include <string>
#include <queue>

using namespace std;

vector< vector<int> > Grp_int;
queue<int> Queue;


int Create_grpah(string begin, string target, vector<string> words)
{
    // 이번 문제의 그래프 규칙 : 서로 한글자씩 차이나는 string끼리만 연결된다.
    string temp;
    int NumOfVertex = 1 + words.size(); // begin 정점(1개)와 words의 개수
    
    int LengthOfWords = begin.size(); // 각 단어들의 길이
    int Target_index = -1;
    
    // 먼저 words 원소, begin을 그래프로 나타내기 위해- vertex 번호를 부여한다.
    // 내가 만든 규칙은
    // words의 원소들은 각 자신의 index번호를 vertex 번호로 가지고
    // begin은 words 마지막 + 1의 index를 갖도록 한다.
    vector<string> Vertex;
    for (int i = 0; i < NumOfVertex - 1; ++i)
    {
        Vertex.push_back(words[i]);
        if (words[i] == target)
        {
            Target_index = i; // target이 몇번 vertex인지 찾아서 리턴으로 전달
        }
    }
    Vertex.push_back(begin);
    // <== vertex 번호부여 완료

    // Vector 이차원배열 assign 후 접근!!!
    Grp_int.assign(NumOfVertex, vector<int>(NumOfVertex, 0)); // 2차원벡터 0으로 초기화!!!

    for (int i = 0; i < NumOfVertex; ++i)
    {
        for (int j = 0; j < NumOfVertex; ++j)
        {
            int same_char_count = 0;
            for (int ch = 0; ch < LengthOfWords; ++ch) // 이 for문은 string내의 문자를 하나하나 체크하기위함
            {
                if (Vertex[i][ch] == Vertex[j][ch]) // 하나만 다를 때 연결
                {
                    same_char_count++;
                    if (same_char_count >= LengthOfWords - 1) // 한글자만 다르면
                    {
                        Grp_int[i][j] = 1; // 연결
                        break;
                    }
                }
            }
          
        }
    }
   
    

    // 생성한 그래프 인접 행렬 테스트 출력
    for (int i = 0; i < NumOfVertex; ++i)
    {
        for (int j = 0; j < NumOfVertex; ++j)
        {
            cout << Grp_int[i][j];
        }
        cout << endl;
    }

    return Target_index;
}


int FindShortestPath_BFS(int begin_index, int target_index)
{
    // Target을 어디서 검사하는가?
    // Length를 어디서 update하는가?(리턴 위치 고려)

    // 이 문제에서는 단순히 몇번 이동했는지만 알면 되기때문에(비용이 같음) 굳이 다익스트라x, BFS로 가능.
    int Length = 0; // depth와 같음
    int depth_count = 0;
    int bfs_count = 0;
    int adj_vertex_count = 0;
    

    int curr, next;
    vector<int> Is_visited_Before(Grp_int.size(), 0); // 방문여부 : 0으로 초기화
    
    Queue.push(begin_index);

    while (Queue.empty() == false) // Queue에 아무것도 없을때까지 반복 
    {
        
        curr = Queue.front();
        Is_visited_Before[curr] = 1; // 방문함
        
        for (int i = 0; i < Grp_int.size(); ++i) // curr에서 갈 수 있는 vertex 찾는 for문
        {
            if (Grp_int[curr][i] == 1 && Is_visited_Before[i] == 0) // 현재꺼낸 vertex와 연결되어있고, 이전에 방문되지 않았다면
            {
                if (i == target_index) // 연결가능하다면, 먼저 Target index인지 검사
                {// 맞다면 끝
                    return Length + 1; // curr의 다음이므로 + 1
                }
                
                adj_vertex_count++; // 이전dep개수만큼(bfs_count) 순회할때, 그 다음 depth의 갯수를 누적카운트
                Queue.push(i); // Target이 아니면, 큐에 넣음
            }
        }
        if (bfs_count == 0) { // 
            bfs_count = adj_vertex_count; // 처음에도 들어와서, 다음 bfs 몇번동안 depth가 같은지 bfs_count에 넣음
            adj_vertex_count = 0; // 다음 depth를 돌때, 그 다음 depth의 갯수를 카운트하기 위한 변수
            Length++;
        }
        
        Queue.pop();
        bfs_count--;
    }

    // 위의 중간 결과에서 return을 못하면 못찾은 경우임
    return 0; // 0 반환하면 target을 못찾은 경우
}


int solution(string begin, string target, vector<string> words) { // main
    int answer = 0;
    int Target_index;
    int Shortest;

    // create graph
    Target_index = Create_grpah(begin, target, words);

    // find shortest path (from begin to target)
    int Begin_index = words.size(); // 7번째이지만 index로는 6임
    Shortest = FindShortestPath_BFS(Begin_index, Target_index);
    


    answer = Shortest;
    cout << "answer = " << answer << endl;

    return answer;
}





int main()
{
    string input_string = "hit";
    string input_target = "cog";
    vector<string> words{"hot","dot","dog","lot","log"};


    solution(input_string, input_target, words);

    return 0;
}