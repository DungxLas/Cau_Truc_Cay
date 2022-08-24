//
//  Cay_Nhi_Phan_TimKiem.cpp
//  Cau_Truc_Cay
//
//  Created by PHẠM HÙNG DŨNG on 20/07/2022.
//

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <fstream>
#include <vector>

#include "Cay_Nhi_Phan_TimKiem.hpp"

using namespace std;

//void ClearScreen()
//    {
//    cout << string( 100, '\n' );
//    }

int main() {
    int max = 100;
    int min = -100;
    int n = 20;
    int a[n];
    srand(time(NULL));
    for (int i = 0; i < n; ++i) {
        a[i] = rand() % (max - min + 1) + min;
    }

    Node* Root;
    iNit(Root);
    taoCayTuDaySo(Root, a, n);
    inOrder(Root);
    
    cout << "\n";
    
    int count = 0;
    demSoLuongGiaTriPhanBietVaTanSuatXuatHien_DeQuy(Root, count);
    cout << "\n=> Co " << count << " gia tri phan biet.";
    
//    kiemTraCayNhiPhanTimKiem(Root);
//
//    Node* x;
//    x = timMinTrongCay_DeQuy(Root);
//    cout << "\n" << x->Data;
//    x = timMinTrongCay_KoDeQuy(Root);
//    cout << "\n" << x->Data;
//    x = timMaxTrongCay_DeQuy(Root);
//    cout << "\n" << x->Data;
//    x = timMaxTrongCay_KoDeQuy(Root);
//    cout << "\n" << x->Data;
    
//    int x = demNodeAmTrongCay_DeQuy(Root);
//    cout << "\nSo Node am trong cay: " << x;
//    int y = demNodeAmTrongCay_KoDeQuy(Root);
//    cout << "\nSo Node am trong cay: " << y;
//    int z = 0;
//    demNodeAmTrongCay_DeQuy_CaiTien(Root, z);
//    cout << "\nSo Node am trong cay: " << z;
    
//    int x = -50;
//    int y = 50;
//    vector<int> b;
//    buoc1_TaoMangChuaCacNodeVaXY_KhuDeQuy(Root, b, x, y);
//    for (int i = 0; i < b.size(); ++i) {
//        cout << b[i] << " ";
//    }
//    cout << "\n";
//
//    int index_X = buoc2_TimKiemNhiPhanXY_KhuDeQuy(b, x);
//    int index_Y = buoc2_TimKiemNhiPhanXY_KhuDeQuy(b, y);
//
//    // Phong truong hop cay co san X va Y
//    if (index_X - 1 >= 0 && index_X - 1 < b.size()) {
//        if (b[index_X - 1] == x) {
//            index_X--;
//        }
//    }
//    if (index_Y + 1 >= 0 && index_X + 1 < b.size()) {
//        if (b[index_Y + 1] == y) {
//            index_Y++;
//        }
//    }
//
//    int soLuongNodeTrongDoanXY = index_Y - index_X + 1 - 2;
//    cout << "\nSo luong Node trong doan x = " << x << ", y = " << y << " la: " << soLuongNodeTrongDoanXY << endl;
    
    system("pause");
    return 0;
}
