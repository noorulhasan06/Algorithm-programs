#include<iostream>
#include<fstream>
#include<map>

using namespace std;


class node{
public:
  char colour;
  int info;
  node *left,*right,*parent;
  node *left_null,*right_null;
  /* node(){
     left=right=0;
     colour='R';
    }*/
   node(int data,node* p=0){
      left=0;
      right=0;
      colour='R';
      parent=p;
      info=data;
      left_null=0;
      right_null=0;
    }
};
map<string,node*> coll;
void read_data(node obj,char* fname);
void write_data(node obj,char* fname);

class RedBlackTree{
  
  public:
   node* root;
    RedBlackTree(){
      root=0;
    }
 void insert(int data);
 void RB_Insert_Fixup(node *prev); 
 void left_rotate(node *);
 void right_rotate(node *);
 void Inorder(node *);     
 void RB_transplant(node* u,node*v);
 node* search(int data);
 void RB_delete(int data);
 node* tree_minium(node* tmp);
 void RB_delete_fixup(node* );
};

void RedBlackTree::insert(int data){
      node *tmp=root;
      node *prev=0;
    //  node *pass=0;
      while(tmp!=0){
        prev=tmp;
        if(data>tmp->info)
          tmp=tmp->right;
        else
          tmp=tmp->left;
      }
      if(root==0){
       tmp=root=new node(data);
    //    root->colour='R';
    //    pass=root;
       }
       else if(data>prev->info){
         tmp=prev->right=new node(data,prev);
      //    prev->right->colour='R';
      //    prev->right->parent=prev;
      //    pass=prev->right;
         }
       else if(data<prev->info){
         tmp=prev->left=new node(data,prev);
      //   prev->left->colour='R';
      //   prev->left->parent=prev;
      //   pass=prev->left;
        }
       
       RB_Insert_Fixup(tmp);
      
 }
 
 void RedBlackTree::RB_Insert_Fixup(node *nd){
 
    while(nd->parent!=0 && nd->parent->colour=='R'){
       if(nd->parent==nd->parent->parent->left){
           node *y=nd->parent->parent->right;
           if(y!=0 && y->colour=='R'){
              nd->parent->colour='B';
              y->colour='B';
              nd->parent->parent->colour='R';
              nd=nd->parent->parent;
            }
          else {
                 if(nd==nd->parent->right){
                      nd=nd->parent;
                      left_rotate(nd);
                   }
                 nd->parent->colour='B';
                 nd->parent->parent->colour='R';
                 right_rotate(nd->parent->parent);
            }
           }
         else{
           node *y=nd->parent->parent->left;
           if(y!=0 && y->colour=='R'){
              nd->parent->colour='B';
              y->colour='B';
              nd->parent->parent->colour='R';
              nd=nd->parent->parent;
            }
          else {
                 if(nd==nd->parent->left){
                      nd=nd->parent;
                      right_rotate(nd);
                   }
                 nd->parent->colour='B';
                 nd->parent->parent->colour='R';
                 left_rotate(nd->parent->parent);
            }
           }
        }
        root->colour='B';

 }
   
void RedBlackTree::left_rotate(node *nd){
  
   node *y=nd->right;
  
  nd->right=y->left;
   if(y->left!=0)
      y->left->parent=nd;
   y->parent=nd->parent;
   if(nd->parent==0)
      root=y;
   else if(nd==nd->parent->left)
      nd->parent->left=y;
    else
      nd->parent->right=y;
    y->left=nd;
    nd->parent=y;
 }

void RedBlackTree::right_rotate(node *nd){
  
   node *y=nd->left;
   nd->left=y->right;
   if(y->right!=0)
      y->right->parent=nd;
   y->parent=nd->parent;
   if(y->parent==0)
      root=y;
   else if(nd==nd->parent->left)
      nd->parent->left=y;
    else
      nd->parent->right=y;
    y->right=nd;
    nd->parent=y;
  
}

 void RedBlackTree::Inorder(node *nd){
   if(nd!=0){
     cout<<nd->info<<"  "<<nd->colour<<endl;;
     Inorder(nd->left);
     Inorder(nd->right);
    }
  }  
  
node* RedBlackTree::search(int data){
 node* tmp1=root;
 while(tmp1!=0){
    if(data==tmp1->info)
      break;
    else if(data>tmp1->info)
      tmp1=tmp1->right;
    else
      tmp1=tmp1->left;
  }
 if(tmp1!=0)
    return tmp1;
 }
 void RedBlackTree::RB_transplant(node* u,node*v){
   if(u->parent==0)
     root=v;
   else if(u==u->parent->left)
     u->parent->left=v;
   else
     u->parent->right=v;
   if(v!=0)
      v->parent=u->parent;
}

