#include<iostream>

using namespace std;

void Merge(int *,int ,int,int);
void MergeSort(int *,int ,int);

int main(){
  int Array[20],i,B[20];
  cout<<"Enter the elements\n";
  for(i=0;i<5;i++)
     cin>>Array[i];
  MergeSort(Array,0,4);
  cout<<"Your sorted array is:\n";
  for(i=0;i<5;i++)
     cout<<Array[i]<<endl;
return 0;
}

void MergeSort(int *Array,int Low,int High){
if(Low<High){
        int Mid=(Low+High)/2;
        MergeSort(Array,Low,Mid);
        MergeSort(Array,Mid+1,High);
        Merge(Array,Low,High,Mid);
      }
return;
}

void Merge(int *Array,int Low,int High,int Mid){
int i,j,k,c[50];
i=Low;
k=Low;
j=Mid+1;
while(i<=Mid && j<=High){
    if(Array[i]<Array[j]){
        c[k]=Array[i];
        k++;
        i++;
    }
    else{
        c[k]=Array[j];
        j++;
        k++;
    }
}
while(i<=Mid){
    c[k]=Array[i];
    k++;
    i++;
}
while(j<=High){
    c[k]=Array[j];
    j++;
    k++;
}
for(i=Low;i<k;i++)
    Array[i]=c[i];
}
