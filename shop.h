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
    SE password[MAXPassword + 1];//密码
    SE shoptype[MAX + 1];//店类型
    SE shopName[MAX + 1];//店名
    SE avgScore[5];//平均分
    SE avePrice[5];//平均价格
    SE address[MAX + 1];//地址
    SE phone[13];
    SE food_id[MAXFood][MAX + 1];
    SE food_name[MAXFood][MAX + 1];
    SE food_price[MAXFood][5];
    int food_size;
    SE comment[MAXComment][MAX + 1];
    int comment_size;
    struct ShopListNode *next;   //指向下一个结点的指针
} *ShopNode;
typedef struct HashTable {   //哈希表
    struct ShopListNode head[SIZE];
} *Hash;

typedef struct SuggestListNode {
    ShopNode shop;
    struct SuggestListNode *next;
} *SuggestNode;

int gethash(SE shopname[MAX + 1]);//哈希函数
void initHashTable(Hash hash);//初始化哈希表
void initShop(Hash hash);//完善哈希表
_Bool insertShop(ShopNode head, ShopNode node);//插入商家信息表
void ShopDataSave(Hash hash);//保存商家信息
_Bool checkShop(ShopNode head, SE shopid[MAX + 1], SE password[MAXPassword + 1]);//登陆验证
_Bool printShop(ShopNode head, SE shopname[MAX + 1], bool choice);//打印商家信息
_Bool printShop(ShopNode head, SE shopname[MAX + 1]);
_Bool findShop(ShopNode head, SE shopid[MAX + 1]);//查找商家
_Bool deleteShop(ShopNode head, SE shopid[MAX + 1]);//注销商家
_Bool modifyShop(ShopNode head, SE shopid[MAX + 1]);//修改商家信息
void initSuggestList(SuggestNode head);//初始化推荐表
_Bool insertSuggestList(SuggestNode head, ShopNode shop);//插入推荐表
void printSuggestList(SuggestNode head);//打印推荐表
_Bool shopSuggest(Hash hash, SuggestNode head, SE shopinfo[MAX + 1], int choice);//餐馆推荐
int *getNext(char *str);//next数组
int KMP(char *chang,char *duan);//kmp算法

int gethash(SE shopname[MAX + 1]) {   //哈希函数
    return strlen(shopname) % SIZE;
}
void initHashTable(Hash hash) {
    for (int i = 0; i < SIZE; i++) {
        hash->head[i].next = nullptr;
        hash->head[i].shopid[MAX + 1] = {'\0'};
        hash->head[i].password[MAXPassword + 1] = {'\0'};//密码
        hash->head[i].shoptype[MAX + 1] = {'\0'};//店类型
        hash->head[i].shopName[MAX + 1] = {'\0'};//店名
        hash->head[i].avgScore[5] = {'\0'};//平均分
        hash->head[i].avePrice[5] = {'\0'};//平均价格
        hash->head[i].address[MAX + 1] = {'\0'};//地址
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
        cout << "无法打开商店信息文件" << endl;
    }
    infile.getline(data, sizeof(data));
    while (!infile.eof()) {
        SE *id;
        id = strstr(data, "shoptype");
        if (id != nullptr) {
            auto node = (struct ShopListNode *) malloc(sizeof(struct ShopListNode));
            node->next = nullptr;
            node->shopid[MAX + 1] = {'\0'};
            node->password[MAXPassword + 1] = {'\0'};//密码
            node->shoptype[MAX + 1] = {'\0'};//店类型
            node->shopName[MAX + 1] = {'\0'};//店名
            node->avgScore[5] = {'\0'};//平均分
            node->avePrice[5] = {'\0'};//平均价格
            node->address[MAX + 1] = {'\0'};//地址
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
//        cout << "账号" << head->shopid << " " << "密码:" << head->password << " " << "电话:" << head->phone << endl;
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
_Bool deleteShop(ShopNode head, SE shopname[MAX + 1]) {//删除用户信息
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
            ShopNode tmp = head->next;   //先拿到待删除结点
            head->next = head->next->next;   //直接让前驱结点指向下一个的下一个结点
            free(tmp);   //最后使用free函数释放掉待删除结点的内存
            return true;
        }
        head = head->next;
    }

}
_Bool modifyShop(ShopNode head, SE shopname[MAX + 1]) {//修改用户信息
    head = head->next;    //先走到第一个结点
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
            cout << "是否修改类型（0/1）" << endl;
            bool sign;
            cin >> sign;
            if (sign) {
                cout << "新类型>>" << endl;
                cin >> head->shoptype;
            }
            cout << "是否修改店名（0/1）" << endl;
            cin >> sign;
            if (sign) {
                cout << "新店名" << endl;
                cin >> head->shopName;
            }
            cout << "是否修改密码（0/1）" << endl;
            cin >> sign;
            if (sign) {
                cout << "新密码" << endl;
                cin >> head->password;
            }
            cout << "是否修改人均消费（0/1）" << endl;
            cin >> sign;
            if (sign) {
                cout << "新人均消费" << endl;
                cin >> head->avePrice;
            }
            cout << "是否修改地址（0/1）" << endl;
            cin >> sign;
            if (sign) {
                cout << "新地址" << endl;
                cin >> head->address;
            }
            cout << "是否修改电话（0/1）" << endl;
            cin >> sign;
            if (sign) {
                cout << "新电话" << endl;
                cin >> head->phone;
            }
            cout << "是否修改特色菜（0/1）" << endl;
            cin >> sign;
            if (sign) {
                cout << "修改后特色菜数量" << endl;
                cin >> head->food_size;
                for (int i = 0; i < head->food_size; i++) {
                    cout << "特色菜" << (i + 1) << endl;
                    cout << "id" << endl;
                    cin >> head->food_id[i];
                    cout << "名称" << endl;
                    cin >> head->food_name[i];
                    cout << "价格" << endl;
                    cin >> head->food_price[i];
                }
            }
            return true;
        }
        head = head->next;   //没找到就继续向后看
    }
    return false;   //都已经走到链表尾部了，那么就确实没找到了，返回-1
}

//kmp
int *getNext(char *str) {
    int len = strlen(str);
    int *next = (int *) calloc(len, sizeof(int));
    next[0] = -1;
    int i = 0, k = -1;
    while (i < len - 1) { //这里注意-1
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
    head->next = NULL;   //头结点默认下一个为NULL
}
_Bool insertSuggestList(SuggestNode head, ShopNode shop) {
    while (head->next) {   //寻找前驱结点
        if (strtod(head->next->shop->avgScore, nullptr) < strtof(shop->avgScore, nullptr))
            break;
        head = head->next;   //正常情况下继续向后找
    }
    auto node = (struct SuggestListNode *) malloc(sizeof(struct SuggestListNode));
    if (node == nullptr) return true;   //创建一个新的结点，如果内存空间申请失败返回0
    node->shop = shop;   //将元素保存到新创建的结点中
    node->next = head->next;   //先让新插入的节点指向原本位置上的这个结点
    head->next = node;   //接着将前驱结点指向新的这个结点
    return true;
}
void printSuggestList(SuggestNode head) {
    while (head->next) {
        head = head->next;
        cout << head->shop->shopName << " 评分：" << head->shop->avgScore << endl;
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