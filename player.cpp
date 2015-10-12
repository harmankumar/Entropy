#include "player.h"

entropy::entropy(int boardsize,bool asOrder){
	n = boardsize;
	order = asOrder;
	firstMove = false;
	board.resize(n,vector<char>(n,'-'));
	for(int i=0;i<n*n;i++)
		empty_cells.insert(i);
	maxdepth = 3;
	tileOfEachColor.resize(5,5);
	tilesLeft = 25;
	tileToMinNode = '-';
    tileLocations.resize(n,unordered_set<int>());
}

void entropy::printBoard(){
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++)
			cout<<board[i][j]<<" ";
		cout<<"\n";
	}

}

void entropy::setDepth(int depth){
	maxdepth = depth;
}

int entropy::diff_order(int initx,int inity,int finx,int finy){
	int difference = 0;
	string topWord,bottomWord,leftWord,rightWord;
	topWord = bottomWord = leftWord = rightWord = "";
	int y = inity + 1;
	while(y < n){
		if(board[initx][y] == '-')
			break;
		else{
			rightWord+=board[initx][y];
			y++;
		}
	}
	int x = initx + 1;
	while(x < n){
		if(board[x][inity] == '-')
			break;
		else{
			bottomWord+=board[x][inity];
			x++;
		}
	}
	y = inity - 1;
	while(y >= 0){
		if(board[initx][y] == '-')
			break;
		else{
			y--;
		}
	}
	y++;
	while(y != inity)
		leftWord+=board[initx][y++];
	
	x = initx - 1;
	while(x>=0){
		if(board[x][inity] == '-')
			break;
		else{
			x--;
		}
	}
	x++;
	while(x!=initx)
		topWord+=board[x++][inity];
	
	
	string completeWord = leftWord + board[initx][inity] + rightWord;
	difference = difference - getScore(completeWord) + getScore(leftWord) + getScore(rightWord);
	completeWord = topWord + board[initx][inity] + bottomWord;
	difference = difference - getScore(completeWord) + getScore(topWord) + getScore(bottomWord);
	char color = board[initx][inity];
	board[initx][inity] = '-';

	topWord = bottomWord = leftWord = rightWord = "";
	y = finy + 1;
	while(y < n){
		if(board[finx][y] == '-')
			break;
		else{
			rightWord+=board[finx][y];
			y++;
		}
	}
	x = finx + 1;
	while(x < n){
		if(board[x][finy] == '-')
			break;
		else{
			bottomWord+=board[x][finy];
			x++;
		}
	}
	y = finy - 1;
	while(y >= 0){
		if(board[finx][y] == '-')
			break;
		else{
			y--;
		}
	}
	y++;
	while(y != finy)
		leftWord+=board[finx][y++];
	
	x = finx - 1;
	while(x>=0){
		if(board[x][finy] == '-')
			break;
		else{
			x--;
		}
	}
	x++;
	while(x != finx)
		topWord+=board[x++][finy];
	
	completeWord = leftWord + color + rightWord;
	difference = difference + getScore(completeWord) - getScore(leftWord) - getScore(rightWord);
	completeWord = topWord + color + bottomWord;
	
	difference = difference + getScore(completeWord) - getScore(topWord) - getScore(bottomWord);
	board[initx][inity] = color;
	return difference;

}

int entropy::diff_chaos(int posx,int posy,char color){
	string topWord,bottomWord,leftWord,rightWord;
	topWord = bottomWord = leftWord = rightWord = "";
	int difference = 0;
	int y = posy + 1;
	while(y < n){
		if(board[posx][y] == '-')
			break;
		else{
			rightWord+=board[posx][y];
			y++;
		}
	}
	int x = posx + 1;
	while(x < n){
		if(board[x][posy] == '-')
			break;
		else{
			bottomWord+=board[x][posy];
			x++;
		}
	}
	y = posy - 1;
	while(y >= 0){
		if(board[posx][y] == '-')
			break;
		else{
			y--;
		}
	}
	y++;
	while(y!=posy)
		leftWord+=board[posx][y++];

	x = posx - 1;
	while(x>=0){
		if(board[x][posy] == '-')
			break;
		else{
			x--;
		}
	}
	x++;
	while(x!=posx)
		topWord+=board[x++][posy];
	
	string completeWord = leftWord + color + rightWord;
	difference = difference + getScore(completeWord) - getScore(leftWord) - getScore(rightWord);
	completeWord = topWord + color + bottomWord;
	difference = difference + getScore(completeWord) - getScore(topWord) - getScore(bottomWord);
	return difference;
}

