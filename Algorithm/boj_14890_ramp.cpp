#include <iostream>
#include <vector>

using namespace std;

class dir {
public:
	int y_dir;
	int x_dir;
};

vector< vector<int> > map;
vector< vector<int> > rampmap;
dir direction[2] = {1, 0, 0, 1}; // direction[0]:�Ʒ�����, direction[1] : �����ʹ���
int map_size;

bool isRampAvailable(int y, int x, int ramp_length, int caseud)
{
	bool avail = true;

	switch (caseud)
	{
	case 0: // �Ʒ��������� ramp ��ġ
	{
		if (rampmap[y + 1][x] == 1) { avail = false; break; }
		for (int i = 1; i < ramp_length; ++i)
		{
			if (y + i + 1 <= map_size - 1 && map[y + i + 1][x] == map[y + i][x]) continue;
			else { avail = false; break; }
		}

		if (avail == true) // ramp ��ġ
		{
			for (int i = 1; i <= ramp_length; ++i)
			{
				rampmap[y + i][x] = 1;
			}
		}
		break;
	}
	case 1: //���������� ��ġ
	{
		if (rampmap[y][x] == 1) { avail = false; break; }
		for (int i = 0; i < ramp_length - 1; ++i)
		{
			if (y - i - 1 >= 0 && map[y - i - 1][x] == map[y - i][x] &&
				rampmap[y-i][x] != 1 && rampmap[y - i - 1][x] != 1) continue; // ���� ramp�� ����� ��
			else { avail = false; break; }
		}
		if (avail == true) // ramp ��ġ
		{
			for (int i = 0; i < ramp_length; ++i)
			{
				rampmap[y - i][x] = 1;
			}
		}
		break;
	}
	case 2: // ������
	{
		if (rampmap[y][x + 1] == 1) { avail = false; break; }
		for (int i = 1; i < ramp_length; ++i)
		{
			if (x + i + 1 <= map_size - 1 && map[y][x + i + 1] == map[y][x + i]) continue;
			else { avail = false; break; }
		}

		if (avail == true) // ramp ��ġ
		{
			for (int i = 1; i <= ramp_length; ++i)
			{
				rampmap[y][x + i] = 1;
			}
		}
		break;
	}
	case 3:
	{
		if (rampmap[y][x] == 1) { avail = false; break; }

		for (int i = 0; i < ramp_length - 1; ++i)
		{
			if (x - i - 1 >= 0 && map[y][x - i - 1] == map[y][x - i] &&
				rampmap[y][x - i] != 1 && rampmap[y][x - i - 1] != 1) continue; // ���� ramp�� ����� ��
			else { avail = false; break; }
		}
		if (avail == true) // ramp ��ġ
		{
			for (int i = 0; i < ramp_length; ++i)
			{
				rampmap[y][x - i] = 1;
			}
		}
		break;
	}
	}
	
	
	return avail;
}

