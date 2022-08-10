//
//  Cay_Nhi_Phan_TimKiem.cpp
//  Cau_Truc_Cay
//
//  Created by PHẠM HÙNG DŨNG on 20/07/2022.
//

#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>

#include "Cay_Nhi_Phan_TimKiem.hpp"

using namespace std;

void ClearScreen()
    {
    cout << string( 100, '\n' );
    }

//int main() {
//    int a[] = {40, 5, 35, 45, 15, 56, 48, 13, 16, 49, 47};
//    int n = sizeof(a)/sizeof(a[0]);
//
//    Node* Root;
//    taoCayTuDaySo(Root, a, n);
//    inOrder(Root);
//
//    cout << "\n";
//
//    int x = 5;
//    timVaXoaNode_DeQuy(Root, x);
//    inOrder(Root);
//
//    system("pause");
//    return 0;
//}

int main() {
    Node *Root;
    iNit(Root);
    
    int menu1;
    
menu01:
    
    do {
        cout << "================> Menu <================" << endl;
        cout << "1. Doc du lieu tu tap tin vao cay" << endl;
        cout << "2. Them Node vao cay (du lieu nhap tu ban phim)" << endl;
        cout << "3. Tim kiem Node" << endl;
        cout << "4. Xoa Node" << endl;
        cout << "5. Duyet cay" << endl;
        cout << "6. Giai phong cay" << endl;
        cout << "========================================" << endl;
        
        cout << "Nhap vao lua chon (1->6): ";
        cin >> menu1;
        if (menu1 < 1 || menu1 > 6) {
            cout << "Lua chon khong hop le. Xin nhap lai!" << endl;
            ClearScreen();
        }
    } while (menu1 < 1 || menu1 > 6);
    
    if (menu1 == 1) {
        string str;
        cout << "Hay nhap vao duong dan toi tap tin can doc: ";
        // Xóa khỏi bộ nhớ đệm 32767 ký tự, hoặc đến khi gặp ký tự '\n'
        cin.ignore(32767, '\n');
        getline(cin, str);
        
        fstream fileIn;
        fileIn.open(str, ios:: in);
        
        if (!fileIn.is_open()) {
            cout << "Mo file that bai, khong tim thay file co duong dan: " << str << endl;
            //cout << "Nhan Enter de quay lai menu chinh." << endl;
        }
        else {
            taoCayTuTapTin(Root, fileIn);
            
            if (Root != NULL) {
                cout << "Cay da duoc tao thanh cong!!!" << endl;
            }else {
                cout << "Cay khong duoc tao do tap tin khong co du lieu." << endl;
            }
            
            fileIn.close();
        }
        
        ClearScreen();
        goto menu01;
    }
    else if (menu1 == 2) {
        // taoCayNhapTuBanPhimKhongBietTruocSoLuong(Root);
        ClearScreen();
        goto menu01;
    }
    else if (menu1 == 3) {
        // TimKiem
        ClearScreen();
        goto menu01;
    }
    else if (menu1 == 4) {
        // Xoa Node
        ClearScreen();
        goto menu01;
    }
    else if (menu1 == 5) {
        // Duyet cay
        ClearScreen();
        goto menu01;
    }
    else if (menu1 == 6) {
        // Giai phong cay
        ClearScreen();
        goto menu01;
    }
    
    return 0;
}
