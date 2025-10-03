#include <stdio.h>
#include <stdlib.h>
#include <time.h>
static clock_t T0, T1;
void StartClock(void){ T0 = clock(); }
void StopClock(void){  T1 = clock(); }
double CPUtime(void){ return (double)(T1 - T0) / CLOCKS_PER_SEC; }


int *buildList(int n, int min, int max);      
int  findKthSmallest(const int L[], int n, int k);     // O(n + k log n)
void printList(const int L[], int n);

//최소힙 기준 다운힙
static void downHeapMin(int *H, int n, int i){
    while (2 * i <= n){
        int k = 2 * i;                       // k를 왼쪽 자식으로 설정
        if (k + 1 <= n && H[k+1] < H[k]) k++; // 더 작은 자식
        if (H[i] <= H[k]) break; //부모가 자식보다 작으면 break
        int t = H[i]; H[i] = H[k]; H[k] = t;
        i = k;
    }
}
static void buildMinHeap(int *H, int n){
    for (int i = n/2; i >= 1; --i) downHeapMin(H, n, i);
}

//min과 max사이의 무작위 정수 n개로 리스트를 생성하여 반환하는 함수
int *buildList(int n, int min, int max){
    if (n <= 0 || max < min) return NULL;
    int *arr = (int*)malloc(sizeof(int) * (n + 1)); 
    if (!arr) return NULL;                   
    for (int i = 1; i <= n; ++i) arr[i] = min + rand() % max - min + 1;
    return arr;                                      
}
//리스트 출력 함수
void printList(const int L[], int n){
    for (int i = 1; i <= n; ++i){
        printf("%d ", L[i]);
    }
    printf("\n");
}

// k번째 최소: O(n + k log n) 
int findKthSmallest(const int L[], int n, int k){
    if (!L || k < 1 || k > n) return -1;

    //배열 heap에 L을 복사해 최소힙 생성
    int *heap = (int*)malloc(sizeof(int) * (n + 1));
    if (!heap) return -1;
    for (int i = 1; i <= n; i++) heap[i] = L[i];
    buildMinHeap(heap, n);                // O(n)

    int size = n;
    int kthMin = -1;
    // 최솟값을 k번 pop -> k번째가 정답
    for (int i = 1; i <= k; i++){
        kthMin = heap[1];                    // 현재 최소
        heap[1] = heap[size--];           // 루트 제거
        downHeapMin(heap, size, 1);       // O(log n)
    }
    free(heap);
    return kthMin;
}


/* 총 6줄 출력 */
int main(){
    srand((unsigned)time(NULL));          //난수 시드

    //크기가 10인 리스트 생성
    int n = 10;
    int *L = buildList(n, 1, 100);
    printList(L, n);                      //라인 1

    //k = 1,2,3 일 때의 각각의 결과를 1줄에 출력
    int output1 = findKthSmallest(L, n, 1);
    int output2 = findKthSmallest(L, n, 2);
    int output3 = findKthSmallest(L, n, 3);
    printf("%d %d %d\n", output1, output2, output3); //라인 2

    free(L);              
    //크기가 100,000인 리스트로 재생성 (출력은 하지 않음)                
    n = 100000;
    L = buildList(n, 1, 1000000);
    int karray[4] = {1, 100, 99900, 99999};
    for (int i = 0; i < 4; ++i){
        StartClock();
        int e = findKthSmallest(L, n, karray[i]);
        StopClock();
        printf("%d %.6f\n", e, CPUtime());          //라인 3~6
    }

    free(L);
    return 0;
}
