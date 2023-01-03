#include<iostream>
#include<bits/stdc++.h>
#include <cstdio>
#include <utility>

using namespace std;
typedef char SE;
#define MAXFood 100
#define MAXComment 300
#define MAX 300
#define MAXPassword 20
#define SIZE 10

typedef struct ShopListNode {
    SE shopid[MAX + 1];
    SE password[MAXPassword + 1];//����
    SE shoptype[MAX + 1];//������
    SE shopName[MAX + 1];//����
    SE avgScore[5];//ƽ����
    SE avePrice[5];//ƽ���۸�
    SE address[MAX + 1];//��ַ
    SE phone[13];
    SE food_id[MAXFood][MAX + 1];
    SE food_name[MAXFood][MAX + 1];
    SE food_price[MAXFood][5];
    int food_size;
    SE comment[MAXComment][MAX + 1];
    int comment_size;
    struct ShopListNode *next;   //ָ����һ������ָ��
} *ShopNode;
typedef struct HashTable {   //��ϣ��
    struct ShopListNode head[SIZE];
} *Hash;

typedef struct SuggestListNode {
    ShopNode shop;
    struct SuggestListNode *next;
} *SuggestNode;

int gethash(SE shopname[MAX + 1]);//��ϣ����
void initHashTable(Hash hash);//��ʼ����ϣ��
void initShop(Hash hash);//���ƹ�ϣ��
_Bool insertShop(ShopNode head, ShopNode node);//�����̼���Ϣ��
void ShopDataSave(Hash hash);//�����̼���Ϣ
_Bool checkShop(ShopNode head, SE shopid[MAX + 1], SE password[MAXPassword + 1]);//��½��֤
_Bool printShop(ShopNode head, SE shopname[MAX + 1], bool choice);//��ӡ�̼���Ϣ
_Bool printShop(ShopNode head, SE shopname[MAX + 1]);
_Bool findShop(ShopNode head, SE shopid[MAX + 1]);//�����̼�
_Bool deleteShop(ShopNode head, SE shopid[MAX + 1]);//ע���̼�
_Bool modifyShop(ShopNode head, SE shopid[MAX + 1]);//�޸��̼���Ϣ
void initSuggestList(SuggestNode head);//��ʼ���Ƽ���
_Bool insertSuggestList(SuggestNode head, ShopNode shop);//�����Ƽ���
void printSuggestList(SuggestNode head);//��ӡ�Ƽ���
_Bool shopSuggest(Hash hash, SuggestNode head, SE shopinfo[MAX + 1], int choice);//�͹��Ƽ�
int *getNext(char *str);//next����
int KMP(char *chang,char *duan);//kmp�㷨

