#include<iostream>
#include <utility>
#include<bits/stdc++.h>
#include<cstring>
using namespace std;
typedef int E;
#define MAX 300
typedef struct OrderListNode {
    E userid;
    char shopname[MAX + 1];
    char time[MAX + 1];
    struct OrderListNode *next;
} *OrderNode;

void initorder(OrderNode head);//初始化预定链表
bool insertOrder(OrderNode head, OrderNode node);//插入预定信息
void OrderDataSave(OrderNode head);//保存预定信息
int gettime(char time[40]);

void printOrderList(OrderNode head);

_Bool deleteOrder(OrderNode head, char shopname[MAX + 1], int index);//删除商家前n条预定
_Bool printOrder(OrderNode head, E userid, char shopname[MAX + 1]);//打印指定用户预定信息
_Bool printOrder(OrderNode head, char shopname[MAX + 1]);//打印商家所有预定信息
void order();//测试用

void initorder(OrderNode head) {
    head->next = nullptr;
    head->userid = 0;
    head->shopname[MAX + 1] = {'\0'};
    head->time[MAX + 1] = {'\0'};
    ifstream infile("../order_temp.txt");
//    string data;
    char data[1024];
    if (!infile) {
        cout << "无法打开预定信息文件" << endl;
    }
    infile.getline(data, sizeof(data));

    while (!infile.eof()) {
        infile.getline(data, sizeof(data));
        OrderNode node = (struct OrderListNode *) malloc(sizeof(struct OrderListNode));
        node->userid = 0;
        node->shopname[MAX + 1] = {'\0'};
        node->time[MAX + 1] = {'\0'};
        char *id = strtok(data, " ");
        if(id!= nullptr)node->userid = atoi(id);
//        cout << node->userid << " ";
        id = strtok(nullptr, " ");
        if(id!= nullptr)strcpy(node->shopname, id);
        id = strtok(nullptr, " ");
        if(id!= nullptr)strcpy(node->time, id);
//        infile.getline(data,sizeof (data));
//        cout << node->time << endl;
//        cout << "用户" << node->userid << " " << "商家名称" <<node->shopname << " " << "时间" << node->time << endl;
        insertOrder(head, node);
    }
    infile.close();
}

void OrderDataSave(OrderNode head) {
    ofstream outfile("../order_temp.txt");
    outfile << "用户账号 \t    商家名称\t\t           预定时间" << endl;
    while (head->next) {
        head = head->next;
        outfile << head->userid << " " << head->shopname << " " << head->time << endl;
    }
}

int gettime(char time[30]) {
    char wan[30] = {'\0'};
    strcpy(wan, "晚餐");
    char zao[30] = {'\0'};
    strcpy(zao, "早餐");
    char zhong[8] = "午餐";
    strcpy(zhong, "午餐");
    if (strcmp(time, wan) == 0)return 3;
    else if (strcmp(time, zhong) == 0)return 2;
    else if (strcmp(time, zao) == 0)return 1;
}

_Bool insertOrder(OrderNode head, OrderNode node) {//添加用户信息
    if (head == nullptr)return false;
    while (head->next) {
        if (strcmp(head->next->shopname, node->shopname) == 0) {
//            cout <<head->next->shopname<< " "<<node->shopname <<endl;
            int node_day = 0;
            int node_month = 0;
            char node_time[20] = {'\0'};
            sscanf(node->time, "%d月%d日%s餐", &node_month, &node_day, node_time);
//            cout << node_month << " " << node_day << " "<< node_time;
            int head_day = 0;
            int head_month = 0;
            char head_time[20] = {'\0'};
            sscanf(head->next->time, "%d月%d日%s餐", &head_month, &head_day, head_time);
//            cout << head_month << " " << head_day << " "<< head_time;
            if (node_month < head_month)break;
            else if (node_month==head_month&&node_day < head_day)break;
            else if (node_month==head_month&&node_day == head_day&&gettime(node_time) < gettime((head_time)))break;
            else if(node_month==head_month&&node_day == head_day&&gettime(node_time) == gettime((head_time)))break;
            else if(head->next->next!= nullptr&&strcmp(head->next->next->shopname, node->shopname) != 0) {
                head=head->next;
                break;
            }
        }
        head = head->next;
        if (head == nullptr)break;
    }
    node->next = head->next;
    head->next = node;
    return true;
}

