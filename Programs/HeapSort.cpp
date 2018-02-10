//HEAP SORT

#include<iostream>
using namespace std;

class Heap{
	int Size,HeapSize;
	public :
		Heap(int last){
			Size=last;
		}
	void HeapSort(int []);
	void BuildMaxHeap(int []);
	void MaxHeapify(int [],int);
};

void Heap::HeapSort(int Array[]){
	BuildMaxHeap(Array);
	for(int i=Size;i>1;i--){
		int tmp=Array[1];
		Array[1]=Array[i];
		Array[i]=tmp;
	   HeapSize--;
	   MaxHeapify(Array,1);
	}
}

void Heap::BuildMaxHeap(int Array[]){
	HeapSize=Size;
	for(int i=Size/2;i>=1;i--)
	   MaxHeapify(Array,i);
}

void Heap::MaxHeapify(int Array[],int i){
	int left=2*i;
	int right=2*i+1;
	int max;
	if(left<=HeapSize && Array[left]>Array[i])
	    max=left;
	else
	   max=i;
	if(right<=HeapSize && Array[right]>Array[max])
	   max=right;
	if(max!=i){
	   int tmp=Array[max];
		Array[max]=Array[i];
		Array[i]=tmp;
	  MaxHeapify(Array,max);
	}
}

int main(){
	int size;
	cout<<"Enter the size of the array.\n";
	cin>>size;
	
	int Array[size];
	cout<<"Enter your elements.\n";
	for(int i=1;i<=size;i++)
	  cin>>Array[i];
	  
	Heap object(size);
	object.HeapSort(Array);
	cout<<"Your sorted elements are :\n";
	for(int i=1;i<=size;i++)
	  cout<<Array[i]<<endl;
return 0;
}
