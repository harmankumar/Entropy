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
vector< vector<char> > board(5 , vector<char>(5,' '));

int diff(int xini, int yini, int xfin, int yfin, char color)
{
	int difference = 0;
	
	if( (yfin == yini) && (xfin==xini))	// Trivial.
		return difference;

	if( (yfin != yini) && (xfin != xini))	// Not a Possible move
		return -1;

	if(yfin == yini)	// Movement in a column.
	{
		int i = yfin;
		int j = 1;

		// Value Reduced.
		// Odd Pal.
		while((i-j >= 0) && (j+i < boardsize))
		{
			if((board[xini][i-j] == board[xini][i+j]) && (board[xini][i-j] != ' '))
				difference -= 2*j+1;
			else
				break;
			j++;
		}

		// Even Pal. Forward.
		if( !(yini == boardsize-1))
		{	
			// i = yfin;		
			if(board[xini][i] == board[xini][i+1])
			{
				difference -= 2;
				j=1;
				while(i-j >= 0 && i+j+1 < boardsize)
				{
					if((board[xini][i-j] == board[xini][i+j+1]) && (board[xini][i-j] != ' '))
						difference -= 2*j+2;
					else 
						break;
					j++;
				}

			}
		}
		// Backward.
		if( !(yfin == 0))
		{			
			// i = yfin;
			if(board[xini][i] == board[xini][i-1])
			{
				difference -= 2;
				j=1;
				while(i-j-1 >= 0 && i+j < boardsize)
				{
					if((board[xini][i-j-1] == board[xini][i+j]) && (board[xini][i-j-1] != ' '))
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
		// i = yfin;
		j = 1;

		while((i-j >= 0) && (j+i < boardsize))
		{
			if((board[xfin][i-j] == board[xfin][i+j]) && (board[xfin][i-j] != ' '))
				difference += 2*j+1;
			else
				break;
			j++;
		}

		// Even Pal. Forward
		if( !(yfin == boardsize-1))
		{			
			if(board[xfin][i] == board[xfin][i+1])
			{
				difference += 2;
				j=1;
				while(i-j >= 0 && i+j+1 < boardsize)
				{
					if((board[xfin][i-j] == board[xfin][i+j+1]) && (board[xfin][i-j] != ' '))
						difference += 2*j+2;
					else 
						break;
					j++;
				}

			}
		}
		// Backward.
		if( !(yfin == 0))
		{			
			// i=yfin;
			if(board[xfin][i] == board[xfin][i-1])
			{
				difference += 2;
				j=1;
				while(i-j-1 >= 0 && i+j < boardsize)
				{
					if((board[xfin][i-j-1] == board[xfin][i+j]) && (board[xfin][i-j-1] != ' '))
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
					if( (board[xini][yini] == board[xini + 3][yini]) && (board[xini + 1][yini] == board[xini + 2][yini]) )
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

		board[xfin][yfin] = ' ';

	}

	if(xfin == xini)	// Movement in a Row
	{
		int i = xfin;
		int j = 1;

		// Value Reduced.
		// Odd Pal.
		while((i-j >= 0) && (j+i < boardsize))
		{
			if((board[i-j][yini] == board[i+j][yini]) && (board[i-j][yini] != ' '))
				difference -= 2*j+1;
			else
				break;
			j++;
		}

		// Even Pal. Downward.
		if( !(xini == boardsize-1))
		{			
			if(board[i][yini] == board[i+1][yini])
			{
				difference -= 2;
				j=1;
				while(i-j >= 0 && i+j+1 < boardsize)
				{
					if((board[i-j][yini] == board[i+j+1][yini]) && (board[i-j][yini] != ' '))
						difference -= 2*j+2;
					else 
						break;
					j++;
				}

			}
		}
		// Upward.
		if( !(xini == 0))
		{			
			// i=xfin;
			if(board[i][yini] == board[i-1][yini])
			{
				difference -= 2;
				j=1;
				while(i-j-1 >= 0 && i+j < boardsize)
				{
					if((board[i-j-1][yini] == board[i+j][yini]) && (board[i-j-1][yini] != ' '))
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
		// i = xfin;
		j = 1;
		while((i-j >= 0) && (j+i < boardsize))
		{
			if((board[i-j][yfin] == board[i+j][yfin]) && (board[i-j][yfin] != ' '))
				difference += 2*j+1;
			else
				break;
			j++;
		}

		// Even Pal. Downward.
		if( !(xfin == boardsize-1))
		{			
			if(board[i][yfin] == board[i+1][yfin])
			{
				difference += 2;
				j=1;
				while(i-j >= 0 && i+j+1 < boardsize)
				{
					if((board[i-j][yfin] == board[i+j+1][yfin]) && (board[i-j][yfin] != ' '))
						difference += 2*j+2;
					else 
						break;
					j++;
				}

			}
		}
		// Upward.
		if( !(xfin == 0))
		{			
			// i = xfin;
			if(board[i][yfin] == board[i-1][yfin])
			{
				difference += 2;
				j=1;
				while(i-j-1 >= 0 && i+j < boardsize)
				{
					if((board[i-j-1][yfin] == board[i+j][yfin]) && (board[i-j-1][yfin] != ' '))
						difference += 2*j+2;
					else 
						break;
					j++;
				}

			}
		}

		// The one diff in the other direction.
		// This part is not Generic Enough for the 7x7 board.
		int sumleft = 0;
		int sumright = 0;

		int iterleft = yini+1;
		int iterright = boardsize - yfin + 1;
		
		i=2;
		while(1)
		{
			if(iterleft < i)
				break;
			switch(i)
			{
				case 2 :
					if(board[xini][yini] == board[xini][yini - 1])
						sumleft += 2;
					break;

				case 3 :
					if(board[xini][yini] == board[xini][yini - 2])
						sumleft += 3;
					break;

				case 4 :
					if( (board[xini][yini] == board[xini][yini - 3]) && (board[xini][yini - 1] == board[xini][yini - 2]) )
						sumleft += 3;
					break;

				default :
					break;

			}

			i++;
		}
	
		i=2;
		while(1)
		{
			if(iterright < i)
				break;
			switch(i)
			{
				case 2 :
					if(board[xini][yini] == board[xini][yini + 1])
						sumright += 2;
					break;

				case 3 :
					if(board[xini][yini] == board[xini][yini + 2])
						sumright += 3;
					break;

				case 4 :
					if( (board[xini][yini] == board[xini][yini + 3]) && (board[xini][yini + 1] == board[xini][yini + 2]) )
						sumright += 4;
					break;

				default :
					break;

			}
			i++;
		}

		if(yfin > yini)
		{
			difference += sumright;
			difference -= sumleft;
		}

		if(yfin < yini)
		{
			difference -= sumright;
			difference += sumleft;
		}

		board[xfin][yfin] = ' ';

	}

	return difference;
}


int main()
{
	boardsize = 5;
	// Init the board

//	cout<<diff( , , , , B);

	return 0;
}


/*
			int j=1;
			//  Even
			while(yini-j >= 0 && yini+j+1 < boardsize)
			{
				if((board[xfin][yini-j] == board[xfin][yini+j+1]) && (board[xfin][yini-j] != ' '))
					difference += 2*j+2;
				else 
					break;
				j++;
			}
			// Odd
			while((yini-j >= 0) && (j+yini < boardsize))
			{
				if((board[xfin][yini-j] == board[xfin][yini+j]) && (board[xfin][yini-j] != ' '))
					difference += 2*j+1;
				else
					break;
				j++;
			}

*/