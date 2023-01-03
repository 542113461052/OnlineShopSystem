#include<iostream>
#include "user.h"
#include"shop.h"
#include "order.h"
#include "distance.h"

using namespace std;
typedef int E;
typedef char SE;
#define MAXFood 100
#define MAXPassword 20
void distance(char shopname[MAX+1]);//��̾���
_Bool uIm(UserNode head, E userid, char *password);//�û������˵�
_Bool userToshop(E userid,  int choice);
void userMenu(UserNode head, E userid, char *password);//�û��˵�
_Bool sIm1(Hash hash, SE shopname[MAX+1]);//�̼Ҷ����˵�
void sIm2(SE shopname[MAX + 1]);//�̼Ҷ����˵�
void sMenu(Hash hash, SE shopname[MAX + 1], SE password[MAXPassword + 1]);//�̼Ҳ˵�
void login();//ע��

//distance
void distance(char shopname[MAX+1]) {
    struct MatrixGraph graph;
    init(&graph);
    create(&graph);
//    cout << getindex(&graph,4817740);
    Dijkstra(&graph, getindex(&graph, "֣���Ṥҵ��ѧ"));
    cout << "·��:";
    Traceback(&graph, getindex(&graph, "֣���Ṥҵ��ѧ"), getindex(&graph, shopname));
//    print(&graph);
    cout << "\nԴ��1������4�����·������Ϊ��" << graph.data[4].path << endl;
}
// user
_Bool uIm(UserNode head, E userid, char *password) {
    cout << "=====================" << endl;
    //��ӡ�û���Ϣ
    printUser(head, userid);
    cout << "0.�޸��û���Ϣ" << endl;
    cout << "1.ע���û�" << endl;
    cout << "2.�˳�" << endl;
    int choice;
    cin >> choice;
    if (choice == 1) {
        deleteUser(head, userid);
        cout << "�û���ע��" << endl;
        UserDataSave(head);
        exit(0);
    } else if (choice == 0) {
        cout << "�����������룺" << endl;
        char newpassword[7];
        for (int i = 0; i < 6; i++) {
            cin >> newpassword[i];
        }
        newpassword[6] = '\0';
        cout << "�������µ绰��" << endl;
        char newphone[12];
        for (int i = 0; i < 11; i++) {
            cin >> newphone[i];
        }
        newphone[11] = '\0';
        modifyUser(head, userid, newpassword, newphone);
//        modifyUser(head,userid,"123456","12345678901");
        cout << "�û���Ϣ�޸����" << endl;
        UserDataSave(head);
        return true;
    } else if (choice == 2) {
        return true;
    }
}
_Bool userToshop(E userid,  int choice) {
    Hash hash = (struct HashTable *) malloc(sizeof(struct HashTable));
    initHashTable(hash);
    initShop(hash);
//    cout<<"123"<<endl;
    switch (choice) {
        case 2:{
            cout << "��������Ҫ��ѯ�Ĳ͹���" << endl;
            SE shopname[MAX+1]={'\0'};
            cin >> shopname;
            if(printShop(&hash->head[gethash(shopname)], shopname, false)){
                distance(shopname);
            }else{
                cout << "���޴˲͹�" << endl;
            }
        }break;
        case 3: {
            cout << "1.Ԥ���͹�"<<endl;
            cout << "2.��ѯ����Ԥ��"<<endl;
            cout << "3.��ѯָ���͹ݵ�Ԥ��"<<endl;
            int mode;
            cin >>mode;
            struct OrderListNode Orderhead;
            initorder(&Orderhead);
            switch (mode) {
                case 1:{
                    cout << "������͹���" << endl;
                    SE shopname[MAX+1]={'\0'};
                    cin >> shopname;
                    if (!findShop(&hash->head[gethash(shopname)], shopname))return false;
                    OrderNode node = (struct OrderListNode *) malloc(sizeof(struct OrderListNode));
                    if (node == nullptr)return false;
                    node->userid = userid;
                    node->shopname[MAX + 1] = {'\0'};
                    node->time[MAX + 1] = {'\0'};
                    strcpy(node->shopname, shopname);
                    cout << "ʱ��" << endl;
                    cin >> node->time;
                    insertOrder(&Orderhead, node);
                    cout << "Ԥ���ɹ�" << endl;
                    OrderDataSave(&Orderhead);
                    return true;
                }break;
                case 2:{
                        printOrder(&Orderhead,userid);
                    return true;
                };break;
                case 3:{
                    cout << "�͹���"<<endl;
                    SE shopname[MAX+1]={'\0'};
                    cin >> shopname;
                    printOrder(&Orderhead,userid,shopname);
                    return true;
                }break;
            }
        }
        case 4: {
            struct SuggestListNode head;
            initSuggestList(&head);
            cout << "1.���ݲ͹����ͽ����Ƽ�"<<endl;
            cout << "2.���ݲ͹���ɫ�˽����Ƽ�"<<endl;
            int mode;
            cin >>mode;
            switch (mode) {
                case 1:{
                    cout << "�͹�����"<<endl;
                    SE shoptype[MAX+1]={'\0'};
                    cin >>shoptype;
                    if(!shopSuggest(hash,&head,shoptype,1)){
                        cout << "�޲͹�" << endl;
                    }

                }break;
                case 2:{
                    cout << "��ɫ��"<<endl;
                    SE foodname[MAX+1]={'\0'};
                    cin >>foodname;
                    if(!shopSuggest(hash,&head,foodname,2)){
                        cout << "�޲͹�" << endl;
                    }
                }break;
            }


            return true;
        }
    }
}
void userMenu(UserNode head, E userid, char *password) {
    while (true) {
        cout << "=====================" << endl;
        cout << "��ӭ�����û���ϵͳ" << endl;
        cout << "��ѡ����Ҫʹ�õĹ���>>>" << endl;
        cout << "1.������Ϣ����" << endl;
        cout << "2.�͹ݲ�ѯ" << endl;
        cout << "3.�͹�Ԥ��" << endl;
        cout << "4.�͹��Ƽ�" << endl;
        cout << "5.�˳�ϵͳ" << endl;
        int choice;
        cin >> choice;
        switch (choice) {
            case 1:
                uIm(head, userid, password);
                break;
            case 2: {
                userToshop(0,  2);
            }
                break;
            case 3: {
                userToshop(userid,  3);
            }
                break;
            case 4: {
                userToshop(0, 4);
            }
                break;
            case 5: {
                UserDataSave(head);
                return;
            }
        }
    }
}
//shop
_Bool sIm1(Hash hash, SE shopname[MAX+1]) {//�͹���Ϣ����
    cout << "=====================" << endl;
    //��ӡ�͹���Ϣ
    printShop(&hash->head[gethash(shopname)], shopname);
    cout << "0.�޸Ĳ͹���Ϣ" << endl;
    cout << "1.ע���͹�" << endl;
    cout << "2.�˳�" << endl;
    int choice;
    cin >> choice;
    if (choice == 1) {
        if (deleteShop(&hash->head[gethash(shopname)], shopname)) {
            cout << "�͹���ע��" << endl;
            ShopDataSave(hash);
            exit(0);
        }
        return false;
    } else if (choice == 0) {
        if (modifyShop(&hash->head[gethash(shopname)], shopname)) {
            cout << "�͹���Ϣ�޸����" << endl;
            ShopDataSave(hash);
            return true;
        }
        return false;
    } else if (choice == 2) {
        ShopDataSave(hash);
        return true;
    }
}
void sIm2(SE shopname[MAX + 1]) {//�͹�Ԥ����Ϣ����
    cout << "=====================" << endl;
    cout << "0.��ѯ�͹�����Ԥ��" << endl;
    cout << "1.��ѯָ���û���Ԥ��" << endl;
    cout << "2.����Ԥ��" << endl;
    int choice;
    cin >> choice;
    OrderNode head= (struct OrderListNode *) malloc(sizeof(struct OrderListNode));
    initorder(head);
    OrderNode node = (struct OrderListNode *) malloc(sizeof(struct OrderListNode));
    node->userid = 0;
    node->shopname[MAX + 1] = {'\0'};
    node->time[MAX + 1] = {'\0'};
    switch (choice) {
        case 0:
            printOrder(head, shopname);
//            cout << "�͹�����Ԥ��" << endl;
            break;
        case 1: {
            cout << "�û�ID" << endl;
            cin >> node->userid;
            printOrder(head, node->userid, shopname);
//            cout << node->userid << shopname<<endl;
        }
            break;
        case 2: {
            cout << "��������" << endl;
            int index = 0;
            cin>>index;
            if (deleteOrder(head, shopname, index)) {
                cout << "����ɹ�" << endl;
                OrderDataSave(head);
            };
        }
    }
}
void sMenu(Hash hash, SE shopname[MAX + 1], SE password[MAXPassword + 1]) {
    while (true) {
        cout << "=====================" << endl;
        cout << "��ӭ�����̼���ϵͳ" << endl;
        cout << "��ѡ����Ҫʹ�õĹ���>>>" << endl;
        cout << "1.�͹���Ϣ����" << endl;
        cout << "2.�͹�Ԥ����Ϣ����" << endl;
        cout << "3.�˳�ϵͳ" << endl;
        int choice;
        cin >> choice;
        switch (choice) {
            case 1: {
                sIm1(hash, shopname);
            }
                break;
            case 2:
                sIm2(shopname);
                break;
            case 3: {
                ShopDataSave(hash);
                return;
            }

        }
    }
}

