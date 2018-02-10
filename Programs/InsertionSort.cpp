//Insertion Sort Implementation
#include<iostream>
using namespace std;


int main(){
	int size;
	cout<<"Enter your size.\n";
	cin>>size;
	int Array[size];
	
	cout<<"Enter your elements.\n";
	
	for(int i=0;i<size;i++){
		cin>>Array[i];
		int large=Array[i];
		int j=i;
		for(;j>0;j--){
			if(Array[j-1]>large)
				Array[j]=Array[j-1];
			else
			   break;
		}
		Array[j]=large;
		
		cout<<"Your elements are :\n";
		for(int k=0;k<=i;k++)
		  cout<<Array[k]<<endl;
	}
}
