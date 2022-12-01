/*
1. Compute Edit Distance Table
2. Show OPT path and Algorithms Path
3. Show Alignment of Chars as -,|,/,+,* denoting Left, Top, Diagonal, and Tie
4. ApproxAlgo used is -> At (i,j), move in direction from which min ED[i][j]+D/2 was obtained. Tie break is UP move.
*/
#include<iostream>
#include<vector>
#include<iomanip>
#include<string>
#include<float.h>

using namespace std;

/*
	Locate whether ED(i,j)+D/2 is underneath (i,j) or Left of (i,j)
	returns 'x' if x-index to be incremented and respt. 'y'
*/
char findNextMove(int i, int j, vector<vector<int> > & ED){
	float vert= ED[i][j],hor=ED[i][j];
    // ED[x'][j] underneath (i,j)
    for (int z=i;z>=0;z--){
        float U= ED[z][j] + (float)(i-z)/2;
        if(U < vert){
            vert= U;
        }
    }
    // ED[i][x'] left of (i,j)
    for (int z=j;z>=0;z--){
        float U= ED[i][z] + (float)(j-z)/2;
        if(U < hor){
            hor= U;
        }
    }
    //cout<<"Vert "<<vert<<"\n Hor "<<hor<<endl;
    if(vert < hor){
        return 'x';
    }
    else if ( vert > hor){
        return 'y';
    }
    else{
        return 'D';
    }
}

/*
* Finds approxED with designed Algorithm.
* AlgoPath has path by the Algorithm denoted by '.'
*/
int approxEditDistance(string x, string y,vector<vector<int> >&ED,vector<vector<char> >&algoPath){
	int i=1,j=1,u=0,m=x.length(),n=y.length();
	while(i<=n && j<=m){
		algoPath[i][j]='.';
        if(x[j-1]==y[i-1]){
			i++;
			j++;
		}
		else if(findNextMove(i,j,ED)=='x'){
            u++;
            j++;
        }
        else if(findNextMove(i,j,ED)=='y'){
            u++;
            i++;
        }
        else if(findNextMove(i,j,ED)=='D'){
            u++;
            i++;
            //j++;
        }
        //cout<<i<<" | "<<j<<" | "<<u<<endl;
	}
	int unprocessed_chars=0;
	if(i<=n || j <=m){
		if(n-i>=0)
			unprocessed_chars+=n-i+1;
		else if(m-j >= 0)
			unprocessed_chars+=m-j+1;
	}
	return u + unprocessed_chars;
};

void traceOptimumPath(int i, int j, vector<vector<char> > &align, vector<vector<char> > &optPath){
		if(i<1 || j<1)
			return;

		if(align[i][j]=='-'){
			traceOptimumPath(i,j-1,align,optPath);
			optPath[i][j-1]='O';
		}
		else if(align[i][j]=='|'){
			traceOptimumPath(i-1,j,align,optPath);
			optPath[i-1][j]='O';
		}
		else if(align[i][j]=='+'){
			traceOptimumPath(i,j-1,align,optPath);
			traceOptimumPath(i-1,j,align,optPath);
			optPath[i][j-1]='O';
			optPath[i-1][j]='O';
		}
		else if(align[i][j]=='/'){
			traceOptimumPath(i-1,j-1,align,optPath);
			optPath[i-1][j-1]='O';
		}
		else if(align[i][j]=='*'){
			traceOptimumPath(i,j-1,align,optPath);
			traceOptimumPath(i-1,j,align,optPath);
			traceOptimumPath(i-1,j-1,align,optPath);
			optPath[i][j-1]='O';
			optPath[i-1][j]='O';
			optPath[i-1][j-1]='O';
		}
}

void showOptAndAlgoPath(vector<vector<char> > &optPath, vector<vector<char> > &algoPath){
	//ToDo
	int m=optPath.size()-1,n=optPath[0].size()-1; // m=y.length
	for(int i=m;i>=0;i--){
		for(int j=0;j<=n;j++){
			if(optPath[i][j]=='O' && algoPath[i][j]=='.'){
				cout
				<<left
				<<setw(2)
				<<setfill(' ')
				<<'@';
			}
			else if(optPath[i][j]=='O' && algoPath[i][j]!='.'){
				cout
				<<left
				<<setw(2)
				<<setfill(' ')
				<<optPath[i][j];
			}
			else if(optPath[i][j]!='O' && algoPath[i][j]=='.'){
				cout
				<<left
				<<setw(2)
				<<setfill(' ')
				<<algoPath[i][j];
			}
			else{
				cout
				<<left
				<<setw(2)
				<<setfill(' ')
				<<algoPath[i][j];
			}

		}
		cout<<endl;
	}
	cout<<endl;
}

