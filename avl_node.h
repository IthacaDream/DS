#ifndef AVL_NODE_H_
#define AVL_NODE_H_


template<class KeyT>
struct TNode {
  KeyT key;
  short bal;
  TNode *lch;
  TNode *rch;
  void *value;
};




#endif
