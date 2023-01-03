#include<iostream>
#include <utility>
#include<bits/stdc++.h>
using namespace std;
typedef int E;
typedef char SE;
#define MAXFood 100
#define MAXComment 300
#define MAX 300
#define MAXPassword 20
#define SIZE 10
typedef struct UserListNode {
    E userid;   //保存当前元素
    char* password;
    char* phone;
    struct UserListNode * next;   //指向下一个结点的指针
}*UserNode;
void inituser(UserNode head);//用户表初始化
_Bool insertUser(UserNode head, E userid, char* password,char* phone);//用户表插入
void UserDataSave(UserNode head);//保存用户表
void printUserList(UserNode head);
_Bool deleteUser(UserNode head, E userid);//注销用户
_Bool printUser(UserNode head,E userid);//打印用户信息
_Bool CheckUser(UserNode head, E userid,char* password);//登陆验证
_Bool modifyUser(UserNode head, E userid, char* password,char* phone);//修改用户信息

void inituser(UserNode head){
    head->next = nullptr;
    head->userid=0;
    head->password= nullptr;
    head->phone= nullptr;
    ifstream infile("../user_temp.txt");
//    string data;
    char data[1000];
    if(!infile){
        cout << "无法打开用户信息文件" << endl;
    }
    infile.getline(data,sizeof (data));

    while(!infile.eof()){
//        getline(infile,data);
        infile.getline(data,sizeof (data));
        char* id= strtok(data," ");
//        E userid=int(strtok(data," ")[0]);
//        cout << userid << endl;
        E userid=atoi(id);
//        cout << userid << " ";
        id= strtok(nullptr," ");
        char *passsword = id;
//        cout << passsword << " ";
        id= strtok(nullptr," ");
        char* phone = id;
//        cout << phone << endl;
        if(passsword== nullptr||phone== nullptr)continue;
        insertUser(head,userid,passsword,phone);
    }
    infile.close();
}
void UserDataSave(UserNode head){
    ofstream outfile("../user_temp.txt");
    outfile << "用户账号   密码 \t 联系方式" << endl;
    while (head->next) {
        head = head->next;
        outfile << head->userid <<" " << head->password << " " << head->phone << endl;
    }
}
_Bool insertUser(UserNode head, E userid, char* password,char* phone){//添加用户信息
    if(head== nullptr)return false;
    while (head->next) {
        head=head->next;
    }
    UserNode node = (struct UserListNode*)malloc(sizeof (struct UserListNode));
    if(node == nullptr) return false;   //创建一个新的结点，如果内存空间申请失败返回0
    node->userid = userid;   //将元素保存到新创建的结点中
    node->password=(char *)malloc(7*sizeof (char));
    for(int i=0;i<6;i++ ){
        node->password[i]=password[i];
    }
    node->password[6]='\0';
    node->phone=(char *)malloc(12*sizeof (char));
    for(int i=0;i<11;i++ ){
        node->phone[i]=phone[i];
    }
    node->phone[11]='\0';//不加有脏数据
    node->next = head->next;
    head->next = node;
    return true;
}
void printUserList(UserNode head){
    while (head->next) {
        head = head->next;
        cout << "账号" << head->userid << " " << "密码" <<head->password << " " << "电话" << head->phone << endl;
    }
}
_Bool deleteUser(UserNode head, E userid){//删除用户信息
    if(head->next== nullptr)return false;
    bool sign = false;
    while (true) {
        if(head->next->userid==userid){
            sign= true;
            break;
        }
        head = head->next;
        if(head== nullptr)return false;
    }
    if(sign){
        UserNode tmp = head->next;   //先拿到待删除结点
        head->next = head->next->next;   //直接让前驱结点指向下一个的下一个结点
        free(tmp);   //最后使用free函数释放掉待删除结点的内存
    }
    return sign;
}
_Bool printUser(UserNode head,E userid){
    head = head->next;    //先走到第一个结点
    while (head) {
        if(head->userid == userid) {
            cout << "账号" << head->userid << " " << "密码" <<head->password << " " << "电话" << head->phone << endl;
            return true;
        }
        head = head->next;   //没找到就继续向后看
    }
    return false;   //都已经走到链表尾部了，那么就确实没找到了，返回-1
}
_Bool CheckUser(UserNode head, E userid,char* password){//登陆验证
    head = head->next;    //先走到第一个结点
    while (head) {
        if(head->userid == userid) {
            for(int i=0;i<6;i++){
                if(head->password[i]!=password[i])return false;
            }
//            cout << "账号" << head->userid << " " << "密码" <<head->password << " " << "电话" << head->phone << endl;
            return true;
        }
        head = head->next;   //没找到就继续向后看
    }
    return false;   //都已经走到链表尾部了，那么就确实没找到了，返回-1
}
_Bool modifyUser(UserNode head, E userid, char* password,char* phone){//修改用户信息
    head = head->next;    //先走到第一个结点
    while (head) {
        if(head->userid == userid) {
            head->password=(char *)malloc(7*sizeof (char));
            for(int i=0;i<6;i++ ){
                head->password[i]=password[i];
            }
            head->password[6]='\0';
            head->phone=(char *)malloc(12*sizeof (char));
            for(int i=0;i<11;i++ ){
                head->phone[i]=phone[i];
            }
            head->phone[11]='\0';//不加有脏数据
            return true;
        }
        head = head->next;   //没找到就继续向后看
    }
    return false;   //都已经走到链表尾部了，那么就确实没找到了，返回-1
}

