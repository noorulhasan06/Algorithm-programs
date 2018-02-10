// Program of Quick Sort

#include<iostream>
using namespace std;

void QuickSort(int [],int ,int);
int Partition(int [],int ,int ,int);
int extendLargeRegion(int [],int,int,int);
int extendSmallRegion(int [],int,int,int);


int main(){
	int size;
	cout<<"Enter the size of the array.\n";
	cin>>size;
	
	int Array[size];
	cout<<"Enter the elements.\n";
	
	for(int i=1;i<=size;i++)
	   cin>>Array[i];
	
	QuickSort(Array,1,size);
	
	cout<<"Your Elements in sorted Order.\n";
	for(int i=1;i<=size;i++)
	   cout<<Array[i]<<endl;
}

void QuickSort(int Array[],int first,int last){
	if(first<last){
		int Pivot=Array[first];
		int SplitPoint=Partition(Array,Pivot,first,last);
		Array[SplitPoint]=Pivot;
		
		QuickSort(Array,first,SplitPoint-1);
		QuickSort(Array,SplitPoint+1,last);
	}
  return ;
}

int Partition(int Array[],int Pivot,int first,int last){
	int low =first;
	int high=last;
	while(low<high){
		int highVacc=extendLargeRegion(Array,Pivot,low,high);
		int lowVacc=extendSmallRegion(Array,Pivot,low+1,highVacc);
		low=lowVacc;
		high=highVacc-1;
	}
	return low;
}

int extendLargeRegion(int Array[],int Pivot,int lowVacc ,int high){
	int curr=high;
	int highVacc=lowVacc;
	while(curr>=lowVacc){
		if(Array[curr]<Pivot){
			int tmp=Array[curr];
			Array[curr]=Array[lowVacc];
			Array[lowVacc]=tmp;
			highVacc=curr;
			break;
		}
		else 
		  curr--;
	}
	return highVacc;
}

int extendSmallRegion(int Array[],int Pivot,int low ,int highVacc){
	int curr=low;
	int lowVacc=highVacc;
	while(curr<=highVacc){
		if(Array[curr]>Pivot){
			int tmp=Array[curr];
			Array[curr]=Array[lowVacc];
			Array[lowVacc]=tmp;
			lowVacc=curr;
			break;
		}
		else 
		  curr++;
	}
	return lowVacc;
}
