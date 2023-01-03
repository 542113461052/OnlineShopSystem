#include<iostream>
#include<bits/stdc++.h>
#include <cstdio>
#include <utility>

typedef long long DE;
#define MaxVertex 843
#define MAX 300
#define MaxPath 100

using namespace std;
typedef struct Shop {
    DE shopId;
    char shopName[MAX + 1];
    double path;
    int pre;
} Shop;

typedef struct MatrixGraph {
    int vertexCount;   //顶点数
    int edgeCount;     //边数
    double **matrix;   //邻接矩阵
    Shop data[MaxVertex];    //各个顶点对应的数据
} *Graph;

void init(Graph graph);//初始化图
void addVertex(Graph graph, Shop shop);//添加顶点
int getindex(Graph graph, char shopname[MAX+1]);//获取顶点下标
void addEdge(Graph graph, int a, int b, double distance);//添加边
void create(Graph graph);//建图
void Dijkstra(Graph graph, int v);//Dijkstra算法
void Traceback(Graph graph, int start, int end);//输出最短路径

void init(Graph graph) {   //创建时，我们可以指定图中初始有多少个结点
    graph->matrix = (double **) malloc(MaxVertex * sizeof(double *));
    for (int i = 0; i < MaxVertex; i++) {
        graph->matrix[i] = (double *) malloc(MaxVertex * sizeof(double));
    }
    graph->vertexCount = 0;    //顶点和边数肯定一开始是0
    graph->edgeCount = 0;
    for (int i = 0; i < MaxVertex; ++i)    //记得把矩阵每个位置都置为0
        for (int j = 0; j < MaxVertex; ++j)
            graph->matrix[i][j] = MaxPath;
//    graph->matrix[MaxVertex][MaxVertex]={0};
}

void addVertex(Graph graph, Shop shop) {
    if (graph->vertexCount >= MaxVertex) return;
    graph->data[graph->vertexCount++] = shop;   //添加新元素
}

int getindex(Graph graph, char shopname[MAX+1]) {
    for (int i = 0; i < graph->vertexCount; i++){
        bool shopname_sign = true;
        for(int j=0;j<MAX+1;j++){
            if(graph->data[i].shopName[j]!=shopname[j]){
                shopname_sign= false;
                break;
            }
            if(graph->data[i].shopName[j]=='\0'&&shopname[j]=='\0')break;
        }
        if (shopname_sign)return i;
    }
    return -1;
}

void addEdge(Graph graph, int a, int b, double distance) {   //添加几号顶点到几号顶点的边
    if (graph->matrix[a][b] == MaxPath) {
        graph->matrix[a][b] = distance;  //注意如果是无向图的话，需要[a][b]和[b][a]都置为1
        graph->matrix[b][a] = distance;
        graph->edgeCount++;
    }
}

void create(Graph graph) {
    ifstream infile("../distance_temp.txt");
//    string data;
    char data[1024];
    if (!infile) {
        cout << "无法打开距离信息文件" << endl;
    }
    infile.getline(data, sizeof(data));
    infile.getline(data, sizeof(data));
    while (!infile.eof()) {

        Shop shop1;
        shop1.shopId = 0;
        shop1.shopName[MAX + 1] = {'\0'};
        Shop shop2;
        shop2.shopId = 0;
        shop2.shopName[MAX + 1] = {'\0'};

        char distance[MAX + 1] = {'\0'};
        char *temp = nullptr;

        temp = strtok(data, " ");
        char shopid[MAX + 1];
        strcpy(shopid, temp);
//        cout<< shopid << " ";
        shop1.shopId = atof(shopid);
//        cout << shop1.shopId << " ";

        temp = strtok(nullptr, " ");
        strcpy(shop1.shopName, temp);
//        cout<< shop1.shopName << " ";

        temp = strtok(nullptr, " ");
        strcpy(shopid, temp);
//        cout<< shopid << " ";
        shop2.shopId = atof(shopid);
//        cout << shop2.shopId << " ";
        temp = strtok(nullptr, " ");
//        cout << temp << endl;
        strcpy(shop2.shopName, temp);
//        cout<< shop2.shopName << " ";

        temp = strtok(nullptr, " ");
        strcpy(distance, temp);
//        cout<< shopid << endl;
//        sscanf(data, "%s %s %s %s %s", shop1.shopiId,shop1.shopName,shop2.shopiId,shop2.shopName,tempdistance);
//        cout << shop1.shopId << " " << shop1.shopName<<" "<<shop2.shopId<< " "<< shop2.shopName<<" "<<stof(shopid) <<endl;
        if (getindex(graph, shop1.shopName) == -1) {
            addVertex(graph, shop1);
        }
        if (getindex(graph, shop2.shopName) == -1) {
            addVertex(graph, shop2);
        }
        addEdge(graph, getindex(graph, shop1.shopName), getindex(graph, shop2.shopName), atof(distance));
        infile.getline(data, sizeof(data));
    }
    infile.close();

}

void Dijkstra(Graph graph, int v) {
    bool s[MaxVertex];    // 顶点集合s
    for (int i = 0; i < MaxVertex; i++) {
        graph->data[i].path = graph->matrix[v][i];    // 从源到顶点i的最短特殊路径长度
        s[i] = false;

        if (graph->data[i].path == MaxPath)
            graph->data[i].pre = 0;    // 从源到顶点i的最短路径上前一个顶点
        else
            graph->data[i].pre = v;
    }

    graph->data[v].path = 0;
    s[v] = true;

    for (int i = 0; i < MaxVertex - 1; i++) {
        int temp = MaxPath;        //
        int u = v;            // 上一顶点

        // 找到具有最短特殊路长度的顶点u
        for (int j = 0; j < MaxVertex; j++) {
            if ((!s[j]) && (graph->data[j].path < temp)) {
                u = j;
                temp = graph->data[j].path;
            }
        }
        s[u] = true;

        // 更新dist值
        for (int j = 0; j < MaxVertex; j++) {
            if ((!s[j]) && (graph->matrix[u][j] < MaxPath)) {
                double newdist = graph->data[u].path + graph->matrix[u][j];
                if (newdist < graph->data[j].path) {
                    graph->data[j].path = newdist;
                    graph->data[j].pre = u;
                }
            }
        }
    }
}

void Traceback(Graph graph, int start, int end) {
    // 源点等于终点时，即找出全部路径
    if (start == end) {
//        printf("%d",end);
        cout << graph->data[end].shopName;
        return;
    }
    Traceback(graph, start, graph->data[end].pre);
//    printf("->%lf",end);
    cout << "->" << graph->data[end].shopName;
}



