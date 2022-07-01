//
//  Tinh_Bieu_Thuc.hpp
//  Cau_Truc_Cay
//
//  Created by PHẠM HÙNG DŨNG on 30/06/2022.
//

#ifndef Tinh_Bieu_Thuc_hpp
#define Tinh_Bieu_Thuc_hpp

#include <iostream>
#include <string>
#include <vector>
#include <stack>

using namespace std;

vector<string> ChuanHoaBieuThuc(string bieuThuc)
{
    vector<string> bieuThuc_trungTo;
    
    string nhoTam;
    for (int i = 0; i < bieuThuc.length(); ++i) {
        if (bieuThuc[i] == ' ') {
            bieuThuc_trungTo.push_back(nhoTam);
            nhoTam.clear();
            continue;
        }
        nhoTam.push_back(bieuThuc[i]);
    }
    bieuThuc_trungTo.push_back(nhoTam);
    
    return bieuThuc_trungTo;
}

bool KiemTraToanTu(string s)
{
    if (s == "/" || s == "*" || s == "+" || s == "-") {
        return true;
    }
    return false;
}

int TinhDoUuTien(string s)
{
    if (s == "*" || s == "/") {
        return 2;
    }
    if (s == "+" || s == "-") {
        return 1;
    }
    return 0;
}

vector<string> TrungToThanhHauTo(string bieuThuc)
{
    vector<string> bieuThuc_trungTo = ChuanHoaBieuThuc(bieuThuc);
    vector<string> bieuThuc_hauTo;
    
    stack<string> nganXep;
    int sizeTrungTo = bieuThuc_trungTo.size();
    for (int i = 0; i < sizeTrungTo; ++i) {
        if (48 <= bieuThuc_trungTo[i][0] && bieuThuc_trungTo[i][0] <= 57)
        {
            bieuThuc_hauTo.push_back(bieuThuc_trungTo[i]);
        }
        else if (bieuThuc_trungTo[i] == "(") {
            nganXep.push(bieuThuc_trungTo[i]);
        }
        else if (KiemTraToanTu(bieuThuc_trungTo[i]) == true) {
            if (nganXep.empty()) {
                nganXep.push(bieuThuc_trungTo[i]);
            }
            else {
                while (!nganXep.empty()) {
                    if (TinhDoUuTien(bieuThuc_trungTo[i]) > TinhDoUuTien(nganXep.top())) {
                        nganXep.push(bieuThuc_trungTo[i]);
                        break;
                    }
                    else {
                        bieuThuc_hauTo.push_back(nganXep.top());
                        nganXep.pop();
                    }
                }
                if (nganXep.empty()) {
                    nganXep.push(bieuThuc_trungTo[i]);
                }
            }
        }
        else if (bieuThuc_trungTo[i] == ")") {
            while (!nganXep.empty()) {
                if (nganXep.top() == "(") {
                    nganXep.pop();
                    break;
                }
                bieuThuc_hauTo.push_back(nganXep.top());
                nganXep.pop();
            }
        }
    }
    
    while (!nganXep.empty()) {
        if (nganXep.top() != "(") {
            bieuThuc_hauTo.push_back(nganXep.top());
            nganXep.pop();
        }
        else {
            nganXep.pop();
        }
    }
    
    return bieuThuc_hauTo;
}

#endif /* Tinh_Bieu_Thuc_hpp */