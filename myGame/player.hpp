#ifndef PLAYER_HPP
#define PLAYER_HPP
#include <iostream>
#include <algorithm>
#include <vector>
#include <unordered_set>
#include <limits>
using namespace std;

#define INF numeric_limits<float>::max()
#define MINF numeric_limits<float>::min()

struct triple{
	float score;int row;int column;
	triple(float a,int b,int c){
		score = a;row = b;column = c;
	}
	void print(){
		printf("%f %d %d\n",score,row,column);
	}
};


struct comparator_structure{
	bool operator()(triple* a,triple* b){
		if(a && b){
			if(a->score > b->score)
				return true;
			else
				return false;
		}
		else{
			printf("Either one of the values is null. Check \n");
			return false;
		}
	}
};


class bot{
	int n;
	vector<vector<char> > board; // The board
	vector<int> colors; // Number of tiles left of valid colors
	vector<pair<int,int> > tilePos; //The position of tiles.
	bool order; //Whether order or chaos
	int maxdepth; //The max depth to which we can go(0,maxdepth), both inclusive.
	int totaltilesleft; // number of tiles left
	char tileToMinNode;
	int score;
	unordered_set<int> unvisited_cells;
	comparator_structure comparison;
	void setScore(){
	// TODO: RESET SCORE	
	}
	
	//Book keeping for maintaining actions
	
	//Order
	int initx,inity,finx,finy;
	
	//Chaos
	char tilecolor;
	int posx,posy;

public:
	
	bot(int n,bool ord):board(n,vector<char>(n,'W')){
		order = ord; // Unnecessary ? 
		this->n = n;
		colors.resize(n,n);
		maxdepth = 3; // Vary this to get different depths.
		totaltilesleft = 25;
		tileToMinNode = 'W';
		score = 0;
		initx=inity=finx=finy = posx=posy = -1;
		for(int i=0;i<n*n;i++)
			unvisited_cells.insert(i);
	}
	
	float expectiminimax(int state,int depth);	
	float utilityFunction();
	void playAsOrder(char TileUsedByChaos,int row,int col);
	void playAsChaos(char TileColorGiven);
};
#endif