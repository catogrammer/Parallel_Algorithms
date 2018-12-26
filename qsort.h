#ifndef QSORT_H
#define QSORT_H


void qsort__(int* arr, int first, int last){
    // printf("%p %d %d", arr, first, last);
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
        qsort__(arr, first, right);
        qsort__(arr, left, last);
    }
}

#endif //QSORT_H
