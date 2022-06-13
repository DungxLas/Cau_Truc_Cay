//
//  Cay_Nhi_Phan_Linked.h
//  Cau_Truc_Cay
//
//  Created by PHẠM HÙNG DŨNG on 06/06/2022.
//

#ifndef Cay_Nhi_Phan_Linked_h
#define Cay_Nhi_Phan_Linked_h

#include <iostream>
#include <queue>
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

/* Tao cay */
void TaoCay(Node *&Root) {
    char x;
    cout << "Nhap du lieu cho Node goc: ";
    cin >> x;
    Root = GetNode(x);
    
    queue<Node *> q;
    q.push(Root);
    while (!q.empty()) {  // Lap toi khi hang doi rong
        Node *p = q.front(); // Lay Node dau tien dang cho duoc xu ly gan vao p
        q.pop(); // Bo phan tu dau tien ra khoi hang doi
        
        int SoCon;
        do {
            cout << "\nNhap vao so luong con cua Node " << p->Data << "(0 hay 1 hay 2): ";
            cin >> SoCon;
            
            if (SoCon < 0 || SoCon > 2) {
                cout << "\nSo luong con khong hop le!!!!";
            }
        } while (SoCon < 0 || SoCon > 2);
        
        if (SoCon == 1) {
            char LoaiCon;
            do {
                cout << "\nBan muon con cua Node " << p->Data << " la con trai hay phai? Neu la trai nhap L(l) - Neu la phai nhap R(r): ";
                cin >> LoaiCon;
                if (LoaiCon != 'L' && LoaiCon != 'R' && LoaiCon != 'l' && LoaiCon != 'r') {
                    cout << "\nNhap sai, xin hay nhap lai!!!";
                }
            } while (LoaiCon != 'L' && LoaiCon != 'R' && LoaiCon != 'l' && LoaiCon != 'r');
            
            char y;
            cout << "Nhap du lieu cho Node: ";
            cin >> y;
            Node *k = GetNode(y);
            if (LoaiCon == 'L' || LoaiCon == 'l') {
                p->Left = k;
            }
            else {
                p->Right = k;
            }
            q.push(k);
        }
        else if (SoCon == 2) {
            char z;
            cout << "Nhap du lieu cho Node trai: ";
            cin >> z;
            Node *l = GetNode(z);
            p->Left = l;
            q.push(l);
            cout << "Nhap du lieu cho Node phai: ";
            cin >> z;
            Node *r = GetNode(z);
            p->Right = r;
            q.push(r);
            
        }
    }
}

/* Duyet cay */
    // Duyet theo chieu rong; 'true' la duyet trai qua phai, 'false' la duyet phai qua trai
void Duyet_theo_chieu_rong(Node *Root, bool ChieuDuyet)
{
    queue<Node *> q;
    q.push(Root);
    
    while (!q.empty()) {
        Node *p = q.front();
        cout << p->Data << " ";
        q.pop();
        
        if (ChieuDuyet == true) {
            if (p->Left != NULL) {
                q.push(p->Left);
            }
            if (p->Right != NULL) {
                q.push(p->Right);
            }
        }
        else {
            if (p->Right != NULL) {
                q.push(p->Right);
            }
            if (p->Left != NULL) {
                q.push(p->Left);
            }
        }
    }
}
    // Duyet theo chieu sau
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

/* Giai phong */
void RemoveAll(Node *&Root)
{
    if (Root != NULL) {
        RemoveAll(Root->Left);
        RemoveAll(Root->Right);
        delete Root;
    }
}

/* Thao tac cho cay */
    // Dem so node tren cay
int DemSoNode_DeQuyThuong(Node *Root)
{
    // Dieu kien dung
    if (Root == NULL) {
        return 0;
    }
    // Buoc de quy
    return 1 + DemSoNode_DeQuyThuong(Root->Left) + DemSoNode_DeQuyThuong(Root->Right);
}

void DemSoNode_DeQuyDuoi(Node *Root, int &dem)
{
    if (Root != NULL) {
        dem++;
        DemSoNode_DeQuyDuoi(Root->Left, dem);
        DemSoNode_DeQuyDuoi(Root->Right, dem);
    }
}

int DemSoNode_KhuDeQuy(Node *Root, bool ChieuDuyet)
{
    queue<Node *> q;
    q.push(Root);
    
    int dem = 0;
    while (!q.empty()) {
        Node *p = q.front();
        dem++;
        q.pop();
        
        if (ChieuDuyet == true) {
            if (p->Left != NULL) {
                q.push(p->Left);
            }
            if (p->Right != NULL) {
                q.push(p->Right);
            }
        }
        else {
            if (p->Right != NULL) {
                q.push(p->Right);
            }
            if (p->Left != NULL) {
                q.push(p->Left);
            }
        }
    }
    
    return dem;
}

    // Dem so node la tren cay
