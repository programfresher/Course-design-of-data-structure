#ifndef HEAP_H
#define HEAP_H
#include<vector>
class Heap{
protected:
    std::vector<int> H;
public:
    Heap();
    void HeapAdjust(std::vector<int>& H, int s, int m);
    void HeapSort();
};

#endif // HEAP_H

