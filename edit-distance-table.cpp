#include<iostream>
#include<vector>
#include<iomanip>


using namespace std;
/*
* Finds approxED with designed Algorithm.
* Replaces Align[i][j] with # highlighting the path by the Algorithm.
*/
int approxEditDistance(vector<vector<char> > &align, string x, string y,vector<vector<char> >&algoPath){
	int i=1,j=1,u=0,m=x.length(),n=y.length();
	while(i<=n && j<=m){
		algoPath[i][j]='.';
		if(x[j-1]==y[i-1]){
			i++;
			j++;
		}
		else{
			u++;
			if(align[i][j]=='|'){ // Go Up on
				j++;
			}
			else if(align[i][j]=='-'){
				i++;
			}
			else if(align[i][j]=='+'){ // Tie breaker
				j++;
			}
			else{
				i++;
				j++;
			}
			//cout<<i<<" : "<<j<<": "<<u<<endl;
		}
	}
	int unprocessed_chars=0;
	if(i<n || j <m){
		if(n-i>0)
			unprocessed_chars+=n-i;
		else if(m-j > 0)
			unprocessed_chars+=m-j;
	}
	return u+ unprocessed_chars;
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
	//x="377983722676523043163724904147708069694985201921063119571283049859400604220352146333975113375728503594148610756360741014817528800820666286894043795908954361308468594758592613205696384344294961025972171337572850359414861075636074101481752880082066628689404379590895436130846859475859261320569638434429496102597217",
	//y="377514143931007465839742569924776101736572452559733364840538364798478318617582392264971811748422741305672228877700112854487260264513275048351882707236905932436140742562981532510658013996976818774500541337572850359414861075636074101481752880082066628689404379590895436130846859475859261320569638434429496102597217";
	//x="amithiamithiamithi",
	//y="thiamithiamithiami";   //Approx Factor=2 with above x
//x="abcdefghijklmnopqrstuvwxyz",
//y="zyxwvutsrqponmlkjihgfedcba";
//x="abcdefghij",
//y="fedcba";
y="0111011001",
x="1101011001"; //Gives approx factor = 4.5 with new strategy of tie breaking
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


				/*if(1+min(ED[i][j-1],ED[i-1][j]) > ED[i-1][j-1])
					align[i][j]='/';
				else{
					if(ED[i][j-1] > ED[i-1][j])
						align[i][j]='-'; L
					else
						align[i][j]='|';
				}*/
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
	int approxED=approxEditDistance(align,x,y,algoPath);

	// Trace the optimum path by ED algorithm
	vector<vector<char> > optPath(m+1,vector<char>(n+1,' '));
	optPath=align;
	traceOptimumPath(m,n,align,optPath);
	optPath[m][n]='O';

	// PRINT TABLE WITH ALIGNMENT
	/*for(int i=m;i>=0;i--){
		for(int j=0;j<=n;j++){
			cout
			<<left
			<<setw(2)
			<<setfill(' ')
			<<align[i][j];//+to_string(ED[i][j]);
		}
		cout<<endl;
	}*/


	cout<<"Edit Distance = "<<ED[m][n]<<endl;
	cout<<"Approx Edit Distance = "<<approxED<<endl;
	cout<<"Approximation Factor = "<<(float)approxED/ED[m][n]<<endl;
	cout<<endl;
	showOptAndAlgoPath(optPath,algoPath);
	cout<<endl<<x<<endl<<y<<endl;
	return 0;
}
