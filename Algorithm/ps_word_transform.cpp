#include <iostream>
#include <vector>
#include <string>
#include <queue>

using namespace std;

vector< vector<int> > Grp_int;
queue<int> Queue;


int Create_grpah(string begin, string target, vector<string> words)
{
    // �̹� ������ �׷��� ��Ģ : ���� �ѱ��ھ� ���̳��� string������ ����ȴ�.
    string temp;
    int NumOfVertex = 1 + words.size(); // begin ����(1��)�� words�� ����
    
    int LengthOfWords = begin.size(); // �� �ܾ���� ����
    int Target_index = -1;
    
    // ���� words ����, begin�� �׷����� ��Ÿ���� ����- vertex ��ȣ�� �ο��Ѵ�.
    // ���� ���� ��Ģ��
    // words�� ���ҵ��� �� �ڽ��� index��ȣ�� vertex ��ȣ�� ������
    // begin�� words ������ + 1�� index�� ������ �Ѵ�.
    vector<string> Vertex;
    for (int i = 0; i < NumOfVertex - 1; ++i)
    {
        Vertex.push_back(words[i]);
        if (words[i] == target)
        {
            Target_index = i; // target�� ��� vertex���� ã�Ƽ� �������� ����
        }
    }
    Vertex.push_back(begin);
    // <== vertex ��ȣ�ο� �Ϸ�

    // Vector �������迭 assign �� ����!!!
    Grp_int.assign(NumOfVertex, vector<int>(NumOfVertex, 0)); // 2�������� 0���� �ʱ�ȭ!!!

    for (int i = 0; i < NumOfVertex; ++i)
    {
        for (int j = 0; j < NumOfVertex; ++j)
        {
            int same_char_count = 0;
            for (int ch = 0; ch < LengthOfWords; ++ch) // �� for���� string���� ���ڸ� �ϳ��ϳ� üũ�ϱ�����
            {
                if (Vertex[i][ch] == Vertex[j][ch]) // �ϳ��� �ٸ� �� ����
                {
                    same_char_count++;
                    if (same_char_count >= LengthOfWords - 1) // �ѱ��ڸ� �ٸ���
                    {
                        Grp_int[i][j] = 1; // ����
                        break;
                    }
                }
            }
          
        }
    }
   
    

    // ������ �׷��� ���� ��� �׽�Ʈ ���
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
    // Target�� ��� �˻��ϴ°�?
    // Length�� ��� update�ϴ°�?(���� ��ġ ���)

    // �� ���������� �ܼ��� ��� �̵��ߴ����� �˸� �Ǳ⶧����(����� ����) ���� ���ͽ�Ʈ��x, BFS�� ����.
    int Length = 0; // depth�� ����
    int depth_count = 0;
    int bfs_count = 0;
    int adj_vertex_count = 0;
    

    int curr, next;
    vector<int> Is_visited_Before(Grp_int.size(), 0); // �湮���� : 0���� �ʱ�ȭ
    
    Queue.push(begin_index);

    while (Queue.empty() == false) // Queue�� �ƹ��͵� ���������� �ݺ� 
    {
        
        curr = Queue.front();
        Is_visited_Before[curr] = 1; // �湮��
        
        for (int i = 0; i < Grp_int.size(); ++i) // curr���� �� �� �ִ� vertex ã�� for��
        {
            if (Grp_int[curr][i] == 1 && Is_visited_Before[i] == 0) // ���粨�� vertex�� ����Ǿ��ְ�, ������ �湮���� �ʾҴٸ�
            {
                if (i == target_index) // ���ᰡ���ϴٸ�, ���� Target index���� �˻�
                {// �´ٸ� ��
                    return Length + 1; // curr�� �����̹Ƿ� + 1
                }
                
                adj_vertex_count++; // ����dep������ŭ(bfs_count) ��ȸ�Ҷ�, �� ���� depth�� ������ ����ī��Ʈ
                Queue.push(i); // Target�� �ƴϸ�, ť�� ����
            }
        }
        if (bfs_count == 0) { // 
            bfs_count = adj_vertex_count; // ó������ ���ͼ�, ���� bfs ������� depth�� ������ bfs_count�� ����
            adj_vertex_count = 0; // ���� depth�� ����, �� ���� depth�� ������ ī��Ʈ�ϱ� ���� ����
            Length++;
        }
        
        Queue.pop();
        bfs_count--;
    }

    // ���� �߰� ������� return�� ���ϸ� ��ã�� �����
    return 0; // 0 ��ȯ�ϸ� target�� ��ã�� ���
}


int solution(string begin, string target, vector<string> words) { // main
    int answer = 0;
    int Target_index;
    int Shortest;

    // create graph
    Target_index = Create_grpah(begin, target, words);

    // find shortest path (from begin to target)
    int Begin_index = words.size(); // 7��°������ index�δ� 6��
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