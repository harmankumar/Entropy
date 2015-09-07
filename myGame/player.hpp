#ifndef PLAYER_HPP
#define PLAYER_HPP
#include <iostream>
#include <vector>
using namespace std;

#define INF numeric_limits<float>::max
#define MINF numeric_limits<float>::min

class bot{
	int sizeOfBoard;
	vector<vector<char> > board; // The board
	vector<int> colors; // Number of tiles left of valid colors
	vector<pair<int,int> > tilePos; //The position of tiles.
	bool order; //Whether order or chaos
	int maxdepth; //The max depth to which we can go(0,maxdepth), both inclusive.
	int totaltilesleft; // number of tiles left
	char tileToMinNode;
	int score;
	void score(){
		
	}
public:
	bot(int n,bool ord):board(n,vector<char>(n,'')){
		order = ord;
		sizeOfBoard = n;
		colors.resize(26,0);
		maxdepth = 3; // Vary this to get different depths.
		totaltilesleft = 25;
		tileToMinNode = '';
		score = 0;
	}
	float expectiminimax(int state, int depth){
		if(depth == maxdepth)
			return utilityFunction();
		if(state == 0){ 
			float globalmax = MINF;
			// This is max node
			for(int i = 0;i<tilePos.size();i++){
				int column = get<0>(tilePos[i]);
				int row = get<1>(tilePos[i]);
				vector<int> columnMovements;
				vector<int> rowMovements;
				int i = 1;
				flag = true;
				while(flag){
					flag = false;
					if(column + i < sizeOfBoard && board[row][column+i] == ''){
						columnMovements.push_back(column + i);
						flag = true;
					}
					if(colume - i >= 0 && board[row][column - i] == ''){
						columnMovements.push_back(column-i);
						flag = true;
					}
					if(flag==true)
						i++;
				}
				i = 1;
				flag = false;
				while(flag){
					flag = false;
					if(row + i < sizeOfBoard && board[row+i][column] == ''){
						rowMovements.push_back(row + i);
						flag = true;
					}
					if(row - i >= 0 && board[row-i][column] == ''){
						rowMovements.push_back(row-i);
						flag = true;
					}
					if(flag==true)
						i++;
				}
				//for valid movements of tile on board{
					// make movement
					int localstate = state;
					state  = (state + 1)%3;
					float tempval = expectiminimax(state,depth+1);
					state = localstate;
					if(tempval > globalmax){
						globalmax = tempval;
						// Store action that lead to this state
					}
					//Restore board
					//}
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
			//for valid moves of min nodes with tileToMinNode{
				//make movement
				int localstate = state;
				state = (state+1)%3;	
				float localmin = expectiminimax(state,depth+1);
				state = localstate;
				if(localmin < globalmin){
					localmin = globalmin;
					//Store action to this state
				}
				//Restore board

			//}
			return globalmin;
		}
	}	
	float utilityFunction(){
		// DO SOME MAGIC HERE
		return 0.0;
	}
	void playAsOrder(char TileUsedByChaos,int row,int col);
	void playAsChaos(char TileColorGiven);
};
#endif