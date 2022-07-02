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

bool KiemTraToanTu(string s);
bool KiemTraSo(string s);

//Tach cac phan tu trong bieu thuc ban dau
vector<string> ChuanHoaBieuThuc(string bieuThuc)
{
    vector<string> bieuThuc_trungTo;

    string nhoTam1;
    string nhoTam2;
    for (int i = 0; i < bieuThuc.length(); ++i) {
        if (bieuThuc[i] == ' ') {
            continue;
        }
        else if (bieuThuc[i] < 48 || bieuThuc[i] > 57) {
            if (bieuThuc[i] == '/' || bieuThuc[i] == '*'|| bieuThuc[i] == '('|| bieuThuc[i] == ')') {
                nhoTam1.push_back(bieuThuc[i]);
                bieuThuc_trungTo.push_back(nhoTam1);
                nhoTam1.clear();
            }
            else if (bieuThuc[i] == '+' || bieuThuc[i] == '-') {
                if (i == 0 || bieuThuc[i - 1] == '(' || bieuThuc[i - 1] == '*' || bieuThuc[i - 1] == '/' || bieuThuc[i - 1] == '+' || bieuThuc[i - 1] == '-' || bieuThuc[i - 1] == ' ') {
                    nhoTam2.push_back(bieuThuc[i]);
                }
                else if (bieuThuc[i - 1] == ')' || (bieuThuc[i - 1] >= 48 && bieuThuc[i - 1] <= 57)) {
                    nhoTam1.push_back(bieuThuc[i]);
                    bieuThuc_trungTo.push_back(nhoTam1);
                    nhoTam1.clear();
                }
            }
            else if (bieuThuc[i] == '.') {
                nhoTam2.push_back(bieuThuc[i]);
            }
        }
        else if (bieuThuc[i] >= 48 && bieuThuc[i] <= 57) {
            nhoTam2.push_back(bieuThuc[i]);
            if ((bieuThuc[i + 1] < 48 || bieuThuc[i + 1] > 57) && bieuThuc[i + 1] != '.') {
                bieuThuc_trungTo.push_back(nhoTam2);
                nhoTam2.clear();
            }
        }
    }

    return bieuThuc_trungTo;
}

bool KiemTraSo(string s)
{
    return 48 <= s[s.length() - 1] && s[s.length() - 1] <= 57;
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
        if (KiemTraSo(bieuThuc_trungTo[i]) == true)
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
