#include <bits/stdc++.h>

using namespace std;

int boardsize;
vector< vector<char> > board(5 , vector<char>(5,'-'));

int getscore(string s)
{
	int ssize = s.size();
	int score = 0;

	for(int i=0; i<ssize; i++)
	{
		int j=1;
		while((i-j >= 0) && (j+i < ssize))
		{
			if((s[i-j] == s[i+j]) && (s[i-j] != '-' && (s[i] != '-')))
				score += 2*j+1;
			else
				break;
			j++;
		}
	}
	for(int i=0; i<ssize-1; i++)
	{
		
		if((s[i] == s[i+1]) && (s[i] != '-'))
		{
			score += 2;
			int j=1;
			while(i-j >= 0 && i+j+1 < ssize)
			{
				if((s[i-j] == s[i+j+1]) && (s[i-j] != '-'))
					score += 2*j+2;
				else 
					break;
				j++;
			}
		}
	}
	return score;
}
int tentative_palindrome_count()
{
	int tentative_delta = 0;

	for(int i=0; i<boardsize; i++)
	{
		for(int j=0; j<boardsize; j++)
		{
			if(board[i][j] == '-')	// Empty Location Detected.
			{
				for(int l=0; l<5; l++)	// Iterating through the colors and getting the score.
				{
					int addscore_col = 0;

					string row, col;
					while(k<boardsize)
					{
						row += board[i][k];
						col += board[k][j];
						k++;
					}

					addscore_col -= getscore(row);
					addscore_col -= getscore(col)

					row.resize(0);
					col.resize(0);
					char color = 'A'+l;

					while(k<boardsize)
					{
						row += board[i][k];
						col += board[k][j];
						k++;
					}

					addscore_col += getscore(row);
					addscore_col += getscore(col)

					tentative_delta += addscore_col;	// Multiply with the probability of the color appearing.
				}
				board[i][j] = '-'	// Restoring the board.
			}
		}
	}
}
// For the relative positions of similar tiles.
int scattering()
{
	vector< vector<int> > mapping;
	mapping.resize(5);
	int scat_coeff = 0;
	// Getting the loations of the tiles, this could be improved by maintaining this map.
	for(int i=0; i<boardsize; i++)
		for(int j=0; j<boardsize; j++)
			if(board[i][j] != '-')
				(mapping[board[i][j]-65]).push_back(boardsize*i + j);

		
	for(int i=0; i<boardsize; i++)
	{
		for(int j=0; j<(mapping[i]).size(); j++)
		{
			for(int k=j+1; k<(mapping[i]).size(); k++)
			{
				scat_coeff += (abs(mapping[i][j]/boardsize - mapping[i][k]/boardsize) );
				scat_coeff += (abs(mapping[i][j]%boardsize - mapping[i][k]%boardsize) );
			}
		}
	}
	cout<< scat_coeff;
	return scat_coeff;
}


float calc_util()
{
	// Assuming the colors are A, B, C, D, E
	//scattering();	// Sum of all pairs of tiles of the same colour.
	tentative_palindrome_count();
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
		cout<<rowi<<" "<<rowf<<" "<<col<<"\n";
		difference -= getscore(rowf);
		difference -= getscore(rowi);
		difference -= getscore(col);
		
		
		rowi.resize(0);
		rowf.resize(0); 
		col.resize(0);
		
		board[xini][yini] = '-';
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

		board[xfin][yfin] = '-';
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
		
		board[xini][yini] = '-';
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

		board[xfin][yfin] = '-';
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
			board[i][j] = '-';
	}
	board[0][0] = board[4][0] = board[4][4] = board[0][4] = board[2][4] ='A';

	board[4][1] = board[0][1] = 'B';
	// board[1][3] = board[2][3] = board[3][3] = board[4][3] = 'B';
	// board[3][3] = 'A';
	// cout<<diff(3,3,3,1,'R')<<"\n";
	scattering();

	return 0;
}