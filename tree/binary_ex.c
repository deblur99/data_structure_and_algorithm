#include <stdio.h>

#define MAX 100

typedef struct _node {
    int valid;
    char *data;
    struct _node *left;
    struct _node *right;
}NODE;

NODE tree[MAX];

void init() {
    for (int i = 0; i < MAX; i++) {
        tree[i].valid = 0;
        tree[i].data = NULL;
        tree[i].left = tree[i].right = NULL;
    }
}

// 어디에 저장되는지 알아야 함 -> 인수 지정
// 첫 번째 매개변수: 저장될 위치, 두 번쨰 매개변수: 저장될 값
void insert(int index, char *data) {
    // 입력받은 값 저장
    tree[index].data = data;
    tree[index].valid = 1;

    // 부모 노드의 위치 계산
    int parentIndex = (index - 1) / 2;

    // 부모 노드의 인덱스는 0 이상이어야 함
    if (parentIndex < 0) return;

    // 저장될 인덱스가 짝수면 오른쪽에 저장
    if (index % 2 == 0)     // right child
        tree[parentIndex].right = &tree[index];
    else
        tree[parentIndex].left = &tree[index];
}

void dfs_preorder(int index) {
    printf("%s ", tree[index].data);
    if (tree[index].left != NULL)
        dfs_preorder(index * 2 + 1);
    if (tree[index].right != NULL)
        dfs_preorder(index * 2 + 2);
}

void dfs_inorder(int index) {
    if (tree[index].left != NULL && tree[index].right != NULL)
        printf("( ");
    if (tree[index].left != NULL)
        dfs_inorder(index * 2 + 1);
    printf("%s ", tree[index].data);
    if (tree[index].right != NULL)
        dfs_inorder(index * 2 + 2);
    if (tree[index].left != NULL && tree[index].right != NULL)
        printf(" )");
}

void dfs_postorder(int index) {
    if (tree[index].left != NULL)
        dfs_postorder(index * 2 + 1);
    if (tree[index].right != NULL)
        dfs_postorder(index * 2 + 2);
    printf("%s ", tree[index].data);
}

NODE *queue[MAX];
int front, rear;

void initQ() {
    for (int i = 0; i < MAX; i++) {
        queue[i] = NULL;
    }

    front = rear = -1;
}

void enqueue(NODE *node) {
    queue[++rear] = node;
    if (front == -1) front++;
}

NODE *dequeue() {
    NODE *node = queue[front];
    if (front == rear)
        front = rear = -1;
    else front++;
    return node;
}

int isEmpty() {
    if (front == -1 && rear == -1) return 1;
    return 0;
}

void bfs() {
    NODE *currentNode = &tree[0];
    initQ();
    while (currentNode != NULL) {
        printf("%s ", currentNode->data);
        if (currentNode->left != NULL)
            enqueue(currentNode->left);
        if (currentNode->right != NULL)
            enqueue(currentNode->right);
        if (!isEmpty())
            currentNode = dequeue();
        else
            currentNode = NULL;
    }
}

void bfsArray() {
    for (int i = 0; i < MAX; i++) {
        if (tree[i].valid)
            printf("%s ", tree[i].data);
    }
}

int main() {
    init();
    insert(0, "+");
    insert(1, "x");
    insert(2, "d");
    insert(3, "a");
    insert(4, "+");    
    insert(9, "b");    
    insert(10, "c");

    //dfs_preorder(0);
    //dfs_inorder(0);
    //dfs_postorder(0);
    bfs();
    printf("\n");
    bfsArray();

    return 0;
}