#include <stdio.h>
#include <stdlib.h>

void printArr(int* arr, int size){
    printf("[ ");
    int i;
    for(i = 0; i < size; i++){
        printf("%d ", arr[i]);
    }
    printf(" ]\n");
}

void merge_sort(int* arr1, int* arr2, int* res, int size1, int size2){
    int k = 0;
    int i = 0;
    int j = 0;
    while(k < size1 + size2){
        // printf("i = %d j = %d k = %d\n", i, j, k);
        if( arr1[i] < arr2[j]){
            res[k++] = arr1[i++];
        }else{
            if( j < size2 )
                res[k++] = arr2[j];
            j++; //Warning inf loop
        }
    }
}

// void OddEvenSort(int* arr, int n){
//     int i;
//     for(i = 0; i < n; i++){
//         if(i%2 == 0){
//             int j;
//             for(j = 2; i < n; j+=2){
//                 merge_sort();
//                 }
//         }else{
//             int j;
//             for(j = 0; j < n; j+=2){
//                 merge_sort();
//             }   
//         }
//     }
// }

int* merge_sort2(int* arr, int len, int left, int right){
    int k = 0;
    int i = left;
    int j = right;
    int* res = malloc(len*sizeof(int));
    while(k < len){
        printf("%d < %d ", arr[i], arr[j] );
        if( arr[i] < arr[j] && i < right){
            res[k++] = arr[i++];
        }else{
            if( j < len ){
                res[k++] = arr[j];
                j++;
            }
             //Warning inf loop
        }
        printArr(res, len);
    }
    return res;
}


int main(int argc, char const *argv[])
{
    // int arr1[6] = {-4, 0, 3, 6, 8, 9};
    // int arr2[8] = {-2, -1, 0, 2, 3, 6, 7, 9};
    // int* res = malloc((6 + 8)*sizeof(int));
    // printArr(sorting(arr2, arr1, res, 8, 6), 6+8);
    
    int arr3[12] = {0, 2, 3, 4, 5, 5, 1, 2, 4, 7, 8, 8};
    printArr(arr3, 12);
    int* res = merge_sort2(arr3, 12, 0, 6);
    printArr(res, 12);


    
    return 0;
}
