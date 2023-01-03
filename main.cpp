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
void distance(char shopname[MAX+1]);//最短距离
_Bool uIm(UserNode head, E userid, char *password);//用户二级菜单
_Bool userToshop(E userid,  int choice);
void userMenu(UserNode head, E userid, char *password);//用户菜单
_Bool sIm1(Hash hash, SE shopname[MAX+1]);//商家二级菜单
void sIm2(SE shopname[MAX + 1]);//商家二级菜单
void sMenu(Hash hash, SE shopname[MAX + 1], SE password[MAXPassword + 1]);//商家菜单
void login();//注册

//distance
void distance(char shopname[MAX+1]) {
    struct MatrixGraph graph;
    init(&graph);
    create(&graph);
//    cout << getindex(&graph,4817740);
    Dijkstra(&graph, getindex(&graph, "郑州轻工业大学"));
    cout << "路径:";
    Traceback(&graph, getindex(&graph, "郑州轻工业大学"), getindex(&graph, shopname));
//    print(&graph);
    cout << "\n源点1到顶点4的最短路径长度为：" << graph.data[4].path << endl;
}
// user
_Bool uIm(UserNode head, E userid, char *password) {
    cout << "=====================" << endl;
    //打印用户信息
    printUser(head, userid);
    cout << "0.修改用户信息" << endl;
    cout << "1.注销用户" << endl;
    cout << "2.退出" << endl;
    int choice;
    cin >> choice;
    if (choice == 1) {
        deleteUser(head, userid);
        cout << "用户已注销" << endl;
        UserDataSave(head);
        exit(0);
    } else if (choice == 0) {
        cout << "请输入新密码：" << endl;
        char newpassword[7];
        for (int i = 0; i < 6; i++) {
            cin >> newpassword[i];
        }
        newpassword[6] = '\0';
        cout << "请输入新电话：" << endl;
        char newphone[12];
        for (int i = 0; i < 11; i++) {
            cin >> newphone[i];
        }
        newphone[11] = '\0';
        modifyUser(head, userid, newpassword, newphone);
//        modifyUser(head,userid,"123456","12345678901");
        cout << "用户信息修改完毕" << endl;
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
            cout << "请输入你要查询的餐馆名" << endl;
            SE shopname[MAX+1]={'\0'};
            cin >> shopname;
            if(printShop(&hash->head[gethash(shopname)], shopname, false)){
                distance(shopname);
            }else{
                cout << "查无此餐馆" << endl;
            }
        }break;
        case 3: {
            cout << "1.预定餐馆"<<endl;
            cout << "2.查询所有预定"<<endl;
            cout << "3.查询指定餐馆的预定"<<endl;
            int mode;
            cin >>mode;
            struct OrderListNode Orderhead;
            initorder(&Orderhead);
            switch (mode) {
                case 1:{
                    cout << "请输入餐馆名" << endl;
                    SE shopname[MAX+1]={'\0'};
                    cin >> shopname;
                    if (!findShop(&hash->head[gethash(shopname)], shopname))return false;
                    OrderNode node = (struct OrderListNode *) malloc(sizeof(struct OrderListNode));
                    if (node == nullptr)return false;
                    node->userid = userid;
                    node->shopname[MAX + 1] = {'\0'};
                    node->time[MAX + 1] = {'\0'};
                    strcpy(node->shopname, shopname);
                    cout << "时间" << endl;
                    cin >> node->time;
                    insertOrder(&Orderhead, node);
                    cout << "预定成功" << endl;
                    OrderDataSave(&Orderhead);
                    return true;
                }break;
                case 2:{
                        printOrder(&Orderhead,userid);
                    return true;
                };break;
                case 3:{
                    cout << "餐馆名"<<endl;
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
            cout << "1.根据餐馆类型进行推荐"<<endl;
            cout << "2.根据餐馆特色菜进行推荐"<<endl;
            int mode;
            cin >>mode;
            switch (mode) {
                case 1:{
                    cout << "餐馆类型"<<endl;
                    SE shoptype[MAX+1]={'\0'};
                    cin >>shoptype;
                    if(!shopSuggest(hash,&head,shoptype,1)){
                        cout << "无餐馆" << endl;
                    }

                }break;
                case 2:{
                    cout << "特色菜"<<endl;
                    SE foodname[MAX+1]={'\0'};
                    cin >>foodname;
                    if(!shopSuggest(hash,&head,foodname,2)){
                        cout << "无餐馆" << endl;
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
        cout << "欢迎进入用户子系统" << endl;
        cout << "请选择您要使用的功能>>>" << endl;
        cout << "1.个人信息管理" << endl;
        cout << "2.餐馆查询" << endl;
        cout << "3.餐馆预订" << endl;
        cout << "4.餐馆推荐" << endl;
        cout << "5.退出系统" << endl;
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
_Bool sIm1(Hash hash, SE shopname[MAX+1]) {//餐馆信息管理
    cout << "=====================" << endl;
    //打印餐馆信息
    printShop(&hash->head[gethash(shopname)], shopname);
    cout << "0.修改餐馆信息" << endl;
    cout << "1.注销餐馆" << endl;
    cout << "2.退出" << endl;
    int choice;
    cin >> choice;
    if (choice == 1) {
        if (deleteShop(&hash->head[gethash(shopname)], shopname)) {
            cout << "餐馆已注销" << endl;
            ShopDataSave(hash);
            exit(0);
        }
        return false;
    } else if (choice == 0) {
        if (modifyShop(&hash->head[gethash(shopname)], shopname)) {
            cout << "餐馆信息修改完毕" << endl;
            ShopDataSave(hash);
            return true;
        }
        return false;
    } else if (choice == 2) {
        ShopDataSave(hash);
        return true;
    }
}
void sIm2(SE shopname[MAX + 1]) {//餐馆预订信息管理
    cout << "=====================" << endl;
    cout << "0.查询餐馆所有预订" << endl;
    cout << "1.查询指定用户的预订" << endl;
    cout << "2.处理预订" << endl;
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
//            cout << "餐馆所有预订" << endl;
            break;
        case 1: {
            cout << "用户ID" << endl;
            cin >> node->userid;
            printOrder(head, node->userid, shopname);
//            cout << node->userid << shopname<<endl;
        }
            break;
        case 2: {
            cout << "处理条数" << endl;
            int index = 0;
            cin>>index;
            if (deleteOrder(head, shopname, index)) {
                cout << "处理成功" << endl;
                OrderDataSave(head);
            };
        }
    }
}
void sMenu(Hash hash, SE shopname[MAX + 1], SE password[MAXPassword + 1]) {
    while (true) {
        cout << "=====================" << endl;
        cout << "欢迎进入商家子系统" << endl;
        cout << "请选择您要使用的功能>>>" << endl;
        cout << "1.餐馆信息管理" << endl;
        cout << "2.餐馆预订信息管理" << endl;
        cout << "3.退出系统" << endl;
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
    cout << "欢迎使用本餐馆预订管理系统" << endl;
    cout << "请选择您的角色>>>0.商家,1.个人用户" << endl;
    int role;
    cin >> role;
    if (role == 0) {
        cout << "请输入账号：" << endl;
        SE shopname[MAX + 1] = {'\0'};
        cin >> shopname;
        cout << "请输入密码：" << endl;
        SE password[MAXPassword + 1] = {'\0'};
        cin >> password;
        struct HashTable hash;
        initHashTable(&hash);
        initShop(&hash);
        if (!checkShop(&hash.head[gethash(shopname)], shopname, password)) {
            cout << "账号或者密码错误" << endl;
            return;
        }
        sMenu(&hash, shopname, password);
    } else if (role == 1) {
        cout << "请选择：登陆（1）或者注册（2）" << endl;
        int choice;
        cin >> choice;

        if(choice==1){
            // user
            cout << "请输入账号：" << endl;
            E userid;
            cin >> userid;
            cout << "请输入密码：" << endl;
            char password[7] = {'\0'};
            cin >> password;
            struct UserListNode head;
            inituser(&head);//初始化user表
            //检查登陆
            if (!CheckUser(&head, userid, password)) {
                cout << "账号或者密码错误" << endl;
                return;
            }
            userMenu(&head, userid, password);
        }else if(choice==2){
            cout << "请输入您的密码："<<endl;
            char password[7]={'\0'};
            cin >>password;
            cout << "请输入您的联系方式："<<endl;
            char phone[13]={'\0'};
            cin >>phone;
            struct UserListNode head;
            inituser(&head);//初始化user表
            struct UserListNode temp_head=head;
            while(head.next){
                head=*head.next;
            }
            insertUser(&temp_head,head.userid+1,password,phone);
            UserDataSave(&temp_head);
            cout << "您的账号为:"<<(head.userid+1)<<endl;
        }

    }
}

int main() {
    login();
}