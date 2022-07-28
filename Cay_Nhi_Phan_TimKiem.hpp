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

#endif /* Cay_Nhi_Phan_TimKiem_hpp */
