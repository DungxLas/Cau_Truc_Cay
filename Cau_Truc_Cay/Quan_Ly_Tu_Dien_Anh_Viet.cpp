//
//  Quan_Ly_Tu_Dien_Anh_Viet.cpp
//  Cau_Truc_Cay
//
//  Created by PHẠM HÙNG DŨNG on 25/08/2022.
//

#include "convertString.h"
#include "Quan_Ly_Tu_Dien_Anh_Viet.hpp"
#include <iostream>
using namespace std;

void Menu()
{
    NODE *Root;
    iNit(Root); // Phải nhớ khởi tạo cho cây để tránh bị lỗi
    
    DocFileTuDien(Root);
    
    int menu1;

menucha:

    do{
        printf("\n===============> Menu <===============\n");
        printf("\n1. Them tu moi vao tu dien");
        printf("\n2. Xoa mot tu trong tu dien");
        printf("\n3. Cap nhap tu dien");
        printf("\n4. Tra cuu tu trong tu dien");
        printf("\n5. Xuat cac tu trong tu dien theo thu tu tang dan");
        printf("\n0. Thoat chuong trinh");
        printf("\n======================================\n");

        printf("\nNhap vao lua chon (0 -> 5): ");
        scanf("%d", &menu1);

        if(menu1 < 0 || menu1 > 5)
        {
            printf("\nLua chon chi duoc trong khoang 0 -> 5. Nhan '.' de quay tro lai Menu chinh");
            fflush(stdin);
            char getch;
            cin >> getch;//getch()
        }
    }while(menu1 < 0 || menu1 > 5);

    if(menu1 == 0) // Thoat chuong trinh => phải giải phóng cây
    {
        GhiFileTuDien(Root);

        cout << "\nDu lieu tu dien da duoc ghi vao tap tin tudien.txt";

        preOrder(Root);
        
        GiaiPhongCay_KhuDeQuy(Root);

        if(Root == NULL)
            printf("\nCay duoc giai phong thanh cong truoc khi thoat chuong trinh");
        else
            printf("\nCay chua duoc giai phong truoc khi thoat chuong trinh vi ly do gi do");

        fflush(stdin);
        char getch;
        cin >> getch;//getch()
        exit(0); // tắt chương trình luôn
    }
    else if(menu1 == 1) // Them Node vao cay (du lieu nhap vao tu ban phim)
    {
        taoCayTuBanPhimKoBietTruocSoLuong(Root);
    }
    else if(menu1 == 2)
    {
        TU s;
        fflush(stdin);
        cout << "\nNhap vao tu Tieng Anh can xoa khoi cay tu dien: ";
        getline(cin, s.Eng);

        // Nhớ là phải có hàm này để chuẩn hóa tất cả thành chữ thường mới so sánh được
        strlwr(s.Eng);

        int kq = XoaNodeTrongCay_KhuDeQuy(Root, s);

        if(kq == 1)
            cout << "\nDa xoa thanh cong tu: " << s.Eng << " ra khoi cay";
        else if(kq == 0)
            cout << "\nKhong tim thay tu " << s.Eng << " trong cay nen khong xoa duoc!";
    }
    else if (menu1 == 3)
    {
        TU s;
        fflush(stdin);
        cout << "\nNhap vao tu Tieng Anh can cap nhat: ";
        getline(cin, s.Eng);

        // Nhớ là phải có hàm này để chuẩn hóa tất cả thành chữ thường mới so sánh được
        strlwr(s.Eng);

        NODE *p = timNode_KhuDeQuy(Root, s);

        if(p->Data == s) // tìm thấy
        {
            int luachon;
            do{
                cout << "\nBan muon cap nhat tu Tieng Viet hay muon cap nhat ca Tieng Anh lan Tieng Viet?";
                cout << "\n1. Cap nhat tu Tieng Viet";
                cout << "\n2. Cap nhat ca Tieng Anh lan Tieng Viet";

                cout << "\nNhap vao lua chon cua Ban: ";
                cin >> luachon;

                if(luachon < 1 || luachon > 2)
                    cout << "\nLua chon chi duoc la 1 hoac 2. Xin kiem tra lai!";

            }while(luachon < 1 || luachon > 2);

            if(luachon == 1)
            {
                fflush(stdin);
                cout << "\nNhap vao nghia Tieng Viet can cap nhat lai cho tu nay: ";
                getline(cin, s.Vie);

                strlwr(s.Vie);

                p->Data.Vie = s.Vie; // Cập nhật lại tiếng việt

                cout << "\nDa cap nhat thanh cong nghia Tieng Viet cua tu " << s.Eng;
            }
            else
            {
                cout << "\nNhu vay chuong trinh se xoa di tu hien tai va them moi lai tu moi cho Ban nhap vao";
                XoaNodeTrongCay_KhuDeQuy(Root, p->Data);

                TU x;
                nhapMotTu(x);
                int kq = ThemNode_KhuDeQuy(Root, x);

                if(kq == 1)
                    cout << "\nDa them thanh cong tu moi";
                else if(kq == 0)
                    cout << "\nKhong them duoc do tu can them da bi trung voi 1 tu dang co trong cay tu dien";
                else if(kq == -1)
                    cout << "\nKhong them duoc do khong du bo nho de cap phat";

            }

            
        }
        else // không tìm thấy
            cout << "\nKhong tim thay tu Tieng Anh: " << s.Eng << " trong cay nen khong cap nhat duoc!";
    }
    else if (menu1 == 4)
    {
        TU s;
        fflush(stdin);
        cout << "\nNhap vao tu Tieng Anh can tra cuu: ";
        getline(cin, s.Eng);

        // Nhớ là phải có hàm này để chuẩn hóa tất cả thành chữ thường mới so sánh được
        strlwr(s.Eng);

        NODE *p = timNode_KhuDeQuy(Root, s);

        if(p->Data == s) // tìm thấy
        {
            cout << "\n Tu Tieng Anh: " << s.Eng << " co nghia la: " << s.Vie;
            
        }
        else // không tìm thấy
            cout << "\nKhong tim thay tu Tieng Anh: " << s.Eng << " trong cay nen khong tra cuu duoc!";
    }
    else if(menu1 == 5)
    {
        inOrder(Root);
    }
    
    printf("\nNhan '.' de quay tro lai Menu chinh");
    fflush(stdin);
    char getch;
    cin >> getch;//getch()
    goto menucha;
}

int main(){
    Menu();
    
    return 0;
}
