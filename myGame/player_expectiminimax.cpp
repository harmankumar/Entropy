#ifndef PLAYER_CPP
#define PLAYER_CPP

#include "playerExpMinMax.hpp"
using namespace std;

float bot::utilityFunction(){
	// DO SOME MAGIC HERE
	float theMagicValue = ((float) score /*/ 150.0 */);
    theMagicValue -= ((float) scattering / 250.0);
    if(controlTentativePalindromes)
    	theMagicValue += ((float) tentative_palindrome_count() / 20.0);
    theMagicValue += ((float) skipCount() / 15.0);
    return theMagicValue;
}
void bot::setDepth(int depth){
    maxdepth = depth;
}

void bot::moveTile(int initx, int inity, int finx, int finy){
    if(initx == finx && inity == finy)
        return;
    char tile = board[initx][inity];
    if(tile == '-'){
        cout<<"Error hai bhai\n";
        return;
    }
    board[initx][inity] = '-';
    board[finx][finy] = tile;
    int ii = (n*finx) + finy;
    int jj = (n*initx) + inity;
    visited_cells.erase(jj);
    visited_cells.insert(ii);
    
    unvisited_cells.insert(jj);
    unvisited_cells.erase(ii);

    int idx = tile - 65;
    mapping[idx].erase(jj);
    mapping[idx].insert(ii);
    for(unordered_set<int>::const_iterator it = (mapping[idx]).begin(); it != (mapping[idx]).end();it++){
    		int row = (*it) / n;
    		int col = (*it) % n;
            if(row == finx && col ==finy)
                continue;
    		scattering += abs(row - finx) + abs(col - finy) - abs(row - initx) - abs(col - inity);
    }
    if(scattering < 0){
        printBoard();
        
    }

}

void bot::placeTile(int posx, int posy, char C){
    if(board[posx][posy] != '-')
        return;
    board[posx][posy] = C;
    int idx = C - 65;
    colors[idx]--;
    totaltilesleft--;
    int ii = (posx*n) + posy;
    visited_cells.insert(ii);
    unvisited_cells.erase(ii);
    
    idx = C - 65;
    
    for(unordered_set<int>::const_iterator it = mapping[idx].begin(); it != mapping[idx].end();it++){
    		int row = (*it) / n;
    		int col = (*it) % n;
    		scattering += (abs(row - posx) + abs(col - posy));
    }
    mapping[idx].insert(ii);
    if(scattering < 0){
        printBoard();
        
    }
}

void bot::removeTile(int posx, int posy){
    if(board[posx][posy] == '-')
        return;
    int idx = board[posx][posy] - 65;
    colors[idx]++;
    totaltilesleft++;
    board[posx][posy] = '-';
    int ii = n*posx + posy;
    visited_cells.erase(ii);
    unvisited_cells.insert(ii);

    mapping[idx].erase(ii);
    for(unordered_set<int>::const_iterator it = mapping[idx].begin(); it != mapping[idx].end();it++){
    		int row = (*it) / n;
    		int col = (*it) % n;
    		scattering -= (abs(row - posx) + abs(col - posy));
    }
    if(scattering < 0){
        printBoard();
        
    }
}
void bot::playAsOrder(char TileUsedByChaos,int row,int col){
	
	//UPDATE SCORE and INITIALIZE ALPHA and BETA
	
	score += diff_chaos(row,col,TileUsedByChaos);
    
    placeTile(row, col, TileUsedByChaos);
	if(totaltilesleft<=17)
		controlTentativePalindromes = true;
	if(totaltilesleft<8)
		controlTentativePalindromes = false;
	
	initx = inity = -1;
	
	float dummy = expectiminimax(0,0,MINF,INF);
    
	score += diff_order(initx,inity,finx,finy);
	
    moveTile(initx, inity, finx, finy);
	
	printf("%d %d %d %d\n",initx,inity,finx,finy);
    
}

void bot::playAsChaos(char TileColorGiven){
	
	
	tileToMinNode = TileColorGiven;
    
    posx = posy = -1;
	
    float dummy = expectiminimax(2,0,MINF,INF);
	
	score += diff_chaos(posx,posy,TileColorGiven);
    placeTile(posx, posy, TileColorGiven);
	if(totaltilesleft<=15)
		controlTentativePalindromes = true;
	if(totaltilesleft<8)
		controlTentativePalindromes = false;
    
    printf("%d %d\n",posx,posy);
}
void bot::playAsChaos(char TileColorGiven,int initx,int inity,int finx,int finy){
    score += diff_order(initx,inity,finx,finy);
    
    moveTile(initx, inity, finx, finy);
    
    debug_flag = true;
    playAsChaos(TileColorGiven);
    
    
}

