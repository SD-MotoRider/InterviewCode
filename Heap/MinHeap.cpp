//
//  MinHeap.cpp
//  Heap
//
//  Created by Michael Simpson on 4/7/18.
//  Copyright © 2018 Michael Simpson. All rights reserved.
//

#include "MinHeap.h"

using namespace std;

static int parentIndex(int index)
{
    return (index - 1) / 2;
}

static int leftChild(int index)
{
    return 2 * index + 1;
}

static int rightChild(int index)
{
    return 2 * index + 2;
}

static void swap(int& i, int& j)
{
    i = i ^ j;
    j = i ^ j;
    i = i ^ j;
}

MinHeap::MinHeap() :
    _count(0)
{
    _heap.resize(32, -1);
}

MinHeap::~MinHeap()
{
    _heap.clear();
}

void MinHeap::add(int value)
{
    if (_count == _heap.size()) {
        try {
            _heap.resize(_count * 2, -1);
        } catch (std::bad_alloc e) {
            return;
        }
    }
    
    _heap[_count++] = value;
    
    minHeap(_count);
}

int MinHeap::top()
{
    int result(-1);
    
    switch (_count)
    {
    case 0:
        break;
        
    case 1:
        result = _heap[0];
        _heap[0] = -1;
        _count = 0;
        break;
            
    default:
        _count--;
        result = _heap[0];
        swap(_heap[0], _heap[_count]);
        heapify(_count);
        break;
    }
    
    return result;
}

void MinHeap::minHeap(int index)
{
    int i = index - 1;
    if (i > 0)
    {
        int pi = parentIndex(i);
        if (_heap[i] < _heap[pi])
        {
            swap(_heap[i], _heap[pi]);
            minHeap(pi + 1);
        }
    }
}

void MinHeap::heapify(int index)
{
    int leftChildIndex = leftChild(index);
    int rightChildIndex = rightChild(index);
    
    int largest = (leftChildIndex < _count && _heap[leftChildIndex] > _heap[index]) ? leftChildIndex : index;
    
    if (rightChildIndex < _count && _heap[rightChildIndex] > _heap[largest])
    {
        largest = rightChildIndex;
    }
    
    if (largest != index)
    {
        swap(_heap[index], _heap[largest]) ;
        heapify(largest) ;
    }
}
