#include "heap.h"

Heap::Heap()
{
    H.push_back(INT32_MIN);
}
void Heap::HeapAdjust(std::vector<int>& H, int s, int m) {
    int rc = H[s];
    for (int j = 2 * s; j <= m; j *= 2) {
        if (j < m && H[j] < H[j + 1])
            ++j;
        if (rc >= H[j])
            break;
        H[s] = H[j];
        s = j;
    }
    H[s] = rc;
}
void Heap::HeapSort() {
    for (int i = (this->H.size()-1) / 2; i >0 ; i--)
        HeapAdjust(this->H, i, this->H.size()-1);
    for (int i = H.size()-1; i > 1; i--) {
        int tmp = H[1];
        H[1] = H[i];
        H[i] = tmp;
        HeapAdjust(this->H, 1,i-1);
    }
}
