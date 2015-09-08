#include <bits/stdc++.h>

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
vector< vector<char> > board(5 , vector<char>(5,''));

int diff(int xini, int yini, int xfin, int yfin, char color)
{
	int difference = 0;
	
	if( (yfin == yini) && (xfin==xini))	// Trivial.
		return difference;

	if(yfin == yini)	// Movement in a column.
	{
		int i = yfin;
		int j = 1;

		// Value Reduced.
		// Odd Pal.
		while((i-j >= 0) && (j+i < boardsize))
		{
			if((board[xini][i-j] == board[xini][i+j]) && (board[xini][i-j] != ''))
				difference -= 2*j+1;
			else
				break;
			j++;
		}
		// Even Pal.
		if( !(yini == boardsize-1))
		{			
			if(board[xini][i] == board[xini][i+1])
			{
				difference += 2;
				j=1;
				while(i-j >= 0 && i+j+1 < boardsize)
				{
					if((board[xini][i-j] == board[xini][i+j+1]) && (board[xini][i-j] != ''))
						difference -= 2*j+2;
					else 
						break;
					j++;
				}

			}
		}
		if( !(yfin == 0))
		{			
			i=yfin;
			if(board[xini][i] == board[xini][i-1])
			{
				difference -= 2;
				j=1;
				while(i-j-1 >= 0 && i+j < boardsize)
				{
					if((board[xini][i-j-1] == board[xini][i+j]) && (board[xini][i-j-1] != ''))
						difference -= 2*j+2;
					else 
						break;
					j++;
				}

			}
		}
		// Value Added.	
		// Odd Pal.

		board[xfin][yfin] = color;
		i = yfin;
		j = 1;

		while((i-j >= 0) && (j+i < boardsize))
		{
			if((board[xfin][i-j] == board[xfin][i+j]) && (board[xfin][i-j] != ''))
				difference += 2*j+1;
			else
				break;
			j++;
		}

		// Even Pal.
		if( !(yfin == boardsize-1))
		{			
			if(board[xfin][i] == board[xfin][i+1])
			{
				difference += 2;
				j=1;
				while(i-j >= 0 && i+j+1 < boardsize)
				{
					if((board[xfin][i-j] == board[xfin][i+j+1]) && (board[xfin][i-j] != ''))
						difference += 2*j+2;
					else 
						break;
					j++;
				}

			}
		}

		if( !(yfin == 0))
		{			
			i=yfin;
			if(board[xfin][i] == board[xfin][i-1])
			{
				difference += 2;
				j=1;
				while(i-j-1 >= 0 && i+j < boardsize)
				{
					if((board[xfin][i-j-1] == board[xfin][i+j]) && (board[xfin][i-j-1] != ''))
						difference += 2*j+2;
					else 
						break;
					j++;
				}

			}
		}

		// The one diff in the other direction.
		// This part is not Generic Enough for the 7x7 board.
		int sumup = 0;
		int sumdown = 0;

		int iterup = xini+1;
		int iterdown = boardsize - xfin + 1;
		
		i=2;
		while(1)
		{
			if(iterup < i)
				break;
			switch(i)
			{
				case 2 :
					if(board[xini][yini] == board[xini - 1][yini])
						sumup += 2;
					break;

				case 3 :
					if(board[xini][yini] == board[xini - 2][yini])
						sumup += 3;
					break;

				case 4 :
					if( (board[xini][yini] == board[xini - 3][yini]) && (board[xini - 1][yini] == board[xini - 2][yini]) )
						sumup += 3;
					break;

				default :
					break;

			}

			i++;
		}
	
		i=2;
		while(1)
		{
			if(iterdown < i)
				break;
			switch(i)
			{
				case 2 :
					if(board[xini][yini] == board[xini + 1][yini])
						sumdown += 2;
					break;

				case 3 :
					if(board[xini][yini] == board[xini + 2][yini])
						sumdown += 3;
					break;

				case 4 :
					if(board[xini][yini] == board[xini + 3][yini]) && (board[xini + 1][yini] == board[xini + 2][yini]) )
						sumdown += 4;
					break;

				default :
					break;

			}
			i++;
		}

		if(xfin > xini)
		{
			difference += sumdown;
			difference -= sumup;
		}

		if(xfin < xini)
		{
			difference -= sumdown;
			difference += sumup;
		}

		board[xfin][yfin] = '';

	}



int main()
{
	boardsize = 5;
	// Init the board

	cout<<diff( , , , , B);

	return 0;
}


/*
			int j=1;
			//  Even
			while(yini-j >= 0 && yini+j+1 < boardsize)
			{
				if((board[xfin][yini-j] == board[xfin][yini+j+1]) && (board[xfin][yini-j] != ''))
					difference += 2*j+2;
				else 
					break;
				j++;
			}
			// Odd
			while((yini-j >= 0) && (j+yini < boardsize))
			{
				if((board[xfin][yini-j] == board[xfin][yini+j]) && (board[xfin][yini-j] != ''))
					difference += 2*j+1;
				else
					break;
				j++;
			}

*/