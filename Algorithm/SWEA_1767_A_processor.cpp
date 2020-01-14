#include <iostream>
#include <vector>
using namespace std;

#define N 12 // N�� �ּ� 7, �ִ� 12
#define LEFT 0
#define RIGHT 1
#define UP 2
#define DOWN 3

#define STATE_EMPTY 0
#define STATE_CORE_UNPROCESSED 1
#define STATE_CABLE 2
#define STATE_CORE_POWERED 3
#define STATE_CORE_CANNOT 4

int cell_state[N][N]; //  2���� �迭 for processor cell
int result_state[N][N];
int cell_wh;


int max_core = 0;
int min_wire_length = 9999;

// ����ȭ ���뺯��
int core_num; // ����ȭ�� ���� ���� ���.
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
			if (cell_state[h][i] != STATE_EMPTY) //�ϳ��� 0(��cell)�̾ƴϸ� ���� �Ұ�
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
		

	return available; // ���ᰡ�ɿ��� return
}


int direction_fill(int h, int w, int dir)
{
	int filled_length = 0;

	switch (dir)
	{

	case LEFT:
	{
		for (int i = 0; i < w; ++i) // w-1�����ϰɷ� �����ߴµ�, w������.. 
		{
			if (cell_state[h][i] != STATE_EMPTY)
			{
				cout << "warning - state exception : not empty cell";
			}
			else {
				cell_state[h][i] = STATE_CABLE; // ������(Cable) ���� ���·� ����
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

	cell_state[h][w] = STATE_CORE_POWERED; // ���� ���� ����
	return filled_length;
}


int direction_recover(int h, int w, int dir) // fill�� ������
{
	switch (dir)
	{

	case LEFT:
	{
		for (int i = 0; i < w; ++i)
		{
			cell_state[h][i] = STATE_EMPTY; // �� cell ���·� ����
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

	cell_state[h][w] = STATE_CORE_UNPROCESSED; // ��ó�� ���·� ����
	return 1;
}


int FindMaxCore(int connected_core, int wire_length_sum, int remaining_core){
	int h, w;
	bool find_unprocessed = false; // ó������ ���� �ھ� ���翩��.
	bool left_cannot = true;
	bool right_cannot = true;
	bool up_cannot = true;
	bool down_cannot = true;

	//===================== Check cell state ... ===========================
	for (int i = 0; i < cell_wh; ++i) // ���� ó������ ���� �ھ� ã��
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
	if (!find_unprocessed) // ��� core�� ó���� ���� : base case -> "Ž�� ��� �� case�� �ֽ�ȭ"
	{
		if (max_core < connected_core) // ���ݱ��� ã�� �ִ� �ھ�� ���� ������ ���
		{
			max_core = connected_core; // max core�� �ֽ�ȭ
			min_wire_length = wire_length_sum; // min wire�� ���簪���� �ֽ�ȭ
			for (int q = 0; q < cell_wh; ++q)
				for (int a = 0; a < cell_wh; ++a)
					result_state[q][a] = cell_state[q][a];
		}
		else if (max_core == connected_core) // ���� �ִ� ���� �ھ� ���� ������, �������� ��
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
	else // �� ���� ���� ���ɿ��� �Ǵ� �� ���� �� ���� ȣ��.
	{
		int new_length = 0;
		if (connected_core + remaining_core < max_core)
			return -1; // ���ݱ��� ����� �ھ�� + ���� �ھ���� ������� �ִ� �ھ������ ������
		else 
		{


			if (direction_check(h, w, LEFT)) // ���� wire ���� check
			{
				left_cannot = false;
				new_length = direction_fill(h, w, LEFT); // ���ʿ��� ����
				wire_length_sum += new_length;
				FindMaxCore(++connected_core, wire_length_sum, --remaining_core); // ����� �ھ�� �������� ȣ��
				direction_recover(h, w, LEFT);
				--connected_core;
				++remaining_core;
				wire_length_sum -= new_length;
				// �ٸ� ���� ȣ�� �� ���� ���� ����, connected_core, wire_length_sum ��� ���󺹱�
			}
			if (direction_check(h, w, RIGHT))
			{
				right_cannot = false;
				new_length = direction_fill(h, w, RIGHT); // ���ʿ��� ����
				wire_length_sum += new_length;
				FindMaxCore(++connected_core, wire_length_sum, --remaining_core); // ����� �ھ�� �������� ȣ��
				direction_recover(h, w, RIGHT);
				--connected_core;
				++remaining_core;
				wire_length_sum -= new_length;
			}

			if (direction_check(h, w, UP))
			{
				up_cannot = false;
				new_length = direction_fill(h, w, UP); // ���ʿ��� ����
				wire_length_sum += new_length;
				FindMaxCore(++connected_core, wire_length_sum, --remaining_core); // ����� �ھ�� �������� ȣ��
				direction_recover(h, w, UP);
				--connected_core;
				++remaining_core;
				wire_length_sum -= new_length;
			}

			if (direction_check(h, w, DOWN))
			{
				down_cannot = false;
				new_length = direction_fill(h, w, DOWN); // ���ʿ��� ����
				wire_length_sum += new_length;
				FindMaxCore(++connected_core, wire_length_sum, --remaining_core); // ����� �ھ�� �������� ȣ��
				direction_recover(h, w, DOWN);
				--connected_core;
				++remaining_core;
				wire_length_sum -= new_length;
			}

			// �������� �ʰ�, pass�ϴ� ���
			
			cell_state[h][w] = STATE_CORE_CANNOT; // �ش� �ھ���¸� ���� �� �ٽ� ȣ��
			FindMaxCore(connected_core, wire_length_sum, --remaining_core); // �� ó��, ��ó�� �ʿ����. XX!!
			++remaining_core;
			cell_state[h][w] = STATE_CORE_UNPROCESSED; // �ٽ� �� Ž���� ������ �ٽ� �������ƾ���..
			
			/*
			if (left_cannot && right_cannot && up_cannot && down_cannot) // ��� ���⿡�� ����Ұ����Ѱ��
			{
				cell_state[h][w] = STATE_CORE_CANNOT; // �ش� �ھ���¸� ���� �� �ٽ� ȣ��
				FindMaxCore(connected_core, wire_length_sum, --remaining_core); // �� ó��, ��ó�� �ʿ����. xxx!!
				++remaining_core;
				cell_state[h][w] = STATE_CORE_UNPROCESSED; // �ٽ� �� Ž���� ������ �ٽ� �������ƾ���..
			}
			*/
		}
	}
	

	return 0;
}


int main() {
	int case_n; // test case ��ȣ
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
				{ // �ھ��̸� �װ��� �����ڸ����� üũ
					++core_num;
					if ((w == 0 || w == cell_wh || h == 0 || h == cell_wh))
					{
						cell_state[h][w] = STATE_CORE_POWERED;
						++connected_core;
						// �����ڸ��̸� �������� ���·� �� ó��.
					}
				}
			}
		}
		
		FindMaxCore(connected_core, 0, core_num - connected_core);
		
	//	cout << "#" << i+1 << " core : " << max_core << " length : " << min_wire_length << endl;
		cout << "#" << i + 1 << " " << min_wire_length << endl;

		// max_core, min_wire_length, cell_state�迭 �ʱ�ȭ
		max_core = 0; min_wire_length = 999; connected_core = 0;
		for (int j = 0; j < N; ++j)
			for (int k = 0; k < N; ++k)
				cell_state[j][k] = 0;
	}

	return 0;
}
