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

void initorder(OrderNode head);//��ʼ��Ԥ������
bool insertOrder(OrderNode head, OrderNode node);//����Ԥ����Ϣ
void OrderDataSave(OrderNode head);//����Ԥ����Ϣ
int gettime(char time[40]);

void printOrderList(OrderNode head);

_Bool deleteOrder(OrderNode head, char shopname[MAX + 1], int index);//ɾ���̼�ǰn��Ԥ��
_Bool printOrder(OrderNode head, E userid, char shopname[MAX + 1]);//��ӡָ���û�Ԥ����Ϣ
_Bool printOrder(OrderNode head, char shopname[MAX + 1]);//��ӡ�̼�����Ԥ����Ϣ
void order();//������

void initorder(OrderNode head) {
    head->next = nullptr;
    head->userid = 0;
    head->shopname[MAX + 1] = {'\0'};
    head->time[MAX + 1] = {'\0'};
    ifstream infile("../order_temp.txt");
//    string data;
    char data[1024];
    if (!infile) {
        cout << "�޷���Ԥ����Ϣ�ļ�" << endl;
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
//        cout << "�û�" << node->userid << " " << "�̼�����" <<node->shopname << " " << "ʱ��" << node->time << endl;
        insertOrder(head, node);
    }
    infile.close();
}

void OrderDataSave(OrderNode head) {
    ofstream outfile("../order_temp.txt");
    outfile << "�û��˺� \t    �̼�����\t\t           Ԥ��ʱ��" << endl;
    while (head->next) {
        head = head->next;
        outfile << head->userid << " " << head->shopname << " " << head->time << endl;
    }
}

int gettime(char time[30]) {
    char wan[30] = {'\0'};
    strcpy(wan, "���");
    char zao[30] = {'\0'};
    strcpy(zao, "���");
    char zhong[8] = "���";
    strcpy(zhong, "���");
    if (strcmp(time, wan) == 0)return 3;
    else if (strcmp(time, zhong) == 0)return 2;
    else if (strcmp(time, zao) == 0)return 1;
}

_Bool insertOrder(OrderNode head, OrderNode node) {//����û���Ϣ
    if (head == nullptr)return false;
    while (head->next) {
        if (strcmp(head->next->shopname, node->shopname) == 0) {
//            cout <<head->next->shopname<< " "<<node->shopname <<endl;
            int node_day = 0;
            int node_month = 0;
            char node_time[20] = {'\0'};
            sscanf(node->time, "%d��%d��%s��", &node_month, &node_day, node_time);
//            cout << node_month << " " << node_day << " "<< node_time;
            int head_day = 0;
            int head_month = 0;
            char head_time[20] = {'\0'};
            sscanf(head->next->time, "%d��%d��%s��", &head_month, &head_day, head_time);
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
        cout << "�û� " << head->userid << " " << "�̼����� " << head->shopname << " " << "ʱ��" << head->time << endl;
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
            OrderNode tmp = head->next;   //���õ���ɾ�����
            head->next= head->next->next;   //ֱ����ǰ�����ָ����һ������һ�����
            free(tmp);   //���ʹ��free�����ͷŵ���ɾ�������ڴ�
            index--;
            if (index == 0)return true;
        }
        if (index == 0)return false;
        head = head->next;
    }
    return false;
}

_Bool printOrder(OrderNode head, E userid, char shopname[MAX + 1]) {
    head = head->next;    //���ߵ���һ�����
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
                cout << "�û� " << head->userid << " " << "ʱ��" << head->time
                     << endl;
                sign2 = true;
            }
        }
        head = head->next;   //û�ҵ��ͼ������
    }
    return sign2;   //���Ѿ��ߵ�����β���ˣ���ô��ȷʵû�ҵ��ˣ�����-1
}

_Bool printOrder(OrderNode head, char shopname[MAX + 1]) {
    head = head->next;    //���ߵ���һ�����
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
            cout << "order" << index << ":" << "�û�" << head->userid << " " << "ʱ��" << head->time << endl;
        }
        head = head->next;   //û�ҵ��ͼ������
    }
    return sign2;
}

_Bool printOrder(OrderNode head, E userid) {
    head = head->next;    //���ߵ���һ�����
    bool sign2 = false;
    while (head) {
        if (head->userid == userid) {
                cout << "�͹� " << head->shopname << " " << "ʱ�� " << head->time
                     << endl;
                sign2 = true;
        }
        head = head->next;   //û�ҵ��ͼ������
    }
    return sign2;   //���Ѿ��ߵ�����β���ˣ���ô��ȷʵû�ҵ��ˣ�����-1
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
//    printOrder(&head,"��������˹�");
    printOrderList(&head);
//    cout << deleteOrder(&head, node->shopname, 2) << endl;
//    OrderDataSave(&head);
}