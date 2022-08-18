//
//  Cay_Nhi_Phan_TimKiem.hpp
//  Cau_Truc_Cay
//
//  Created by PHẠM HÙNG DŨNG on 20/07/2022.
//

#ifndef Cay_Nhi_Phan_TimKiem_hpp
#define Cay_Nhi_Phan_TimKiem_hpp

#include <iostream>
#include <string>
#include <fstream>
#include <queue>

using namespace std;

/* 1/ Khai bao cau truc du lieu cay nhi phan tim kiem */
struct Node
{
    int Data;
    Node *Left, *Right;
};

/* 2/ Khoi tao cay */
void iNit(Node *&Root)
{
    Root = NULL;
}

/* 3/ Tao Node */
Node* getNode(int x)
{
    Node* p = new Node;
    if (p == NULL) {
        return NULL;
    }
    p->Data = x;
    p->Left = p->Right = NULL;
    return p;
}

/* 4/ Them Node */
void ThemNode_DeQuy(Node*& Root, int x)
{
    if (Root != NULL) {
        if (x > Root->Data) {
            ThemNode_DeQuy(Root->Right, x);
        }
        else if (x < Root->Data) {
            ThemNode_DeQuy(Root->Left, x);
        }
    }
    else
    {
        Root = getNode(x);
    }
}

void ThemNode_KhuDeQuy(Node*& Root, int x)
{
    if (Root == NULL) {
        Root = getNode(x);
    }
    else
    {
        Node* p;
        Node* q = Root;
        while (q != NULL) {
            p = q;
            if (x > q->Data) {
                q = q->Right;
            }
            else if (x < q->Data) {
                q = q->Left;
            }
            else {
                return;
            }
        }
        
        if (x > p->Data) {
            p->Right = getNode(x);
        }
        else if (x < p->Data) {
            p->Left = getNode(x);
        }
    }
}

void taoCayTuDaySo(Node*& Root, int a[], int n)
{
    for (int i = 0; i < n; ++i) {
        ThemNode_DeQuy(Root, a[i]);
    }
}
void taoCayTuTapTin(Node*& Root, fstream &fileIn)
{
    
}

void preOrder(Node *Root)    // Node-Left-Right
{
    if (Root != NULL) {
        cout << Root->Data << " ";
        preOrder(Root->Left);
        preOrder(Root->Right);
    }
}

void inOrder(Node *Root)    // Left-Node-Right
{
    if (Root != NULL) {
        inOrder(Root->Left);
        cout << Root->Data << " ";
        inOrder(Root->Right);
    }
}

void postOrder(Node *Root)    // Left-Right-Node
{
    if (Root != NULL) {
        postOrder(Root->Left);
        postOrder(Root->Right);
        cout << Root->Data << " ";
    }
}

Node* timNode_DeQuy1(Node* Root, int x)
{
    if (Root != NULL) {
        if (x > Root->Data) {
            return timNode_DeQuy1(Root->Right, x);
        }
        else if (x < Root->Data) {
            return timNode_DeQuy1(Root->Left, x);
        }
        else {
            return Root;
        }
    }
    return NULL;
}

Node* timNode_DeQuy2(Node* Root, int x)
{
    if (Root == NULL) {
        return NULL;
    }

    if (Root->Data == x) {
        return Root;
    }

    Node* p;
    if (x > Root->Data) {
        p = timNode_DeQuy2(Root->Right, x);
    }
    else if (x < Root->Data) {
        p = timNode_DeQuy2(Root->Left, x);
    }
    return p;
}

void timNodeVaThemNode_DeQuy(Node*& Root, int x)
{
    if (Root != NULL) {
        if (x > Root->Data) {
            timNodeVaThemNode_DeQuy(Root->Right, x);
        }
        else if (x < Root->Data) {
            timNodeVaThemNode_DeQuy(Root->Left, x);
        }
        else {
            cout << "Node can tim co trong cay!" << endl;
            return;
        }
    }
    else
    {
        Root = getNode(x);
        cout << "Node can tim ko co trong cay. Da tu dong them vao cay!" << endl;
    }
}

Node* timNode_KhuDeQuy(Node* Root, int x)
{
    while (Root != NULL) {
        if (x > Root->Data) {
            Root = Root->Right;
        }
        else if (x < Root->Data) {
            Root = Root->Left;
        }
        else {
            return Root;
        }
    }
    return NULL;
}

Node* timNodeVaThemNode_KhuDeQuy(Node*& Root, int x)
{
    Node* p;
    Node* q = Root;
    if (q == NULL) {
        return Root = getNode(x);
    }
    else
    {
        while (q != NULL) {
            p = q;
            if (x > q->Data) {
                q = q->Right;
            }
            else if (x < q->Data) {
                q = q->Left;
            }
            else if (x == q->Data) {
                cout << "Node can tim co trong cay!" << endl;
                return q;
            }
        }
    }
    
    cout << "Node can tim ko co trong cay. Da tu dong them vao cay!" << endl;
    if (x > p->Data) {
        p->Right = getNode(x);
        p = p->Right;
    }
    else if (x < p->Data) {
        p->Left = getNode(x);
        p = p->Left;
    }
    return p;
}