int gethash(SE shopname[MAX + 1]) {   //��ϣ����
    return strlen(shopname) % SIZE;
}
void initHashTable(Hash hash) {
    for (int i = 0; i < SIZE; i++) {
        hash->head[i].next = nullptr;
        hash->head[i].shopid[MAX + 1] = {'\0'};
        hash->head[i].password[MAXPassword + 1] = {'\0'};//����
        hash->head[i].shoptype[MAX + 1] = {'\0'};//������
        hash->head[i].shopName[MAX + 1] = {'\0'};//����
        hash->head[i].avgScore[5] = {'\0'};//ƽ����
        hash->head[i].avePrice[5] = {'\0'};//ƽ���۸�
        hash->head[i].address[MAX + 1] = {'\0'};//��ַ
        hash->head[i].phone[13] = {'\0'};
        hash->head[i].food_id[MAXFood][MAX + 1] = {'\0'};
        hash->head[i].food_name[MAXFood][MAX + 1] = {'\0'};
        hash->head[i].food_price[MAXFood][5] = {'\0'};
        hash->head[i].food_size = 0;
        hash->head[i].comment[MAXComment][MAX + 1] = {'\0'};
        hash->head[i].comment_size = 0;
    }
}
void initShop(Hash hash) {

    ifstream infile("../shop_temp.txt");
//    string data;
    SE data[1024];
    if (!infile) {
        cout << "�޷����̵���Ϣ�ļ�" << endl;
    }
    infile.getline(data, sizeof(data));
    while (!infile.eof()) {
        SE *id;
        id = strstr(data, "shoptype");
        if (id != nullptr) {
            auto node = (struct ShopListNode *) malloc(sizeof(struct ShopListNode));
            node->next = nullptr;
            node->shopid[MAX + 1] = {'\0'};
            node->password[MAXPassword + 1] = {'\0'};//����
            node->shoptype[MAX + 1] = {'\0'};//������
            node->shopName[MAX + 1] = {'\0'};//����
            node->avgScore[5] = {'\0'};//ƽ����
            node->avePrice[5] = {'\0'};//ƽ���۸�
            node->address[MAX + 1] = {'\0'};//��ַ
            node->phone[13] = {'\0'};
            node->food_id[MAXFood][MAX + 1] = {'\0'};
            node->food_name[MAXFood][MAX + 1] = {'\0'};
            node->food_price[MAXFood][MAX + 1] = {'\0'};
            node->food_size = 0;
            node->comment_size = 0;

            if (node == nullptr)return;
            sscanf(data, "shoptype: %s", node->shoptype);
            infile.getline(data, sizeof(data));
//            cout << node->shoptype<<endl;
            id = strstr(data, "shopId");
            if (id != nullptr) {
                sscanf(data, "shopId: %s", node->shopid);
                infile.getline(data, sizeof(data));
            }
//            cout << node->shopid<<endl;

            id = strstr(data, "shopName");
            if (id != nullptr) {
                sscanf(data, "shopName: %s", node->shopName);
                infile.getline(data, sizeof(data));
            }
//            cout << node->shopName<<endl;

            id = strstr(data, "Password");
            if (id != nullptr) {
                sscanf(data, "shopPassword: %s", node->password);
                infile.getline(data, sizeof(data));
            }
//            cout << node->password << endl;

            id = strstr(data, "avgScore");
            if (id != nullptr) {
                sscanf(data, "avgScore: %s", node->avgScore);
                infile.getline(data, sizeof(data));
            }
//            cout << node->avgScore << endl;

            id = strstr(data, "avePrice");
            if (id != nullptr) {
                sscanf(data, "avePrice: %s", node->avePrice);
                infile.getline(data, sizeof(data));
            }
//            cout << node->avePrice << endl;


            id = strstr(data, "address");
            if (id != nullptr) {
                sscanf(data, "address: %s", node->address);
                infile.getline(data, sizeof(data));
            }
//            cout << node->address << endl;


            id = strstr(data, "phone");
            if (id != nullptr) {
                sscanf(data, "phone: %s", node->phone);
                infile.getline(data, sizeof(data));
            }
//            cout << node->phone << endl;

            id = strstr(data, "food_id");
            while (id != nullptr && !infile.eof()) {
                sscanf(data, "food_id: %s food_name: %s food_price: %s", node->food_id[node->food_size],
                       node->food_name[node->food_size], node->food_price[node->food_size]);
//                cout << node->food_id[node->food_size] << " " << node->food_name[node->food_size] << " " << node->food_price[node->food_size] << endl;
                node->food_size = node->food_size + 1;
                infile.getline(data, sizeof(data));
                id = strstr(data, "food_id");
            }

            id = strstr(data, "Comment");
            while (id != nullptr) {
                for (int i = 0; i < MAXComment; i++) {
                    if (id[i] == '\0')break;
                    node->comment[node->comment_size][i] = id[i];
                }
//                cout<<node->comment[node->comment_size]<<endl;
                node->comment_size = node->comment_size + 1;
                infile.getline(data, sizeof(data));
                id = strstr(data, "Comment");
            }
            insertShop(&hash->head[gethash(node->shopName)], node);
        } else {
            infile.getline(data, sizeof(data));
        }
//        infile.getline(data, sizeof(data));
    }
    infile.close();
}
_Bool insertShop(ShopNode head, ShopNode node) {
    if (head == nullptr)return false;
    while (head->next) {
        head = head->next;
        if (head == nullptr)break;
    }
    node->next = head->next;
    head->next = node;
    return true;
}
void ShopDataSave(Hash hash) {
    ofstream outfile("../shop_temp.txt");
    for (int i = 0; i < SIZE; i++) {
        struct ShopListNode *head = &hash->head[i];
        while (head->next) {
            head = head->next;
            outfile << "shoptype: " << head->shoptype << endl;
            outfile << "shopId: " << head->shopid << endl;
            outfile << "shopName: " << head->shopName << endl;
            outfile << "shopPassword: " << head->password << endl;
            outfile << "avgScore: " << head->avgScore << endl;
            outfile << "avePrice: " << head->avePrice << endl;
            outfile << "address: " << head->address << endl;
            outfile << "phone: " << head->phone << endl;
            int food_size = head->food_size;
            for (int i = 0; i < food_size; i++) {
                outfile << "food_id: " << head->food_id[i] << " food_name: " << head->food_name[i] << " food_price: "
                        << head->food_price[i] << endl;
//                if(i!=food_size-1)outfile<<endl;
            }
            int comment_size = head->comment_size;
            for (int i = 0; i < comment_size; i++) {
                outfile << head->comment[i] << endl;
//                if(i!=food_size-1||food_size==1)outfile<<endl;
            }
        }
    }
    outfile.close();
}
_Bool checkShop(ShopNode head, SE shopname[MAX + 1], SE password[MAXPassword + 1]) {
    while (head->next) {
        head = head->next;
        bool shopid_sign = true;
        for (int i = 0; i < MAX + 1; i++) {
            if (head->shopName[i] != shopname[i]) {
                shopid_sign = false;
                break;
            }
            if (head->shopName[i] == '\0' && shopname[i] == '\0')break;
        }
        if (shopid_sign) {
            bool password_sign = true;
            for (int i = 0; i < MAXPassword + 1; i++) {
                if (head->password[i] != password[i]) {
                    password_sign = false;
                    break;
                }
                if (head->password[i] == '\0' && password[i] == '\0')break;
            }
            if (password_sign)return true;
        }
//        cout << "�˺�" << head->shopid << " " << "����:" << head->password << " " << "�绰:" << head->phone << endl;
    }
    return false;
}
_Bool printShop(ShopNode head, SE shopname[MAX + 1], bool choice) {
    while (head->next) {
        head = head->next;
        bool sign = true;
        for (int i = 0; i < MAX + 1; i++) {
            if (shopname[i] == '\0')break;
            if (head->shopName[i] != shopname[i]) {
                sign = false;
                break;
            }
        }
        if (sign) {
            cout << "=====================" << endl;
            cout << "shoptype: " << head->shoptype << endl;
            cout << "shopId: " << head->shopid << endl;
            cout << "shopName: " << head->shopName << endl;
            if (choice)cout << "shopPassword: " << head->password << endl;
            cout << "avgScore: " << head->avgScore << endl;
            cout << "avePrice: " << head->avePrice << endl;
            cout << "address: " << head->address << endl;
            cout << "phone: " << head->phone << endl;
            int food_size = head->food_size;
            for (int i = 0; i < food_size; i++) {
                cout << "food_id: " << head->food_id[i] << " food_Name: " << head->food_name[i] << " food_price: "
                     << head->food_price[i] << endl;
            }
            int comment_size = head->comment_size;
            for (int i = 0; i < comment_size; i++) {
                cout << head->comment[i] << endl;
            }
            return true;
        }
    }
    return false;
}
_Bool printShop(ShopNode head, SE shopname[MAX + 1]) {
    while (head->next) {
        head = head->next;
        bool sign = true;
        for (int i = 0; i < MAX + 1; i++) {
            if (shopname[i] == '\0')break;
            if (head->shopName[i] != shopname[i]) {
                sign = false;
                break;
            }
        }
        if (sign) {
            cout << "=====================" << endl;
            cout << "shoptype: " << head->shoptype << endl;
            cout << "shopId: " << head->shopid << endl;
            cout << "shopName: " << head->shopName << endl;
            cout << "shopPassword: " << head->password << endl;
            cout << "avgScore: " << head->avgScore << endl;
            cout << "avePrice: " << head->avePrice << endl;
            cout << "address: " << head->address << endl;
            cout << "phone: " << head->phone << endl;
            int food_size = head->food_size;
            for (int i = 0; i < food_size; i++) {
                cout << "food_id: " << head->food_id[i] << " food_Name: " << head->food_name[i] << " food_price: "
                     << head->food_price[i] << endl;
            }
            int comment_size = head->comment_size;
            for (int i = 0; i < comment_size; i++) {
                cout << head->comment[i] << endl;
            }
            return true;
        }
    }
    return false;
}
_Bool findShop(ShopNode head, SE shopname[MAX + 1]) {
    while (head->next) {
        head = head->next;
        bool sign = true;
        for (int i = 0; i < MAX + 1; i++) {
            if (shopname[i] == '\0')break;
            if (head->shopName[i] != shopname[i]) {
                sign = false;
                break;
            }
        }
        if (sign) return true;
    }
    return false;
}
_Bool deleteShop(ShopNode head, SE shopname[MAX + 1]) {//ɾ���û���Ϣ
    if (head->next == nullptr)return false;
    while (true) {
        bool sign2 = true;
        for (int i = 0; i < MAX + 1; i++) {
            if (shopname[i] == '\0')break;
            if (head->next->shopName[i] != shopname[i]) {
                sign2 = false;
                break;
            }
        }
        if (sign2) {
            ShopNode tmp = head->next;   //���õ���ɾ�����
            head->next = head->next->next;   //ֱ����ǰ�����ָ����һ������һ�����
            free(tmp);   //���ʹ��free�����ͷŵ���ɾ�������ڴ�
            return true;
        }
        head = head->next;
    }

}
_Bool modifyShop(ShopNode head, SE shopname[MAX + 1]) {//�޸��û���Ϣ
    head = head->next;    //���ߵ���һ�����
    while (head) {
        bool sign2 = true;
        for (int i = 0; i < MAX + 1; i++) {
            if (shopname[i] == '\0')break;
            if (head->shopName[i] != shopname[i]) {
                sign2 = false;
                break;
            }
        }
        if (sign2) {
            cout << "=====================" << endl;
            cout << "�Ƿ��޸����ͣ�0/1��" << endl;
            bool sign;
            cin >> sign;
            if (sign) {
                cout << "������>>" << endl;
                cin >> head->shoptype;
            }
            cout << "�Ƿ��޸ĵ�����0/1��" << endl;
            cin >> sign;
            if (sign) {
                cout << "�µ���" << endl;
                cin >> head->shopName;
            }
            cout << "�Ƿ��޸����루0/1��" << endl;
            cin >> sign;
            if (sign) {
                cout << "������" << endl;
                cin >> head->password;
            }
            cout << "�Ƿ��޸��˾����ѣ�0/1��" << endl;
            cin >> sign;
            if (sign) {
                cout << "���˾�����" << endl;
                cin >> head->avePrice;
            }
            cout << "�Ƿ��޸ĵ�ַ��0/1��" << endl;
            cin >> sign;
            if (sign) {
                cout << "�µ�ַ" << endl;
                cin >> head->address;
            }
            cout << "�Ƿ��޸ĵ绰��0/1��" << endl;
            cin >> sign;
            if (sign) {
                cout << "�µ绰" << endl;
                cin >> head->phone;
            }
            cout << "�Ƿ��޸���ɫ�ˣ�0/1��" << endl;
            cin >> sign;
            if (sign) {
                cout << "�޸ĺ���ɫ������" << endl;
                cin >> head->food_size;
                for (int i = 0; i < head->food_size; i++) {
                    cout << "��ɫ��" << (i + 1) << endl;
                    cout << "id" << endl;
                    cin >> head->food_id[i];
                    cout << "����" << endl;
                    cin >> head->food_name[i];
                    cout << "�۸�" << endl;
                    cin >> head->food_price[i];
                }
            }
            return true;
        }
        head = head->next;   //û�ҵ��ͼ������
    }
    return false;   //���Ѿ��ߵ�����β���ˣ���ô��ȷʵû�ҵ��ˣ�����-1
}

