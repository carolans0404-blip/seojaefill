#include <stdio.h>
#include <string.h>
#include <stdlib.h>
typedef struct Node{
    int data;
    struct Node *next;
}Node;

Node *getnode(int value){
    Node *p = (Node*)malloc(sizeof(Node));
    if(!p) return NULL;
    p->data = value;
    p->next = NULL;
    return p;
}

void printList(Node *head){
    Node *p = head;
    while(p){
        printf(" %d", p->data);
        p = p->next;
    }
}
void freeNode(Node *head){
    while(head){
        Node *tmp = head;
        head = head->next;
        free(tmp);
    }
}

void appendNode(Node **head, Node **tail, int v) {
    Node *p = getnode(v);
    if (*head == NULL) {
        *head = *tail = p;
    } else {
        (*tail)->next = p;
        *tail = p;
    }
}

void partition(Node *head, int K, Node **leftHead, Node **rightHead) {
    if (K <= 0 || head == NULL) {
        *leftHead = NULL;
        *rightHead = head;
        return;
    }
    Node *cur = head;
    int i = 1;
    while (i < K && cur->next) { cur = cur->next; i++; }
    *leftHead = head;
    *rightHead = cur->next;
    cur->next = NULL;
}
Node* merge(Node *a, Node *b) {
    Node dummy;
    Node *tail = &dummy;
    dummy.next = NULL;
    while (a && b) {
        if (a->data <= b->data) {      // <= 로 하면 stable
            tail->next = a;
            a = a->next;
        } else {
            tail->next = b;
            b = b->next;
        }
        tail = tail->next;
    }
    tail->next = (a ? a : b);
    return dummy.next;
}

Node* mergeSort(Node *head) {
    if (!head || !head->next) return head; // 길이 0 또는 1이면 이미 정렬됨

    int len = list_length(head);
    int K = len / 2; // 앞 절반을 left로 (len 짝수면 같은 크기, 홀수면 left가 1개 더 가짐)

    Node *left = NULL, *right = NULL;
    partition(head, K, &left, &right);

    left = mergeSort(left);
    right = mergeSort(right);

    return merge(left, right);
}


int main(){
    int n;
    scanf("%d", &n);
    Node *p = NULL, *q = NULL;
    for(int i = 0; i < n; i++){
        int v;
        scanf("%d", &v);
        appendNode(&p, &q, v);
    }

    p = mergeSort(p);
    printList(p);
    freeNode(p);
    return 0;
}