//
//  Doc_Gia.h
//  Cau_Truc_Cay
//
//  Created by PHẠM HÙNG DŨNG on 27/06/2022.
//

#ifndef Doc_Gia_h
#define Doc_Gia_h

#include <iostream>
#include <queue>
#include <math.h>
#include <vector>
#include <string>
using namespace std;

/* Khai bao cau truc du lieu cay nhi phan */
struct Ngay {
    int Day, Month, Year;
};

struct DocGia {
    char MaDocGia[6];
    char TenDocGia[31];
    Ngay NgaySinh;
    char DiaChi[31];
    Ngay NgayLapThe;
};

struct Node {
    DocGia Data;
    struct Node *Left, *Right;
};

bool operator > (Ngay x, Ngay y)
{
    if (x.Year < y.Year) {
        return true;
    }
    else if (x.Year > y.Year) {
        return false;
    }
    
    if (x.Month < y.Month) {
        return true;
    }
    else if (x.Month > y.Month) {
        return false;
    }
    
    if (x.Day < y.Day) {
        return true;
    }
//    else if (x.Day > y.Day) {
//        return false;
//    }
    return false;
}

/* Khoi tao cay nhi phan */
void Init(Node *&Root) {
    Root = NULL;
}

/* Tao Node */
Node* GetNode(DocGia x) {
    Node* p = new Node;
    if (p == NULL) {
        return NULL;
    }
    p->Data = x;
    p->Left = p->Right = NULL;
    
    return p;
}

///* Tao cay */
//void TaoCay(Node *&Root) {
//    char x;
//    cout << "Nhap du lieu cho Node goc: ";
//    cin >> x;
//    Root = GetNode(x);
//
//    queue<Node *> q;
//    q.push(Root);
//    while (!q.empty()) {  // Lap toi khi hang doi rong
//        Node *p = q.front(); // Lay Node dau tien dang cho duoc xu ly gan vao p
//        q.pop(); // Bo phan tu dau tien ra khoi hang doi
//
//        int SoCon;
//        do {
//            cout << "\nNhap vao so luong con cua Node " << p->Data << "(0 hay 1 hay 2): ";
//            cin >> SoCon;
//
//            if (SoCon < 0 || SoCon > 2) {
//                cout << "\nSo luong con khong hop le!!!!";
//            }
//        } while (SoCon < 0 || SoCon > 2);
//
//        if (SoCon == 1) {
//            char LoaiCon;
//            do {
//                cout << "\nBan muon con cua Node " << p->Data << " la con trai hay phai? Neu la trai nhap L(l) - Neu la phai nhap R(r): ";
//                cin >> LoaiCon;
//                if (LoaiCon != 'L' && LoaiCon != 'R' && LoaiCon != 'l' && LoaiCon != 'r') {
//                    cout << "\nNhap sai, xin hay nhap lai!!!";
//                }
//            } while (LoaiCon != 'L' && LoaiCon != 'R' && LoaiCon != 'l' && LoaiCon != 'r');
//
//            char y;
//            cout << "Nhap du lieu cho Node: ";
//            cin >> y;
//            Node *k = GetNode(y);
//            if (LoaiCon == 'L' || LoaiCon == 'l') {
//                p->Left = k;
//            }
//            else {
//                p->Right = k;
//            }
//            q.push(k);
//        }
//        else if (SoCon == 2) {
//            char z;
//            cout << "Nhap du lieu cho Node trai: ";
//            cin >> z;
//            Node *l = GetNode(z);
//            p->Left = l;
//            q.push(l);
//            cout << "Nhap du lieu cho Node phai: ";
//            cin >> z;
//            Node *r = GetNode(z);
//            p->Right = r;
//            q.push(r);
//
//        }
//    }
//}
//
///* Duyet cay */
//    // Duyet theo chieu rong; 'true' la duyet trai qua phai, 'false' la duyet phai qua trai
//void Duyet_theo_chieu_rong(Node *Root, bool ChieuDuyet)
//{
//    queue<Node *> q;
//    q.push(Root);
//
//    while (!q.empty()) {
//        Node *p = q.front();
//        cout << p->Data << " ";
//        q.pop();
//
//        if (ChieuDuyet == true) {
//            if (p->Left != NULL) {
//                q.push(p->Left);
//            }
//            if (p->Right != NULL) {
//                q.push(p->Right);
//            }
//        }
//        else {
//            if (p->Right != NULL) {
//                q.push(p->Right);
//            }
//            if (p->Left != NULL) {
//                q.push(p->Left);
//            }
//        }
//    }
//}
//    // Duyet theo chieu sau
//void preOrder(Node *Root)    // Node-Left-Right
//{
//    if (Root != NULL) {
//        cout << Root->Data << " ";
//        preOrder(Root->Left);
//        preOrder(Root->Right);
//    }
//}
//
//void inOrder(Node *Root)    // Left-Node-Right
//{
//    if (Root != NULL) {
//        inOrder(Root->Left);
//        cout << Root->Data << " ";
//        inOrder(Root->Right);
//    }
//}
//
//void postOrder(Node *Root)    // Left-Right-Node
//{
//    if (Root != NULL) {
//        postOrder(Root->Left);
//        postOrder(Root->Right);
//        cout << Root->Data << " ";
//    }
//}
//
//    /* Duyet theo chieu sau KO dung de quy, KO dung ngan xep */
//void DuyetCay_KoDeQuy_KoNganXep(Node *Root, char *s)
//{
//    cout << s << endl;
//
//    while (true) {
//        if (Root->ThuTuDuyet <= 2) {
//            if (s[Root->ThuTuDuyet] == 'N') {
//                cout << Root->Data << "   ";
//                Root->ThuTuDuyet++;
//            }
//            else if (s[Root->ThuTuDuyet] == 'L')
//            {
//                Root->ThuTuDuyet++;
//                if (Root->Left != NULL) {
//                    Root = Root->Left;
//                }
//            }
//            else if (s[Root->ThuTuDuyet] == 'R')
//            {
//                Root->ThuTuDuyet++;
//                if (Root->Right != NULL) {
//                    Root = Root->Right;
//                }
//            }
//        }
//        else {
//            Root->ThuTuDuyet = 0;
//            Root = Root->Cha;
//            if (Root == NULL) {  //Dieu Kien Dung
//                break;
//            }
//        }
//    }
//}

