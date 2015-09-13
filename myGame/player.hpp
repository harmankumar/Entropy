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

	//float alpha,beta;
    float epsilon;
	
	int getscore(string s);
	int diff_order(int xini,int yini,int xfin,int yfin);
	int diff_chaos(int x,int y,char color);
    
    bool debug_flag;
	
	//Book keeping for maintaining actions
	
	//Order
	int initx,inity,finx,finy;
	
	//Chaos
	char tilecolor;
	int posx,posy;
	int scattering;
	vector<unordered_set<int> > mapping;
    float boundChanceNode(int i);

public:
	
	bot(int n,bool ord):board(n,vector<char>(n,'-')) , mapping(5){
		order = ord; // Unnecessary ? 
		this->n = n;
		movedTile = -1;
        epsilon = 2.0;
		scattering = 0;
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
        debug_flag = false;
        scattering = 0;
      
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
    int tentative_palindrome_count();
    int skipCount();
    
};
#endif