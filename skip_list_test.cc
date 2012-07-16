#include <iostream>
#include "skip_list.h"

using namespace std;

int main(int argc, char **argv) {
  
  SkipList sl;
  char* key1 = "hello";
  int value1 = 1;
  char* key2 = "word";
  int value2 = 2;
  sl.insert(key1,&value1);
  sl.insert(key2,&value2);
  int * res = (int*)sl.find(key1);
  cout<<*res<<endl;
  res = (int*)sl.find(key2);
  cout<<*res<<endl;
  sl.remove(key1);
  res = (int*)sl.find(key1);
  if(res != NULL)
    cout<<*res<<endl;
  else
    cout<<"null"<<endl;
  res = (int*)sl.find(key2);
  cout<<*res<<endl;

  return 0;
}