int DemSoNodeLa_DeQuyThuong(Node *Root)
{
    // Dieu kien dung
    if (Root == NULL) {
    return 0;
    }
    
    int dem = 0;
    if (Root->Left == NULL && Root->Right == NULL) {
        dem = 1;
    }
    
    // Buoc de quy
    return dem + DemSoNodeLa_DeQuyThuong(Root->Left) + DemSoNodeLa_DeQuyThuong(Root->Right);
}

void DemSoNodeLa_DeQuyDuoi(Node *Root, int &dem)
{
    if (Root != NULL) {
        if (Root->Left == NULL && Root->Right == NULL) {
            dem++;
        }
        DemSoNodeLa_DeQuyDuoi(Root->Left, dem);
        DemSoNodeLa_DeQuyDuoi(Root->Right, dem);
    }
}

    // Dem so node chi 1 con con tren cay
int DemSoNode1Con_DeQuyThuong(Node *Root)
{
        // Dieu kien dung
    if (Root == NULL) {
    return 0;
    }

    int dem = 0;
    if ((Root->Left == NULL && Root->Right != NULL) || (Root->Left != NULL && Root->Right == NULL)) {
        dem = 1;
    }

    // Buoc de quy
    return dem + DemSoNode1Con_DeQuyThuong(Root->Left) + DemSoNode1Con_DeQuyThuong(Root->Right);
    }

void DemSoNode1Con_DeQuyDuoi(Node *Root, int &dem)
{
    if (Root != NULL) {
        if ((Root->Left == NULL && Root->Right != NULL) || (Root->Left != NULL && Root->Right == NULL)) {
            dem++;
        }
        DemSoNode1Con_DeQuyDuoi(Root->Left, dem);
        DemSoNode1Con_DeQuyDuoi(Root->Right, dem);
    }
}

    // Dem so node du 2 con tren cay
int DemSoNodeDu_DeQuyThuong(Node *Root)
{
        // Dieu kien dung
    if (Root == NULL) {
    return 0;
    }

    int dem = 0;
    if (Root->Left != NULL && Root->Right != NULL) {
        dem = 1;
    }

    // Buoc de quy
    return dem + DemSoNodeDu_DeQuyThuong(Root->Left) + DemSoNodeDu_DeQuyThuong(Root->Right);
    }

void DemSoNodeDu_DeQuyDuoi(Node *Root, int &dem)
{
    if (Root != NULL) {
        if (Root->Left != NULL && Root->Right != NULL) {
            dem++;
        }
        DemSoNodeDu_DeQuyDuoi(Root->Left, dem);
        DemSoNodeDu_DeQuyDuoi(Root->Right, dem);
    }
}

    // Tim bac cua 1 node
int BacCua1Node(Node *X)
{
    int dem = 0;
    
    if (X->Left != NULL) {
        dem++;
    }
    if (X->Right != NULL) {
        dem++;
    }
    
    return dem;
}

    // Tim Bac cua 1 cay
void BacCua1Cay(Node *Root, int &maxBac)
{
    if (Root != NULL) {
        // Xu ly
        int bac = BacCua1Node(Root);
        if (bac > maxBac) {
            maxBac = bac;
            if (maxBac == 2) {
                return;
            }
        }
        
        // De quy
        BacCua1Cay(Root->Left, maxBac);
        BacCua1Cay(Root->Right, maxBac);
    }
}

    // Tim Muc cua 1 cay(Chieu cao cua 1 cay)
int MucCua1Cay_DeQuyThuong(Node *Root)
{
    if (Root == NULL) {
        return 0;
    }
    
    int left = MucCua1Cay_DeQuyThuong(Root->Left);
    int right = MucCua1Cay_DeQuyThuong(Root->Right);
    
    return left > right ? left + 1 : right + 1;
}

void MucCua1Cay_DeQuyDuoi(Node *Root,int &ChieuCao, int level)
{
    if (Root != NULL) {
        if (level > ChieuCao) {
            ChieuCao = level;
        }
        level++;
        MucCua1Cay_DeQuyDuoi(Root->Left, ChieuCao, level);
        MucCua1Cay_DeQuyDuoi(Root->Right, ChieuCao, level);
    }
}

    // Tim Muc cua 1 node
int MucCua1Node_DeQuyThuong(Node *Root, Node *X)
{
    if (Root == NULL) {
        return 0;
    }
    
    int left = MucCua1Node_DeQuyThuong(Root->Left, X);
    int right = MucCua1Node_DeQuyThuong(Root->Right, X);
    
    return left > right ? left + 1 : right + 1;
}

#endif /* Cay_Nhi_Phan_Linked_h */