int entropy::getScore(const string & s){
	int n = s.length();
	int left,right;
	int counter = 0;
	for(int i=0;i<n-1;i++){
		left = i-1;
		right = i+1;
		while(left >= 0 && right < n ){
			if(s[left] == s[right]){
				counter+= right - left + 1;
				left--;
				right++;
			}
			else{
				break;
			}
		}
		left = i;
		right = i+1;
		while(left >=0 && right < n){
			if(s[left] == s[right]){
				counter+= right - left + 1;
				left--;
				right++;
			}
			else{
				break;
			}
		}
	}
	return counter;
}


void entropy::moveTile(int initx,int inity,int finx,int finy){
	char color = board[initx][inity];
	removeTile(initx,inity);
	placeTile(finx,finy,color);
}

void entropy::placeTile(int posx,int posy,char color){
	if(board[posx][posy] != '-')
		return;
	board[posx][posy] = color;
	tilesLeft--;
	tileOfEachColor[color-65]--;
	int tileIdx = n*posx + posy;
	visited_cells.insert(tileIdx);
	empty_cells.erase(tileIdx);
	tileLocations[color-65].insert(tileIdx);
}

void entropy::removeTile(int posx,int posy){
	if(board[posx][posy] == '-')
		return;
	char color = board[posx][posy];
	board[posx][posy] = '-';
	tilesLeft++;
	tileOfEachColor[color-65]++;
	int tileIdx = n*posx + posy;
	visited_cells.erase(tileIdx);
	empty_cells.insert(tileIdx);
	tileLocations[color-65].erase(tileIdx);
}

void entropy::getMovementsOrder(vector<orderNode*> & movements){
	bool flag = false;
	for(set_it it = visited_cells.begin(); it != visited_cells.end();it++){
		int row = (*it) / n;
		int col = (*it) % n;
		if(!flag){
			flag = true;
			movements.push_back(new orderNode(0,0,row,col,row,col));
		}
		int i = col + 1;
		while( i < n){
			if(board[row][i] != '-')
				break;
			else{
				int scoreDiff = diff_order(row,col,row,i);
				movements.push_back(new orderNode(scoreDiff,0,row,col,row,i));
                i++;
			}
		}
		i = col - 1;
		while(i>=0){
			if(board[row][i] != '-')
				break;
			else{
				int scoreDiff = diff_order(row,col,row,i);
				movements.push_back(new orderNode(scoreDiff,0,row,col,row,i));
                i--;
			}
		}
		i = row + 1;
		while(i < n){
			if(board[i][col] != '-')
				break;
			else{
				
				int scoreDiff = diff_order(row,col,i,col);
				movements.push_back(new orderNode(scoreDiff,0,row,col,i,col));
                i++;
			}
		}
		i = row - 1;
		while(i>=0){
			if(board[i][col] != '-')
				break;
			else{
				
				int scoreDiff = diff_order(row,col,i,col);
				movements.push_back(new orderNode(scoreDiff,0,row,col,i,col));
                i--;
			}
		}
	}
	sort(movements.begin(),movements.end(),comparator_order);
}

void entropy::getMovementsChaos(vector<chaosNode*> & movements){
	for(set_it it = empty_cells.begin();it != empty_cells.end();it++){
		int row  = (*it) / n;
		int col = (*it) % n;
		int scoreDiff = diff_chaos(row,col,tileToMinNode);
		movements.push_back(new chaosNode(scoreDiff,0,row,col));
	}
	sort(movements.begin(),movements.end(),comparator_chaos);
} 

