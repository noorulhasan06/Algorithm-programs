#include<iostream>
#include<cctype>
#include<iomanip>

using namespace std;

void Sort();
void RedBlackTree();

class node{
	public :
		int info;
		char color;
		node *left,*right,*parent;
		node(int data,node *p){
			info=data;
			parent=p;
			left=0;
			right=0;
			color='B';
		}
};


//class for RBT
class RBT{
	node *root,*Tnil;
	public:
		RBT(){
			Tnil=new node(0,0);
            root=Tnil;
		}
        node* getRoot();
        void RBT_Insert(int );
        void Insert_Fixup(node* );
        void LeftRotate(node* );
        void RightRotate(node* );
        void Preorder(node* );
        node* RBT_Search(int );
        void RBT_Delete(node* );
        void Delete_Fixup(node* );
        void RBT_Transplant(node* ,node* );
        node* getTnil();
		node* TreeMinium(node*);
};

//class for RBT
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
//functions for merge sart
    void MergeSort(int [],int,int);
    void Merge(int [],int,int,int);

};

void Sorting::MergeSort(int Array[],int Low,int High){
	if(Low<High){
		int Mid=(Low+High)/2;
		MergeSort(Array,Low,Mid);
		MergeSort(Array,Mid+1,High);
		Merge(Array,Low,High,Mid);
	}
	return;
}

void Sorting::Merge(int Array[],int Low,int High,int Mid){
	int i,j,k,c[Size];
	i=Low;
	j=Mid+1;
	k=Low;
	while(i<=Mid && j<=High){
		if(Array[i]<Array[j]){
			c[k]=Array[i];
			k++;
			i++;
		}
		else{
			c[k]=Array[j];
			k++;
			j++;
		}
	}
	while(i<=Mid){
		c[k]=Array[i];
		i++;
		k++;
	}
	while(j<=High){
		c[k]=Array[j];
		j++;
		k++;
	}
	for(i=Low;i<k;i++)
	  Array[i]=c[i];
}

node* RBT::getRoot(){
	return root;
}

node* RBT::getTnil(){
	return Tnil;
}

void RBT::RBT_Insert(int data){
	node *tmp=root;
	node *prev=Tnil;
	node *pass;
	while(tmp!=Tnil){
		prev=tmp;
		if(data<tmp->info)
		  tmp=tmp->left;
		else 
		  tmp=tmp->right;
	}
	
    if(root==Tnil){
    	root=new node(data,Tnil);
    	root->left=Tnil;
    	root->right=Tnil;
    	root->color='R';
    	pass=root;
	}
	else if(data<prev->info){
		prev->left=new node(data,prev);
		prev->left->left=Tnil;
		prev->left->right=Tnil;
		prev->left->color='R';
		pass=prev->left;
	}
	else{
		prev->right=new node(data,prev);
		prev->right->left=Tnil;
		prev->right->right=Tnil;
		prev->right->color='R';
		pass=prev->right;
	}
	Insert_Fixup(pass);
}

void RBT::Insert_Fixup(node *x){
	while(x->parent->color=='R'){
		node *y;
		if(x->parent==x->parent->parent->left){
			y=x->parent->parent->right;
			if(y->color=='R'){
				y->color='B';
				x->parent->color='B';
				x->parent->parent->color='R';
				x=x->parent->parent;
			}
			else{
				if(x==x->parent->right){
					x=x->parent;
					LeftRotate(x);
				}
				x->parent->color='B';
				x->parent->parent->color='R';
				RightRotate(x->parent->parent);
			}
		}
	  else{
	  	y=x->parent->parent->left;
			if(y->color=='R'){
				y->color='B';
				x->parent->color='B';
				x->parent->parent->color='R';
				x=x->parent->parent;
			}
			else{
				if(x==x->parent->left){
					x=x->parent;
					RightRotate(x);
				}
				x->parent->color='B';
				x->parent->parent->color='R';
				LeftRotate(x->parent->parent);
			
	  }
	}
  }
	root->color='B';
}

