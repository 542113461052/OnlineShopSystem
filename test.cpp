#include<iostream>
#include<cstdio>
#include<bits/stdc++.h>
#include "order.h"
#include "shop.h"
using namespace  std;

int main(){
//    cout<<gettime("���")<<endl;
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
    printOrder(head, "���ھӣ���̫ƽׯ�꣩");
//    shopSuggest(hash2,&head2,shoptype,2);
//        for(int i=0;i<SIZE;i++){
//        printShopList(&hash2->head[i]);
//    }
//    char name[30]={'\0'};
//    strcpy(name,"����Ժ");
//    cout << strcmp(name,"����Ժ");
//    char nodetime[30]={'\0'};
//    strcpy(nodetime,"11��7�����");
//    int node_day=0;
//    int node_month=0;
//    char node_time[20]={'\0'};
//    sscanf(nodetime,"%d��%d��%s��",&node_month,&node_day,node_time);
//    cout << node_month << " " << node_day << " "<< node_time;
}

////��̰���㷨����Դ���·������
//#include <stdio.h>
//#include <stdlib.h>
//#define N 5		// 5�����㣬1��2��3��4��5
//#define M 9999	// maxint��������
//
//void Dijkstra(int n, int v, int dist[], int prev[], int c[][N]);
//void Traceback(int v, int i, int prev[]);
//
//int main()
//{
//    int v = 0;			// Դ��Ϊ1
//    int dist[N ];	// ��Դ������i���������·������
//    int	prev[N ];	// ��Դ������i�����·����ǰһ������
//    // ��Ȩ����ͼ���ڽӾ����к����±��1��ʼ
//    int c[N ][N ] = {
//            {	M,	10,	M,	30,	100	},
//            {	M,	M,	50,	M,	M	},
//            {	M,	M,	M,	M,	10	},
//            {	M,	M,	20,	M,	60	},
//            {	M,	M,	M,	M,	M	},
//    };
//
//    // Dijkstra�㷨
//    Dijkstra(N, v, dist, prev, c);
//
//    // ���
//    printf("Դ��1������4�����·������Ϊ��%d\n", dist[4]);
//    printf("·��Ϊ��");
//    Traceback(0, 4, prev);
//    return 0;
//}
//
//void Dijkstra(int n, int v, int dist[], int prev[], int c[][N])
//{
//    bool s[N];	// ���㼯��s
//    for (int i = 0; i < n; i++)
//    {
//        dist[i] = c[v][i];	// ��Դ������i���������·������
//        s[i] = false;
//
//        if (dist[i] == M)
//            prev[i] = 0;	// ��Դ������i�����·����ǰһ������
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
//        int u = v;			// ��һ����
//
//        // �ҵ������������·���ȵĶ���u
//        for (int j = 0; j < n; j++){
//            if ((!s[j]) && (dist[j] < temp)){
//                u = j;
//                temp = dist[j];
//            }
//        }
//        s[u] = true;
//
//        // ����distֵ
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
////������·�� vԴ�㣬i�յ㣬
//void Traceback(int v, int i, int prev[])
//{
//    // Դ������յ�ʱ�����ҳ�ȫ��·��
//    if (v == i)
//    {
//        printf("%d",i);
//        return;
//    }
//    Traceback(v, prev[i], prev);
//    printf("->%d",i);
//}





