#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 100
#define MAX_QUEUE 100

// Khai báo cấu trúc đồ thị
typedef struct {
    int n; // số đỉnh
    int a[MAX_VERTICES][MAX_VERTICES]; // ma trận kề
} Graph;

// Khai báo cấu trúc danh sách liên kết
typedef struct {
    int data[MAX_QUEUE];
    int front, rear;
} Queue;

// Khởi tạo danh sách liên kết
void makeNullQueue(Queue *q) {
    q->front = -1;
    q->rear = -1;
}

// Kiểm tra danh sách liên kết rỗng
int isEmptyQueue(Queue *q) {
    return q->front == -1;
}

// Kiểm tra danh sách liên kết đầy
int isFullQueue(Queue *q) {
    return (q->rear - q->front + 1) == MAX_QUEUE;
}

// Thêm phần tử vào danh sách liên kết
void enQueue(Queue *q, int x) {
    if (isFullQueue(q)) {
        printf("Queue is full!\n");
    } else {
        if (isEmptyQueue(q)) {
            q->front = 0;
        }
        q->rear++;
        q->data[q->rear] = x;
    }
}

// Lấy phần tử ra khỏi danh sách liên kết
int deQueue(Queue *q) {
    if (isEmptyQueue(q)) {
        printf("Queue is empty!\n");
        return -1;
    } else {
        int x = q->data[q->front];
        q->front++;
        if (q->front > q->rear) {
            makeNullQueue(q);
        }
        return x;
    }
}

// Khởi tạo đồ thị
void initGraph(Graph *G, int n) {
    G->n = n;
    int i, j;
    for (i = 1; i <= n; i++) {
        for (j = 1; j <= n; j++) {
            G->a[i][j] = 0;
        }
    }
}

// Thêm cạnh vào đồ thị
void addEdge(Graph *G, int x, int y) {
    G->a[x][y] = 1;
    G->a[y][x] = 1;
}

// Tô màu các đỉnh của đồ thị
void colorGraph(Graph *G) {
    int color[MAX_VERTICES];
    int i, j, k;
    for (i = 1; i <= G->n; i++) {
        color[i] = 0;
    }
    int count = 0;
    // Duyệt qua tất cả các đỉnh của đồ thị
for (i = 1; i <= G->n; i++) {
if (color[i] == 0) { // Nếu đỉnh chưa được tô màu
count++;
color[i] = count; // Tô màu cho đỉnh hiện tại
Queue q;
makeNullQueue(&q);
enQueue(&q, i);
while (!isEmptyQueue(&q)) { // Duyệt BFS để tô màu cho các đỉnh kề
int u = deQueue(&q);
for (j = 1; j <= G->n; j++) {
if (G->a[u][j] != 0 && color[j] == 0) {
color[j] = count;
enQueue(&q, j);
}
}
}
}
}// In kết quả
printf("Total number of colors used: %d\n", count);
for (k = 1; k <= count; k++) {
    printf("Color %d: ", k);
    for (i = 1; i <= G->n; i++) {
        if (color[i] == k) {
            printf("%d ", i);
        }
    }
    printf("\n");
}
}

int main() {
Graph G;
int n, m, u, v, i;
// Nhập đồ thị
printf("Enter number of vertices: ");
scanf("%d", &n);
initGraph(&G, n);
printf("Enter number of edges: ");
scanf("%d", &m);
for (i = 1; i <= m; i++) {
    printf("Enter edge %d (u v): ", i);
    scanf("%d %d", &u, &v);
    addEdge(&G, u, v);
}

// Tô màu đồ thị
colorGraph(&G);

return 0;
}
