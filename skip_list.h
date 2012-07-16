#ifndef SKIP_LIST_H_
#define SKIP_LIST_H_


#include <stdlib.h>
#include <string.h>

typedef char* KeyT;
typedef void* ValueT;
 
const int MAX_LEVEL = 16;
const int SKIPLIST_P = 0.25;

struct ListNode {
  KeyT key;
  ValueT value;
  ListNode *forward[];
};


class SkipList {

public:
  SkipList();
  ~SkipList();
    
  int insert(KeyT key, ValueT value);
  ValueT find(KeyT key);
  int remove(KeyT key);
  
private:
  ListNode* create_node(int level, KeyT key, ValueT value);
  int random_level();
  
  int level_;
  int length_;
  ListNode *header_;
};

#endif
