#include <cmath>

#include "storage.h"


template<typename El>
void sortStorage(Storage<El>& st) {
    size_t n = st.size();
    auto* stack1 = new size_t[log(n) + 1]();
    auto* stack2 = new size_t[log(n) + 1]();
    size_t sz_stack = 1;
    stack1[0] = 0;
    stack2[0] = n - 1;


    while (sz_stack > 0) {
        size_t from = stack1[sz_stack - 1];
        size_t to = stack2[sz_stack - 1];
        --sz_stack;

        size_t left = from;
        size_t right = to;
        size_t pindex = left + rand() % (right - left);
        El pivot = st[pindex];

        while (left < right) {
            while (st[left] < pivot) { ++left; }
            while (st[right] > pivot) { --right; }

            if (left < right) {
                std::swap(st[left], st[right]);
            }
            else if (left == right) {
                ++left;
                if (right > 0) {
                    --right;
                }
            }
        }
        // ������� �� ���� ��������� ������� ��������
        // ����� ������� ��������
        if (right - from < to - left) {
            // ������ ������, ��� �����
            if (left < to) {
                stack1[sz_stack] = left;
                stack2[sz_stack] = to;
                ++sz_stack;
            }
            if (right > from) {
                stack1[sz_stack] = from;
                stack2[sz_stack] = right;
                ++sz_stack;
            }
        }
        else {
            if (right > from) {
                stack1[sz_stack] = from;
                stack2[sz_stack] = right;
                ++sz_stack;
            }
            if (left < to) {
                stack1[sz_stack] = left;
                stack2[sz_stack] = to;
                ++sz_stack;
            }
        }
    }

    delete[] stack1;
    delete[] stack2;
}