//kmp
int *getNext(char *str) {
    int len = strlen(str);
    int *next = (int *) calloc(len, sizeof(int));
    next[0] = -1;
    int i = 0, k = -1;
    while (i < len - 1) { //����ע��-1
        if (k == -1 || str[i] == str[k]) {
            i++;
            k++;
            next[i] = (str[i] == str[k] ? next[k] : k);
        } else {
            k = next[k];
        }
    }

    return next;
}
int KMP(char *chang, char *duan) {
    int *next = getNext(duan);
    int c_len = strlen(chang);
    int d_len = strlen(duan);
    int i = 0, k = 0;

    while (i < c_len && k < d_len) {

        if (k == -1 || chang[i] == duan[k]) {
            i++;
            k++;
        } else {
            k = next[k];
        }
    }

    return k < d_len ? -1 : i - k;
}

void initSuggestList(SuggestNode head) {
    head->next = NULL;   //ͷ���Ĭ����һ��ΪNULL
}
_Bool insertSuggestList(SuggestNode head, ShopNode shop) {
    while (head->next) {   //Ѱ��ǰ�����
        if (strtod(head->next->shop->avgScore, nullptr) < strtof(shop->avgScore, nullptr))
            break;
        head = head->next;   //��������¼��������
    }
    auto node = (struct SuggestListNode *) malloc(sizeof(struct SuggestListNode));
    if (node == nullptr) return true;   //����һ���µĽ�㣬����ڴ�ռ�����ʧ�ܷ���0
    node->shop = shop;   //��Ԫ�ر��浽�´����Ľ����
    node->next = head->next;   //�����²���Ľڵ�ָ��ԭ��λ���ϵ�������
    head->next = node;   //���Ž�ǰ�����ָ���µ�������
    return true;
}
void printSuggestList(SuggestNode head) {
    while (head->next) {
        head = head->next;
        cout << head->shop->shopName << " ���֣�" << head->shop->avgScore << endl;
    }
}
_Bool shopSuggest(Hash hash, SuggestNode head, SE shopinfo[MAX + 1], int choice) {
    switch (choice) {
        case 1: {
            for (int i = 0; i < SIZE; i++) {
                ShopNode shophead = &hash->head[i];
                while (shophead->next) {
                    shophead = shophead->next;
                    if (KMP(shophead->shoptype, shopinfo) != -1)
                        insertSuggestList(head, shophead);
                }
            }
        }
            break;
        case 2: {
            for (int i = 0; i < SIZE; i++) {
                ShopNode shophead = &hash->head[i];
                while (shophead->next) {
                    shophead = shophead->next;
                    for (int j = 0; j < shophead->food_size; j++) {
                        if (KMP(shophead->food_name[j], shopinfo) != -1) {
                            insertSuggestList(head, shophead);
                            break;
                        }
                    }
                }
            }

        }
            break;
    }
    printSuggestList(head);
    return true;
}