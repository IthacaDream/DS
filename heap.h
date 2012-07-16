#ifndef HEAP_H_
#define HEAP_H_

#include <iostream>
#include <fstream>

const int HEAP_SIZE = 50;

struct HeapNode {
  char *key;
  float value;
  float weight;
};

class Heap
{

public:

  Heap(int size);
  ~Heap();
  
  int insert(const char* key,float value);
  void sift_small(int i);
  void traverse();
  unsigned int size();
  int has_element(const char *key);

  void reset();

private:
  int curr_size_;
  int capacity_;
  HeapNode **heap_;
  
};


#endif
