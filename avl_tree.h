#ifndef AVL_TREE_H_
#define AVL_TREE_H_

#include "avl_node.h"
#include <string.h>
#include <iostream>


#define LH +1
#define EH 0
#define RH -1


template<class KeyT>
class AVLTree {

public:
  AVLTree();
  ~AVLTree();
  
  void insert(TNode<KeyT>* p);
  void remove(KeyT key);
  TNode<KeyT>* find(KeyT key);
  void traverse();
  
  void test(); //test
  
private:
  void insert_node(TNode<KeyT>* &r,TNode<KeyT>* p,bool &taller);
  void remove_node(TNode<KeyT>* &r,KeyT key,bool &shorter);
  TNode<KeyT>* find_node(TNode<KeyT>* r,KeyT key);
  
  void left_balance(TNode<KeyT>* &r,bool &shorter);
  void right_balance(TNode<KeyT>* &r,bool &shorter);
  void rotate_left(TNode<KeyT>* &r);
  void rotate_right(TNode<KeyT>* &r);
  void mid_traverse(TNode<KeyT>* r);
  void destroy(TNode<KeyT>* &r);
    
private:
  TNode<KeyT> *root_;
};

template<class KeyT>
AVLTree<KeyT>::AVLTree() {
  root_=NULL;
}

template<class KeyT>
AVLTree<KeyT>::~AVLTree() {
  destroy(root_);
}

template<class KeyT>
void AVLTree<KeyT>::destroy(TNode<KeyT>* &r) {
  if(r){
    destroy(r->lch);
    destroy(r->rch);
    delete r;
    r = NULL;
  }
}

template<class KeyT>
TNode<KeyT>* AVLTree<KeyT>::find(KeyT key) {
  return find_node(root_,key);
}

template<class KeyT>
TNode<KeyT>* AVLTree<KeyT>::find_node(TNode<KeyT>* r,KeyT key) {
  if(r){
    if(memcmp(&key,&(r->key),sizeof(KeyT)) < 0)
      return find_node(r->lch,key);
    else if(memcmp(&key,&(r->key),sizeof(KeyT)) > 0)
      return find_node(r->rch,key);
    else
      return r;
  }
  else
    return NULL;
}

template<class KeyT>
void AVLTree<KeyT>::insert(TNode<KeyT>* p) {
  bool taller = true;
  //std::cout<<"sizeof:"<<sizeof(KeyT)<<std::endl;
  insert_node(root_,p,taller);
}

template<class KeyT>
void AVLTree<KeyT>::insert_node(TNode<KeyT>* &r,TNode<KeyT>* p,bool &taller) {
  if(r==NULL){ //first node
    r=p;
    taller=true;
  }
  else if(memcmp(&(p->key),&(r->key),sizeof(KeyT)) < 0){
    insert_node(r->lch,p,taller);
    if(taller){
      switch(r->bal){
	
      case LH:
	left_balance(r,taller);
	taller=false;
	break;
      case EH:
	//std::cout<<"test l"<<std::endl;
	r->bal=LH;
	break;
      case RH:
	r->bal=EH;
	taller=false;
	break;
      }
    }
  }
  else if(memcmp(&(p->key),&(r->key),sizeof(KeyT)) > 0){
    insert_node(r->rch,p,taller);
    if(taller){
      switch(r->bal){
      case LH:
	r->bal=EH;
	taller=false;
	break;
      case EH:
	//std::cout<<"test r"<<std::endl;
	r->bal=RH;
	break;
      case RH:
	right_balance(r,taller);
	taller=false;
	break;
      }
    }
  }
  else {//already exist
    taller = false;
    return;
  }
}

template<class KeyT>
void AVLTree<KeyT>::remove(KeyT key) {
  bool shorter = true;
  remove_node(root_,key,shorter);
  
}

