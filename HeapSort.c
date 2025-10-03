#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX 100

int H[MAX];
int n = 0;

void insertItem(int key);
int removeMax();
void upHeap(int i);
void downHeap(int i);
void printHeap();

int main(){ 
    char cmd;
    while(1){
        scanf(" %c", &cmd);
        if(cmd == 'i'){
            int key;
            scanf("%d", &key);
            insertItem(key);
            printf("0\n");
        }
        else if(cmd == 'd'){
            int d = removeMax();
            printf("%d\n", d);
        }
        else if(cmd == 'p'){
            printHeap();
        }
        else if(cmd == 'q') break;
    }
    return 0;
}

void insertItem(int key){
    H[++n] = key;
    upHeap(n);
}

int removeMax(){
    int max = H[1];
    H[1] = H[n];
    n--;
    downHeap(1);
    return max;
}
//업힙은 값이 커졌을 때
void upHeap(int i){
    while(i > 1 && H[i/2] < H[i]){
        int tmp = H[i/2]; H[i/2] = H[i]; H[i] = tmp;
        i /= 2;
    }
}

//최대힙 기준 다운 힙
void downHeap(int i){
   while(2 * i <= n){
        int k = 2 * i;
        if(k + 1 <= n && H[k] < H[k+1]) k++;
        if(H[i] >= H[k]) break; 
        int tmp = H[i]; H[i] = H[k]; H[k] = tmp;
        i = k;
   }
}

void printHeap(){
    for(int i = 1; i <= n; i++){
        printf(" %d", H[i]);
    }
    printf("\n");
}

/*
i 5
i 15
i 10
i 20
i 30
i 25
p 
d
i 31
i 29
d
p
q
*/