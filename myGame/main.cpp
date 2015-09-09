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
			mBot.playAsOrder(C,row,col);
            if(row == 4 && col== 0 )
                
			i++;
		}
		else{
			char C;
			cin>>C;
			mBot.playAsChaos(C);
			i++;
		}
		mBot.printBoard();
	}
	return 0;
}