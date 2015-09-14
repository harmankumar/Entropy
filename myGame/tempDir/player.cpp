#ifndef PLAYER_CPP
#define PLAYER_CPP

#include "player.hpp"
using namespace std;


void bot::setDepth(int depth){
    maxdepth = depth;
}

void bot::moveTile(int initx, int inity, int finx, int finy){
    if(initx == finx && inity == finy)
        return;
   	char tile = board[initx][inity];
   	removeTile(initx,inity);
   	placeTile(finx,finy,tile);
    
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
}
int bot::updatePenaltyForRow(int initx,int inity){
	int ii = initx + 1;
	int p1 = 0,p2=0,p=0;
	while(ii < n){
		if(board[ii][inity] != '-'){
			p1 = diff_order(ii,inity,initx,inity);
			break;
		}
		else{
			ii++;
		}
	}
	ii = initx - 1;
	while( ii >=0 ){
		if(board[ii][inity] != '-'){
			p2 = diff_order(ii,inity,initx,inity);
			break;
		}
		else{
			ii--;
		}
	}
	p = (p1 > p2) ? p1 : p2;
	p = (p > 0) ? p : 0;
	return p;
}

int bot::updatePenaltyForColumn(int initx,int inity){
	int p1 = 0 , p2 = 0,p = 0;
	int ii = inity + 1;
	while(ii < n){
		if(board[initx][ii] != '-'){
			p1 = diff_order(initx,ii,initx,inity);
			break;
		}
		else{
			ii++;
		}
	}
	ii = inity - 1;
	while(ii>=0){
		if(board[initx][ii] != '-'){
			p2 = diff_order(initx,ii,initx,inity);
			break;
		}
		else{
			ii--;
		}
	}
	p = (p1 > p2) ? p1 : p2;
	p = (p > 0) ? p : 0;
	return p;
}

void bot::playAsOrder(char TileUsedByChaos,int row,int col){
	
	//UPDATE SCORE
	
	score += diff_chaos(row,col,TileUsedByChaos);
    
    placeTile(row, col, TileUsedByChaos);
	penalty = 0.0;
	empty.clear();
	//cout<<score<<"\n";
	initx = inity = -1;
	initscore = score;
	expectiminimax(0,0,MINF,INF);
    
	score += diff_order(initx,inity,finx,finy);
	
    moveTile(initx, inity, finx, finy);
	
	printf("%d %d %d %d\n",initx,inity,finx,finy);
    
}

void bot::playAsChaos(char TileColorGiven){
	
	if(!firstMove){
		firstMove = true;
		placeTile(4,4,TileColorGiven);
		printf("%d %d\n",4,4);
		return;
	}
	penalty = 0.0;
	tileToMinNode = TileColorGiven;
    empty.clear();
    posx = posy = -1;
	initscore = score;
    expectiminimax(2,0,MINF,INF);
	
	score += diff_chaos(posx,posy,TileColorGiven);
    placeTile(posx, posy, TileColorGiven);
	
    printf("%d %d\n",posx,posy);
}
void bot::playAsChaos(char TileColorGiven,int initx,int inity,int finx,int finy){
    score += diff_order(initx,inity,finx,finy);
    
    moveTile(initx, inity, finx, finy);
    playAsChaos(TileColorGiven);
    
}

