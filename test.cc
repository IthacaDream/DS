#include "avl_tree.h"
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>

using namespace std;

void test_insert(AvlTree<int>* tree) {
  cout<<"---- insert ----"<<endl;
  for(int i=255;i>=0;--i){
    TNode<int>* pnode=new TNode<int>;
    memset(pnode,0,sizeof(TNode<int>));
    pnode->key=i;
    cout<<"insert: "<<i<<endl;
    tree->insert(pnode);
  }
  
  tree->traverse();
  
}


void test_remove(AvlTree<int>* tree) {
  cout<<"----remove test----"<<endl;
  tree->remove(4);
  tree->remove(6);
  
    /*
      tree->remove(1);
      tree->remove(5);
      tree->remove(3);
      tree->remove(2);
    */
  tree->traverse();

}

void test_remove_no(AvlTree<int>* tree) {
  cout<<"----remove sth. not exist ----"<<endl;
  for(int i=100;i<200;++i){
    cout<<"remove: "<<i<<endl;
    tree->remove(i);
  }
  tree->traverse();
  
}

void test_find(AvlTree<int>* tree) {

  cout<<"---- find test ----"<<endl;
  TNode<int>* result = NULL;
  
  result = tree->find(5);
  if(result)
    cout<<"find "<<result->key<<endl;
  else
    cout<<"not find"<<endl;
  
  
  result = tree->find(4);
  if(result)
    cout<<"find "<<result->key<<endl;
  else
    cout<<"not find"<<endl;
}

void random_test(AvlTree<int>* tree) {

  cout<<"---- random insert 1000000 node ----"<<endl;
  srand(time(NULL));
  for(int i=0;i<1000000;++i){
    TNode<int>* pnode=new TNode<int>;
    memset(pnode,0,sizeof(TNode<int>));
    pnode->key=rand()%1000000;
    
    cout<<"insert: "<<pnode->key<<endl;
    tree->insert(pnode);
    
    if(pnode->key%5==0){
      cout<<"remove: "<<pnode->key<<endl;
      tree->remove(pnode->key);
    }
  }
  cout<<" ---- test end ---- "<<endl;
}

void random_test10000(AvlTree<int>* tree) {

  cout<<"---- random insert 10000 node ----"<<endl;
  srand(time(NULL));
  for(int i=0;i<10000;++i){
    TNode<int>* pnode=new TNode<int>;
    memset(pnode,0,sizeof(TNode<int>));
    pnode->key=rand()%10000;
    
    cout<<"insert: "<<pnode->key<<endl;
    tree->insert(pnode);
    /*
      if(pnode->key%2==0){
      cout<<"remove: "<<pnode->key<<endl;
      tree->remove(pnode->key);
      }
    */
  }
  cout<<" ---- test end ---- "<<endl;
  tree->traverse();
}

void random_test255(AvlTree<int>* tree) {

  cout<<"---- random insert 100 node ----"<<endl;
  srand(time(NULL));
  for(int i=0;i<256;++i){
    TNode<int>* pnode=new TNode<int>;
    memset(pnode,0,sizeof(TNode<int>));
    pnode->key=rand()%256;
    
    cout<<"insert: "<<pnode->key<<endl;
    tree->insert(pnode);
    
    if(pnode->key%2==0){
      cout<<"remove: "<<pnode->key<<endl;
      tree->remove(pnode->key);
    }

  }
  cout<<" ---- test end ---- "<<endl;
  tree->traverse();
}

int main()
{
  AvlTree<int>* tree=new AvlTree<int>;
  //test_insert(tree);
  //test_insert(tree);
  //test_remove(tree);
  //test_find(tree);
  //test_remove_no(tree);
  //random_test(tree);
  
  random_test255(tree);
  
  
  
  //random_test10000(tree);
  //cout<<sizeof(TNode<int>)<<endl;
  
  
  delete tree;
  
  return 0;
}
