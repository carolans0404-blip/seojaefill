#include <stdio.h>
#include <string.h>
#include <stdlib.h>
void inPlaceQuickSort(int A[], int l, int r);
int inPlacePartition(int A[], int l, int r, int k);
int findPivot(int L[], int l, int r);
void swap(int A[], int i, int j);
 

int main(){
    int n;
    scanf("%d", &n);
    int *L = (int*)malloc(sizeof(int) * n);
    for(int i = 0; i < n; i++){
        scanf("%d", &L[i]);
    }

    inPlaceQuickSort(L, 0, n-1);
    for(int i = 0; i < n; i++){
        printf(" %d", L[i]);
    }

    free(L);
    return 0;
}
void swap(int A[], int i, int j){
    int tmp = A[i]; A[i] = A[j]; A[j] = tmp;
}

int inPlacePartition(int A[], int l, int r, int k){
    if(l >= r) return -1;
    if(k < l || k > r) return -1;

    swap(A, k, r); //피벗을 r자리로 숨기기
    int pivot = A[r];
    int i = l;
    int j = r - 1;
    while(i <= j){
        while(i <= j && A[i] <= pivot) i++;
        while(i <= j && A[j] >= pivot) j--;
        if(i < j) swap(A, i, j);
    }
    swap(A, i, r);
    return i;   //분할하여 가운데 위치를 찾아 피벗 인덱스로 반환
}

//중앙값의 인덱스를 반환해주는 함수
int findPivot(int L[], int l, int r){
    int m = l + (r - l) / 2; // 중간 인덱스 쓰는 방법 알고있자
    int a = L[l]; int b = L[m]; int c = L[r];
    if(a <= b && b <= c || c <= b && b <= b) return m;
    if(b <= a && a <= c || c <= a && a <= b) return l;
    return r;
}
void inPlaceQuickSort(int A[], int l, int r){
    if(l >= r) return;
    int k = findPivot(A, l, r);
    int p = inPlacePartition(A, l, r, k);
    inPlaceQuickSort(A, l, p - 1);
    inPlaceQuickSort(A, p + 1, r);
}