template<class KeyT>
void AVLTree<KeyT>::remove_node(TNode<KeyT>* &r,KeyT key,bool &shorter) {
  if (r == NULL){
    //std::cout<<"remove node not exist"<<std::endl;
    shorter=false;
    return;
  }
  else if (memcmp(&key,&(r->key),sizeof(KeyT)) < 0) {
    remove_node(r->lch, key, shorter);
    if (shorter) {
      switch (r->bal) {
      case LH:
	r->bal = EH;
	break;
      case EH:
	r->bal = RH;
	shorter = false;
	break;
      case RH:
	right_balance(r, shorter);
	break;
      }
    }
  }
  else if (memcmp(&key,&(r->key),sizeof(KeyT)>0)) {
    remove_node(r->rch, key, shorter);
    if (shorter) {
      switch (r->bal) {
      case LH:
	left_balance(r, shorter);
	break;
      case EH:
	r->bal = LH;
	shorter = false;
	break;
      case RH:
	r->bal = EH;
	break;
      }
    }
  } else {
    TNode<KeyT> *temp;
    if (r->lch == NULL){
      temp = r->rch;
      r->rch = NULL;
      delete r;//TODO free
      r = temp;
      shorter = true;
    }
    else if (r->rch == NULL){
      temp = r->lch;
      r->lch = NULL;
      delete r;//TODO free
      r = temp;
	    shorter = true;
    }
    else {
      temp = r->rch;
      while (temp->lch != NULL)
	temp = temp->lch;
      
      //copyNode(r,temp);//TODO
      memcpy(&(r->key),&(temp->key),sizeof(KeyT));
      //r->tf = temp->tf;
      r->value = temp->value;
      
      remove_node(r->rch, temp->key, shorter);
      if (shorter) {
	switch (r->bal) {
	case LH:
	  left_balance(r, shorter);
	  break;
	case EH:
	  r->bal = LH;
	  shorter = false;
	  break;
	case RH:
	  r->bal = EH;
	  break;
	}
      }
    }
  }
}

template<class KeyT>
void AVLTree<KeyT>::left_balance(TNode<KeyT>* &r,bool &shorter) {
  TNode<KeyT> *leftTree = r->lch;
  //if(r->lch== NULL)
  //std::std::cout<<"null"<<std::std::endl;
  TNode<KeyT> *rightTree = leftTree->rch;
  
  switch (leftTree->bal) {
  case LH:
    r->bal = EH;
    leftTree->bal = EH;
    rotate_right(r);
    break;
  case EH:
    r->bal = LH;
    leftTree->bal = RH;
    rotate_right(r);
    shorter = false;
    break;
  case RH: {
    switch (rightTree->bal) {
    case LH:
      r->bal = RH;
      leftTree->bal = EH;
      break;
    case EH:
      r->bal = EH;
      leftTree->bal = EH;
      break;
    case RH:
      r->bal = EH;
      leftTree->bal = LH;
      break;
    }
    //std::cout<<"LR"<<std::endl;
    rightTree->bal = EH;
    rotate_left(leftTree);
    r->lch=leftTree;//to update r->lch
    rotate_right(r);
    break;
  }
  }
}

template<class KeyT>
void AVLTree<KeyT>::right_balance(TNode<KeyT>* &r,bool &shorter) {
  TNode<KeyT> *rightTree = r->rch;
  TNode<KeyT> *leftTree = rightTree->lch;
  switch (rightTree->bal) {
  case LH: {
    switch (leftTree->bal) {
    case LH:
      r->bal = EH;
      rightTree->bal = RH;
      break;
    case EH:
      r->bal = EH;
      rightTree->bal = EH;
      break;
    case RH:
      r->bal = LH;
      rightTree->bal = EH;
    }
    leftTree->bal = EH;
    //std::cout<<"RL"<<std::endl;
    rotate_right(rightTree);
    r->rch=rightTree;//BUG:forget to repoint before
    rotate_left(r);
    break;
  }
  case EH:
    r->bal = RH;
    rightTree->bal = LH;
    rotate_left(r);
    shorter = false;
    break;
  case RH:
    r->bal = EH;
    rightTree->bal = EH;
    rotate_left(r);
    break;
  }
}

template<class KeyT>
void AVLTree<KeyT>::rotate_left(TNode<KeyT>* &r) {
  TNode<KeyT>*temp = r->rch;
  r->rch = temp->lch;
  temp->lch = r;
  r = temp;
}

template<class KeyT>
void AVLTree<KeyT>::rotate_right(TNode<KeyT>* &r) {
  TNode<KeyT> *temp = r->lch;
  r->lch = temp->rch;
  temp->rch = r;
  r = temp;
}

template<class KeyT>
void AVLTree<KeyT>::traverse()
{
  mid_traverse(root_);
}

template<class KeyT>
void AVLTree<KeyT>::mid_traverse(TNode<KeyT>* r)
{
  if(r){
    mid_traverse(r->lch);
    std::cout<<r->key<<"\t"<<r->bal<<std::endl;
	mid_traverse(r->rch);
  }
}

template<class KeyT>
void AVLTree<KeyT>::test()
{
  std::cout<<"----test----"<<std::endl;
  std::cout<<root_->key<<std::endl;
  std::cout<<root_->rch->key<<std::endl;
  std::cout<<"----end ----"<<std::endl;
}

#endif
