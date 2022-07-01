//
//  main.cpp
//  Cau_Truc_Cay
//
//  Created by PHẠM HÙNG DŨNG on 05/06/2022.
//

#include <iostream>
#include <vector>

#include "/Users/phamhungdung/CoDe/C:C++/Cau_Truc_Cay/Cay_Nhi_Phan_Linked.h"

using namespace std;

int main() {
    // Bước 1: Tạo ra bấy nhiêu Node tương ứng với các Node có trong cây
    Node *Root = GetNode('A'); // Đây chính là Node gốc
    Node *B = GetNode('B');
    Node *C = GetNode('C');
    Node *D = GetNode('D');
    Node *E = GetNode('E');
    Node *F = GetNode('F');
    Node *G = GetNode('G');
    Node *H = GetNode('H');
    Node *I = GetNode('I');
    Node *J = GetNode('J');
    Node *K = GetNode('K');
    Node *L = GetNode('L');
//    Node *Z = GetNode('Z');;

    // Bước 2: Tạo ra các mối liên kết giữa các Node với nhau
    Root->Left = B;
    B->Cha = Root;
    Root->Right = C;
    C->Cha = Root;
    B->Left = D;
    D->Cha = B;
    B->Right = E;
    E->Cha = B;
    C->Left = F;
    F->Cha = C;
    C->Right = G;
    G->Cha = C;
    D->Left = H;
    H->Cha = D;
    D->Right = I;
    I->Cha = D;
    E->Right = J;
    J->Cha = E;
    F->Left = K;
    K->Cha = F;
    G->Right = L;
    L->Cha = G;
    
    // Duyet
//    cout << "\nDuyet theo chieu rong: ";
//    Duyet_theo_chieu_rong(Root, true);
//
//    cout << "\nDuyet theo chieu sau(Node-Left-Right): ";
//    preOrder(Root);
//
//    cout << "\nDuyet theo chieu sau(Left-Node-Right): ";
//    inOrder(Root);
//
//    cout << "\nDuyet theo chieu sau(Left-Right-Node): ";
//    postOrder(Root);
    
//    cout << "So luong Node tren cay: " << DemSoNode_DeQuyThuong(Root) << endl;
//
//    int soNode = 0;
//    DemSoNode_DeQuyDuoi(Root, soNode);
//    cout << "So luong Node tren cay: " << soNode << endl;
//
//    cout << "So luong Node tren cay: " << DemSoNode_KhuDeQuy(Root, true) << endl;
    
//    cout << "So luong Node la tren cay: " << DemSoNodeLa_DeQuyThuong(Root) << endl;
//
//    int soNode = 0;
//    DemSoNodeLa_DeQuyDuoi(Root, soNode);
//    cout << "So luong Node la tren cay: " << soNode << endl;
    
//    cout << "So luong Node chi 1 con tren cay: " << DemSoNode1Con_DeQuyThuong(Root) << endl;
//
//    int soNode = 0;
//    DemSoNode1Con_DeQuyDuoi(Root, soNode);
//    cout << "So luong Node chi 1 con tren cay: " << soNode << endl;
    
//    cout << "So luong Node du 2 con tren cay: " << DemSoNodeDu_DeQuyThuong(Root) << endl;
//
//    int soNode = 0;
//    DemSoNodeDu_DeQuyDuoi(Root, soNode);
//    cout << "So luong Node du 2 con tren cay: " << soNode << endl;
    
//    int BacCay = 0;
//    BacCua1Cay(Root, BacCay);
//    cout << "Cay co bac la: " << BacCay << endl;
    
//    cout << "Chieu cao cua cay: " << MucCua1Cay_DeQuyThuong(Root) << endl;
//    
//    int ChieuCao = 0;
//    MucCua1Cay_DeQuyDuoi(Root, ChieuCao, 1);
//    cout << "Chieu cao cua cay: " << ChieuCao << endl;
    
//    bool checkNode = false;
//    int muc;
//    TimNode(Root, checkNode, L, muc, 1);
//    if (checkNode == false) {
//        cout << "Node can tim khong co trong cay!!!" << endl;
//    }
//    else {
//        cout << "Node can tim co trong cay, co muc la: " << muc << endl;
//    }
    
//    int k;
//    cout << "Can tim cac Node o tang: k = ";
//    cin >> k;
//    cout << "Cac Node o tang k = " << k << " la: ";
//    int count = 0;
//    CacNodeTangK(Root, k, count, 1);
//    if (count == 0) {
//        cout << "=> Khong co Node tren tang " << k << endl;
//    }
//    else {
//        cout << "=> Co " << count << " Node" << endl;
//    }
    
//    int ChieuCao = 0;
//    MucCua1Cay_DeQuyDuoi(Root, ChieuCao, 1);
//
//    if (KiemTraNhiPhanDayDu(Root, ChieuCao) == true) {
//        cout << "Cay da cho la cay nhi phan day du." << endl;
//    }
//    else {
//        cout << "Cay da cho khong phai la cay nhi phan day du." << endl;
//    }
    
//    if (KiemTraNhiPhanDayDuVector(Root) == true) {
//            cout << "Cay da cho la cay nhi phan day du." << endl;
//    }
//    else {
//            cout << "Cay da cho khong phai la cay nhi phan day du." << endl;
//    }
    
//    if (KiemTraNhiPhanHoanChinhVector(Root)) {
//        cout << "Day la cay nhi phan hoan chinh" << endl;
//    }
//    else {
//        cout << "Day khong phai la cay nhi phan hoan chinh" << endl;
//    }
    
    DuyetCay_KoDeQuy_KoNganXep(Root, "NLR");
    cout << "\n";
    DuyetCay_KoDeQuy_KoNganXep(Root, "LNR");
    cout << "\n";
    DuyetCay_KoDeQuy_KoNganXep(Root, "LRN");
    
    RemoveAll(Root);
    
    return 0;
}
