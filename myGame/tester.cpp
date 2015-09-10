#include <bits/stdc++.h>

using namespace std;

int n=5;
int boardsize;
vector< vector<char> > board(5 , vector<char>(5,'-'));


int getscore(string s){
	int ssize = s.length();
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

int diff_chaos(int x, int y, char color){
	int difference = 0;
	string row, col;

	int i=0;
	while(i<n)
	{
		row += board[x][i];
		col += board[i][y];
		i++;
	}

	difference -= getscore(row);
	difference -= getscore(col);
	
	
	row.resize(0);
	col.resize(0);
	
	board[x][y] = color;

	i=0;
	while(i<n)
	{
		row += board[x][i];
		col += board[i][y];
		i++;
	}
	difference += getscore(row);
	difference += getscore(col);

	board[x][y] = '-';
	return difference;
	return 0;
}

int main()
{
	boardsize = 5;
	// Init the board
	for(int i=0;i<5;i++){
		for(int j=0;j<5;j++)
			board[i][j] = '-';
	}
	/*board[2][1] = board[4][1] = 'B';
	board[1][3] = board[2][3] = board[3][3] = board[4][3] = 'B';
	board[3][3] = 'R';
	*/
	cout<<diff_chaos(4,3,'R')<<"\n";
	

	return 0;
}