float bot::expectiminimax(int state, int depth,float alpha,float beta){
	localdepth = depth;
	if(depth == maxdepth) //Base Case
		return utilityFunction();
	
	if(state == 0){ 
        
        // This is max node
		
		float globalmax = MINF; // globalmax = alpha;
		vector<tuple<int,int,int,int,int> > score_movements;
		
		for(unordered_set<int>::const_iterator ii = visited_cells.begin();ii != visited_cells.end();ii++){			
				int row = (*ii) / n;
				int column = (*ii) % n;
                score_movements.push_back(make_tuple(0,row,column,row,column));
				int i = column + 1;
				while(i < n){
					if(board[row][i] == '-'){
						int scoreDelta = diff_order(row,column,row,i);
							score_movements.push_back(make_tuple(scoreDelta,row,column,row,i));
						i++;
					}
					else{
						break;
					}
				}
				i = column - 1;
				while(i >=0){
					if(board[row][i] =='-'){
						int scoreDelta = diff_order(row,column,row,i);
						score_movements.push_back(make_tuple(scoreDelta,row,column,row,i));
						i--;
					}
					else{
						break;
					}
				}
				i = row + 1;
				while(i < n){
					if(board[i][column]=='-'){
						int scoreDelta = diff_order(row,column,i,column);
						score_movements.push_back(make_tuple(scoreDelta,row,column,i,column));
						i++;
					}
					else{
						break;
					}
				}
				i = row - 1;
				while(i >= 0){
					if(board[i][column] == '-'){
						int scoreDelta = diff_order(row,column,i,column);
							score_movements.push_back(make_tuple(scoreDelta,row,column,i,column));
						i--;
					}else{
						break;
					}
				}
			}
            //Terminal State check.
            if(score_movements.size()==0)
                return utilityFunction();
			//TODO: Change for move ordering :
            sort(score_movements.begin(),score_movements.end());
			reverse(score_movements.begin(),score_movements.end());        

			for (int i=0;i<score_movements.size();i++){
				// make movement
				int scoreDelta = get<0>(score_movements[i]);
				int row =  get<1>(score_movements[i]);
				int column = get<2>(score_movements[i]);
				int newrow = get<3>(score_movements[i]);
				int newcol = get<4>(score_movements[i]);
				
				float penaltySoFar = penalty;
				
				score += scoreDelta;
				if(scoreDelta >= 10)
					penalty+=10.0;
				if(scoreDelta >= 15)
					penalty+=10.0;
				if(scoreDelta < -10)
					penalty-=gammaArray[localdepth]*scoreDelta;

                
                moveTile(row, column, newrow, newcol);
				
				
				float localmax = expectiminimax((state+1)%3,depth+1,alpha,beta);
				localdepth = depth;
				//Restoring board
                
				score -= scoreDelta;
				
                moveTile(newrow,newcol,row,column);
    			penalty = penaltySoFar;
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
                /*if(depth <= 1){
                    if(alpha > beta)
                        return globalmax;
                    
                }
                else{
                    if(alpha >= beta)
                    	return globalmax; 
                }*/
                    if(alpha>=beta)
                    	return globalmax;
				
			}		
		return globalmax;
	}
	
	else if(state == 1){
		// This is chance node
		float expectedvalue = 0.0;
		for(int i=0;i<5;i++){
			float prob = float(colors[i]) / totaltilesleft;
			tileToMinNode = 65+i; //given color.
            if(prob>0.0001){
				expectedvalue += prob*expectiminimax((state+1)%3,depth+1,alpha,beta);
            	localdepth = depth;
            }
		}
		return expectedvalue;

	}

	else{

		//This is min node
		float globalmin = INF;
		
		vector<tuple<int,int,int> > score_movements;
		for(unordered_set<int>::const_iterator it = unvisited_cells.begin();it!= unvisited_cells.end();it++){
			int row =  (*it) / n;
			int col = (*it) % n;
			//TODO: Set scoreDelta
            int scoreDelta = diff_chaos(row,col,tileToMinNode);
			score_movements.push_back(make_tuple(scoreDelta,row,col));
		}
        //Terminal state check
        if(score_movements.size()==0)
            return utilityFunction();
		//TODO: Order moves:
        sort(score_movements.begin(),score_movements.end());
		//TODO:
        
		
        
        for(int i=0;i<score_movements.size();i++){
			//make movement
			int scoreDelta = get<0>(score_movements[i]);
			int row = get<1>(score_movements[i]);
			int col = get<2>(score_movements[i]);
			
			score+=scoreDelta;
			float penaltySoFar = penalty;
			
			if(scoreDelta >=5)
				penalty+=10.0;
			if(scoreDelta >=15)
				penalty+=10.0;

            placeTile(row,col,tileToMinNode);
            
            if(row + 2 < n){
            	if(board[row][col] == board[row+2][col] && board[row+1][col] == '-'){
            		penalty+=5.0;
            		penalty += gammaArray[localdepth] * updatePenaltyForRow(row+1,col);
            	}
            }
            if(row - 2 >= 0){
            	if(board[row][col] == board[row-2][col] && board[row-1][col] == '-'){
            		penalty+=5.0;
            		penalty+= gammaArray[localdepth] * updatePenaltyForRow(row-1,col);
            	}

            }
            if(col + 2 < n){
            	if(board[row][col] == board[row][col+2] && board[row][col+1] == '-'){
            		penalty+=5.0;
            		penalty+= gammaArray[localdepth] * updatePenaltyForColumn(row,col+1); 
            	}
            }
            if(col - 2 >=0){
            	if(board[row][col] == board[row][col-2] && board[row][col-1] == '-'){
            		penalty+=5.0;
            		penalty+= gammaArray[localdepth] * updatePenaltyForColumn(row,col-1);
            	}
            }
            


			float localmin = (float) expectiminimax((state+1)%3,depth+1,alpha,beta);
			localdepth = depth;
            //Restore board
            removeTile(row, col);
			score-=scoreDelta;
            penalty = penaltySoFar;
            
			if(localmin < globalmin){
				globalmin = localmin;
                if(depth==0){
                    tilecolor = tileToMinNode;
                    posx = row;
                    posy = col;
                }
			}
            beta = (beta < globalmin)? beta:globalmin;
            /*if(depth==2){
                if(alpha > beta){
                    return globalmin;
                }
            }else{
                if(alpha>=beta){
                	return globalmin;
                }
            }*/
            if(alpha >= beta)
            	return globalmin;

		}
        
		return globalmin;
	}
    
}