int main()
{
	int x = 0; int y = 0;
	int road_count = 0;
	int ramp_length;
	cin >> map_size;
	cin >> ramp_length;
	map.assign(map_size, vector<int>(map_size, 0));
	rampmap.assign(map_size, vector<int>(map_size, 0));

	for (int i = 0; i < map_size; ++i)
	{
		for (int j = 0; j < map_size; ++j)
		{
			int temp;
			cin >> temp;
			map[i][j] = temp;
			cout << map[i][j] << "\t";
		}
		cout << endl;
	}

	x = 0; y = 0;
	// �� ���� : ���Ϲ��⸸ �˻�
	while (1)
	{
		bool available = true;
		if (y + ramp_length < map_size && map[y][x] - 1 == map[y + 1][x]) // �Ʒ�ĭ�� 1 �� ����, ���� ĭ�� ramp_length �̻��� ���
		{
			// ramp_length��ŭ �������� ĭ�� ���̰� ������ �˻��ϰ� �����ϸ� �� ĭ��ŭ ramp ��ġ
			// �Ұ����ϸ� false ����
			if (isRampAvailable(y, x, ramp_length, 0)) // ���̰� ���� ���
			{
				// ramp_map�� �̹� 1���� �˻� �ʿ� ���� : �Ʒ��������� �˻��ϱ� ������
				// ramp ��ġ�� �ϸ��
				// ok : ���⼭�� �ƹ� �͵� ����(if�� �ۿ��� ����ĭ �̵�)

			}
			else { // ���� ��ġ �Ұ�
				available = false;
			}
		}
		else if (y + 1 - ramp_length >= 0 && map[y][x] + 1 == map[y + 1][x]) // �Ʒ�ĭ�� 1 �� ���� ���
		{ 
			
			if (isRampAvailable(y, x, ramp_length, 1)) // ramp�� ������ �ִٸ� ����, 1�� ������ ��ġ�� �ǹ�
			{
				// ok
			}
			else
			{
				available = false;
			}
		}
		else if (y + 1 < map_size && map[y][x] == map[y + 1][x])// ���� ��� (ramp lenth ���̺��� ���� ���� ���)
		{
			// ok (ramp ���� �ʿ� ����)
		}
		else // ���� ���̰� 2�̻��� ��� or ���� ĭ�� ������ ��� ��  : �Ұ���. -> �ٷ� ���� ���� �̵�.
		{
			available = false;
		}

		// ����ĭ���� �̵�
		x += direction[0].x_dir; // ###
		y += direction[0].y_dir;

		cout << endl << " checking .. (" << y << " , " << x << ")" << endl;

		// �� ���ǹ����� �ϳ��� false �߻��� ���� ĭ���� �̵� �Ǵ� y �ʰ�
		if (y >= map_size - 1 || available == false)  // ������ĭ�� �˻� ���ص� ��
		{
			if (available == true) ++road_count;
			// available == false�� ��� x�������� ����
			y = 0;
			x += direction[1].x_dir;
			y += direction[1].y_dir;

			if (x >= map_size) break;// x������ ���� �ʰ��� ��� ��.
		}
	}

	x = 0; y = 0;
	rampmap.assign(map_size, vector<int>(map_size, 0));
	
	while (1) // �¿� ����
	{
		bool available = true;
		if (x + ramp_length < map_size && map[y][x] - 1 == map[y][x + 1]) // ����ĭ�� 1 �� ����, ���� ĭ�� ramp_length �̻��� ���
		{
			if (isRampAvailable(y, x, ramp_length, 2)) // 2�� ����������.. 
			{
				// ok 
			}
			else { // ���� ��ġ �Ұ�
				available = false;
			}
		}
		else if (x + 1 - ramp_length >= 0 && map[y][x] + 1 == map[y][x + 1]) // ����ĭ�� 1 �� ���� ��� + ramp lenth�̻� ĭ�� ���� ���
		{
			if (isRampAvailable(y, x, ramp_length, 3)) // 3�� ���ʹ��� : ����ĭ ���� rampĭ �˻�����
			{
				// ok
			}
			else
			{
				available = false;
			}
		}
		else if (x + 1 < map_size && map[y][x] == map[y][x + 1])// ���� ��� (ramp lenth ���̺��� ���� ���� ���)
		{
			// ok (ramp ���� �ʿ� ����)
		}
		else // ���� ���̰� 2�̻��� ��� or ���� ĭ�� ������ ��� ��  : �Ұ���. -> �ٷ� ���� ���� �̵�.
		{
			available = false;
		}

		// ����ĭ���� �̵�
		x += direction[1].x_dir; // ###
		y += direction[1].y_dir;

		cout << endl << " checking .. (" << y << " , " << x << ")" << endl;

		// �� ���ǹ����� �ϳ��� false �߻��� ���� ĭ���� �̵� �Ǵ� y �ʰ�
		if (x >= map_size - 1 || available == false)  // ������ĭ�� �˻� ���ص� ��
		{
			if (available == true) ++road_count;
			// available == false�� ��� x�������� ����
			x = 0;
			x += direction[0].x_dir;
			y += direction[0].y_dir;

			if (y >= map_size) break;// x������ ���� �ʰ��� ��� ��.
		}
	}
	
	cout << road_count;


	return 0;
}