//
//  main.cpp
//  Cau_Truc_Cay
//
//  Created by PHẠM HÙNG DŨNG on 05/06/2022.
//

#include <iostream>

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

    // Bước 2: Tạo ra các mối liên kết giữa các Node với nhau
    Root->Left = B;
    Root->Right = C;
    B->Left = D;
    B->Right = E;
    C->Left = F;
    C->Right = G;
    D->Left = H;
    D->Right = I;
    E->Right = J;
    F->Left = K;
    G->Right = L;
    
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
    
    cout << "Muc cua Node: " << MucCua1Node_DeQuyThuong(Root, B) << endl;
    
    RemoveAll(Root);
    
    return 0;
}
