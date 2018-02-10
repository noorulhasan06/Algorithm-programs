#include<iostream>
#include<fstream>
#include<cstdio>
using namespace std;

struct Work{
string name;
int id;
string job;
}p[10];

int main(){
   // Work p[10];
int b,d;
char f[20];
ofstream file;
jump:

cout<<"The db++ database application.\n";
cout<<"1:-To enter the data.\n";
cout<<"2:-To read the data.\n";
cout<<"3:-To save the data.\n";

cout<<"Enter your choice\n";
cin>>d;
switch(d){
case 1:cout<<"Enter the no. of workers to get the data.\n";
       cin>>b;
       cout<<"Enter the name of the workers.\n";
       for(int i=1;i<=b;i++)
         cin>>p[i].name;
       cout<<"Enter the id no. of the workers.\n";
       for(int i=1;i<=b;i++)
         cin>>p[i].id;
       cout<<"Enter the Job of the workers.\n";
       for(int i=1;i<=b;i++)
         cin>>p[i].job;
    goto jump;
case 2:for(int i=1;i<=b;++i)
         cout<<i<<"-"<<p[i].name<<" "<<p[i].id<<" "<<p[i].job<<endl;
        goto jump;
case 3:
       file.open("report.db",ios::out|ios::binary);
       for(int i=i;i<=b;++i)
         file<<i<<'-'<<p[i].name<<' '<<p[i].id<<' '<<p[i].job<<endl;
      cout<<"The file is saved.\n";
      file.close();
      break;
default:cout<<"**Error!! wrong choice.\n";
         break;
}
return 0;
}