float entropy::maxnode(int depth,float alpha,float beta){
	if(depth == maxdepth)
		return utilityFunction();
	vector<orderNode*> movements;
	getMovementsOrder(movements);
	if(movements.size() == 0)
		return utilityFunction();
	float v = MINF;
	for(int i=0;i<movements.size();i++){
		int initx = movements[i]->initx,inity = movements[i]->inity,finx=movements[i]->finx,finy=movements[i]->finy,scoreDiff = movements[i]->scoreDiff;
		score+=scoreDiff;
		moveTile(initx,inity,finx,finy);
		float val = chancenode(depth+1,alpha,beta);
		moveTile(finx,finy,initx,inity);
		score-=scoreDiff;
		if(val > v){
			v = val;
			if(depth == 0){
				ix = initx;
				iy = inity;
				fx = finx;
				fy = finy;
			}
		}
		/*alpha = (alpha > v) ? alpha : v;
		if(alpha >= beta){
			movements.clear();
			return v; 
		}*/
	}
	return v;
}

float entropy::chancenode(int depth,float alpha,float beta){
	if(depth == maxdepth)
		return utilityFunction();
	float expectedValue = 0.0;
	for(int i = 0;i < n;i++){
		if(tileOfEachColor[i] == 0)
			continue;
		else{
			float prob = tileOfEachColor[i] / float(tilesLeft);
			tileToMinNode = i+65;
			expectedValue += prob * minnode(depth+1,alpha,beta);
		}
	}
	return expectedValue;
}

float entropy::minnode(int depth,float alpha,float beta){
	if(maxdepth == depth)
		return utilityFunction();
	vector<chaosNode*> movements;
	getMovementsChaos(movements);
	if(movements.size() ==0)
		return utilityFunction();
	float v = INF;
	for(int i = 0;i < movements.size();i++){
		int posx = movements[i]->posx, posy = movements[i]->posy, scoreDiff = movements[i]->scoreDiff;
		placeTile(posx,posy,tileToMinNode);
		score+=scoreDiff;
		float val = maxnode(depth+1,alpha,beta);
		score-=scoreDiff;
		removeTile(posx,posy);
		if(val < v){
			v = val;
			if(depth==0){
				px = posx;
				py = posy;
			}
		}
		/*beta = (beta < v) ? beta : v;
		if(alpha >= beta){
			movements.clear();
			return v;	
		}*/	
	}
	return v;
}

float entropy::utilityFunction(){
		return score;
}



void entropy::playAsOrder(int posx,int posy,char color){
	score = 0;
	placeTile(posx,posy,color);
	ix = iy = fx = fy = -1;
	maxnode(0,MINF,INF);
	moveTile(ix,iy,fx,fy);
	printf("%d %d %d %d\n",ix,iy,fx,fy);
}

void entropy::playAsChaos(char color){
	if(!firstMove){
		firstMove = true;
		printf("%d %d\n",4,4);
		placeTile(4,4,color);
		return;
	}
	px = py = -1;
	score = 0;
	tileToMinNode = color;
	minnode(0,MINF,INF);
	placeTile(px,py,color);
	printf("%d %d\n",px,py);
}

void entropy::playAsChaos(int initx,int inity,int finx,int finy,char color){
	moveTile(initx,inity,finx,finy);
	playAsChaos(color);
}



int entropy::skipcount(){
	int counter = 0;
	for(int i=0;i<n;i++){
		for(int j=0;j<n-2;j++){
			if(board[i][j] == board[i][j+2] && board[i][j+1] == '-' ){
				if(board[i][j] != '-')
					counter ++;
			}
			if(board[j][i] == board[j+2][i] && board[j+1][i] == '-'){
				if(board[j][i] != '-')
					counter++;	
			}
		}
	}
	for(int i=0;i<n;i++){
		if(board[i][0] == board[i][2] && board[i][2] == board[i][4] && board[i][1]=='-' && board[i][3]=='-'){
			if(board[i][0] != '-')
				counter+=1;
		}
		if(board[0][i] == board[2][i] && board[2][i] == board[4][i] && board[1][i] == '-' && board[3][i]=='-'){
			if(board[0][i] != '-')
				counter+=1;
		}


	}
	return counter;
}



