#ifndef PLAYER_HPP
#define PLAYER_HPP
#include <iostream>
#include <algorithm>
#include <vector>
#include <unordered_set>
#include <limits>
#include <cmath>
#include <tuple>
using namespace std;

#define INF 5000000.0
#define MINF -5000000.0


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
	//comparator_structure comparison;
	
	int getScore(const string &s);
	int diff_order(int xini,int yini,int xfin,int yfin);
	int diff_chaos(int x,int y,char color);
    int initscore;
    float penalty;
	//Book keeping for maintaining actions
	
	//Order
	int initx,inity,finx,finy;
	
	//Chaos
	char tilecolor;
	int posx,posy;
	unordered_set<int> empty;
    bool firstMove;
    int updatePenaltyForRow(int initx,int inity);
    int updatePenaltyForColumn(int initx,int inity);
    int localdepth;
    vector<float> gammaArray;
    float gamma;
public:
	
	bot(int n,bool ord):board(n,vector<char>(n,'-')){
		order = ord; // Unnecessary ? 
		this->n = n;
		colors.resize(n,n);
        if(order)
            maxdepth = 3; // Vary this to get different depths.
        else
            maxdepth = 5;
		totaltilesleft = 25;
		tileToMinNode = '-';
		score = 0;
		initx=inity=finx=finy = posx=posy = -1;
		for(int i=0;i<n*n;i++)
			unvisited_cells.insert(i);
		errScore = numeric_limits<int>::max();
		firstMove = false;
		gammaArray.resize(10,1.0);
		gammaArray[0] = 2.0;
		if(order)
			gamma = 0.8;
		else
			gamma = 0.5;
		for(int i = i;i < 10;i++){
			gammaArray[i] = gammaArray[i-1] * gamma;
		}
	}
	
	float expectiminimax(int state,int depth,float alpha,float beta);
	float utilityFunction();
	void playAsOrder(char TileUsedByChaos,int row,int col);
	void playAsChaos(char TileColorGiven);
    void playAsChaos(char TileColorGiven,int initx,int inity,int finx,int finy);
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
	void moveTile(int initx,int inity,int finx,int finy);
    void placeTile(int posx,int posy,char C);
    void removeTile(int posx,int posy);
    void setDepth(int depth);
    
};
#endif