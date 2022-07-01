//
//  Doc_Gia.cpp
//  Cau_Truc_Cay
//
//  Created by PHẠM HÙNG DŨNG on 27/06/2022.
//

#include <iostream>
#include <string>
#include <vector>

#include "/Users/phamhungdung/CoDe/C:C++/Cau_Truc_Cay/Doc_Gia.h"

using namespace std;

int main() {
    DocGia dg_1;
    strcpy(dg_1.MaDocGia, "1");
    strcpy(dg_1.TenDocGia, "Nguyen Van A");
    dg_1.NgaySinh.Day = 18;
    dg_1.NgaySinh.Month = 12;
    dg_1.NgaySinh.Year = 1953;
    strcpy(dg_1.DiaChi, "Go Vap");
    dg_1.NgayLapThe.Day = 25;
    dg_1.NgayLapThe.Month = 12;
    dg_1.NgayLapThe.Year = 2000;
    
    DocGia dg_2;
    strcpy(dg_2.MaDocGia, "2");
    strcpy(dg_2.TenDocGia, "Nguyen Van B");
    dg_2.NgaySinh.Day = 7;
    dg_2.NgaySinh.Month = 7;
    dg_2.NgaySinh.Year = 1954;
    strcpy(dg_2.DiaChi, "Tan Phu");
    dg_2.NgayLapThe.Day = 27;
    dg_2.NgayLapThe.Month = 8;
    dg_2.NgayLapThe.Year = 1999;
    
    DocGia dg_3;
    strcpy(dg_3.MaDocGia, "3");
    strcpy(dg_3.TenDocGia, "Ly Thi C");
    dg_3.NgaySinh.Day = 31;
    dg_3.NgaySinh.Month = 10;
    dg_3.NgaySinh.Year = 1994;
    strcpy(dg_3.DiaChi, "Binh Thach");
    dg_3.NgayLapThe.Day = 27;
    dg_3.NgayLapThe.Month = 2;
    dg_3.NgayLapThe.Year = 2009;
    
    DocGia dg_4;
    strcpy(dg_4.MaDocGia, "4");
    strcpy(dg_4.TenDocGia, "Teo Van D");
    dg_4.NgaySinh.Day = 6;
    dg_4.NgaySinh.Month = 3;
    dg_4.NgaySinh.Year = 1996;
    strcpy(dg_4.DiaChi, "Kien Giang");
    dg_4.NgayLapThe.Day = 31;
    dg_4.NgayLapThe.Month = 3;
    dg_4.NgayLapThe.Year = 2012;
    
    DocGia dg_5;
    strcpy(dg_5.MaDocGia, "5");
    strcpy(dg_5.TenDocGia, "Khoai Thi E");
    dg_5.NgaySinh.Day = 2;
    dg_5.NgaySinh.Month = 10;
    dg_5.NgaySinh.Year = 1990;
    strcpy(dg_5.DiaChi, "Ho Chi Minh");
    dg_5.NgayLapThe.Day = 30;
    dg_5.NgayLapThe.Month = 4;
    dg_5.NgayLapThe.Year = 2009;
    
    Node *dg1 = GetNode(dg_1);
    Node *dg2 = GetNode(dg_2);
    Node *dg3 = GetNode(dg_2);
    Node *dg4 = GetNode(dg_4);
    Node *dg5 = GetNode(dg_5);
    
    dg1->Left = dg2;
    dg1->Right = dg3;
    dg2->Left = dg4;
    dg3->Right = dg5;
    
    return 0;
}

