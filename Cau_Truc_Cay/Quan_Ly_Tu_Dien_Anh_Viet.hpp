//
//  Quan_Ly_Tu_Dien_Anh_Viet.hpp
//  Cau_Truc_Cay
//
//  Created by PHẠM HÙNG DŨNG on 25/08/2022.
//

#ifndef Quan_Ly_Tu_Dien_Anh_Viet_hpp
#define Quan_Ly_Tu_Dien_Anh_Viet_hpp

#include <iostream>
#include <string>
#include <fstream>
#include <queue>
#include <cstdlib>


#include "convertString.h"

using namespace std;

/* 1/ Khai bao cau truc du lieu cay nhi phan tim kiem */
struct TU
{
    string Vie, Eng;
};

struct NODE
{
    TU Data;
    NODE *Cha, *Left, *Right;
    int ThuTuDuyet;
};

    //Xay dung phep toan operator
bool operator >(TU A, TU B)
{
    return A.Eng > B.Eng;
}
bool operator >=(TU A, TU B)
{
    return A.Eng >= B.Eng;
}
bool operator <(TU A, TU B)
{
    return A.Eng < B.Eng;
}
bool operator <=(TU A, TU B)
{
    return A.Eng <= B.Eng;
}
bool operator ==(TU A, TU B)
{
    return A.Eng == B.Eng;
}
bool operator !=(TU A, TU B)
{
    return A.Eng != B.Eng;
}

/* 2/ Khoi tao cay */
void iNit(NODE *&Root)
{
    Root = NULL;
}

/* 3/ Tao Node */
NODE* getNode(TU x)
{
    NODE* p = new NODE;
    if (p == NULL) {
        return NULL;
    }
    p->Data = x;
    p->Left = p->Right = p->Cha = NULL;
    p->ThuTuDuyet = 0;
    return p;
}

/* 4/ Them Node */
NODE* timNode_KhuDeQuy(NODE* Root, TU x)
{
    NODE* p = Root;
    NODE* q = p;
    while (p != NULL) {
        q = p;
        
        if (x > p->Data) {
            p = p->Right;
        }
        else if (x < p->Data) {
            p = p->Left;
        }
        else {
            return p;
        }
    }
    return q; //Tra ve node cuoi cung truoc khi den NULL
}

int ThemNode_KhuDeQuy(NODE*& Root, TU x)
{
    if (Root == NULL) {
        Root = getNode(x);
    }
    else
    {
        NODE* p = timNode_KhuDeQuy(Root, x);
        
        if (p->Data != x) {
            NODE* conMoi = getNode(x);
            
            if (conMoi == NULL) {
                return -1;
            }
            if (x > p->Data) {
                p->Right = conMoi;
            }
            else if (x < p->Data) {
                p->Left = conMoi;
            }
            conMoi->Cha = p;
        }
        else {
            return 0;
        }
    }
    return 1;
}

/* 5/ Giai phong cay*/
void GiaiPhongCay_KhuDeQuy(NODE *&Root)
{
    char s[] = "NLR";

    if(Root != NULL)
    {
        NODE *cha = Root->Cha;
        Root->Cha = NULL; // quy ước Root chính là gốc của cây đang xét (nó có thể là cây nhỏ cho nên phải cho điều kiện dừng là Root->Cha = NULL)
        while(true)
        {
            if(Root->ThuTuDuyet <= 2)
            {
                if(s[Root->ThuTuDuyet] == 'N' || s[Root->ThuTuDuyet] == 'n')
                {

                    Root->ThuTuDuyet++;
                }
                else if(s[Root->ThuTuDuyet] == 'L' || s[Root->ThuTuDuyet] == 'l')
                {
                    Root->ThuTuDuyet++;

                    if(Root->Left != NULL)
                        Root = Root->Left;
                }
                else if(s[Root->ThuTuDuyet] == 'R' || s[Root->ThuTuDuyet] == 'r')
                {
                    Root->ThuTuDuyet++;

                    if(Root->Right != NULL)
                        Root = Root->Right;
                }
            }
            else // khi đi vào đây tức là 1 node đã đi hết thang thứ tự duyệt rồi, lúc này không đi tới được nữa mà phải lùi về cha của nó để xét theo hướng khác
            {
                Root->ThuTuDuyet = 0; // trước khi trở về cha thì sẽ reset lại thứ tự duyệt của node đó về 0 để có thể sau hàm này còn nhu cầu duyệt tiếp kiểu khác nữa

                if(Root->Cha == NULL)
                {
                    Root->Cha = cha; // trả lại cha ban đầu của Root;

                    delete Root;
                    Root = NULL;
                    break; // ĐIỀU KIỆN DỪNG => TỪ GỐC TRỎ VỀ CHA SẼ LÀ NULL => DỪNG LẠI
                }
                else
                {
                    NODE *q = Root;
                    Root = Root->Cha;
                    delete q;
                    q = NULL;
                }
            }
        }
    }
}


