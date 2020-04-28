#include <iostream>
#include <vector>
#include <queue>

using namespace std;

vector <vector <int> > map;
vector <vector <int> > tempmap;
int height, width;

class pos {
public:
	int x;
	int y;

	pos(int iny, int inx) { // !!!
		x = inx;
		y = iny;
	}
};

int nextstepY[4] = {0, 0, -1, 1}; // !!!
int nextstepX[4] = {1, -1, 0, 0,};


int Spread()
{
	int zeros = 0;
	queue<pos> qu; // !!!

	
	for (int h = 0; h < height; ++h)
	{
		for (int w = 0; w < width; ++w)
		{
			if (map[h][w] == 2) {
				qu.push(pos(h, w));
			}
			tempmap[h][w] = map[h][w];
		}
	}

	
	while (!qu.empty())
	{
		pos thispos = qu.front();
		qu.pop();
		

		
		for (int d = 0; d < 4; ++d)
		{
			int nexty = thispos.y + nextstepY[d]; 
			int nextx = thispos.x + nextstepX[d];
			
			if (nexty >= 0 && nexty < height && nextx >= 0 && nextx < width && map[nexty][nextx] == 0)
			{
				map[nexty][nextx] = 2;
				qu.push(pos(nexty, nextx)); 
			}
		}
	}

	for (int h = 0; h < height; ++h)
	{
		for (int w = 0; w < width; ++w)
		{
			if (map[h][w] == 0) {
				++zeros;
			}
			map[h][w] = tempmap[h][w]; 
		}
	}

	

	return zeros;
}



int BuildWall(int NumberOfWall)
{
	
	if (NumberOfWall == 3) 
	{
		
		int zero = Spread();
		return zero;
	}
	else
	{
		int max = -1;
		int tempmax = 0;
		
		for (int h = 0; h < height; ++h)
		{
			for (int w = 0; w < width; ++w)
			{
				
				if (map[h][w] == 0) 
				{
					map[h][w] = 1;
					tempmax = BuildWall(++NumberOfWall);

					
					if (tempmax > max) 
					{
						max = tempmax;
						for (int he = 0; he < height; ++he)
						{
							for (int wi = 0; wi < width; ++wi)
							{
								maxmap[he][wi] = map[he][wi];
							}
						}
					}
					
					map[h][w] = 0;
					--NumberOfWall;
				}
			}
		}

		return max;
	}
}


int main()
{

	cin >> height >> width;

	map.assign(height, vector<int>(width, 0));
	tempmap.assign(height, vector<int>(width, 0));


	for (int h = 0; h < height; ++h)
	{

		for (int w = 0; w < width; ++w)
		{
			cin >> map[h][w];
		}
	}


	int max = BuildWall(0);

	cout << max ;
	


	return 0;
}