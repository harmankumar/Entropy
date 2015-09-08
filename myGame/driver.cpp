#include <iostream>
#include "player.hpp"
using namespace std;


int main(){
	int N; string player;
	cin>>N;
	cin>>player;
	int i = 0;
	bool order = (player == "ORDER");
	bot mBot(N,order);
	while(i<N*N){
		if(order){
			int row,col;
			char C;
			cin>>row>>col>>C;
			playAsOrder(C,row,col);
			i++;
		}
		else{
			char C;
			cin>>C;
			playAsChaos(C);
			i++;
		}
	}
	return 0;
}