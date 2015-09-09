#ifndef PLAYER_CPP
#define PLAYER_CPP

#include "player.hpp"
using namespace std;

float bot::utilityFunction(){
	// DO SOME MAGIC HERE
	float theMagicValue = score;
	return theMagicValue;
}

void bot::playAsOrder(char TileUsedByChaos,int row,int col){
	//UPDATE SCORE 
	score += diff_chaos(row,col,TileUsedByChaos);
	
	unvisited_cells.erase(n*row + col);
	visited_cells.insert(n*row + col);
	
	int idx = TileUsedByChaos - 65;
	
	colors[idx]--;
	totaltilesleft--;
	board[row][col] = TileUsedByChaos;
	
	//cout<<score<<"\n";
	initx = inity = -1;
	
	float dummy = expectiminimax(0,0);
    
	score += diff_order(initx,inity,finx,finy);
	
	board[finx][finy] = board[initx][inity];
	board[initx][inity] = '-';
	
	unvisited_cells.erase(n*finx + finy);
	unvisited_cells.insert(n*initx + inity);
	visited_cells.erase(n*initx + inity);
	visited_cells.insert(n*finx + finy);
	
	printf("%d %d %d %d\n",initx,inity,finx,finy);
    
}

void bot::playAsChaos(char TileColorGiven){
	tileToMinNode = TileColorGiven;
	
	float dummy = expectiminimax(2,0);
	
	score += diff_chaos(posx,posy,TileColorGiven);
	
	board[posx][posy] = TileColorGiven;
	unvisited_cells.erase(n*posx + posy);
	visited_cells.insert(n*posx + posy);

	printf("%d %d\n",posx,posy);
}

