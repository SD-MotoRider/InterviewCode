//
//  main.cpp
//  Heap
//
//  Created by Michael Simpson on 4/7/18.
//  Copyright © 2018 Michael Simpson. All rights reserved.
//

#include "MinHeap.h"

#include <iostream>

int main(int argc, const char * argv[]) {
    MinHeap minHeap;
    
    minHeap.add(3);
    minHeap.add(9);
    minHeap.add(12);
    minHeap.add(7);
    minHeap.add(1);
    
    while (int top = minHeap.top() != -1)
    {
        std::cout << top << std::endl;
    }
    
    return 0;
}