int main(){

	string
	
//x="0111011001",
//y="1101011001"; //Gives approx factor = 4.5 with new strategy of tie breaking
//x="00010110110001001001",
//y="00101011011000100001";
//x="010010010110011100110000011101100100010110110001001000100000100010000",
//y="010010011101100111110000110101100100101011011000100001000010000010000";
//x="0100111011001|0101010101",
//y="1011101011001|0101010110";
//x="11010001001001101000010110110001001001",
//y="1010001010010011010001010110110001001";
//x="0111100110110110101001001000100000011",//
//y="0111001010110110101001001000100000011";// Approx factor = 14
//x="1100001110110110101010110110111011100010",
//y="1100011010110110101010110110111011100010";
//x="0010110110101001010110110111010100010000",
//y="0001011011010101010110110111010100010000";
//x="110100100101010110110101010010",
//y="101010010010101010110101010010";
// x="111011011101111011000101011010",
// y="110101101110111101100101011010";
//x="0011101100101011", //Bug approx factor = 0.5
//y="0001110110010101";
//x="111011011001110111010011011101",
//y="110100001101100111010011011101";
//x="aaaaaabcdefghijklmnopqrstuvwxyz",
//y="aaaaaaijklmnopqrstuvwxyz";
//x="abcdefgh",
//y="bcdefgh";
//x="01001110110010100111011001",
//y="11101100101001110110010100";
//x="010010010110011100110000",
//y="010010011101100111110000";
//x="abcdefghijklmnabcdefghijklmnabcdefghijklmnabcdefghijklmnabcdefghijklmn",
//y="hijklmnabcdefghijklmnabcdefghijklmnabcdefghijklmnabcdefghijklmnabcdefg";
x="01000111100100011110010001111001000111100100011110",
y="11110010001111001000111100100011110010001111001000";
	//cin>>x;
	int n=x.length();
	//cout<<"String Y: \n";
	//cin>>y;
	int m=y.length();
	vector<vector<int> > ED(m+1,vector<int>(n+1,0));
	vector<vector<char> > align(m+1,vector<char>(n+1,' ')); //Alignment Vector
	for(int i=0;i<=m;i++){
		for(int j=0;j<=n;j++){
			if(i==0){
				ED[i][j]=j;
				align[i][j]='-'; //Alignment
			}
			else if(j==0){
				ED[i][j]=i;
				align[i][j]='|'; //Alignment
			}
			else if(x[j-1]==y[i-1]){
				ED[i][j]=min(1+min(ED[i][j-1],ED[i-1][j]) ,ED[i-1][j-1]);

				//Alignment
				if(ED[i-1][j]==ED[i][j-1] && ED[i-1][j-1] == 1+ED[i-1][j]){ //All EQUAL alignment=*
					align[i][j]='*';
				}
				else if(ED[i-1][j-1] < 1+ min(ED[i-1][j],ED[i][j-1])){ // Diagonal = /
					align[i][j]='/';
				}
				else if(ED[i-1][j] == ED[i][j-1]){ // both ways
					align[i][j]='+';
				}
				else if(ED[i-1][j] < ED[i][j-1]){ // Bottom = |
					align[i][j]='|';
				}
				else{
					align[i][j]='-';
				}
			}
			else{ // x[j-1]!=y[i-1]
				ED[i][j]=min(1+min(ED[i][j-1],ED[i-1][j]) , 1+ ED[i-1][j-1]);


				if(ED[i-1][j]==ED[i][j-1] && ED[i-1][j-1] == ED[i-1][j]){ //All EQUAL alignment=*
					align[i][j]='*';
				}
				else if(ED[i-1][j-1] < min(ED[i-1][j],ED[i][j-1])){ // Diagonal = /
					align[i][j]='/';
				}
				else if(ED[i-1][j] == ED[i][j-1]){ // both ways
					align[i][j]='+';
				}
				else if(ED[i-1][j] < ED[i][j-1]){ // Bottom = |
					align[i][j]='|';
				}
				else{
					align[i][j]='-';
				}
			}
		}
	}
	// Save AlgoPath in algoPath
	vector<vector<char> > algoPath(m+1,vector<char>(n+1,' '));
	algoPath=align;
	int approxED=approxEditDistance(x,y,ED,algoPath);

	// Trace the optimum path by ED algorithm
	vector<vector<char> > optPath(m+1,vector<char>(n+1,' '));
	optPath=align;
	traceOptimumPath(m,n,align,optPath);
	optPath[m][n]='O';

	// PRINT TABLE WITH ALIGNMENT
	for(int i=m;i>=0;i--){
		for(int j=0;j<=n;j++){
			cout
			<<left
			<<setw(2)
			<<setfill(' ')
			<<ED[i][j];//+to_string(ED[i][j]);
		}
		cout<<endl;
	}


	cout<<"Edit Distance = "<<ED[m][n]<<endl;
	cout<<"Approx Edit Distance = "<<approxED<<endl;
	cout<<"Approximation Factor = "<<(float)approxED/ED[m][n]<<endl;
	cout<<endl;
	showOptAndAlgoPath(optPath,algoPath);
	cout<<endl<<"X: "<<x<<endl<<"Y: "<<y<<endl;
	return 0;
}