void RBT::LeftRotate(node *x){
	node *y=x->right;
	x->right=y->left;
	if(y->left!=Tnil)
	   y->left->parent=x;
	RBT_Transplant(x,y);
	y->left=x;
	x->parent=y;
}

void RBT::RightRotate(node *x){
	node *y=x->left;
	x->left=y->right;
	if(y->right!=Tnil)
	   y->right->parent=x;
	RBT_Transplant(x,y);
	y->right=x;
	x->parent=y;
}

void RBT::RBT_Transplant(node *x,node *y){
	y->parent=x->parent;
	if(x->parent==Tnil)
	    root=y;
    else if(x==x->parent->left)
        x->parent->left=y;
    else
        x->parent->right=y;
}

void RBT::Preorder(node *x){
	if(x!=Tnil){
		cout<<"\t|"<<setw(15)<<x->info<<'|'<<setw(5)<<x->color<<"|\n";
		cout<<"\t+---------------+-----+\n";
		Preorder(x->left);
		Preorder(x->right);
	}
}

node* RBT::RBT_Search(int data){
	node *tmp=root;
	while(tmp!=Tnil){
		if(data==tmp->info)
		   break;
		else if(data<tmp->info)
		   tmp=tmp->left;
		else
		   tmp=tmp->right;
	}
   return tmp;
}

node* RBT::TreeMinium(node *x){
	while(x->left!=Tnil)
	   x=x->left;
  return x;
}

void RBT::RBT_Delete(node *z){
	node *y=z;
	node *x;
	char y_original_color=y->color;
	if(z->left==Tnil){
		x=z->right;
		RBT_Transplant(z,z->right);
	}
	else if(y->right==Tnil){
		x=z->left;
		RBT_Transplant(z,z->left);
	}
	else{
		y=TreeMinium(z->right);
		y_original_color=y->color;
		x=y->right;
		if(y->parent==z)
		   x->parent=y;
		else{
			RBT_Transplant(y,x);
			y->right=z->right;
			z->right->parent=y;
		}
		RBT_Transplant(z,y);
		y->left=z->left;
		z->left->parent=y;
		y->color=z->color;
	}
   if(y_original_color=='B')
      Delete_Fixup(x);
}

void RBT::Delete_Fixup(node *x){
	node *w;
	while(x!=root && x->color=='B'){
		if(x==x->parent->left){
		   w=x->parent->right;
		   if(w->color=='R'){                      //To get the w of the color black
		   	  w->color='B';
		   	  x->parent->color='R';
		   	  LeftRotate(x->parent);
		   	  w=x->parent->right;
		   }	
		   if(w->left->color=='B' && w->right->color=='B'){    //to equate the w subtree with x subtree
		   	 w->color='R';
		   	 x=x->parent;
		   }
		   else{
		   	if(w->right->color=='B'){                    //because we want the color of the right of the w red
		   		 w->left->color='B';
		   		 w->color='R';
		   		 RightRotate(w);
		   		 w=x->parent->right;
			   }
			   w->right->color='B';
			   w->color=x->parent->color;
			   x->parent->color='B';
			   LeftRotate(x->parent);
			   x=root;
		   }
		}
	 else{
	 	 w=x->parent->left;
		   if(w->color=='R'){                      //To get the w of the color black
		   	  w->color='B';
		   	  x->parent->color='R';
		   	  RightRotate(x->parent);
		   	  w=x->parent->left;
		   }	
		   if(w->left->color=='B' && w->right->color=='B'){    //to equate the w subtree with x subtree
		   	 w->color='R';
		   	 x=x->parent;
		   }
		   else{
		   	if(w->left->color=='B'){                    //because we want the color of the right of the w red
		   		 w->right->color='B';
		   		 w->color='R';
		   		 LeftRotate(w);
		   		 w=x->parent->left;
			   }
			   w->left->color='B';
			   w->color=x->parent->color;
			   x->parent->color='B';
			   RightRotate(x->parent);
			   x=root;
		   }

	 }
	}
	x->color='B';
}



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


