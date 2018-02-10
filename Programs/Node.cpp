#include<iostream>

using namespace std;

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