void RedBlackTree::RB_delete(int data){
 node* z=root;
   while(z!=0){
      if(data==z->info)
        break;
      else if(data<z->info)
         z=z->left;
       else
         z=z->right;
     }
    if(z!=0){
      node* x;
      node* y=z;
      char y_original_colour=y->colour;
      if(z->left==0){
         x=z->right;
         RB_transplant(z,z->right);
       }
      else if(z->right==0){
        x=z->left;
        RB_transplant(z,z->left);
       }
      else{
         y=tree_minium(z->right);
         y_original_colour=y->colour;
         x=y->right;
         if(y->parent==z)
             x->parent==y;
         else{
            RB_transplant(y,y->right);
            y->right=z->right;
            y->right->parent=y;
            }
          RB_transplant(z,y);
          y->left=z->left;
          y->left->parent=y;
          y->colour=z->colour;
         }
    if(y_original_colour=='B' && x!=0)
         RB_delete_fixup(x);
   }
 }
 
 node* RedBlackTree::tree_minium(node* tmp){
    node* prev=tmp;
    while(tmp!=0){
      prev=tmp;
      tmp=tmp->left;
     }
 return prev;
}
 
 void RedBlackTree::RB_delete_fixup(node* x){
  node* w;
  cout<<"Entering in rb_fixup.\n";
  while(x!=root && x->colour=='B'){
      if(x==x->parent->left){
          w=x->parent->right;
          if(w!=0 && w->colour=='R'){
              w->colour='B';
              x->parent->colour='R';
              left_rotate(x->parent);
              w=x->parent->right;
             }
            if(w->left->colour=='B' && w->right->colour=='B'){
                   w->colour='R';
                   x=x->parent;
                }
            else{
              if(w->right->colour=='B'){
                  w->left->colour='B';
                  w->colour='R';
                  right_rotate(w);
                  w=x->parent->right;
                }
              w->colour=x->parent->colour;
              x->parent->colour='B';
              w->right->colour='B';
              left_rotate(x->parent);
              x=root;
            }
        }
          else{
          w=x->parent->left;
          if(w!=0 && w->colour=='R'){
              w->colour='B';
              x->parent->colour='R';
              right_rotate(x->parent);
              w=x->parent->left;
             }
            if(w->left->colour=='B' && w->right->colour=='B'){
                   w->colour='R';
                   x=x->parent;
                }
            else{
              if(w->left->colour=='B'){
                  w->right->colour='B';
                  w->colour='R';
                  left_rotate(w);
                  w=x->parent->left;
                }
              w->colour=x->parent->colour;
              x->parent->colour='B';
              w->left->colour='B';
              right_rotate(x->parent);
              x=root;
            }
        }
     }
   x->colour='B';           
 cout<<"Ending of rb_fixup.\n";
 }

//void read_data(node obj,char* fname){
   
 
int main(){
RedBlackTree t1;
node* found;
fstream fobj;
fobj.open("R.B.Tree.txt",ios::in|ios::app|ios::binary);
fobj.read((char* )&t1,sizeof(t1));
cout<<"\t+-------------------------+\n";
cout<<"\t|********MENU*************|\n";
cout<<"\t+-------------------------+\n";
cout<<"\t|1:-Insert an element.    |\n";
cout<<"\t|2:-Print.                |\n";
cout<<"\t|3:-Search.               |\n";
cout<<"\t|4:-Delete data           |\n";
cout<<"\t|0:-Exit.                 |\n";
cout<<"\t+-------------------------+\n";
int choice,num;
do{
cout<<"Enter your choice.\n";
cin>>choice;
switch(choice){
 case 0:fobj.write((char *)&t1,sizeof(t1));
        fobj.close();
        cout<<"Thanks.......\n";
        break;
 case 1:cout<<"\tEnter the number you want to insert.\n";
        cin>>num;
        t1.insert(num);
       
        break;
case 2:t1.Inorder(t1.root);
       break;
case 3:cout<<"\tEnter the number you want to search.\n";
       cin>>num;
       found=t1.search(num);
        if(found!=0)
          cout<<"Data :"<<found->info<<"  Colour :"<<found->colour<<endl;
        else
          cout<<"Data not found .\n";
          break;
case 4:cout<<"Enter the data.\n";
       cin>>num;
       t1.RB_delete(num);
       break;
default:cout<<"Wrong choice.\n";
        break;
        }}while(choice!=0);

return 0;
}                                       
