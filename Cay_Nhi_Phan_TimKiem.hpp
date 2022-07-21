//
//  Cay_Nhi_Phan_TimKiem.hpp
//  Cau_Truc_Cay
//
//  Created by PHẠM HÙNG DŨNG on 20/07/2022.
//

#ifndef Cay_Nhi_Phan_TimKiem_hpp
#define Cay_Nhi_Phan_TimKiem_hpp

#include <iostream>

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

/* 4/ */
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

void taoCayTuDaySo(Node*& Root, int a[], int n)
{
    iNit(Root);
    for (int i = 0; i < n; ++i) {
        ThemNode_DeQuy(Root, a[i]);
    }
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

#endif /* Cay_Nhi_Phan_TimKiem_hpp */
