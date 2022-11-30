/*
    Algorithm Strategy proposed by Mike.
    1. U= ED(i,j)+1/2D 
    2. Move in the direction where it is minimum
*/

#include<iostream>
#include<vector>
#include<iomanip>
#include<fstream>
#include<time.h>
#include<string>
#include<float.h>

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
Calculate ED Table and returns optimum Edit Distance
Substitution cost = 
*/
int calculateED(string x, string y, vector<vector<int> > &ED){
  	int n=x.length();
	int m=y.length();
	//vector<vector<int> > ED(m+1,vector<int>(n+1,0));
	for(int i=0;i<=m;i++){
		for(int j=0;j<=n;j++){
			if(i==0){
				ED[i][j]=j;
				//align[i][j]='-'; //Alignment
			}
			else if(j==0){
				ED[i][j]=i;
				//align[i][j]='|'; //Alignment
			}
			else if(x[j-1]==y[i-1]){
				ED[i][j]=min(1+min(ED[i][j-1],ED[i-1][j]) ,ED[i-1][j-1]);

				/* //Alignment
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
				}*/
			}
			else{ // x[j-1]!=y[i-1]
				ED[i][j]=min(1+min(ED[i][j-1],ED[i-1][j]) , 1+ ED[i-1][j-1]);

				/*if(ED[i-1][j]==ED[i][j-1] && ED[i-1][j-1] == ED[i-1][j]){ //All EQUAL alignment=*
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
				}*/
			}
		}
	}
  return ED[m][n];
};

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
ApproximateED calculation
Substitution Cost =  (Diagonal Move)
*/
int calculateApproxED(string x, string y,vector<vector<int> > &ED){
  int i=1,j=1,u=0,m=x.length(),n=y.length();
	while(i<=n && j<=m){
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
            j++;
        }
	}
	int unprocessed_chars=0;
	if(i<n || j <m){
		if(n-i>0)
			unprocessed_chars+=n-i;
		else if(m-j > 0)
			unprocessed_chars+=m-j;
	}
	return u + unprocessed_chars;
};

int main(){
  string x,y;
  int len=30;
  string filename="EDSearchSpace_Algo1_WithSubs_"+to_string(len)+".txt";
  ofstream cout(filename);
  float maxApproxFactor= 0.0;
  srand(time(0));
  long iter=1000000;
  
  while(iter--){
    //x=getRandomBinaryString(len);//random binary string
    //y=getRandomBinaryString(len)
	//delete one from y
	for(int i=0;i<len;i++){
		for(int j=0;j<len;j++){
			iter++;
			x=getRandomBinaryString(len);
			y=x;
			y.erase(i,1);
			//insert a char in x
			y.insert(j,to_string(rand()%2));
    		int n=x.length();
  			int m=y.length();
    		//vector<vector<char> > align(m+1,vector<char>(n+1,' ')); //Alignment Vector
			vector<vector<int> > ED(m+1,vector<int>(n+1,0)); //Dynamic Progr Table
    		int optEditDistance= calculateED(x,y,ED);
			int approxEditDistance = calculateApproxED(x,y,ED);

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
			if(iter%2000==0){
				cout<<"################################"<<endl;
				cout<<endl<<"X: "<<x<<endl<<"Y: "<<y<<endl;
				cout<<"Edit Distance = "<< optEditDistance<<endl;
				cout<<"Approx Edit Distance = "<< approxEditDistance<<endl;
				cout<<"Approximation Factor = "<<approxFactor<<endl;
				cout<<"Max Approx Factor "<<maxApproxFactor<<endl;
			}
		}
	}

 }

  return 0;
}
