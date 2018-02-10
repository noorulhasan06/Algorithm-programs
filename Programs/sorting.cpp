// sorting programs

#include<iostream>
#include<cctype>

using namespace std;

class Sorting{
	int Size,HeapSize;            //variables for heap sort
	public:
		Sorting(int size){
			Size=size;
		}
	void getData(int [],int ,int );
	void Print(int [],int ,int );
	
//functions for heap sort
	void  QuickSort(int [],int ,int);
	int Partition(int [],int ,int,int);
	int extendLargeRegion(int [],int,int,int);
	int extendSmallRegion(int [],int,int,int);
	
//functions for Insertion sort
	void InsertionSort(int [],int ,int);
	
//functions for Heap Sort
	void HeapSort(int []);
	void BuildMaxHeap(int []);
	void MaxHeapify(int [],int);
};

void Sorting::HeapSort(int Array[]){
	BuildMaxHeap(Array);
	for(int i=Size;i>1;i--){
		int tmp=Array[1];
		Array[1]=Array[i];
		Array[i]=tmp;
	   HeapSize--;
	   MaxHeapify(Array,1);
	}
}

void Sorting::BuildMaxHeap(int Array[]){
	HeapSize=Size;
	for(int i=Size/2;i>=1;i--)
	   MaxHeapify(Array,i);
}

void Sorting::MaxHeapify(int Array[],int i){
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



void Sorting::InsertionSort(int Array[],int first,int last){
		cout<<"Enter your elements.\n";
	
	for(int i=first;i<=last;i++){
		cin>>Array[i];
		int large=Array[i];
		int j=i;
		for(;j>1;j--){
			if(Array[j-1]>large)
				Array[j]=Array[j-1];
			else
			   break;
		}
		Array[j]=large;
		
		cout<<"Your elements are :\n";
		for(int k=1;k<=i;k++)
		  cout<<Array[k]<<endl;
	}
}

void Sorting::Print(int Array[],int first,int last){
   	cout<<"elements are : \n";
	
	for(int i=first;i<=last;i++)
	   cout<<Array[i]<<endl;

}

void Sorting::getData(int Array[],int first,int last){
	cout<<"Enter the elements.\n";
	
	for(int i=first;i<=last;i++)
	   cin>>Array[i];
}

void Sorting::QuickSort(int Array[],int first,int last){
	if(first<last){
		int Pivot=Array[first];
		int SplitPoint=Partition(Array,Pivot,first,last);
		Array[SplitPoint]=Pivot;
		
		QuickSort(Array,first,SplitPoint-1);
		QuickSort(Array,SplitPoint+1,last);
	}
  return ;
}

int Sorting::Partition(int Array[],int Pivot,int first,int last){
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

int Sorting::extendLargeRegion(int Array[],int Pivot,int lowVacc,int high){
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

int Sorting::extendSmallRegion(int Array[],int Pivot,int low,int highVacc){
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

int main(){
	
    cout<<"\t+------------------------------+\n";
	cout<<"\t|E:-Exit.                      |\n";
	cout<<"\t|A:-Assign values.             |\n";
	cout<<"\t|P:-Print.                     |\n";
	cout<<"\t|Q:-Quick Sort.                |\n";
	cout<<"\t|I:-Insertion Sort.            |\n";
	cout<<"\t|H:-Heap Sort.                 |\n";
//	cout<<"\t|M:-Merge Sort.                |\n";
	cout<<"\t+------------------------------+\n";
	
	int size=0;
	a:                                           //for use goto function
	cout<<"Enter the size of the array.\n";

	cin>>size;

    if(cin.fail()){
    	cin.clear();        //this correct the stream clear the flag 
    	cin.ignore();       //this skip the left over stream data cin.ignore(INT_MAX,'\n')  this means that ignore until INT_MAX is dicarded or '\n' is discarded
    	cout<<"**Error!! Please enter a number.\n";
		goto a;              //you should use while or for loop for this don't use goto this is only for illstration
	}
	
	Sorting object1(size);
	int Array[size];
	
	char choice;
	do{
		cout<<"Enter your choice.\n";
        cin>>choice;
       
	  choice=toupper(choice);
	switch(choice){
	case 'E':cout<<"Bye Bye.\n";
	       exit(100);
	       break;
	case 'A':object1.getData(Array,1,size);
	         break;
	case 'P':object1.Print(Array,1,size);
	         break;
	case 'Q':object1.QuickSort(Array,1,size);
	        break;
	case 'I':object1.InsertionSort(Array,1,size);
	         break;
    case 'H':object1.HeapSort(Array);
             break;
	default:cout<<"**Error!! wrong choice please select a right choice.\n";
	        break;
	
	}	}while(choice!='0');

	return 0;
}

