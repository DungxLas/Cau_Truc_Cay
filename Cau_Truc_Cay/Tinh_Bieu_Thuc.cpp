//
//  Tinh_Bieu_Thuc.cpp
//  Cau_Truc_Cay
//
//  Created by PHẠM HÙNG DŨNG on 30/06/2022.
//
#include <iostream>
#include <string>
#include <vector>
#include <stack>

#include "/Users/phamhungdung/CoDe/C:C++/Cau_Truc_Cay/Tinh_Bieu_Thuc.hpp"

using namespace std;

int main()
{
    string bieuThuc = "(2 ^ (3 + 4) - 4) / 5 + 2";
    vector<string> bieuThuc_hauTo = TrungToThanhHauTo(bieuThuc);
    
    cout << "Bieu thuc da cho: " << bieuThuc << endl;
    
    cout << "Bieu thuc hau to: ";
    Node *Root = ChuyenHauToThanhCay(bieuThuc_hauTo); //Cay bieu thuc
    
    TinhGiaTriBieuThuc(Root);
    cout << "\n Ket qua bieu thuc: " << Root->ketqua << endl;
    
    system("pause");
    return 0;
}