void printOrderList(OrderNode head) {
    int index = 0;
    while (head->next) {
        head = head->next;
        index++;
        cout << "用户 " << head->userid << " " << "商家名称 " << head->shopname << " " << "时间" << head->time << endl;
    }
}

_Bool deleteOrder(OrderNode head, char shopname[MAX + 1], int index) {
    while (head->next) {
        bool sign = true;
        for (int i = 0; i < MAX + 1; i++) {
            if (head->next->shopname[i] == '\0' && shopname[i] == '\0')break;
            if (head->next->shopname[i] == '\0' && shopname[i] != '\0') {
                sign = false;
                break;
            }
            if (head->next->shopname[i] != shopname[i]) {
                sign = false;
                break;
            }
        }
        if (sign) {
            OrderNode tmp = head->next;   //先拿到待删除结点
            head->next= head->next->next;   //直接让前驱结点指向下一个的下一个结点
            free(tmp);   //最后使用free函数释放掉待删除结点的内存
            index--;
            if (index == 0)return true;
        }
        if (index == 0)return false;
        head = head->next;
    }
    return false;
}

_Bool printOrder(OrderNode head, E userid, char shopname[MAX + 1]) {
    head = head->next;    //先走到第一个结点
    bool sign2 = false;
    while (head) {
        if (head->userid == userid) {
            bool sign = true;
            for (int i = 0; i < MAX + 1; i++) {
                if (head->shopname[i] == '\0' && shopname[i] == '\0')break;
                if (head->shopname[i] == '\0' && shopname[i] != '\0') {
                    sign = false;
                    break;
                }
                if (head->shopname[i] != shopname[i]) {
                    sign = false;
                    break;
                }
            }
            if (sign) {
                cout << "用户 " << head->userid << " " << "时间" << head->time
                     << endl;
                sign2 = true;
            }
        }
        head = head->next;   //没找到就继续向后看
    }
    return sign2;   //都已经走到链表尾部了，那么就确实没找到了，返回-1
}

_Bool printOrder(OrderNode head, char shopname[MAX + 1]) {
    head = head->next;    //先走到第一个结点
    bool sign2 = false;
    int index = 0;
    while (head) {
        bool sign = false;
        for (int i = 0; i < MAX + 1; i++) {
            if (head->shopname[i] == '\0' && shopname[i] == '\0') {
                sign = true;
            }
            if ((shopname[i] != head->shopname[i]) || (shopname[i] != '\0' && head->shopname[i] == '\0'))
                break;
        }
        if (sign) {
            sign2 = true;
            index++;
            cout << "order" << index << ":" << "用户" << head->userid << " " << "时间" << head->time << endl;
        }
        head = head->next;   //没找到就继续向后看
    }
    return sign2;
}

_Bool printOrder(OrderNode head, E userid) {
    head = head->next;    //先走到第一个结点
    bool sign2 = false;
    while (head) {
        if (head->userid == userid) {
                cout << "餐馆 " << head->shopname << " " << "时间 " << head->time
                     << endl;
                sign2 = true;
        }
        head = head->next;   //没找到就继续向后看
    }
    return sign2;   //都已经走到链表尾部了，那么就确实没找到了，返回-1
}

void order() {
    struct OrderListNode head;
    initorder(&head);
    OrderNode node = (struct OrderListNode *) malloc(sizeof(struct OrderListNode));
    node->userid = 0;
    node->shopname[MAX + 1] = {'\0'};
    node->time[MAX + 1] = {'\0'};
//    cin >> node->userid;
//    node->userid=190001;
//    cin >> node->shopname;
//    cin >> node->time;
//    insertOrder(&head,node);
//    printOrder(&head,node->userid);
//    printOrder(&head,"鼎坤朋湘菜馆");
    printOrderList(&head);
//    cout << deleteOrder(&head, node->shopname, 2) << endl;
//    OrderDataSave(&head);
}