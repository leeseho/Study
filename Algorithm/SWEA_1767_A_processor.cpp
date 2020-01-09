#include <iostream>
#include <vector>
using namespace std;
#define N 12

int cell[N][N]; //  2차원 배열 for processor cell


int main() {
	int case_n; // test case 번호
	int cell_wh;


	cin >> case_n;
	for (int i = 0; i < case_n; ++i) // for test case
	{
		cin >> cell_wh;  // 7 <= cell_wh <= 12

		for (int h = 0; h < cell_wh; ++h)  // for processor core input
		{
			for (int w = 0; w < cell_wh; ++w)
			{
				cin >> cell[h][w];
			}
		}
		
		


	}

	return 0;
}
