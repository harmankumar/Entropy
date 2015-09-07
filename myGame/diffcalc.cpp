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

	if(yfin == yini)
	{
		// Value Added.
		board[xfin][yfin] = color; 
		
		int i = yfin;
		int j = 1;
		
		// Odd Pal.
		while((i-j >= 0) && (j+i < boardsize))
		{
			if((board[xfin][i-j] == board[xfin][i+j]) && (board[xfin][i-j] != ''))
				difference += 2*j+1;
			else
				break;
			j++;
		}

		// Even Pal.
		if( !(xfin == boardsize-1))
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

		if( !(xfin == 0))
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
		board[xfin][yfin] = '';

		// Value Reduced.

		while((i-j >= 0) && (j+i < boardsize))
		{
			if((board[xfin][i-j] == board[xfin][i+j]) && (board[xfin][i-j] != ''))
				difference -= 2*j+1;
			else
				break;
			j++;
		}

		if( !(xfin == boardsize-1))
		{			
			if(board[xfin][i] == board[xfin][i+1])
			{
				difference += 2;
				j=1;
				while(i-j >= 0 && i+j+1 < boardsize)
				{
					if((board[xfin][i-j] == board[xfin][i+j+1]) && (board[xfin][i-j] != ''))
						difference -= 2*j+2;
					else 
						break;
					j++;
				}

			}
		}

		if( !(xfin == 0))
		{			
			i=yfin;
			if(board[xfin][i] == board[xfin][i-1])
			{
				difference -= 2;
				j=1;
				while(i-j-1 >= 0 && i+j < boardsize)
				{
					if((board[xfin][i-j-1] == board[xfin][i+j]) && (board[xfin][i-j-1] != ''))
						difference -= 2*j+2;
					else 
						break;
					j++;
				}

			}
		}

		// The one diff in the other direction.
		// This part is not Generic Enough for the 7x7 board.
		if(xfin > xini)
		{
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
							difference -= 2;
						break;

					case 3 :
						if(board[xini][yini] == board[xini - 2][yini])
							difference -= 3;
						break;

					case 4 :
						if(board[xini][yini] == board[xini - 3][yini] && )
							difference -= 3;
						break;

					default :
						break;

				}
				i++;
			}
		
			i=2;
			while(1)
			{
				if(iterup < i)
					break;
				switch(i)
				{
					case 2 :
						if(board[xini][yini] == board[xini - 1][yini])
							difference -= 2;
						break;

					case 3 :
						if(board[xini][yini] == board[xini - 2][yini])
							difference -= 3;
						break;

					case 4 :
						if(board[xini][yini] == board[xini - 3][yini] && )
							difference -= 3;
						break;

					default :
						break;

				}
				i++;
			}

		}


	}



	if(yfin == yini)
	{
		// Value Added.
		board[xfin][yfin] = color; 
		
		int i = yfin;
		int j = 1;
		
		while((i-j >= 0) && (j+i < boardsize))
		{
			if((board[xfin][i-j] == board[xfin][i+j]) && (board[xfin][i-j] != ''))
				difference += 2*j+1;
			else
				break;
			j++;
		}

		if( !(xfin == boardsize-1))
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

		if( !(xfin == 0))
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
		board[xfin][yfin] = '';

		// Value Reduced.

		while((i-j >= 0) && (j+i < boardsize))
		{
			if((board[xfin][i-j] == board[xfin][i+j]) && (board[xfin][i-j] != ''))
				difference -= 2*j+1;
			else
				break;
			j++;
		}

		if( !(xfin == boardsize-1))
		{			
			if(board[xfin][i] == board[xfin][i+1])
			{
				difference += 2;
				j=1;
				while(i-j >= 0 && i+j+1 < boardsize)
				{
					if((board[xfin][i-j] == board[xfin][i+j+1]) && (board[xfin][i-j] != ''))
						difference -= 2*j+2;
					else 
						break;
					j++;
				}

			}
		}

		if( !(xfin == 0))
		{			
			i=yfin;
			if(board[xfin][i] == board[xfin][i-1])
			{
				difference -= 2;
				j=1;
				while(i-j-1 >= 0 && i+j < boardsize)
				{
					if((board[xfin][i-j-1] == board[xfin][i+j]) && (board[xfin][i-j-1] != ''))
						difference -= 2*j+2;
					else 
						break;
					j++;
				}

			}
		}

	}

	return difference;
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