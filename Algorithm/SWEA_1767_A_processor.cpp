#include <iostream>
#include <vector>
using namespace std;

#define N 12 // N은 최소 7, 최대 12
#define LEFT 0
#define RIGHT 1
#define UP 2
#define DOWN 3

#define STATE_EMPTY 0
#define STATE_CORE_UNPROCESSED 1
#define STATE_CABLE 2
#define STATE_CORE_POWERED 3
#define STATE_CORE_CANNOT 4

int cell_state[N][N]; //  2차원 배열 for processor cell
int result_state[N][N];
int cell_wh;


int max_core = 0;
int min_wire_length = 9999;

// 최적화 전용변수
int core_num; // 최적화를 위해 변수 사용.
//int remaining_core;


bool direction_check(int h, int w, int dir)
{
	bool available = true;
	switch (dir)
	{
	case LEFT :
	{
		for (int i = 0; i < w; ++i)
		{
			if (cell_state[h][i] != STATE_EMPTY) //하나라도 0(빈cell)이아니면 연결 불가
				available = false;
		}
		break;
	}

	case RIGHT:
	{
		for (int i = cell_wh; i > w ; --i)
		{
			if (cell_state[h][i] != STATE_EMPTY)
				available = false;
		}
		break;
	}

	case UP:
	{
		for (int i = 0; i < h; ++i)
		{
			if (cell_state[i][w] != STATE_EMPTY)
				available = false;
		}
		break;
	}

	case DOWN:
	{
		for (int i = cell_wh; i > h; --i)
		{
			if (cell_state[i][w] != STATE_EMPTY)
				available = false;
		}
		break;
	}

	}// swtich end
		

	return available; // 연결가능여부 return
}


int direction_fill(int h, int w, int dir)
{
	int filled_length = 0;

	switch (dir)
	{

	case LEFT:
	{
		for (int i = 0; i < w; ++i) // w-1까지일걸로 생각했는데, w까지임.. 
		{
			if (cell_state[h][i] != STATE_EMPTY)
			{
				cout << "warning - state exception : not empty cell";
			}
			else {
				cell_state[h][i] = STATE_CABLE; // 전원선(Cable) 연결 상태로 변경
				++filled_length;
			}
		}
		break;
	}

	case RIGHT:
	{
		for (int i = cell_wh-1; i > w; --i)
		{
			cell_state[h][i] = STATE_CABLE;
			++filled_length;
		}
		break;
	}


	case UP:
	{
		for (int i = 0; i < h; ++i)
		{
			cell_state[i][w] = STATE_CABLE;
			++filled_length;
		}
		break;
	}

	case DOWN:
	{
		for (int i = cell_wh-1; i > h; --i)
		{
			cell_state[i][w] = STATE_CABLE;
			++filled_length;
		}
		break;
	}

	} // swtich end

	cell_state[h][w] = STATE_CORE_POWERED; // 전원 연결 상태
	return filled_length;
}


int direction_recover(int h, int w, int dir) // fill의 역과정
{
	switch (dir)
	{

	case LEFT:
	{
		for (int i = 0; i < w; ++i)
		{
			cell_state[h][i] = STATE_EMPTY; // 빈 cell 상태로 변경
		}
		break;
	}

	case RIGHT:
	{
		for (int i = cell_wh-1; i > w; --i)
		{
			cell_state[h][i] = STATE_EMPTY;
		}
		break;
	}


	case UP:
	{
		for (int i = 0; i < h; ++i)
		{
			cell_state[i][w] = STATE_EMPTY;
		}
		break;
	}

	case DOWN:
	{
		for (int i = cell_wh-1; i > h; --i)
		{
			cell_state[i][w] = STATE_EMPTY;
		}
		break;
	}

	} // swtich end

	cell_state[h][w] = STATE_CORE_UNPROCESSED; // 미처리 상태로 변경
	return 1;
}