int bot::getScore(const string & s){
	int n = s.length();
	int left,right;
	int counter = 0;
	for(int i=0;i<n-1;i++){
		left = i-1;
		right = i+1;
		while(left >= 0 && right < n ){
			if(s[left] == s[right]){
				counter+= right - left + 1;
				left--;
				right++;
			}
			else{
				break;
			}
		}
		left = i;
		right = i+1;
		while(left >=0 && right < n){
			if(s[left] == s[right]){
				counter+= right - left + 1;
				left--;
				right++;
			}
			else{
				break;
			}
		}
	}
	return counter;
}

int bot::diff_order(int initx,int inity,int finx,int finy){
	int difference = 0;
	string topWord,bottomWord,leftWord,rightWord;
	topWord = bottomWord = leftWord = rightWord = "";
	int y = inity + 1;
	while(y < n){
		if(board[initx][y] == '-')
			break;
		else{
			rightWord+=board[initx][y];
			y++;
		}
	}
	int x = initx + 1;
	while(x < n){
		if(board[x][inity] == '-')
			break;
		else{
			bottomWord+=board[x][inity];
			x++;
		}
	}
	y = inity - 1;
	while(y >= 0){
		if(board[initx][y] == '-')
			break;
		else{
			y--;
		}
	}
	y++;
	while(y != inity)
		leftWord+=board[initx][y++];
	
	x = initx - 1;
	while(x>=0){
		if(board[x][inity] == '-')
			break;
		else{
			x--;
		}
	}
	x++;
	while(x!=initx)
		topWord+=board[x++][inity];
	
	
	string completeWord = leftWord + board[initx][inity] + rightWord;
	difference = difference - getScore(completeWord) + getScore(leftWord) + getScore(rightWord);
	completeWord = topWord + board[initx][inity] + bottomWord;
	difference = difference - getScore(completeWord) + getScore(topWord) + getScore(bottomWord);
	char color = board[initx][inity];
	board[initx][inity] = '-';

	topWord = bottomWord = leftWord = rightWord = "";
	y = finy + 1;
	while(y < n){
		if(board[finx][y] == '-')
			break;
		else{
			rightWord+=board[finx][y];
			y++;
		}
	}
	x = finx + 1;
	while(x < n){
		if(board[x][finy] == '-')
			break;
		else{
			bottomWord+=board[x][finy];
			x++;
		}
	}
	y = finy - 1;
	while(y >= 0){
		if(board[finx][y] == '-')
			break;
		else{
			y--;
		}
	}
	y++;
	while(y != finy)
		leftWord+=board[finx][y++];
	
	x = finx - 1;
	while(x>=0){
		if(board[x][finy] == '-')
			break;
		else{
			x--;
		}
	}
	x++;
	while(x != finx)
		topWord+=board[x++][finy];
	
	completeWord = leftWord + color + rightWord;
	difference = difference + getScore(completeWord) - getScore(leftWord) - getScore(rightWord);
	completeWord = topWord + color + bottomWord;
	
	difference = difference + getScore(completeWord) - getScore(topWord) - getScore(bottomWord);
	board[initx][inity] = color;
	return difference;
}