/* 6/ Thao tac voi tu dien*/

void nhapMotTu(TU &a){
    fflush(stdin);
    cout << "\nNhap vao tu tieng anh: ";
    getline(cin, a.Eng);
    a.Eng = strlwr(a.Eng);
    
    fflush(stdin);
    cout << "\nNhap nghia tieng viet tuong ung: ";
    getline(cin, a.Vie);
    a.Vie = strlwr(a.Vie);
}

void taoCayTuBanPhimKoBietTruocSoLuong(NODE *&Root){
    TU x;
    char select;
    do {
        nhapMotTu(x);
        
        int ketqua = ThemNode_KhuDeQuy(Root, x);
        if (ketqua == 0) {
            cout << "\nLoi: Gia tri Node nay da ton tai trong cay roi cho nen khong them vao cay duoc nua!!!";
        }
        else if (ketqua == -1) {
            cout << "\nLoi: Khong du bo nho de cap nhap cho Node!!!";
        }
        else if (ketqua == 1) {
            cout << "\nThem thanh cong vao tu dien.";
        }
        
        cout << "\nBan co muon nhap nua ko? nha phim c de nhap tiep / nhan phim bat ki de ket thuc: ";
        cin >> select;
    } while (select == 'c' || select == 'C');
}

void preOrder(NODE *Root)    // Node-Left-Right
{
    if (Root != NULL) {
        cout << Root->Data.Eng << ": " << Root->Data.Vie << endl;
        preOrder(Root->Left);
        preOrder(Root->Right);
    }
}

void inOrder(NODE *Root)    // Left-Node-Right
{
    if (Root != NULL) {
        inOrder(Root->Left);
        cout << Root->Data.Eng << ": " << Root->Data.Vie << endl;
        inOrder(Root->Right);
    }
}

//void postOrder(Node *Root)    // Left-Right-Node
//{
//    if (Root != NULL) {
//        postOrder(Root->Left);
//        postOrder(Root->Right);
//        cout << Root->Data << " ";
//    }
//}
//
//
//
//Node* timNodeVaThemNode_KhuDeQuy(Node*& Root, int x)
//{
//    Node* p;
//    Node* q = Root;
//    if (q == NULL) {
//        return Root = getNode(x);
//    }
//    else
//    {
//        while (q != NULL) {
//            p = q;
//            if (x > q->Data) {
//                q = q->Right;
//            }
//            else if (x < q->Data) {
//                q = q->Left;
//            }
//            else if (x == q->Data) {
//                cout << "Node can tim co trong cay!" << endl;
//                return q;
//            }
//        }
//    }
//    
//    cout << "Node can tim ko co trong cay. Da tu dong them vao cay!" << endl;
//    if (x > p->Data) {
//        p->Right = getNode(x);
//        p = p->Right;
//    }
//    else if (x < p->Data) {
//        p->Left = getNode(x);
//        p = p->Left;
//    }
//    return p;
//}
//
///* 5/ Xoa Node */
//void timPhanTuTheMang(Node*& Root, Node*& p)
//{
//    if (Root->Right != NULL) {
//        timPhanTuTheMang(Root->Right, p);
//    }
//    else {
//        p->Data = Root->Data;
//        p = Root;
//        Root = Root->Left;
//    }
//}
//
//void timVaXoaNode_DeQuy(Node*& Root, int x)
//{
//    if (Root == NULL) {
//        return;
//    }
//    
//    if (Root->Data < x) {
//        timVaXoaNode_DeQuy(Root->Right, x);
//    }
//    else if (Root->Data > x) {
//        timVaXoaNode_DeQuy(Root->Left, x);
//    }
//    else {
//        Node *p = Root;
//        
//        if (p->Left == NULL) {
//            Root = p->Right;
//        }
//        else if (p->Right == NULL) {
//            Root = p->Left;
//        }
//        else {
//            timPhanTuTheMang(Root->Left, p);
//        }
//        
//        delete p;
//    }
//}

#endif /* Quan_Ly_Tu_Dien_Anh_Viet_hpp */
