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
	//x=amit , y=timax  , m=5, n=4 j<=4, i<=5
	vector<vector<int> > ED(m+1,vector<int>(n+1,0));
	vector<vector<char> > align(m+1,vector<char>(n+1,' '));
	//cout<<m<<" "<<n<<endl;
	for(int i=0;i<=m;i++){
		for(int j=0;j<=n;j++){ 
			if(i==0){
				ED[i][j]=j;
				align[i][j]='L';
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
				if(min(ED[i][j-1],ED[i-1][j]) > ED[i-1][j-1])
					align[i][j]='D';
				else{
					if(ED[i][j-1] > ED[i-1][j])
						align[i][j]='L';
					else
						align[i][j]='B';
				}
			}
			
		}
	}
	// PRINT TABLE WITH ALIGNMENT
	for(int i=m;i>=0;i--){
		/*if(i>0)
			cout<<y[i-1]<<" ";
		else
			cout<<"  ";*/
		//string direction=align[i][j];
		
		for(int j=0;j<=n;j++){
			cout
			<<left
			<<setw(5)
			<<setfill(' ')
			<<align[i][j]+to_string(ED[i][j]);
		}
		cout<<endl;
	}

	/*cout<<"   ";
	for(int i=0 ; i<x.length();i++)
		cout<<" "<<x[i];
	cout<<"\n\n";
	for(int i=m;i>=0;i--){
		for(int j=0;j<=n;j++){
			cout<<align[i][j]<<" ";
		}
		cout<<endl;
	}*/

	return 0;
}