float bot::expectiminimax(int state, int depth){

	if(depth == maxdepth) //Base Case
		return utilityFunction();
	
	if(state == 0){ 
		// This is max node
		
		float globalmax = MINF;
		vector<triple*> score_movements;
		
		for(unordered_set<int>::const_iterator ii = visited_cells.begin();ii != visited_cells.end();ii++){			
				int row = (*ii) / n;
				int column = (*ii) % n;
				
				int i = 0;
				while(column + i < n){
					if(board[row][column+i] == '-'){
						int scoreDelta = diff_order(row,column,row,column+i);
						if(scoreDelta != errScore)
							score_movements.push_back(new triple(scoreDelta,(*ii),n*row + column+i));
						i++;
					}
					else{
						break;
					}
				}
				i = 0;
				while(column - i >=0){
					if(board[row][column - i] =='-'){
						int scoreDelta = diff_order(row,column,row,column-i);
						if(scoreDelta != errScore)
							score_movements.push_back(new triple(scoreDelta,(*ii),n*row + column-i));
						else
							cout<<"hey\n";
						i++;
					}
					else{
						break;
					}
				}
				i = 0;
				while(row + i < n){
					if(board[row+i][column]=='-'){
						int scoreDelta = diff_order(row,column,row+i,column);
						if(scoreDelta != errScore)
							score_movements.push_back(new triple(scoreDelta,(*ii),n*(row+i) + column));
						i++;
					}else{
						break;
					}
				}
				i = 0;
				while(row - i >= 0){
					if(board[row-i][column] == '-'){
						int scoreDelta = diff_order(row,column,row-i,column);
						if(scoreDelta != errScore)
							score_movements.push_back(new triple(scoreDelta,(*ii),n*(row-i) + column));
						i++;
					}else{
						break;
					}
				}
			}
			//TODO: Change for move ordering : sort(score_movements.begin(),score_movements.end(),comparison)


			for (int i=0;i<score_movements.size();i++){
				// make movement
				int newrow = score_movements[i]->third / n;
				int newcol = score_movements[i]->third % n;
				int row = score_movements[i]->second /n;
				int column = score_movements[i]->second % n;
				int scoreDelta = score_movements[i]->first;
				
				score += scoreDelta;

				//Memory management: score_management[i] no longer needed. Deleted. 
				delete score_movements[i];
				//End Memory management
				
				visited_cells.erase(n*row + column);
				visited_cells.insert(n*newrow + newcol);
				
				board[newrow][newcol] = board[row][column];
				unvisited_cells.erase(newrow*n + newcol);
				board[row][column] = '-';
				unvisited_cells.insert(row*n + column);
				
				int localstate = state;
				state  = (state + 1)%3;
				float tempval = expectiminimax(state,depth+1);
				
                
				//Restoring board

				state = localstate;
				score -= scoreDelta;
				
				visited_cells.erase(n*newrow + newcol);
				visited_cells.insert(n*row + column);
				
				board[row][column] = board[newrow][newcol];
				unvisited_cells.erase(row*n + column);
				board[newrow][newcol] = '-';
				unvisited_cells.insert(newrow*n + newcol);

				if(tempval > globalmax){
					// Store action that lead to this state
					globalmax = tempval;
					initx = row;
					inity = column;
					finx = newrow;
					finy = newcol;	 
				}
                
			}		
		return globalmax;
	}
	
	else if(state == 1){
		// This is chance node
		float expectedvalue = 0.0;
		for(int i=0;i<5;i++){
			float prob = float(colors[i]) / totaltilesleft;
			colors[i]--;
			totaltilesleft--;
			tileToMinNode = 65+i; //given color.
			int localstate = state;
			state = (state + 1)%3;
            if(prob>0.0001){
				expectedvalue += prob*expectiminimax(state,depth+1);
                if(expectedvalue > 1000.0){
                    cout<<"Warning expected value too large. ";
                }
                    
            }
            state = localstate;
			colors[i]++;
			totaltilesleft++;
		}
		return expectedvalue;

	}

	else{
		//This is min node
		float globalmin = INF;
		
		vector<triple*> score_movements;
		for(unordered_set<int>::const_iterator it = unvisited_cells.begin();it!= unvisited_cells.end();it++){
			int row =  (*it) / n;
			int col = (*it) % n;
			//TODO: Set scoreDelta
			int scoreDelta = diff_chaos(row,col,tileToMinNode);
			score_movements.push_back(new triple(scoreDelta,row,col));
		}
		//TODO: Order moves: sort(score_movements.begin(),score_movements.end(),comparison)
		for(int i=0;i<score_movements.size();i++){
			//make movement
			int row = score_movements[i]->second;
			int col = score_movements[i]->third;
			float scoreDelta = score_movements[i]->first;
			
			//Memory management: score_management[i] no longer needed. Deleted. 
			delete score_movements[i];
			//End Memory management
			
			score+=scoreDelta;
			board[row][col] = tileToMinNode;
			unvisited_cells.erase(n*row + col);
			visited_cells.insert(n*row + col);

			int localstate = state;
			state = (state+1)%3;	
			float localmin = expectiminimax(state,depth+1);
			state = localstate;
			//Restore board
			board[row][col] = '-';
			unvisited_cells.insert(n*row + col);
			visited_cells.erase(n*row + col);
			score-=scoreDelta;
			
			
			if(localmin < globalmin){
				globalmin = localmin;
				tilecolor = tileToMinNode;
				posx = row;
				posy = col;
			}

		}
        if(globalmin > 1000.0)
            cout<<"Warning Large Values\n";
		return globalmin;
	}

}



int bot::getscore(string s){
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


int bot::diff_order(int xini, int yini, int xfin, int yfin){
	int difference = 0;
	char color = board[xini][yini];
	if(color == '-'){
		cout<<"Input fault. Idiot " <<xini<<" "<<yini<<"\n";
		return errScore;
	}
	else if(board[xfin][yfin] != '-'){
		cout<<"Movement fault. Moron"<<xfin<<" "<<yfin<<"\n";
		return errScore;
	}
	if(xini!= xfin && yini!=yfin){
		cout<<"Diagonal fault. Double Moron\n";
		return errScore;
	}
	string s;
	if( (yfin == yini) && (xfin==xini))	// Trivial.
		return difference;

	if( (yfin != yini) && (xfin != xini))	// Not a Possible move
		return errScore;

	if(yfin == yini)	// Column Movement
	{
		string rowi, rowf, col;

		int i=0;
		while(i<n)
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
		
		board[xini][yini] = '-';
		board[xfin][yfin] = color;

		i=0;
		while(i<n)
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
		while(i<n)
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
		while(i<n)
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

int bot::diff_chaos(int x, int y, char color){
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


#endif