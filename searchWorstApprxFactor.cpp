#include<iostream>
#include<vector>
#include<iomanip>
#include<fstream>
#include<time.h>
#include<string>

using namespace std;

int findRandom()
{
    int num = ((int)rand() % 2);
    return num;
};

string getRandomBinaryString(int n,time_t time){
  srand(time);
    string S = "";
    // Iterate over the range [0, N - 1]
    for (int i = 0; i < n; i++) {
        // Store the random number
        int x = findRandom();
        // Append it to the string
        S += to_string(x);
    }
    return S;
};

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
  return ED[m][n];
};
//ApproximateED calculation
int calculateApproxED(string x, string y,vector<vector<char> > &align){
  int i=1,j=1,u=0,m=x.length(),n=y.length();
	while(i<=n && j<=m){
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

int main(){
  string x,y;
  int len=31;
  string filename="EDSearchSpace_new_len"+to_string(len)+".txt";
  //freopen(filename,"w",stdout);
  ofstream cout(filename);
  float maxApproxFactor= 0.0;
  //All binary strings of length
  int iter=20000000;
  while(iter--){

    x=getRandomBinaryString(len,time(NULL));//random binary string
    y=getRandomBinaryString(len-2,time(NULL)+iter);//random binary String
    int n=x.length();
  	int m=y.length();
    vector<vector<char> > align(m+1,vector<char>(n+1,' ')); //Alignment Vector
    int optEditDistance= calculateED(x,y,align);
    int approxEditDistance = calculateApproxED(x,y,align);

    float approxFactor= (float)approxEditDistance/optEditDistance;
  	
    if((approxFactor - maxApproxFactor) > 0.01 ){
      	maxApproxFactor=approxFactor;
      	cout<<"################################"<<endl;
      	cout<<endl<<"X: "<<x<<endl<<"Y: "<<y<<endl;
    	cout<<"Edit Distance = "<< optEditDistance<<endl;
    	cout<<"Approx Edit Distance = "<< approxEditDistance<<endl;
		cout<<"Approximation Factor = "<<approxFactor<<endl;
      	cout<<"Max Approx Factor "<<maxApproxFactor<<endl;
    }
  }
  return 0;
}