/* Giai phong */
void RemoveAll(Node *&Root)
{
    if (Root != NULL) {
        RemoveAll(Root->Left);
        RemoveAll(Root->Right);
        delete Root;
    }
}

///* Thao tac cho cay */
//    // Dem so node tren cay
//int DemSoNode_DeQuyThuong(Node *Root)
//{
//    // Dieu kien dung
//    if (Root == NULL) {
//        return 0;
//    }
//    // Buoc de quy
//    return 1 + DemSoNode_DeQuyThuong(Root->Left) + DemSoNode_DeQuyThuong(Root->Right);
//}
//
//void DemSoNode_DeQuyDuoi(Node *Root, int &dem)
//{
//    if (Root != NULL) {
//        dem++;
//        DemSoNode_DeQuyDuoi(Root->Left, dem);
//        DemSoNode_DeQuyDuoi(Root->Right, dem);
//    }
//}
//
//int DemSoNode_KhuDeQuy(Node *Root, bool ChieuDuyet)
//{
//    queue<Node *> q;
//    q.push(Root);
//
//    int dem = 0;
//    while (!q.empty()) {
//        Node *p = q.front();
//        dem++;
//        q.pop();
//
//        if (ChieuDuyet == true) {
//            if (p->Left != NULL) {
//                q.push(p->Left);
//            }
//            if (p->Right != NULL) {
//                q.push(p->Right);
//            }
//        }
//        else {
//            if (p->Right != NULL) {
//                q.push(p->Right);
//            }
//            if (p->Left != NULL) {
//                q.push(p->Left);
//            }
//        }
//    }
//
//    return dem;
//}
//
//    // Dem so node la tren cay
//int DemSoNodeLa_DeQuyThuong(Node *Root)
//{
//    // Dieu kien dung
//    if (Root == NULL) {
//    return 0;
//    }
//
//    int dem = 0;
//    if (Root->Left == NULL && Root->Right == NULL) {
//        dem = 1;
//    }
//
//    // Buoc de quy
//    return dem + DemSoNodeLa_DeQuyThuong(Root->Left) + DemSoNodeLa_DeQuyThuong(Root->Right);
//}
//
//void DemSoNodeLa_DeQuyDuoi(Node *Root, int &dem)
//{
//    if (Root != NULL) {
//        if (Root->Left == NULL && Root->Right == NULL) {
//            dem++;
//        }
//        DemSoNodeLa_DeQuyDuoi(Root->Left, dem);
//        DemSoNodeLa_DeQuyDuoi(Root->Right, dem);
//    }
//}
//
//    // Dem so node chi 1 con con tren cay
//int DemSoNode1Con_DeQuyThuong(Node *Root)
//{
//        // Dieu kien dung
//    if (Root == NULL) {
//    return 0;
//    }
//
//    int dem = 0;
//    if ((Root->Left == NULL && Root->Right != NULL) || (Root->Left != NULL && Root->Right == NULL)) {
//        dem = 1;
//    }
//
//    // Buoc de quy
//    return dem + DemSoNode1Con_DeQuyThuong(Root->Left) + DemSoNode1Con_DeQuyThuong(Root->Right);
//    }
//
//void DemSoNode1Con_DeQuyDuoi(Node *Root, int &dem)
//{
//    if (Root != NULL) {
//        if ((Root->Left == NULL && Root->Right != NULL) || (Root->Left != NULL && Root->Right == NULL)) {
//            dem++;
//        }
//        DemSoNode1Con_DeQuyDuoi(Root->Left, dem);
//        DemSoNode1Con_DeQuyDuoi(Root->Right, dem);
//    }
//}
//
//    // Dem so node du 2 con tren cay
//int DemSoNodeDu_DeQuyThuong(Node *Root)
//{
//        // Dieu kien dung
//    if (Root == NULL) {
//    return 0;
//    }
//
//    int dem = 0;
//    if (Root->Left != NULL && Root->Right != NULL) {
//        dem = 1;
//    }
//
//    // Buoc de quy
//    return dem + DemSoNodeDu_DeQuyThuong(Root->Left) + DemSoNodeDu_DeQuyThuong(Root->Right);
//    }
//
//void DemSoNodeDu_DeQuyDuoi(Node *Root, int &dem)
//{
//    if (Root != NULL) {
//        if (Root->Left != NULL && Root->Right != NULL) {
//            dem++;
//        }
//        DemSoNodeDu_DeQuyDuoi(Root->Left, dem);
//        DemSoNodeDu_DeQuyDuoi(Root->Right, dem);
//    }
//}
//
//    // Tim bac cua 1 node
//int BacCua1Node(Node *X)
//{
//    int dem = 0;
//
//    if (X->Left != NULL) {
//        dem++;
//    }
//    if (X->Right != NULL) {
//        dem++;
//    }
//
//    return dem;
//}
//
//    // Tim Bac cua 1 cay
//void BacCua1Cay(Node *Root, int &maxBac)
//{
//    if (Root != NULL) {
//        // Xu ly
//        int bac = BacCua1Node(Root);
//        if (bac > maxBac) {
//            maxBac = bac;
//            if (maxBac == 2) {
//                return;
//            }
//        }
//
//        // De quy
//        BacCua1Cay(Root->Left, maxBac);
//        BacCua1Cay(Root->Right, maxBac);
//    }
//}
//
//    // Tim Muc cua 1 cay(Chieu cao cua 1 cay)
//int MucCua1Cay_DeQuyThuong(Node *Root)
//{
//    if (Root == NULL) {
//        return 0;
//    }
//
//    int left = MucCua1Cay_DeQuyThuong(Root->Left);
//    int right = MucCua1Cay_DeQuyThuong(Root->Right);
//
//    return left > right ? left + 1 : right + 1;
//}
//
//void MucCua1Cay_DeQuyDuoi(Node *Root,int &ChieuCao, int level)
//{
//    if (Root != NULL) {
//        if (level > ChieuCao) {
//            ChieuCao = level;
//        }
//        level++;
//        MucCua1Cay_DeQuyDuoi(Root->Left, ChieuCao, level);
//        MucCua1Cay_DeQuyDuoi(Root->Right, ChieuCao, level);
//    }
//}
//
//    // Tim 1 Node co ton tai trong cay khong va Tim Muc cua 1 node
//void TimNode(Node *Root, bool &Check, Node *X, int &muc, int level)
//{
//    // Dieu kien de quy khi Node ton tai va chua duoc tim thay
//    if (Root != NULL && Check == false) {
//        if (Root->Data == X->Data) {
//            Check = true;
//            muc = level;
//            return;
//        }
//
//        level++;
//        TimNode(Root->Left, Check, X, muc, level);
//        TimNode(Root->Right, Check, X, muc, level);
//    }
//}
//
//    // Liet ke va dem cac Node tren tang k
//void CacNodeTangK(Node *Root, int k, int &count, int level)
//{
//    if (Root != NULL) {
//        if (level == k) {
//            count++;
//            //cout << Root->Data << "   ";
//            return;
//        }
//
//        level++;
//        CacNodeTangK(Root->Left, k, count, level);
//        CacNodeTangK(Root->Right, k, count, level);
//    }
//}
//
//    // Dem cac Node tren moi tang dua vao Vector
//void CacNodeTangVector(Node *Root, vector<int> &a, int level = 1)
//{
//    if (Root != NULL) {
//        if (level > a.size()) {
//            a.push_back(0);
//        }
//        a[level - 1]++;
//
//        level++;
//        CacNodeTangVector(Root->Left, a, level);
//        CacNodeTangVector(Root->Right, a, level);
//    }
//}
//bool KiemTraNhiPhanDayDuVector(Node *Root)
//{
//    vector<int> a;
//    CacNodeTangVector(Root, a);
//
//    int SoLuong = a.size();
//    for (int i = 0; i < SoLuong; ++i) {
//        if (a[i] != pow(2.0, i)) {
//            return false;
//        }
//    }
//    return true;
//}
//
//    // Kiem tra cay nhi phan co phai la cay nhi phan day du ko?
//bool KiemTraNhiPhanDayDu(Node *Root, int k) // Can phai biet truoc chieu cao k cua cay
//{
//    for (int i = 1; i <= k; i++) {
//        int count = 0;
//        CacNodeTangK(Root, i, count, 1);
//        if (count != pow(2, i - 1)) {
//            return false;
//        }
//    }
//    return true;
//}
//
//    // Kiem tra cay nhi phan co phai la cay nhi phan hoan chinh ko?
//void DuyetCayThanhMang2Chieu(Node *Root, vector<vector<Node*>> &Mang2ChieuNode, int level = 1)
//{
//    if (Root != NULL) {
//        if (level > Mang2ChieuNode.size()) {  //size cua mang 2 chieu la so hang
//            vector<Node*> temp;
//            temp.push_back(Root);
//            Mang2ChieuNode.push_back(temp);
//        }
//        else {
//            Mang2ChieuNode[level - 1].push_back(Root);
//        }
//        level++;
//        DuyetCayThanhMang2Chieu(Root->Left, Mang2ChieuNode, level);
//        DuyetCayThanhMang2Chieu(Root->Right, Mang2ChieuNode, level);
//    }
//}
//bool KiemTraNhiPhanHoanChinhVector(Node *Root)
//{
//    vector<vector<Node*>> Mang2ChieuNode;
//    DuyetCayThanhMang2Chieu(Root, Mang2ChieuNode);
//
//    int ChieuCaoCay = Mang2ChieuNode.size();
//    for (int i = 0; i < ChieuCaoCay; ++i) {
//        if (Mang2ChieuNode[i].size() != pow(2.0, i)) {
//            return false;
//        }
//    }
//    if (Mang2ChieuNode[ChieuCaoCay - 1].size() == pow(2.0, ChieuCaoCay)) {
//        return false;
//    }
//    for (int j = 0; j < Mang2ChieuNode[ChieuCaoCay - 1].size(); ++j) {
//        Node *Con = Mang2ChieuNode[ChieuCaoCay - 1][j];
//        Node *Cha = Mang2ChieuNode[ChieuCaoCay - 2][j / 2];
//
//        if (j % 2 == 2) {  //Chan => Con trai
//            if (Cha->Left != Con) {
//                return false;
//            }
//        }
//        else {  //Le => Con phai
//            if (Cha->Right != Con) {
//                return false;
//            }
//        }
//    }
//    return true;
//}

#endif /* Doc_Gia_h */
