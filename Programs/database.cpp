#include<iostream>
#include<string>
#include<fstream>

using namespace std;

void Input();
void Search();
void Quit();

int main(){
	cout<<"1:-Input a new name;\n";
	cout<<"2:-search for an emloyee.\n";
	cout<<"3:-Quit.\n";
	
	cout<<"Enter your choice.\n";
	int choice;
	cin>>choice;
	switch(choice){
		case 1:Input();
		       break;
		case 2:Search();
		       break;
		case 3:Quit();
		       break;
		default:cout<<"wrong choice.\n";
		        break;
	}
	
return 0;

}