int main(int argc, char** argv) {
	
char choice;
do{
	cout<<"\t+-----------------------------+\n";
    cout<<"\t|S.Sorting.                   |\n";
    cout<<"\t|R.Red Black Tree.            |\n";
    cout<<"\t|E.Exit.                      |\n";
    cout<<"\t+-----------------------------+\n";
 
    
    cout<<"Enter your choice.\n";

  cin>>choice;
  choice=toupper(choice);
  
  switch(choice){
   
   case 'S':Sort();
             break;
    case 'R':RedBlackTree();
             break;
    case 'E':cout<<"Bye Bye.\n";
              break;
	}
}while(choice!='E');

return 0;
}
	
	
	
void RedBlackTree(){
	RBT object1;
	
	int data;
	node* found;
	
	cout<<"\t+------------------------------+\n";
	cout<<"\t|E:-Exit.                      |\n";
	cout<<"\t|I:-Insert.                    |\n";
	cout<<"\t|P:-Print.                     |\n";
	cout<<"\t|D:-Delete.                    |\n";
	cout<<"\t|S:-Search.                    |\n";
	cout<<"\t+------------------------------+\n";
	char choice;
	do{
	 
	cout<<"Enter your choice :\n";
	cin>>choice;
	choice =toupper(choice);
	switch(choice){
	
	case 'E': cout<<"Bye Bye.\n";
	               break;
	               
    case 'I':cout<<"Enter the data .\n";
                  cin>>data;
	              object1.RBT_Insert(data);
	              break;
	              
	case 'P':cout<<"\t+---------------+-----+\n";
	             cout<<"\t|Element        |Color|\n";
	             cout<<"\t+---------------+-----+\n";
	              object1.Preorder(object1.getRoot());
	              break;
	              
	case 'D':cout<<"Enter the data your want to delete.\n";
	             cin>>data;
	             found=object1.RBT_Search(data);
	             if(found!=object1.getTnil())
	                 object1.RBT_Delete(found);
	             else
	                cout<<"**Error!! Data not found.\n";
	             break;
	             
	case 'S':cout<<"Enter the data your want to Search.\n";
	             cin>>data;
	             found=object1.RBT_Search(data);
	             if(found!=object1.getTnil()){
	             cout<<"\t+---------------+-----+\n";
	             cout<<"\t|Element        |Color|\n";
	             cout<<"\t+---------------+-----+\n";
	             cout<<"\t|"<<setw(15)<<found->info<<'|'<<setw(5)<<found->color<<"|\n";
	             cout<<"\t+---------------+-----+\n";
            }
               else
			      cout<<"**Error!! Data not found.\n";
			          break;
	             
	default:cout<<"**Error!! Please select from Menu.\n";
	        break;
	        
	    }
		}while(choice!='E');
	
	return ;

}

void Sort(){
	
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
	object1.getData(Array,1,size);
	
	
	char choice;
	do{
		cout<<"\t+------------------------------+\n";
	cout<<"\t|E:-Exit.                      |\n";
	cout<<"\t|A:-Assign values.             |\n";
	cout<<"\t|P:-Print.                     |\n";
	cout<<"\t|Q:-Quick Sort.                |\n";
	cout<<"\t|I:-Insertion Sort.            |\n";
	cout<<"\t|H:-Heap Sort.                 |\n";
	cout<<"\t|M:-Merge Sort.                |\n";
	cout<<"\t+------------------------------+\n";
	
		cout<<"Enter your choice.\n";
        cin>>choice;
       
	  choice=toupper(choice);
	switch(choice){
	case 'E':
	          cout<<"Bye Bye.\n";
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
	case 'M':object1.MergeSort(Array,1,size);
             break;
	
	default:cout<<"**Error!! wrong choice please select a right choice.\n";
	        break;
	
	}	
	}while(choice!='E');

	return ;
}