int bot::diff_chaos(int posx,int posy,char color){
	string topWord,bottomWord,leftWord,rightWord;
	topWord = bottomWord = leftWord = rightWord = "";
	int difference = 0;
	int y = posy + 1;
	while(y < n){
		if(board[posx][y] == '-')
			break;
		else{
			rightWord+=board[posx][y];
			y++;
		}
	}
	int x = posx + 1;
	while(x < n){
		if(board[x][posy] == '-')
			break;
		else{
			bottomWord+=board[x][posy];
			x++;
		}
	}
	y = posy - 1;
	while(y >= 0){
		if(board[posx][y] == '-')
			break;
		else{
			y--;
		}
	}
	y++;
	while(y!=posy)
		leftWord+=board[posx][y++];

	x = posx - 1;
	while(x>=0){
		if(board[x][posy] == '-')
			break;
		else{
			x--;
		}
	}
	x++;
	while(x!=posx)
		topWord+=board[x++][posy];
	
	string completeWord = leftWord + color + rightWord;
	difference = difference + getScore(completeWord) - getScore(leftWord) - getScore(rightWord);
	completeWord = topWord + color + bottomWord;
	difference = difference + getScore(completeWord) - getScore(topWord) - getScore(bottomWord);
	return difference;
}

float bot::utilityFunction(){
float value = score - initscore + penalty;
	return value;
	/*unordered_set<int> considered_cells;
	if(totaltilesleft == 0)
		return value;
	float expectedIncreaseInScore = 0.0;
	for(unordered_set<int>::const_iterator it = visited_cells.begin(); it != visited_cells.end();it++){
		int currRow = (*it) / n;
		int currCol = (*it) % n;
		if(currRow + 1 < n && board[currRow + 1][currCol] =='-'){
			int ii = (n*(currRow+1)) + currCol;
			unordered_set<int>::const_iterator it2 = considered_cells.find(ii);
			if(it2 == considered_cells.end()){
				considered_cells.insert(ii);
				for(int color = 0;color < n;color++){
					if(colors[color] != 0){
						expectedIncreaseInScore += (float(colors[color]) / totaltilesleft * float(diff_chaos(currRow+1,currCol,color+65)));
					}
				}
			}	
		}
		
		if(currRow - 1 >= 0 && board[currRow - 1][currCol] =='-'){
			int ii = (n*(currRow-1)) + currCol;
			unordered_set<int>::const_iterator it2 = considered_cells.find(ii);
			if(it2 == considered_cells.end()){
				considered_cells.insert(ii);
				for(int color = 0;color < n;color++){
					if(colors[color] != 0){
						expectedIncreaseInScore += (float(colors[color]) / totaltilesleft * float(diff_chaos(currRow-1,currCol,color+65)));
					}
				}
			}	
		}
		if(currCol + 1 < n && board[currRow][currCol + 1] =='-'){
			int ii = (n*(currRow)) + currCol + 1;
			unordered_set<int>::const_iterator it2 = considered_cells.find(ii);
			if(it2 == considered_cells.end()){
				considered_cells.insert(ii);
				for(int color = 0;color < n;color++){
					if(colors[color] != 0){
						expectedIncreaseInScore += (float(colors[color]) / totaltilesleft * float(diff_chaos(currRow,currCol+1,color+65)));
					}
				}
			}	
		}
		if(currCol - 1 >= 0 && board[currRow][currCol - 1] =='-'){
			int ii = (n*(currRow)) + currCol - 1;
			unordered_set<int>::const_iterator it2 = considered_cells.find(ii);
			if(it2 == considered_cells.end()){
				considered_cells.insert(ii);
				for(int color = 0;color < n;color++){
					if(colors[color] != 0){
						expectedIncreaseInScore += (float(colors[color]) / totaltilesleft * float(diff_chaos(currRow,currCol-1,color+65)));
					}
				}
			}	
		}

	}*/
	
	//return value + expectedIncreaseInScore;
}

#endif