void login() {
    cout << "��ӭʹ�ñ��͹�Ԥ������ϵͳ" << endl;
    cout << "��ѡ�����Ľ�ɫ>>>0.�̼�,1.�����û�" << endl;
    int role;
    cin >> role;
    if (role == 0) {
        cout << "�������˺ţ�" << endl;
        SE shopname[MAX + 1] = {'\0'};
        cin >> shopname;
        cout << "���������룺" << endl;
        SE password[MAXPassword + 1] = {'\0'};
        cin >> password;
        struct HashTable hash;
        initHashTable(&hash);
        initShop(&hash);
        if (!checkShop(&hash.head[gethash(shopname)], shopname, password)) {
            cout << "�˺Ż����������" << endl;
            return;
        }
        sMenu(&hash, shopname, password);
    } else if (role == 1) {
        cout << "��ѡ�񣺵�½��1������ע�ᣨ2��" << endl;
        int choice;
        cin >> choice;

        if(choice==1){
            // user
            cout << "�������˺ţ�" << endl;
            E userid;
            cin >> userid;
            cout << "���������룺" << endl;
            char password[7] = {'\0'};
            cin >> password;
            struct UserListNode head;
            inituser(&head);//��ʼ��user��
            //����½
            if (!CheckUser(&head, userid, password)) {
                cout << "�˺Ż����������" << endl;
                return;
            }
            userMenu(&head, userid, password);
        }else if(choice==2){
            cout << "�������������룺"<<endl;
            char password[7]={'\0'};
            cin >>password;
            cout << "������������ϵ��ʽ��"<<endl;
            char phone[13]={'\0'};
            cin >>phone;
            struct UserListNode head;
            inituser(&head);//��ʼ��user��
            struct UserListNode temp_head=head;
            while(head.next){
                head=*head.next;
            }
            insertUser(&temp_head,head.userid+1,password,phone);
            UserDataSave(&temp_head);
            cout << "�����˺�Ϊ:"<<(head.userid+1)<<endl;
        }

    }
}

int main() {
    login();
}