float bot::expectiminimax(int state, int depth,float alpha,float beta){

	if(depth == maxdepth) //Base Case
		return utilityFunction();
	
	if(state == 0){ 
        
        // This is max node
		
		float globalmax = MINF; // globalmax = alpha;
		vector<triple*> score_movements;
		
		for(unordered_set<int>::const_iterator ii = visited_cells.begin();ii != visited_cells.end();ii++){			
				int row = (*ii) / n;
				int column = (*ii) % n;
                score_movements.push_back(new triple(0,(*ii),(*ii)));
				int i = 1;
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
				i = 1;
				while(column - i >=0){
					if(board[row][column - i] =='-'){
						int scoreDelta = diff_order(row,column,row,column-i);
						if(scoreDelta != errScore)
							score_movements.push_back(new triple(scoreDelta,(*ii),n*row + column-i));
						i++;
					}
					else{
						break;
					}
				}
				i = 1;
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
				i = 1;
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
            //Terminal State check.
            if(score_movements.size()==0)
                return utilityFunction();
			//TODO: Change for move ordering :
            sort(score_movements.begin(),score_movements.end(),comparison);
        

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
                
                moveTile(row, column, newrow, newcol);
				
				
				float localmax = expectiminimax((state+1)%3,depth+1,alpha,beta);
				
				//Restoring board
                
				score -= scoreDelta;
				
                moveTile(newrow,newcol,row,column);
    
				if(localmax > globalmax){
					// Store action that lead to this state
					globalmax = localmax;
                    if(depth == 0){
                        initx = row;
                        inity = column;
                        finx = newrow;
                        finy = newcol;
                    }
				}
                alpha = (alpha > globalmax) ? alpha : globalmax;
                if(depth == 1){
                    if(alpha > beta){
                    	score_movements.clear();
                        return globalmax;
                    }
                }
                else{
                    if(alpha >= beta){
                    	score_movements.clear();
                        return globalmax;
                    }
                }
				
			}		
		return globalmax;
	}
	
	else if(state == 1){
		// This is chance node
		float expectedvalue = 0.0;
		for(int i=0;i<5;i++){
			float prob = float(colors[i]) / totaltilesleft;
			tileToMinNode = 65+i; //given color.
            /*float upperBound = expectedvalue + boundChanceNode(i);
            if(upperBound < alpha)
                return expectedvalue;*/
            if(prob>0.0001){
				expectedvalue += prob*expectiminimax((state+1)%3,depth+1,alpha,beta);
            
            }
		}
		return expectedvalue;

	}

	else if(state == 2){

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
        //Terminal state check
        if(score_movements.size()==0)
            return utilityFunction();
		//TODO: Order moves:
        sort(score_movements.begin(),score_movements.end(),comparison);
		//TODO:
        reverse(score_movements.begin(),score_movements.end());
		
        
        for(int i=0;i<score_movements.size();i++){
			//make movement
			int row = score_movements[i]->second;
			int col = score_movements[i]->third;
			int scoreDelta = score_movements[i]->first;
			
			//Memory management: score_management[i] no longer needed. Deleted. 
			delete score_movements[i];
			//End Memory management
			
			score+=scoreDelta;
            placeTile(row,col,tileToMinNode);
			
			float localmin = (float) expectiminimax((state+1)%3,depth+1,alpha,beta);
			
			
            //Restore board
            removeTile(row, col);
			score-=scoreDelta;
            
            
			if(localmin < globalmin){
				globalmin = localmin;
                if(depth==0){
                    tilecolor = tileToMinNode;
                    posx = row;
                    posy = col;
                }
			}
            beta = (beta < globalmin)? beta:globalmin;
            if(depth==2){
                if(alpha > beta){
                	score_movements.clear();
                    return globalmin;
                }
            }else{
                if(alpha>=beta){
                	score_movements.clear();
                    return globalmin;
                }
            }

		}
        
		return globalmin;
	}
    else{
        return MAXFLOAT;
    }
}

/*float bot::boundChanceNode(int i){
    if(i==0){
        return epsilon;
    }
    else if(i < 2){
        int tileCount = totaltilesleft;
        for(int j = 0;j<i;j++){
            tileCount -= colors[j];
        }
        return float(tileCount) / totaltilesleft * epsilon;
    }
    else{
        int tileCount = 0;
        for(int j = i;j<n;j++)
            tileCount += colors[j];
        return float(tileCount) / totaltilesleft * epsilon;
    }
}*/

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
    if( (yfin == yini) && (xfin==xini))	// Trivial.
        return difference;
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

int bot::tentative_palindrome_count(){

	int tentative_delta = 0;

	for(unordered_set<int>::const_iterator it = unvisited_cells.begin();it!= unvisited_cells.end();it++){
		int i = (*it) / n;
		int j = (*it) % n;
		for(int l=0; l<5; l++)	// Iterating through the colors and getting the score.
		{
			int addscore_col = 0;
            int addscore_row = 0;
			string row, col;
			int k=0; 
			while(k<n)
			{
				row += board[i][k];
				col += board[k][j];
				k++;
			}

			addscore_row -= getscore(row);
			addscore_col -= getscore(col);

			row.resize(0);
			col.resize(0);
			char color = 'A'+l;
			int colrow = -1, colcol = -1;	// Tiles of the same color in its row and column.
			while(k<n)
			{
				if(board[i][k] == color)
					colrow++;
				if(board[k][j] == color)
					colcol++;
				row += board[i][k];
				col += board[k][j];
				k++;
			}
			// Use the variables colrow and colcol somehow.

			addscore_row += getscore(row) + colrow;
			addscore_col += getscore(col) + colcol;
			board[i][j] = '-'; 			// Restoring the board.
			tentative_delta += (colors[i] / (float) totaltilesleft) * addscore_col;	// Multiply with the probability of the color appearing.
		}
			
	}	
	
    return tentative_delta;
}
int bot::skipCount(){
	int counter = 0;
	for(int i=0;i<n;i++){
		for(int j=0;j<n-2;j++){
			if(board[i][j] == board[i][j+2] && board[i][j+1] == '-'){
				counter ++;
				
			}
			if(board[j][i] == board[j+2][i] && board[j+1][i] == '-'){
				counter++;
				
			}
		}
	}
	return 0.0;
}

#endif