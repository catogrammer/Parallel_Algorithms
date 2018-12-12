#ifndef PARALLELQSORT_H
#define PARALLELQSORT_H


void *_qsort__prll(int* arr, int first, int last){
    if (first < last){
        int left = first, right = last, middle = arr[(left + right) / 2];
        do {
            while (arr[left] < middle) 
                left++;
            while (arr[right] > middle) 
                right--;
            if (left <= right){
                int tmp = arr[left];
                arr[left] = arr[right];
                arr[right] = tmp;
                left++;
                right--;
            }
        } while (left <= right);
        _qsort__prll(arr, first, right);
        _qsort__prll(arr, left, last);
    }
}

#endif //QSORT_H