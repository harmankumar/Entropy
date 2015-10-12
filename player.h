#ifndef PLAYER_HPP
#define PLAYER_HPP
#include "gameNodes.h"
#include <vector>
#include <iostream>
#include <unordered_set>
#include <algorithm>

#define set_it unordered_set<int>::const_iterator
#define INF 50000000.0
#define MINF -50000000.0
using namespace std;

class entropy{

	void getMovementsChaos(vector<chaosNode*> &);
	void getMovementsOrder(vector<orderNode*> &);
	float maxnode(int depth,float alpha,float beta);
	float chancenode(int depth,float alpha,float beta);
	float minnode(int depth,float alpth,float beta);
	void moveTile(int initx,int inity,int finx,int finy);
	void placeTile(int posx,int posy,char color);
	void removeTile(int posx,int posy);
	int getScore(const string&);
	int diff_order(int,int,int,int);
	int diff_chaos(int,int,char);
	float utilityFunction();
	compareOrder comparator_order;
	compareChaos comparator_chaos;
	vector<vector<char> > board;
	int n;
	bool order,firstMove;
	unordered_set<int> visited_cells;
	unordered_set<int> empty_cells;
	vector<unordered_set<int> > tileLocations;
	int score;
	int maxdepth;
	int tilesLeft;
	vector<int> tileOfEachColor;
	char tileToMinNode;
	int ix,iy,fx,fy,px,py;
public:
	entropy(int,bool);
	void playAsOrder(int posx,int posy,char color);
	void playAsChaos(char tile);
	void playAsChaos(int initx,int inity,int finx,int finy,char color);
	void printBoard();
	void setDepth(int);
	int skipcount();
};



#endif