#include<iostream>
using namespace std;

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
};

node* RBT::getRoot(){
	return root;
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
    	root->color='R';
    	pass=root;
	}
	else if(data<prev){
		prev->left=new node(data,prev);
		prev->left->left=Tnil;
		prev->left->right=Tnil;
		prev->color='R';
		pass=prev->left;
	}
	else{
		prev->right=new node(data,prev);
		prev->right->left=Tnil;
		prev->right->right=Tnil;
		prev->color='R';
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
				x->parent='B';
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
				x->parent='B';
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
