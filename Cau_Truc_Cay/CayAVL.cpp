//
//  CayAVL.cpp
//  Cau_Truc_Cay
//
//  Created by PHẠM HÙNG DŨNG on 30/08/2022.
//

#include <iostream>

using namespace std;

struct Node
{
    char data;
    struct Node *Left, *Right, *Cha;
};

void iNit(Node *&Root)
{
    Root = NULL;
}


Node* getNode(char x)
{
    Node *p = new Node;
    
    if (p == NULL) {
        return NULL;
    }
    
    p->data = x;
    p->Left = p->Right = p->Cha = NULL;
    
    return p;
}

int tinhChieuCaoCay(Node *Root)
{
    if (Root != NULL) {
        int left = tinhChieuCaoCay(Root->Left);
        int right = tinhChieuCaoCay(Root->Right);
        return left > right ? left + 1 : right + 1;
    }
    return 0;
}

int themNodeVaoCay_DeQuy(Node *&Root, char x)
{
    if (Root != NULL) {
        if (x > Root->data) {
            return themNodeVaoCay_DeQuy(Root->Right, x);
        }
        else if (x < Root->data) {
            return themNodeVaoCay_DeQuy(Root->Left, x);
        }
        else {
            return 0;
        }
    }
    else {
        Node *con = getNode(x);
        
        if (con == NULL) {
            return -1;
        }
        
        Root = con;
        
        return 1;
    }
}

void NLR(Node *Root)
{
    if (Root != NULL) {
        cout << Root->data << " ";
        NLR(Root->Left);
        NLR(Root->Right);
    }
}

void giaiPhongCay(Node *&Root)
{
    if (Root != NULL) {
        giaiPhongCay(Root->Left);
        giaiPhongCay(Root->Right);
        delete Root;
        Root = NULL;
    }
}

int main()
{
    Node *Root;
    iNit(Root);
    
    char x;
    do {
        cout << "\nNhap vao gia tri can them(Nhap '.' de ket thuc qua trinh them): ";
        fflush(stdin);
        cin >> x;
        
        int kq = themNodeVaoCay_DeQuy(Root, x);
        if (kq == 0) {
            cout << "\nKhong them duoc do da bi trung!!!";
        }
        else if (kq == -1) {
            cout << "\nKhong them duoc do khong du bo nho!!!";
        }
        else if (kq == 1) {
            cout << "\nThem thanh cong vao cay.";
            cout << "\nCay sau khi them: ";
            NLR(Root);
            cout << "\nChieu cao cay: " << tinhChieuCaoCay(Root);
        }
    } while (x != '.');
    
    giaiPhongCay(Root);
    
    //system("pause");
    return 0;
}
