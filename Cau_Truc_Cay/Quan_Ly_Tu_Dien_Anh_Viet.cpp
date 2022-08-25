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
    
    //DocFileTuDien(Root);
    
    int menu1;

menucha:

    do{
        printf("\n===============> Menu <===============\n");
        printf("\n1. Them tu moi vao tu dien");
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
//        GhiFileTuDien(Root);
//
//        cout << "\nDu lieu tu dien da duoc ghi vao tap tin tudien.txt";

        preOrder(Root);
        
//        GiaiPhongCay_KhuDeQuy(Root);
//
//        if(Root == NULL)
//            printf("\nCay duoc giai phong thanh cong truoc khi thoat chuong trinh");
//        else
//            printf("\nCay chua duoc giai phong truoc khi thoat chuong trinh vi ly do gi do");
//
//        fflush(stdin);
//        char getch;
//        cin >> getch;//getch()
//        exit(0); // tắt chương trình luôn
    }
    else if(menu1 == 1) // Them Node vao cay (du lieu nhap vao tu ban phim)
    {
        taoCayTuBanPhimKoBietTruocSoLuong(Root);
    }
    else if(menu1 == 2)
    {
//        Word s;
//        fflush(stdin);
//        cout << "\nNhap vao tu Tieng Anh can xoa khoi cay tu dien: ";
//        getline(cin, s.Eng);
//
//        // Nhớ là phải có hàm này để chuẩn hóa tất cả thành chữ thường mới so sánh được
//        strlwr(s.Eng);
//
//        int kq = XoaNodeTrongCay_KhuDeQuy(Root, s);
//
//        if(kq == 1)
//            cout << "\nDa xoa thanh cong tu: " << s.TiengAnh << " ra khoi cay";
//        else if(kq == 0)
//            cout << "\nKhong tim thay tu " << s.TiengAnh << " trong cay nen khong xoa duoc!";
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
