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
            i++;
		}
		else{
			char C;
            int initx,inity,finx,finy;
            if(i==0){
                cin>>C;
                mBot.playAsChaos(C);
                
            }
            else{
                cin>>initx>>inity>>finx>>finy>>C;
                mBot.playAsChaos(C,initx,inity,finx,finy);
            }
            i++;
			
		}
		mBot.printBoard();
	}
	return 0;
}