int FindMaxCore(int connected_core, int wire_length_sum, int remaining_core){
	int h, w;
	bool find_unprocessed = false; // 처리되지 않은 코어 존재여부.
	bool left_cannot = true;
	bool right_cannot = true;
	bool up_cannot = true;
	bool down_cannot = true;

	//===================== Check cell state ... ===========================
	for (int i = 0; i < cell_wh; ++i) // 다음 처리되지 않으 코어 찾기
	{
		for (int j = 0; j < cell_wh; ++j)
		{
			if (cell_state[i][j] == STATE_CORE_UNPROCESSED)
			{
				h = i;
				w = j;
				find_unprocessed = true;
				break;
			}
		}
		if (find_unprocessed) break;
	}

	// ================== Base case =========================
	if (!find_unprocessed) // 모든 core가 처리된 상태 : base case -> "탐색 대상 값 case별 최신화"
	{
		if (max_core < connected_core) // 지금까지 찾은 최대 코어보다 많이 연결한 경우
		{
			max_core = connected_core; // max core수 최신화
			min_wire_length = wire_length_sum; // min wire도 현재값으로 최신화
			for (int q = 0; q < cell_wh; ++q)
				for (int a = 0; a < cell_wh; ++a)
					result_state[q][a] = cell_state[q][a];
		}
		else if (max_core == connected_core) // 기존 최대 연결 코어 수와 같으면, 전선길이 비교
		{
			if (min_wire_length > wire_length_sum)
			{
				min_wire_length = wire_length_sum;
				for (int q = 0; q < cell_wh; ++q)
					for (int a = 0; a < cell_wh; ++a)
						result_state[q][a] = cell_state[q][a];
			}
		}
		else // if max_core > connected_core 
		{
			// nop
		}
	}

	// ================== Call next Recursive.. =======================
	else // 각 방향 연결 가능여부 판단 및 연결 후 다음 호출.
	{
		int new_length = 0;
		if (connected_core + remaining_core < max_core)
			return -1; // 지금까지 연결된 코어수 + 남은 코어수가 현재까지 최대 코어수보다 작으면
		else 
		{


			if (direction_check(h, w, LEFT)) // 왼쪽 wire 가능 check
			{
				left_cannot = false;
				new_length = direction_fill(h, w, LEFT); // 왼쪽에서 연결
				wire_length_sum += new_length;
				FindMaxCore(++connected_core, wire_length_sum, --remaining_core); // 연결된 코어개수 증가시켜 호출
				direction_recover(h, w, LEFT);
				--connected_core;
				++remaining_core;
				wire_length_sum -= new_length;
				// 다른 방향 호출 전 왼쪽 연결 상태, connected_core, wire_length_sum 모두 원상복구
			}
			if (direction_check(h, w, RIGHT))
			{
				right_cannot = false;
				new_length = direction_fill(h, w, RIGHT); // 왼쪽에서 연결
				wire_length_sum += new_length;
				FindMaxCore(++connected_core, wire_length_sum, --remaining_core); // 연결된 코어개수 증가시켜 호출
				direction_recover(h, w, RIGHT);
				--connected_core;
				++remaining_core;
				wire_length_sum -= new_length;
			}

			if (direction_check(h, w, UP))
			{
				up_cannot = false;
				new_length = direction_fill(h, w, UP); // 왼쪽에서 연결
				wire_length_sum += new_length;
				FindMaxCore(++connected_core, wire_length_sum, --remaining_core); // 연결된 코어개수 증가시켜 호출
				direction_recover(h, w, UP);
				--connected_core;
				++remaining_core;
				wire_length_sum -= new_length;
			}

			if (direction_check(h, w, DOWN))
			{
				down_cannot = false;
				new_length = direction_fill(h, w, DOWN); // 왼쪽에서 연결
				wire_length_sum += new_length;
				FindMaxCore(++connected_core, wire_length_sum, --remaining_core); // 연결된 코어개수 증가시켜 호출
				direction_recover(h, w, DOWN);
				--connected_core;
				++remaining_core;
				wire_length_sum -= new_length;
			}

			// 연결하지 않고, pass하는 경우
			
			cell_state[h][w] = STATE_CORE_CANNOT; // 해당 코어상태만 변경 후 다시 호출
			FindMaxCore(connected_core, wire_length_sum, --remaining_core); // 전 처리, 후처리 필요없음. XX!!
			++remaining_core;
			cell_state[h][w] = STATE_CORE_UNPROCESSED; // 다시 위 탐색이 끝나면 다시 돌려놓아야함..
			
			/*
			if (left_cannot && right_cannot && up_cannot && down_cannot) // 모든 방향에서 연결불가능한경우
			{
				cell_state[h][w] = STATE_CORE_CANNOT; // 해당 코어상태만 변경 후 다시 호출
				FindMaxCore(connected_core, wire_length_sum, --remaining_core); // 전 처리, 후처리 필요없음. xxx!!
				++remaining_core;
				cell_state[h][w] = STATE_CORE_UNPROCESSED; // 다시 위 탐색이 끝나면 다시 돌려놓아야함..
			}
			*/
		}
	}
	

	return 0;
}


int main() {
	int case_n; // test case 번호
	int connected_core = 0;



	cin >> case_n;
	for (int i = 0; i < case_n; ++i) // for test case
	{
		core_num = 0;
		cin >> cell_wh;  // 7 <= cell_wh <= 12
		for (int h = 0; h < cell_wh; ++h)  // for processor cell input
		{
			for (int w = 0; w < cell_wh; ++w)
			{
				cin >> cell_state[h][w];
				if (cell_state[h][w] == 1)
				{ // 코어이면 그것이 가장자리인지 체크
					++core_num;
					if ((w == 0 || w == cell_wh || h == 0 || h == cell_wh))
					{
						cell_state[h][w] = STATE_CORE_POWERED;
						++connected_core;
						// 가장자리이면 전원연결 상태로 선 처리.
					}
				}
			}
		}
		
		FindMaxCore(connected_core, 0, core_num - connected_core);
		
	//	cout << "#" << i+1 << " core : " << max_core << " length : " << min_wire_length << endl;
		cout << "#" << i + 1 << " " << min_wire_length << endl;

		// max_core, min_wire_length, cell_state배열 초기화
		max_core = 0; min_wire_length = 999; connected_core = 0;
		for (int j = 0; j < N; ++j)
			for (int k = 0; k < N; ++k)
				cell_state[j][k] = 0;
	}

	return 0;
}