/*



void bot::playAsChaos(char color){
	if(!firstMove){
		firstMove = true;
		addTile(4,4,color);
		printf("%d %d\n",4,4);
		return;
	}
	tileToMinNode = color;
    
    posx = posy = -1;
	initScore = score;
    expectiminimax(2,0,MINF,INF);
	
	score += diff_chaos(posx,posy,color);
    addTile(posx, posy, color);
	
    printf("%d %d\n",posx,posy);
}


void bot::playAsChaos(int initx,int inity,int finx,int finy,char color){
	score += diff_order(initx,inity,finx,finy);
    char colour = board[initx][inity];
    rollingUtility = removingTileUtility(initx, inity) + placingTileUtility(finx, finy, colour);
    moveTile(initx, inity, finx, finy);

    playAsChaos(color);
}

void bot::playAsOrder(char color,int posx,int posy){
	score += diff_chaos(posx,posy,color);
	rollingUtility = placingTileUtility(posx,posy, color);
    addTile(posx,posy,color);
	initx = inity = finx = finy = -1;
	initScore = score;
	expectiminimax(0,0,MINF,INF);

	score+=diff_order(initx,inity,finx,finy);
	moveTile(initx,inity,finx,finy);
	printf("%d %d %d %d\n",initx,inity,finx,finy);

}
void bot::printBoard(){
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++)
			cout<<board[i][j]<<" ";
		cout<<"\n";
	}
}
void bot::setDepth(int depth){
	maxdepth = depth;
}

float bot::expectiminimax(int state,int depth,float alpha,float beta){
	
    if(depth == maxdepth)
		return utilityFunction();
	if(state == 0){
		//max nodes
		vector<orderNode*> score_and_movements;
		for(unordered_set<int>::const_iterator it = visited.begin();it != visited.end(); it++){
			int row = (*it) / n;
			int col = (*it) % n;
            char color = board[row][col];
			score_and_movements.push_back(new orderNode(0,0,row,col,row,col));
			int i = col + 1;
			while(i < n){
				if(board[row][i] != '-')
					break;
				else{
					int diffScore = diff_order(row,col,row,i);
                    
                    int utilityDiff = placingTileUtility(row, i,color) + removingTileUtility(row, col);
					score_and_movements.push_back(new orderNode(diffScore,utilityDiff,row,col,row,i));
					i++;
				}
			}
			i = col - 1;
			while(i >=0 ){
				if(board[row][i] != '-')
					break;
				else{
					int diffScore = diff_order(row,col,row,i);
                    int utilityDiff = placingTileUtility(row, i,color) + removingTileUtility(row, col);
					score_and_movements.push_back(new orderNode(diffScore,utilityDiff,row,col,row,i));
					i--;
				}
			}
			i = row + 1;
			while(i < n){
				if(board[i][col] != '-')
					break;
				else{
					int diffScore = diff_order(row,col,i,col);
                    int utilityDiff = placingTileUtility(row, i,color) + removingTileUtility(row, col);
					score_and_movements.push_back(new orderNode(diffScore,utilityDiff,row,col,i,col));
					i++;
				}
			}
			i = row - 1;
			while(i>=0){
				if(board[i][col] != '-')
					break;
				else{
					int diffScore = diff_order(row,col,i,col);
                    int utilityDiff = placingTileUtility(row, i,color) + removingTileUtility(row, col);
					score_and_movements.push_back(new orderNode(diffScore,utilityDiff,row,col,i,col));
					i--;
				}
			}

		}
		if(score_and_movements.size()==0)
			return utilityFunction();
		
		sort(score_and_movements.begin(),score_and_movements.end(),comparator_one);
		
		float globalMax = alpha;
		for(int i=0;i<score_and_movements.size();i++){
			int scoreDiff = score_and_movements[i]->scoreDiff;
            int utilityDiff = score_and_movements[i]->utility;
			int currRow = score_and_movements[i]->initx;
			int currCol = score_and_movements[i]->inity;
			int newRow = score_and_movements[i]->finx;
			int newCol = score_and_movements[i]->finy;

			score += scoreDiff;
            rollingUtility += utilityDiff;
			moveTile(currRow,currCol,newRow,newCol);
			float localmax = expectiminimax((state+1)%3,depth+1,alpha,beta);
			moveTile(newRow,newCol,currRow,currCol);
			score -= scoreDiff;
            rollingUtility -= utilityDiff;
			if(localmax > globalMax){
				globalMax = localmax;
				if(depth == 0){
					initx = currRow;inity = currCol;finx = newRow;finy = newCol;
				}
			}
			alpha = (alpha > globalMax) ? alpha : globalMax;
			if(depth <= 1){
                if(alpha > beta){
                    score_and_movements.clear();
					return globalMax;
                }
			}
			else{
                if(alpha >= beta){
                    score_and_movements.clear();
					return globalMax;
                }
			}
		}
        score_and_movements.clear();
		return globalMax;
	}
	else if(state == 1){
		// chance node
		float expectedValue = 0.0;
		for(int i=0;i<n;i++){
			tileToMinNode = 65 + i;
			float prob = float(colors[i]) / totalTilesLeft;
			if(prob > 0.0001)
				expectedValue += prob * expectiminimax((state+1)%3,depth+1,alpha,beta);
		}
		return expectedValue;
	}
	else {
		//min node
		vector<chaosNode*> score_and_movements;
		for(unordered_set<int>::const_iterator it = empty.begin(); it != empty.end();it++){
			int row = (*it) / n;
			int col = (*it) % n;
			int scoreDiff = diff_chaos(row,col,tileToMinNode);
            int utilityDiff = placingTileUtility(row, col,tileToMinNode);
			score_and_movements.push_back(new chaosNode(scoreDiff,utilityDiff,row,col));
		}
		if(score_and_movements.size()==0)
			return utilityFunction();
		
		sort(score_and_movements.begin(),score_and_movements.end(),comparator_two);
		float globalMin = beta;
		for(int i=0;i<score_and_movements.size();i++){
			int scoreDiff = score_and_movements[i]->scoreDiff;
            int utilityDiff = score_and_movements[i]->utility;
			int row = score_and_movements[i]->posx;
			int col = score_and_movements[i]->posy;
			score+=scoreDiff;
            rollingUtility+=utilityDiff;
			addTile(row,col,tileToMinNode);	
			float localmin = expectiminimax((state+1)%3,depth+1,alpha,beta);
			removeTile(row,col);
			score-=scoreDiff;
            rollingUtility-=utilityDiff;
			
            if(localmin < globalMin){
				globalMin = localmin;
				if(depth==0){
					posx = row;posy = col;
				}
			}
			beta = (beta < globalMin) ? beta : globalMin;
			if(depth <=1){
                if(alpha > beta){
                    score_and_movements.clear();
					return globalMin;
                }
			}
			else{
                if(alpha >= beta){
                    score_and_movements.clear();
					return globalMin;
                }
			}
		}
        score_and_movements.clear();
		return globalMin;
	}
}


float bot::utilityFunction(){
	float value = score - initScore;
    if(!order)
        value += 1.5*rollingUtility;
	/*if(totalTilesLeft != 0){
		for(unordered_set<int>::const_iterator it = empty.begin();it != empty.end();it++){
			int row = (*it) / n;
			int col = (*it) % n;
			for(int i=0;i<n;i++){
				char color = i + 65;
				if(colors[i] != 0)
					value = value + ((float(colors[i]) / totalTilesLeft) * diff_chaos(row,col,color));
			}
		}
	}
	for(unordered_set<int>::const_iterator it = visited.begin();it != visited.end();it++){
		int row = (*it) / n;
		int col = (*it) % n;
		int i = row + 1;
		int localmax = 0;
		while(i<n){
			if(board[i][col] != '-')
				break;
			else{
				int tempVal = diff_order(row,col,i,col);
				localmax = (localmax > tempVal) ? localmax : tempVal;
				i++;
			}
		}
		i = col + 1;
		while(i < n){
			if(board[row][i] != '-')
				break;
			else{
				int tempVal = diff_order(row,col,row,i);
				localmax = (localmax > tempVal) ? localmax : tempVal;
				i++;
			}
		}
		i = row - 1;
		while(i >=0 ){
			if(board[i][col] != '-')
				break;
			else{
				int tempVal = diff_order(row,col,i,col);
				localmax = (localmax > tempVal) ? localmax : tempVal;
				i--;
			}
		}
		i = col - 1;
		while(i >= 0){
			if(board[row][i] != '-')
				break;
			else{
				int tempVal = diff_order(row,col,row,i);
				localmax = (localmax > tempVal) ? localmax : tempVal;
				i--;
			}
		}
		value += localmax;
	}
	return value;
}
int bot::placingTileUtility(int posx, int posy,char color){
    
    char temp = board[posx][posy];
    board[posx][posy] = color;
    int threeUtility = 0;
    if(posy == 0 || posy == 1){
        if(board[posx][posy] == board[posx][posy + 2] && board[posx][posy+1]=='-'){
            threeUtility++;
        }
        if(posy == 0 && board[posx][4] == board[posx][0] && board[posx][3] == '-')
            threeUtility+=2;
    }
    else if(posy == 3 || posy == 4){
        if(board[posx][posy] == board[posx][posy-2] && board[posx][posy-1]=='-'){
            threeUtility++;
        }
        if(posy == 4 && board[posx][0] == board[posx][posy] && board[posx][1] =='-')
            threeUtility+=2;
    }
    else{
        int count = 0;
        if(board[posx][posy] == board[posx][posy + 2] && board[posx][posy+1]=='-'){
            threeUtility++;
            count++;
        }
        if(board[posx][posy] == board[posx][posy-2] && board[posx][posy-1]=='-'){
            threeUtility++;
            count++;
        }
        if(count == 2)
            threeUtility+=2;
    }
    if(posx == 0 || posx == 1){
        if(board[posx][posy] == board[posx+2][posy] && board[posx+1][posy]=='-'){
            threeUtility++;
        }
        if(posx==0 && board[0][posy] == board[4][posy] && board[3][posy] == '-')
            threeUtility+=2;
    }
    else if(posx == 3 || posx == 4){
        if(board[posx][posy] == board[posx-2][posy] && board[posx-1][posy]=='-'){
            threeUtility++;
        }
        if(posx==4 && board[0][posy] == board[4][posy] && board[1][posy] == '-')
            threeUtility+=2;
    }
    else{
        int count = 0;
        if(board[posx][posy] == board[posx+2][posy] && board[posx+1][posy]=='-'){
            threeUtility++;
            count++;
        }
        if(board[posx][posy] == board[posx-2][posy] && board[posx-1][posy]=='-'){
            threeUtility++;
            count++;
        }
        if(count==2)
            threeUtility+=2;
    }
    
    
    board[posx][posy] = temp;
    return threeUtility;
}
int bot::removingTileUtility(int posx, int posy){
    int threeUtility = 0;
    
    if(posy == 0 || posy == 1){
        if(board[posx][posy] == board[posx][posy + 2] && board[posx][posy+1]=='-'){
            threeUtility--;
        }
        if(posy == 0 && board[posx][4] == board[posx][0] && board[posx][3] == '-')
            threeUtility-=2;
    }
    else if(posy == 3 || posy == 4){
        if(board[posx][posy] == board[posx][posy-2] && board[posx][posy-1]=='-'){
            threeUtility--;
        }
        if(posy == 4 && board[posx][0] == board[posx][posy] && board[posx][1] =='-')
            threeUtility-=2;
    }
    else{
        int count = 0;
        if(board[posx][posy] == board[posx][posy + 2] && board[posx][posy+1]=='-'){
            threeUtility--;
            count++;
        }
        if(board[posx][posy] == board[posx][posy-2] && board[posx][posy-1]=='-'){
            threeUtility--;
            count++;
        }
        if(count == 2)
            threeUtility-=2;
    }
    if(posx == 0 || posx == 1){
        if(board[posx][posy] == board[posx+2][posy] && board[posx+1][posy]=='-'){
            threeUtility--;
        }
        if(posx==0 && board[0][posy] == board[4][posy] && board[3][posy] == '-')
            threeUtility-=2;
    }
    else if(posx == 3 || posx == 4){
        if(board[posx][posy] == board[posx-2][posy] && board[posx-1][posy]=='-'){
            threeUtility--;
        }
        if(posx==4 && board[0][posy] == board[4][posy] && board[1][posy] == '-')
            threeUtility-=2;
    }
    else{
        int count = 0;
        if(board[posx][posy] == board[posx+2][posy] && board[posx+1][posy]=='-'){
            threeUtility--;
            count++;
        }
        if(board[posx][posy] == board[posx-2][posy] && board[posx-1][posy]=='-'){
            threeUtility--;
            count++;
        }
        if(count==2)
            threeUtility-=2;
    }
    return threeUtility;
}

*/