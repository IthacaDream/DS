#include "heap.h"
#include <iostream>

Heap::Heap(int size = HEAP_SIZE):capacity_(size),curr_size_(0) {
  
  heap_ = new HeapNode* [size];
  for(int i = 0; i < size; ++i){
    heap_[i] = NULL;
  }
}

Heap::~Heap() {
  for(int i=0;i<capacity_;++i)
    delete heap_[i];
  delete []heap_;
}

void Heap::reset() {
  for(int i=0;i < capacity_;++i)
    delete heap_[i];
  curr_size_ = 0;
}

int Heap::insert(const char* key,float value) {
  if(curr_size_ < capacity_) {
    HeapNode *tmp = new HeapNode;
    tmp->key = key;
    tmp->value = value;
    heap_[curr_size_++] = tmp;
    
    if(curr_size_ == capacity_){
      for(int i=(capacity_-1)/2; i >= 0; --i)
	sift_small(i);
    }
    return 1;
  }
  else {
    if(value < heap_[0]->value)
      return 0;
    else{
      heap_[0]->key = key;
      heap_[0]->value = value;
      
      sift_small(0);
      //traverse();
      return 1;
    }
  }
}

void Heap::sift_small(int i) {
  int j = 2 * i + 1;
  HeapNode* temp = heap_[i];
  while(j < capacity_) {
    if(j < capacity_ - 1 && heap_[j]->value > heap_[j + 1]->value)
      j++;  //j point to small
    if(temp->value > heap_[j]->value) {
      heap_[i] = heap_[j];
      i = j;
      j = 2 * i + 1;
    } else {
      break;
    }
  }
  heap_[i] = temp;
}

void Heap::traverse() {
  for(int i = 0; i < curr_size_; ++i)
    std::cout<<heap_[i]->key
	     <<"\t\t"
	     <<heap_[i]->value
	     <<std::endl;
  std::cout<<"------------------------------"<<std::endl;
}

unsigned int Heap::size() {
  return curr_size_;     
}

int Heap::has_element(const char *key) {
  for(int i=0; i < curr_size_; ++i)
    if(strcmp(heap_[i]->key, key) == 0)
      return i;
  return -1;
  
}

