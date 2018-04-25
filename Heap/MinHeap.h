//
//  MinHeap.h
//  Heap
//
//  Created by Michael Simpson on 4/7/18.
//  Copyright © 2018 Michael Simpson. All rights reserved.
//

#ifndef MinHeap_h
#define MinHeap_h

#include <vector>

class MinHeap
{
public:
    MinHeap();
    ~MinHeap();
    
    void add(int value);
    int top(void);
    
private:
    void minHeap(int index);
    void heapify(int index);
    
    unsigned int            _count;
    std::vector<int>        _heap;
};

#endif /* MinHeap_h */
