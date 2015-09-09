#ifndef PLAYER_HPP
#define PLAYER_HPP
#include <iostream>
#include <algorithm>
#include <vector>
#include <unordered_set>
#include <limits>
using namespace std;

#define INF 5000000.0
#define MINF -5000000.0

struct triple{
	int first;int second;int third;
	triple(int a,int b,int c){
		first = a;second = b;third = c;
	}
	void print(){
		printf("%d %d %d\n",first,second,third);
	}
};


struct comparator_structure{
	bool operator()(triple* a,triple* b){
		if(a && b){
			if(a->first > b->first)
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
	int errScore;
	vector<vector<char> > board; // The board
	vector<int> colors; // Number of tiles left of valid colors
	
	bool order; //Whether order or chaos
	int maxdepth; //The max depth to which we can go(0,maxdepth), both inclusive.
	int totaltilesleft; // number of tiles left
	char tileToMinNode;
	int score;
	unordered_set<int> unvisited_cells;
	unordered_set<int> visited_cells;
	comparator_structure comparison;
	int movedTile;
	
	int getscore(string s);
	int diff_order(int xini,int yini,int xfin,int yfin);
	int diff_chaos(int x,int y,char color);
	
	//Book keeping for maintaining actions
	
	//Order
	int initx,inity,finx,finy;
	
	//Chaos
	char tilecolor;
	int posx,posy;

public:
	
	bot(int n,bool ord):board(n,vector<char>(n,'-')){
		order = ord; // Unnecessary ? 
		this->n = n;
		movedTile = -1;
		colors.resize(n,n);
		maxdepth = 3; // Vary this to get different depths.
		totaltilesleft = 25;
		tileToMinNode = '-';
		score = 0;
		initx=inity=finx=finy = posx=posy = -1;
		for(int i=0;i<n*n;i++)
			unvisited_cells.insert(i);
		errScore = numeric_limits<int>::max();
	}
	
	float expectiminimax(int state,int depth);	
	float utilityFunction();
	void playAsOrder(char TileUsedByChaos,int row,int col);
	void playAsChaos(char TileColorGiven);
	void printBoard(){
		for(int i=0;i<n;i++){
			for(int j=0;j<n;j++){
				if(board[i][j] == '-')
					cout<<'-';
				else
					cout<<board[i][j];
				cout<<" ";
			}
			cout<<"\n";
		}
	}
};
#endif