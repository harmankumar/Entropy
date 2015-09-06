#ifndef PLAYER_HPP
#define PLAYER_HPP
#include <iostream>
#include <vector>
using namespace std;

class bot{
	int sizeOfBoard;
	vector<vector<char> > board; // The board
	vector<int> colors; // Number of tiles left of valid colors
	vector<pair<int,int> > tilePos; //The position of tiles.
	bool order; //Whether order or chaos
	int maxdepth; //The max depth to which we can go(0,maxdepth), both inclusive.
	vector<char> validColors;
	int totaltilesleft; // number of tiles left
	char tileToMinNode;
public:
	bot(int n,bool ord):board(n,vector<char>(n,'')){
		order = ord;
		sizeOfBoard = n;
		colors.resize(26,0);
		maxdepth = 3; // Vary this to get different depths.
		totaltilesleft = 25;
		tileToMinNode = '';
	}
	float expectiminimax(int state, int depth){
		if(depth == maxdepth)
			return utilityFunction();
		if(state == 0){ 
			float globalmax = -50000.0;
			// This is max node
			for(int i = 0;i<tilePos.size();i++){
				// for valid movements of tile on board{
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
			for(int i=0;i<validColors.size();i++){
				int idx = validColors[i] - 65;
				float prob = float(colors[idx]) / totaltilesleft;
				colors[idx]--;
				totaltilesleft--;
				tileToMinNode = validColors[i];
				int localstate = state;
				state = (state + 1)%3;
				expectedvalue += prob*expectiminimax(state,depth+1);
				colors[idx]++;
				totaltilesleft++;
			}
			return expectedvalue;

		}
		else{
			//This is min node
			float globalmin = 50000.0;
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