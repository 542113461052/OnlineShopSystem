#include<iostream>
#include<cstdio>
#include<bits/stdc++.h>
#include "order.h"
#include "shop.h"
using namespace  std;

int main(){
//    cout<<gettime("早餐")<<endl;
//    order();
//    Hash hash = (struct HashTable *) malloc(sizeof(struct HashTable));
//    initHashTable(hash);
//    initShop(hash);
//    struct SuggestListNode head;
//    initSuggestList(&head);
////    for(int i=0;i<SIZE;i++){
////        printShopList(&hash->head[i]);
////    }
//    ShopDataSave(hash);
//    Hash hash2 = (struct HashTable *) malloc(sizeof(struct HashTable));
//    initHashTable(hash2);
//    initShop(hash2);
//    struct SuggestListNode head2;
//    initSuggestList(&head2);
//    SE shoptype[MAX+1]={'\0'};
//    cin >> shoptype;
    OrderNode head= (struct OrderListNode *) malloc(sizeof(struct OrderListNode));
    initshop(head);
    printOrder(head, "福口居（北太平庄店）");
//    shopSuggest(hash2,&head2,shoptype,2);
//        for(int i=0;i<SIZE;i++){
//        printShopList(&hash2->head[i]);
//    }
//    char name[30]={'\0'};
//    strcpy(name,"丽春院");
//    cout << strcmp(name,"丽春院");
//    char nodetime[30]={'\0'};
//    strcpy(nodetime,"11月7日晚餐");
//    int node_day=0;
//    int node_month=0;
//    char node_time[20]={'\0'};
//    sscanf(nodetime,"%d月%d日%s餐",&node_month,&node_day,node_time);
//    cout << node_month << " " << node_day << " "<< node_time;
}

////【贪心算法】单源最短路径问题
//#include <stdio.h>
//#include <stdlib.h>
//#define N 5		// 5个顶点，1、2、3、4、5
//#define M 9999	// maxint，大整数
//
//void Dijkstra(int n, int v, int dist[], int prev[], int c[][N]);
//void Traceback(int v, int i, int prev[]);
//
//int main()
//{
//    int v = 0;			// 源点为1
//    int dist[N ];	// 从源到顶点i的最短特殊路径长度
//    int	prev[N ];	// 从源到顶点i的最短路径上前一个顶点
//    // 带权有向图的邻接矩阵，行和列下标从1开始
//    int c[N ][N ] = {
//            {	M,	10,	M,	30,	100	},
//            {	M,	M,	50,	M,	M	},
//            {	M,	M,	M,	M,	10	},
//            {	M,	M,	20,	M,	60	},
//            {	M,	M,	M,	M,	M	},
//    };
//
//    // Dijkstra算法
//    Dijkstra(N, v, dist, prev, c);
//
//    // 输出
//    printf("源点1到顶点4的最短路径长度为：%d\n", dist[4]);
//    printf("路径为：");
//    Traceback(0, 4, prev);
//    return 0;
//}
//
//void Dijkstra(int n, int v, int dist[], int prev[], int c[][N])
//{
//    bool s[N];	// 顶点集合s
//    for (int i = 0; i < n; i++)
//    {
//        dist[i] = c[v][i];	// 从源到顶点i的最短特殊路径长度
//        s[i] = false;
//
//        if (dist[i] == M)
//            prev[i] = 0;	// 从源到顶点i的最短路径上前一个顶点
//        else
//            prev[i] = v;
//    }
//
//    dist[v] = 0;
//    s[v] = true;
//
//    for (int i = 0; i < n-1; i++)
//    {
//        int temp = M;		//
//        int u = v;			// 上一顶点
//
//        // 找到具有最短特殊路长度的顶点u
//        for (int j = 0; j < n; j++){
//            if ((!s[j]) && (dist[j] < temp)){
//                u = j;
//                temp = dist[j];
//            }
//        }
//        s[u] = true;
//
//        // 更新dist值
//        for (int j = 0; j < n; j++)
//        {
//            if ((!s[j]) && (c[u][j] < M))
//            {
//                int newdist = dist[u] + c[u][j];
//                if (newdist < dist[j])
//                {
//                    dist[j] = newdist;
//                    prev[j] = u;
//                }
//            }
//        }
//    }
//}
////输出最短路径 v源点，i终点，
//void Traceback(int v, int i, int prev[])
//{
//    // 源点等于终点时，即找出全部路径
//    if (v == i)
//    {
//        printf("%d",i);
//        return;
//    }
//    Traceback(v, prev[i], prev);
//    printf("->%d",i);
//}





