#include "skip_list.h"


SkipList::SkipList() : level_(0), length_(0) {
  this->header_ = create_node(MAX_LEVEL, NULL, NULL);
  for(int i = 0; i < MAX_LEVEL; ++i)
    this->header_->forward[i] = NULL;
}

SkipList::~SkipList() {

  ListNode *p = this->header_;
  ListNode *pre = p;
  while(p->forward[0]){
    p=p->forward[0];
    free(pre);
    pre=p;
  }
  free(pre);
}

ListNode* SkipList::create_node(int level, KeyT key, ValueT value) {
  ListNode *pn = (ListNode *)malloc(sizeof(ListNode) + level * sizeof(ListNode*));
  if(pn == NULL) return NULL;
  pn->key = key;
  pn->value = value;
  return pn;
}

int SkipList::random_level() {
  int level = 1;
  while ((rand() & 0xFFFF) < (SKIPLIST_P * 0xFFFF)){
    level += 1;
    if(level >= MAX_LEVEL)
      return MAX_LEVEL;
  }
  //return (level < MAX_LEVEL) ? level : MAX_LEVEL;
  return level;
}

int SkipList::insert(KeyT key, ValueT value) {
  ListNode *update[MAX_LEVEL];
  ListNode *p, *node = NULL;
  int level, i;
  
  p = this->header_;
  for(i = this->level_ - 1; i >= 0; --i){
    //while((node = p->forward[i]) && (node->key < key)){
    while((node = p->forward[i]) && strcmp(node->key,key) < 0){
      p = node;
    }
    update[i] = p;
  }
  if(node && strcmp(node->key, key) == 0){ //already exist, so just update value
    free(node->value);//TODO
    node->value = value;
    return 1;
  }
  
  level = random_level();
  if (level > this->level_){
    for(i = this->level_; i < level; ++i) //level grows
      update[i] = this->header_;
    this->level_ = level;
  }
  
  node = create_node(level, key, value);
  if(node == NULL)
    return -1; //insert failed
  for(i = 0; i < level; ++i){
    node->forward[i] = update[i]->forward[i];
    update[i]->forward[i] = node;
  }
  ++this->length_;
  return 0; //insert a new node, success
}

ValueT SkipList::find(KeyT key) {
  ListNode *p = this->header_;
  for(int i = this->level_ - 1; i >= 0; --i){
    while(p->forward[i] && strcmp(p->forward[i]->key,key) <= 0){
      if(strcmp(p->forward[i]->key, key) == 0){
	return p->forward[i]->value;
      }
      p = p->forward[i];
    }
  }
  return NULL;
}

int SkipList::remove(KeyT key)
{
  ListNode *update[MAX_LEVEL];
  ListNode *p = this->header_;
  ListNode *last = NULL;
  int i = 0;
  
  for(i = this->level_ - 1; i >= 0; --i){
    while((last = p->forward[i]) && strcmp(last->key, key) < 0)
      p = last;
    update[i] = p;
  }
  
  if(last && strcmp(last->key,key) == 0){
    for(i = 0; i < this->level_; ++i){
      if(update[i]->forward[i] == last)
	update[i]->forward[i] = last->forward[i];
    }

    free(last);
    
    for(i = this->level_ - 1; i >= 0; --i){
      if(this->header_->forward[i] == NULL)
	--this->level_;
    }
    --this->length_;
  }
  else{
    return -1;//not find
  }
  
  return 0;//delete success
}

