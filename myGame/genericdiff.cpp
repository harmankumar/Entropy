#include <iostream>
#include <vector>
#include <string>
#include <limits>

using namespace std;

/*
	--------------------------> Y
	|
	|
	|
	|
	|
	|
	|
	x
*/

int boardsize;
vector< vector<char> > board(5 , vector<char>(5,'W'));

int getscore(string s)
{
	int ssize = s.size();
	int score = 0;

	for(int i=0; i<ssize; i++)
	{
		int j=1;
		while((i-j >= 0) && (j+i < ssize))
		{
			if((s[i-j] == s[i+j]) && (s[i-j] != 'W'))
				score += 2*j+1;
			else
				break;
			j++;
		}
	}
	for(int i=0; i<ssize-1; i++)
	{
		
		if((s[i] == s[i+1]) && (s[i] != 'W'))
		{
			score += 2;
			int j=1;
			while(i-j >= 0 && i+j+1 < ssize)
			{
				if((s[i-j] == s[i+j+1]) && (s[i-j] != 'W'))
					score += 2*j+2;
				else 
					break;
				j++;
			}

		}
	}
	return score;
}

int diff(int xini, int yini, int xfin, int yfin, char color)
{
	int difference = 0;
	string s;
	if( (yfin == yini) && (xfin==xini))	// Trivial.
		return difference;

	if( (yfin != yini) && (xfin != xini))	// Not a Possible move
		return numeric_limits<int>::max();

	if(yfin == yini)	// Column Movement
	{
		string rowi, rowf, col;

		int i=0;
		while(i<boardsize)
		{
			rowi += board[xini][i];
			rowf += board[xfin][i];
			col += board[i][yini];
			i++;
		}
		difference -= getscore(rowf);
		difference -= getscore(rowi);
		difference -= getscore(col);

		rowi.resize(0);
		rowf.resize(0); 
		col.resize(0);
		
		board[xini][yini] = 'W';
		board[xfin][yfin] = color;
		i=0;
		while(i<boardsize)
		{
			rowi += board[xini][i];
			rowf += board[xfin][i];
			col += board[i][yini];
			i++;
		}
		difference += getscore(rowf);
		difference += getscore(rowi);
		difference += getscore(col);

		board[xfin][yfin] = 'W';
		board[xini][yini] = color;
	}

	if(xfin == xini)	// Row Movement
	{
		string coli, colf, row;

		int i=0;
		while(i<boardsize)
		{
			coli += board[i][yini];
			colf += board[i][yfin];
			row += board[xini][i];
			i++;
		}
		difference -= getscore(colf);
		difference -= getscore(coli);
		difference -= getscore(row);

		coli.resize(0);
		colf.resize(0); 
		row.resize(0);
		
		board[xini][yini] = 'W';
		board[xfin][yfin] = color;
		i=0;
		while(i<boardsize)
		{
			coli += board[i][yini];
			colf += board[i][yfin];
			row += board[xini][i];
			i++;		
		}
		difference += getscore(colf);
		difference += getscore(coli);
		difference += getscore(row);

		board[xfin][yfin] = 'W';
		board[xini][yini] = color;
	}

	return difference;
}


int main()
{
	boardsize = 5;
	// Init the board
	for(int i=0;i<5;i++){
		for(int j=0;j<5;j++)
			board[i][j] = 'W';
	}
	board[1][2] = board[1][4] = 'B';
	board[3][1] = board[3][2] = board[3][3] = board[3][4] = 'B';
	cout<<diff(3,3,1,3,'B');

	return 0;
}