/* 5/ Xoa Node */
void timPhanTuTheMang(Node*& Root, Node*& p)
{
    if (Root->Right != NULL) {
        timPhanTuTheMang(Root->Right, p);
    }
    else {
        p->Data = Root->Data;
        p = Root;
        Root = Root->Left;
    }
}

void timVaXoaNode_DeQuy(Node*& Root, int x)
{
    if (Root == NULL) {
        return;
    }
    
    if (Root->Data < x) {
        timVaXoaNode_DeQuy(Root->Right, x);
    }
    else if (Root->Data > x) {
        timVaXoaNode_DeQuy(Root->Left, x);
    }
    else {
        Node *p = Root;
        
        if (p->Left == NULL) {
            Root = p->Right;
        }
        else if (p->Right == NULL) {
            Root = p->Left;
        }
        else {
            timPhanTuTheMang(Root->Left, p);
        }
        
        delete p;
    }
}

/* 6/ Thao tac */
int DemSoNode_DeQuyThuong(Node *Root)
{
    // Dieu kien dung
    if (Root == NULL) {
        return 0;
    }
    // Buoc de quy
    return 1 + DemSoNode_DeQuyThuong(Root->Left) + DemSoNode_DeQuyThuong(Root->Right);
}

int DemSoNode_KhuDeQuy(Node *Root)
{
    queue<Node *> q;
    q.push(Root);
    
    int dem = 0;
    while (!q.empty()) {
        Node *p = q.front();
        dem++;
        q.pop();
        
        if (p->Left != NULL) {
            q.push(p->Left);
        }
        if (p->Right != NULL) {
            q.push(p->Right);
        }
    }
    
    return dem;
}

Node* timMinTrongCay_DeQuy(Node* Root)
{
    if (Root != NULL) {
        if (Root->Left != NULL) {
            return timMinTrongCay_DeQuy(Root->Left);
        }
        return Root;
    }
    return NULL;
}

Node* timMinTrongCay_KoDeQuy(Node* Root)
{
    while (Root != NULL) {
        if (Root->Left != NULL) {
            Root = Root->Left;
            continue;
        }
        break;
    }
    return Root;
}

Node* timMaxTrongCay_DeQuy(Node* Root)
{
    if (Root != NULL) {
        if (Root->Right != NULL) {
            return timMaxTrongCay_DeQuy(Root->Right);
        }
        return Root;
    }
    return NULL;
}

Node* timMaxTrongCay_KoDeQuy(Node* Root)
{
    while (Root != NULL) {
        if (Root->Right != NULL) {
            Root = Root->Right;
            continue;
        }
        break;
    }
    return Root;
}

int demNodeAmTrongCay_DeQuy(Node* Root)
{
    if (Root == NULL) {
        return 0;
    }
    else {
        if (Root->Data >= 0) {
            return demNodeAmTrongCay_DeQuy(Root->Left);
        }
        else {
            if (Root->Data == -1) {
                return 1 + DemSoNode_DeQuyThuong(Root->Left);
            }
            else {
                return 1 + DemSoNode_DeQuyThuong(Root->Left) + demNodeAmTrongCay_DeQuy(Root->Right);
            }
        }
    }
}

void demNodeAmTrongCay_DeQuy_CaiTien(Node *Root, int &count)
{
    if (Root != NULL) {
        demNodeAmTrongCay_DeQuy_CaiTien(Root->Left, count);
        if (Root->Data < 0) {
            ++count;
        }
        else {
            return;
        }
        demNodeAmTrongCay_DeQuy_CaiTien(Root->Right, count);
    }
}

int demNodeAmTrongCay_KoDeQuy(Node* Root)
{
    int dem = 0;
    
xetCayPhai:
    if (Root == NULL) {
        return dem;
    }
    else {
        if (Root->Data >= 0) {
            Root = Root->Left;
            goto xetCayPhai;
        }
        
        ++dem;
        if (Root->Left != NULL) {
            dem += DemSoNode_KhuDeQuy(Root->Left);
        }
        if (Root->Data != 1) {
            Root = Root->Right;
            goto xetCayPhai;
        }
        
        return dem;
    }
}

int j = 0;
bool xCheck = false;
bool yCheck = false;
void demNodeTrongKhoangXY_DeQuy(Node *Root, int x, int y, int a[])
{
    if (Root != NULL) {
        demNodeTrongKhoangXY_DeQuy(Root->Left, x, y, a);
        if (Root->Data >= x && xCheck == false) {
            xCheck = true;
            a[j] = x;
            ++j;
        }
        if (Root->Data >= y && yCheck == false) {
            yCheck = true;
            a[j] = y;
            ++j;
        }
        a[j] = Root->Data;
        
        ++j;
        demNodeTrongKhoangXY_DeQuy(Root->Right, x, y, a);
    }
}

#endif /* Cay_Nhi_Phan_TimKiem_hpp */
