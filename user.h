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
    E userid;   //���浱ǰԪ��
    char* password;
    char* phone;
    struct UserListNode * next;   //ָ����һ������ָ��
}*UserNode;
void inituser(UserNode head);//�û����ʼ��
_Bool insertUser(UserNode head, E userid, char* password,char* phone);//�û������
void UserDataSave(UserNode head);//�����û���
void printUserList(UserNode head);
_Bool deleteUser(UserNode head, E userid);//ע���û�
_Bool printUser(UserNode head,E userid);//��ӡ�û���Ϣ
_Bool CheckUser(UserNode head, E userid,char* password);//��½��֤
_Bool modifyUser(UserNode head, E userid, char* password,char* phone);//�޸��û���Ϣ

void inituser(UserNode head){
    head->next = nullptr;
    head->userid=0;
    head->password= nullptr;
    head->phone= nullptr;
    ifstream infile("../user_temp.txt");
//    string data;
    char data[1000];
    if(!infile){
        cout << "�޷����û���Ϣ�ļ�" << endl;
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
    outfile << "�û��˺�   ���� \t ��ϵ��ʽ" << endl;
    while (head->next) {
        head = head->next;
        outfile << head->userid <<" " << head->password << " " << head->phone << endl;
    }
}
_Bool insertUser(UserNode head, E userid, char* password,char* phone){//����û���Ϣ
    if(head== nullptr)return false;
    while (head->next) {
        head=head->next;
    }
    UserNode node = (struct UserListNode*)malloc(sizeof (struct UserListNode));
    if(node == nullptr) return false;   //����һ���µĽ�㣬����ڴ�ռ�����ʧ�ܷ���0
    node->userid = userid;   //��Ԫ�ر��浽�´����Ľ����
    node->password=(char *)malloc(7*sizeof (char));
    for(int i=0;i<6;i++ ){
        node->password[i]=password[i];
    }
    node->password[6]='\0';
    node->phone=(char *)malloc(12*sizeof (char));
    for(int i=0;i<11;i++ ){
        node->phone[i]=phone[i];
    }
    node->phone[11]='\0';//������������
    node->next = head->next;
    head->next = node;
    return true;
}
void printUserList(UserNode head){
    while (head->next) {
        head = head->next;
        cout << "�˺�" << head->userid << " " << "����" <<head->password << " " << "�绰" << head->phone << endl;
    }
}
_Bool deleteUser(UserNode head, E userid){//ɾ���û���Ϣ
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
        UserNode tmp = head->next;   //���õ���ɾ�����
        head->next = head->next->next;   //ֱ����ǰ�����ָ����һ������һ�����
        free(tmp);   //���ʹ��free�����ͷŵ���ɾ�������ڴ�
    }
    return sign;
}
_Bool printUser(UserNode head,E userid){
    head = head->next;    //���ߵ���һ�����
    while (head) {
        if(head->userid == userid) {
            cout << "�˺�" << head->userid << " " << "����" <<head->password << " " << "�绰" << head->phone << endl;
            return true;
        }
        head = head->next;   //û�ҵ��ͼ������
    }
    return false;   //���Ѿ��ߵ�����β���ˣ���ô��ȷʵû�ҵ��ˣ�����-1
}
_Bool CheckUser(UserNode head, E userid,char* password){//��½��֤
    head = head->next;    //���ߵ���һ�����
    while (head) {
        if(head->userid == userid) {
            for(int i=0;i<6;i++){
                if(head->password[i]!=password[i])return false;
            }
//            cout << "�˺�" << head->userid << " " << "����" <<head->password << " " << "�绰" << head->phone << endl;
            return true;
        }
        head = head->next;   //û�ҵ��ͼ������
    }
    return false;   //���Ѿ��ߵ�����β���ˣ���ô��ȷʵû�ҵ��ˣ�����-1
}
_Bool modifyUser(UserNode head, E userid, char* password,char* phone){//�޸��û���Ϣ
    head = head->next;    //���ߵ���һ�����
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
            head->phone[11]='\0';//������������
            return true;
        }
        head = head->next;   //û�ҵ��ͼ������
    }
    return false;   //���Ѿ��ߵ�����β���ˣ���ô��ȷʵû�ҵ��ˣ�����-1
}

