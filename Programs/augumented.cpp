#include<iostream>
#include<cctype>
#include<iomanip>

using namespace std;

class node{
	public :
		int info,size;
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



class RBT{
	node *root,*Tnil;
	public:
		RBT(){
			Tnil=new node(0,0);
			Tnil->size=0;
            root=Tnil;
		}
        node* getRoot();
       //functions for inserting
	    void RBT_Insert(int );
        void Insert_Fixup(node* );
        
        void LeftRotate(node* );
        void RightRotate(node* );
        
		void Preorder(node* );
        
		node* RBT_Search(int );
        //functions for deletion
		void RBT_Delete(node* );
        void Delete_Fixup(node* );
        void RBT_Transplant(node* ,node* );
        
		node* getTnil();
		node* TreeMinium(node*);
		node* OS_Select(node* ,int);
		int OS_Rank(int);
};

node* RBT::getRoot(){
	return root;
}

node* RBT::getTnil(){
	return Tnil;
}

node* RBT::OS_Select(node *nd,int rank){
	if(nd!=Tnil){
	int RankOfNode=nd->left->size+1;
	if(RankOfNode==rank){
		return nd;
	}
	else if(rank<RankOfNode)
	  return OS_Select(nd->left,rank);
	else
	  return OS_Select(nd->right,rank-RankOfNode);
}
   else
     return Tnil;
}

int RBT::OS_Rank(int data){
		node *tmp=root;
	while(tmp!=Tnil){
		if(data==tmp->info)
		   break;
		else if(data<tmp->info)
		   tmp=tmp->left;
		else
		   tmp=tmp->right;
	}
	if(tmp!=Tnil){
		int rank=tmp->left->size+1;
		node *y=tmp;
		while(y!=root){
			if(y==y->parent->right)
				rank=rank+y->parent->left->size+1;
			y=y->parent;
		}
	return rank;
	}
	else return 0;
}

void RBT::RBT_Insert(int data){
	node *tmp=root;
	node *prev=Tnil;
	node *pass;
	while(tmp!=Tnil){
		 tmp->size++;	
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
    	root->size=1;
    	pass=root;
	}
	else if(data<prev->info){
		prev->left=new node(data,prev);
		prev->left->left=Tnil;
		prev->left->right=Tnil;
		prev->left->color='R';
		prev->left->size=1;
		pass=prev->left;
	}
	else{
		prev->right=new node(data,prev);
		prev->right->left=Tnil;
		prev->right->right=Tnil;
		prev->right->color='R';
		prev->right->size=1;
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
	y->size=x->size;
	x->right=y->left;
	if(y->left!=Tnil)
	   y->left->parent=x;
    y->parent=x->parent;
	if(x->parent==Tnil)
	    root=y;
    else if(x==x->parent->left)
        x->parent->left=y;
    else
		 x->parent->right=y;
	y->left=x;
	x->parent=y;
	y->size=x->size;
	x->size=x->left->size+x->right->size+1;
}


void RBT::RightRotate(node *x){
	node *y=x->left;
	x->left=y->right;
	if(y->right!=Tnil)
	   y->right->parent=x;
	y->parent=x->parent;
	if(x->parent==Tnil)
	    root=y;
    else if(x==x->parent->left)
        x->parent->left=y;
    else
		 x->parent->right=y;
	y->right=x;
	x->parent=y;
	y->size=x->size;
	x->size=x->left->size+x->right->size+1;

}

void RBT::RBT_Transplant(node *x,node *y){
	y->parent=x->parent;
	if(x->parent==Tnil)
	    root=y;
    else if(x==x->parent->left)
      {
        x->parent->left=y;
        x->parent->size=x->parent->left->size+x->parent->right->size+1;
}
    else
       {
		 x->parent->right=y;
       x->parent->size=x->parent->left->size+x->parent->right->size+1;
   }
}

void RBT::Preorder(node *x){
	if(x!=Tnil){
		cout<<"\t|"<<setw(15)<<x->info<<'|'<<setw(5)<<x->color<<"|"<<setw(5)<<x->size<<"|\n";
		cout<<"\t+---------------+-----+-----+\n";
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
	   {
	   x->size--;
	   x=x->left;
       }
  return x;
}

void RBT::RBT_Delete(node *z){
	node *y=z;
	node *x;
	char y_original_color=y->color;
	node *tmp=y;
	if(z->left==Tnil){
		x=z->right;
		while(tmp!=root){
			tmp->parent->size--;
		    tmp=tmp->parent;
		}
		RBT_Transplant(z,z->right);
	}
	else if(y->right==Tnil){
		x=z->left;
		while(tmp!=root){
			tmp->parent->size--;
		    tmp=tmp->parent;
		}
		RBT_Transplant(z,z->left);
	}
	else{
		y=TreeMinium(z->right);
		tmp=y;
		while(tmp!=root){
			tmp->parent->size--;
		    tmp=tmp->parent;
		}
		y_original_color=y->color;
		x=y->right;
		node* tmp=y;
		if(y->parent==z)
		   x->parent=y;
		else{
			RBT_Transplant(y,x);
			y->right=z->right;
			z->right->parent=y;
		}
		y->size=z->size;
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

int main(int argc, char** argv) {
	
	RBT object1;
	
	int data,rank;
	node* found;
	
	cout<<"\t+------------------------------+\n";
	cout<<"\t|E:-Exit.                      |\n";
	cout<<"\t|I:-Insert.                    |\n";
	cout<<"\t|P:-Print.                     |\n";
	cout<<"\t|D:-Delete.                    |\n";
	cout<<"\t|S:-Search.                    |\n";
	cout<<"\t|R:-Find the rank of an element|\n";
	cout<<"\t|D:-Find the element of rank.  |\n";
	cout<<"\t+------------------------------+\n";
	char choice;
	do{
	 
	cout<<"Enter your choice :\n";
	cin>>choice;
	choice =toupper(choice);
	switch(choice){
	
	case 'E': cout<<"Bye Bye.\n";
	               exit(100);
	               break;
	               
    case 'I':cout<<"Enter the data .\n";
                  cin>>data;
	              object1.RBT_Insert(data);
	              break;
	              
	case 'P':    cout<<"\t+---------------+-----+-----+\n";
	             cout<<"\t|Element        |Color|Size |\n";
	             cout<<"\t+---------------+-----+-----+\n";
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
	             cout<<"\t+---------------+-----+-----+\n";
	             cout<<"\t|Element        |Color|Size |\n";
	             cout<<"\t+---------------+-----+-----+\n";
	             cout<<"\t|"<<setw(15)<<found->info<<'|'<<setw(5)<<found->color<<"|"<<setw(5)<<found->size<<"\n";
	             cout<<"\t+---------------+-----+-----+\n";
            }
               else
			      cout<<"**Error!! Data not found.\n";
			          break;
	case 'R':cout<<"Enter your data.\n";
	         cin>>data;
	        rank=object1.OS_Rank(data);
	          if(rank!=0){
	             cout<<"+++++ Rank of "<<data<<" is "<<rank<<"++++++\n";
            }
               else
			      cout<<"**Error!! Data not found.\n";
			          break;

	         
	case 'F':cout<<"Enter the rank of the element.\n";
	        cin>>rank;
	        found=object1.OS_Select(object1.getRoot(),rank);
	         if(found!=object1.getTnil()){
	             cout<<"\t+---------------+-----+-----+\n";
	             cout<<"\t|Element        |Color|Size |\n";
	             cout<<"\t+---------------+-----+-----+\n";
	             cout<<"\t|"<<setw(15)<<found->info<<'|'<<setw(5)<<found->color<<"|"<<setw(5)<<found->size<<"\n";
	             cout<<"\t+---------------+-----+-----+\n";
            }
               else
			      cout<<"**Error!! Rank not found.\n";
			          break;

	        break;
	        
	default:cout<<"**Error!! Please select from Menu.\n";
	        break;
	        
	    }
	}while(choice!='E' && choice!='e');
	
	return 0;
}
