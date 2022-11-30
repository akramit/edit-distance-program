/*
Startegy: If the OPT path passes from underneath (i,j) go to Right
		  If the OPT path passes from Left of (i,j) go UP
*/


#include<iostream>
#include<vector>
#include<iomanip>
#include<fstream>
#include<time.h>
#include<string>

using namespace std;

//Gives a random binary string
string getRandomBinaryString(int n){
    string S = "";
    for (int i = 0; i < n; i++) {
        int x = rand()%2;
        S += to_string(x);
    }
    return S;
};

/*
	Locate whether OPT is underneath (i,j) or Left of (i,j)
	returns 'x' if x-index to be incremented and respt. 'y'
*/
char locateOPTPath(int i, int j, vector<vector<char> > & optPath){
	if(optPath[i][j]=='O'){ // Go Diagonal
		return 'D';
	}
	for(int z=j;z>=0;z--){
		if(optPath[i][z]=='O')
			return 'y';
	}
	return 'x';
}

int calculateED(string x, string y,vector<vector<char> > &align){
  	int n=x.length();
	int m=y.length();
	vector<vector<int> > ED(m+1,vector<int>(n+1,0));
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
				ED[i][j]=min(1+min(ED[i][j-1],ED[i-1][j]) , 2+ ED[i-1][j-1]);

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
  return ED[m][n];
};

//Trace OPT path for Edit Distance
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

//ApproximateED calculation
int calculateApproxED(string x, string y,vector<vector<char> > &optPath){
  int i=1,j=1,u=0,m=x.length(),n=y.length();
	while(i<=n && j<=m){
		if(x[j-1]==y[i-1]){
			i++;
			j++;
		}
		else if(locateOPTPath(i,j,optPath)=='D'){
			u+=2;
			i++;
			j++;
		}
		else{
			u++;
			if(locateOPTPath(i,j,optPath)=='x'){ // Go Up if OPT path on Left
				j++;
			}
			else if(locateOPTPath(i,j,optPath)=='y'){ // Go Right if OPT path bottom
				i++;
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

int main(){
  string x,y;
  int len=30;
  string filename="EDSearchSpace_random_newAlgo"+to_string(len)+".txt";
  ofstream cout(filename);
  float maxApproxFactor= 0.0;
  srand(time(0));
  long iter=10000000;
  // #pragma omp parallel for reduction(max:maxApproxFactor)
  for(int it=0;it<iter;it++){
    x=getRandomBinaryString(len);//random binary string
    //y=getRandomBinaryString(len);
	//delete one from y
	for(int i=0;i<len;i++){
		for(int j=0;j<len;j++){
			//iter++;
			//x=getRandomBinaryString(len);
			y=x;
			y.erase(i,1);
			// //insert a char in x
			y.insert(j,to_string(rand()%2));
    		int n=x.length();
  			int m=y.length();
    		vector<vector<char> > align(m+1,vector<char>(n+1,' ')); //Alignment Vector
    		int optEditDistance= calculateED(x,y,align);
			//trace opt path
			vector<vector<char> > optPath(m+1,vector<char>(n+1,' '));
			optPath=align;
			traceOptimumPath(m,n,align,optPath);
			optPath[m][n]='O';
			//Approx ED
			int approxEditDistance = calculateApproxED(x,y,optPath);

			float approxFactor= (float)approxEditDistance/optEditDistance;
			
			if(approxFactor > maxApproxFactor){
				maxApproxFactor=approxFactor;
				cout<<"################################"<<endl;
				cout<<endl<<"X: "<<x<<endl<<"Y: "<<y<<endl;
				cout<<"Edit Distance = "<< optEditDistance<<endl;
				cout<<"Approx Edit Distance = "<< approxEditDistance<<endl;
				cout<<"Approximation Factor = "<<approxFactor<<endl;
				cout<<"Max Approx Factor "<<maxApproxFactor<<endl;
			}
			/*if(iter%50==0){
				cout<<"################################"<<endl;
				cout<<endl<<"X: "<<x<<endl<<"Y: "<<y<<endl;
				cout<<"Edit Distance = "<< optEditDistance<<endl;
				cout<<"Approx Edit Distance = "<< approxEditDistance<<endl;
				cout<<"Approximation Factor = "<<approxFactor<<endl;
				cout<<"Max Approx Factor "<<maxApproxFactor<<endl;
			}*/
		}
	}

 }
    cout<<"Worst Factor: "<<maxApproxFactor<<endl;
  return 0;
}
