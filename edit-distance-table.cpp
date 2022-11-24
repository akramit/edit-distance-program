#include<iostream>
#include<vector>
#include <iomanip>

using namespace std;

int main(){
	string x,y;
	cout<<"String X: \n";
	cin>>x;
	int n=x.length();
	cout<<"String Y: \n";
	cin>>y;
	int m=y.length();
	vector<vector<int> > ED(m+1,vector<int>(n+1,0));
	vector<vector<char> > align(m+1,vector<char>(n+1,' ')); //Alignment Vector
	for(int i=0;i<=m;i++){
		for(int j=0;j<=n;j++){
			if(i==0){
				ED[i][j]=j;
				align[i][j]='L'; //Alignment
			}
			else if(j==0){
				ED[i][j]=i;
				align[i][j]='B';
			}
			else if(x[j-1]==y[i-1]){
				ED[i][j]=min(1+min(ED[i][j-1],ED[i-1][j]) ,ED[i-1][j-1]);
				if(1+min(ED[i][j-1],ED[i-1][j]) > ED[i-1][j-1])
					align[i][j]='D';
				else{
					if(ED[i][j-1] > ED[i-1][j])
						align[i][j]='L';
					else
						align[i][j]='B';
				}
			}
			else{
				ED[i][j]=min(1+min(ED[i][j-1],ED[i-1][j]) , 1+ ED[i-1][j-1]);
				if(min(ED[i][j-1],ED[i-1][j]) < ED[i-1][j-1]){
					if(ED[i][j-1] > ED[i-1][j])
						align[i][j]='L';
					else
						align[i][j]='B';
				}
				else{
					align[i][j]='D';
				}
			}
		}
	}

	// PRINT TABLE WITH ALIGNMENT
	for(int i=m;i>=0;i--){
		for(int j=0;j<=n;j++){
			cout
			<<left
			<<setw(5)
			<<setfill(' ')
			<<align[i][j]+to_string(ED[i][j]);
		}
		cout<<endl;
	}

	return 0;
}
