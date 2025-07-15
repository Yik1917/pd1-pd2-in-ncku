#include <stdio.h>
#include <string.h>
#include "hw7-5.h"

#define swap(x,y) char temp = *(x); *(x) = *(y); *(y) = temp;  // 交換兩字元

// 將 testcase 以快排方式排序，並回傳排序後字串
char *getAnswer2(char testcase[])
{
    quicksort(testcase, 0, strlen(testcase) - 1);
    return testcase;  // 回傳排序後的字串
}

// 將 s[low..high] 切分，並回傳樞紐位置
int split(char *s, int low, int high)
{
    char pivot = *(s + high);   // 樞紐設為最後一個字元
    int count = 0;
    for (int i = low; i < high; i++){
        if (*(s + i) < pivot){
            swap(s + count + low, s + i);  // 小於 pivot 的字元移到前面
            count++;
        }
    }
    swap(s + count + low, s + high);      // 將 pivot 放回正確位置
    return (count + low);
}

// 快速排序 s[low..high]
void quicksort(char *s, int low, int high)
{
    if (low >= high) return;               // 區間不需排序
    int middle = split(s, low, high);      // 切分取得樞紐位置
    quicksort(s, low, middle - 1);         // 排序左半部
    quicksort(s, middle + 1, high);        // 排序右半部
}
