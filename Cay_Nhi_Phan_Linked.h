//
//  Cay_Nhi_Phan_Linked.h
//  Cau_Truc_Cay
//
//  Created by PHẠM HÙNG DŨNG on 06/06/2022.
//

#ifndef Cay_Nhi_Phan_Linked_h
#define Cay_Nhi_Phan_Linked_h

#include <iostream>
using namespace std;

/* Khai bao cau truc du lieu cay nhi phan */
struct Node {
    char Data;
    struct Node *Left, *Right; //tro trai, tro phai
};

/* Khoi tao cay nhi phan */
void Init(Node *&Root) {
    Root = NULL;
}

/* Tao Node */
Node* GetNode(char x) {
    Node* p = new Node;
    if (p == NULL) {
        return NULL;
    }
    p->Data = x;
    p->Left = p->Right = NULL;
    
    return p;
}

#endif /* Cay_Nhi_Phan_Linked_h */
