#include <stdio.h>
#include <string.h>
#include <stdlib.h>
void swap(int A[], int i, int j);
int inPlacePartition(int A[], int l, int r, int k);
void inPlaceQuickSort(int L[], int l, int r);

int main(){

    return 0;

}
void swap(int A[], int i, int j){
    int tmp = A[i]; A[i] = A[j]; A[j] = tmp;
}

    int inPlacePartition(int A[], int l, int r, int k){
        if(l > r) return -1;
        if(k < l || k > r) return -1;
        swap(A, k, r);
        int pivot = A[r];
        int i = l;
        int j = r - 1;
        while(i <= j){
            while(i <= j && A[i] <= pivot) i++;
            while(i <= j && A[j] >= pivot) j--;
            if(i < j) swap(A, i, j);
        }
        swap(A, i , r);
        return i;
    }
void inPlaceQuickSort(int A[], int l, int r) {
    if (l >= r) return;

    // pivot index k를 랜덤으로 선택 (평균 성능 향상)
    int k = l + rand() % (r - l + 1);

    int p = inPlacePartition(A, l, r, k);
    if (p == -1) return; // 안전장치

    // 재귀로 좌우 분할 정렬
    inPlaceQuickSort(A, l, p - 1);
    inPlaceQuickSort(A, p + 1, r);
}
