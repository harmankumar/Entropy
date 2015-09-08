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
	board[row][col] = TileUsedByChaos;
	unvisited_cells.erase(n*row + col);
	tilePos.push_back(make_pair(row,col));
	int idx = TileUsedByChaos - 65;
	colors[idx]--;
	totaltilesleft--;
	//TODO: UPDATE SCORE 
	float dummy = expectiminimax(0,0);
	printf("%d %d %d %d\n",initx,inity,finx,finy);
}

void bot::playAsChaos(char TileColorGiven){
	tileToMinNode = TileColorGiven;
	float dummy = expectiminimax(2,0);
	printf("%d %d\n",posx,posy);
}

float bot::expectiminimax(int state, int depth){

	if(depth == maxdepth) //Base Case
		return utilityFunction();
	
	if(state == 0){ 

		float globalmax = MINF;
		// This is max node
		for(int ii = 0;ii<tilePos.size();ii++){
			
			int row = tilePos[ii].first;
			int column = tilePos[ii].second;
			
			vector<triple*> score_movements;
			
			int i = 1;
			
			bool stop_one = false,stop_two =false;
			
			while(!stop_one || !stop_two){
				
				if(column + i < n && board[row][column+i] == 'W' && !stop_one){

					//TODO: setScoreDelta 
					float scoreDelta;
					score_movements.push_back(new triple(scoreDelta,row,column+i));
					
				}
				else{
					stop_one = true;
				}
				if(column - i >= 0 && board[row][column - i] == 'W' && !stop_two){
					
					//TODO: setScoreDelta
					float scoreDelta;
					score_movements.push_back(new triple(scoreDelta,row,column-i));
					

				}else{
					stop_two = true;
				}
				i++;
			}
			
			i = 1;
			
			stop_one = false; stop_two = false;
			
			while(!stop_one || !stop_two){
				

				if(row + i < n && board[row+i][column] == 'W' && !stop_one){
					//TODO: setScoreDelta
					float scoreDelta;
					score_movements.push_back(new triple(scoreDelta,row+i,column));
					
				}else{
					stop_one = true;
				}
				if(row - i >= 0 && board[row-i][column] == 'W' && !stop_two){
					//TODO: setScoreDelta
					float scoreDelta;
					score_movements.push_back(new triple(scoreDelta,row-i,column));
					
					
				}else{
					stop_two = true;
				}
				i++;
			}
			
			//TODO: Change for move ordering : sort(score_movements.begin(),score_movements.end(),comparison)


			for (int i=0;i<score_movements.size();i++){
				// make movement
				int newrow = score_movements[i]->row;
				int newcol = score_movements[i]->column;
				float scoreDelta = score_movements[i]->score;
				
				score += scoreDelta;

				//Memory management: score_management[i] no longer needed. Deleted. 
				delete score_movements[i];
				//End Memory management
				
				tilePos[ii].first = newrow;
				tilePos[ii].second = newcol;
				
				board[newrow][newcol] = board[row][column];
				unvisited_cells.erase(newrow*n + newcol);
				board[row][column] = 'W';
				unvisited_cells.insert(row*n + column);
				
				int localstate = state;
				state  = (state + 1)%3;
				float tempval = expectiminimax(state,depth+1);
				
				//Restoring board

				state = localstate;
				score -= scoreDelta;
				
				tilePos[ii].first = row;
				tilePos[ii].second = column;
				
				board[row][column] = board[newrow][newcol];
				unvisited_cells.erase(row*n + column);
				board[newrow][newcol] = 'W';
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
			if(prob>0.0001)
				expectedvalue += prob*expectiminimax(state,depth+1);
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
			float scoreDelta;
			score_movements.push_back(new triple(scoreDelta,row,col));
		}
		//TODO: Order moves: sort(score_movements.begin(),score_movements.end(),comparison)
		for(int i=0;i<score_movements.size();i++){
			//make movement
			int row = score_movements[i]->row;
			int col = score_movements[i]->column;
			float scoreDelta = score_movements[i]->score;
			
			//Memory management: score_management[i] no longer needed. Deleted. 
			delete score_movements[i];
			//End Memory management
			
			score+=scoreDelta;
			board[row][col] = tileToMinNode;
			unvisited_cells.erase(n*row + col);
			tilePos.push_back(make_pair(row,col));

			int localstate = state;
			state = (state+1)%3;	
			float localmin = expectiminimax(state,depth+1);
			state = localstate;
			//Restore board
			board[row][col] = 'W';
			unvisited_cells.insert(n*row + col);
			score-=scoreDelta;
			tilePos.pop_back();
			
			if(localmin < globalmin){
				localmin = globalmin;
				tilecolor = tileToMinNode;
				posx = row;
				posy = col;
			}

		}
		return globalmin;
	}

}


#endif