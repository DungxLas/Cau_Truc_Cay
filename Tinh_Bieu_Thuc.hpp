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

//Buoc1: Chuyen bieu thuc ve dang hau to
bool KiemTraToanTu(string s);
bool KiemTraSo(string s);

//Tach cac phan tu trong bieu thuc ban dau
vector<string> ChuanHoaBieuThuc(string bieuThuc)
{
    vector<string> bieuThuc_trungTo;

    string nhoTam1;
    string nhoTam2;
    int sizeBieuThuc = bieuThuc.length();
    for (int i = 0; i < sizeBieuThuc; ++i) {
        if (bieuThuc[i] == ' ') {
            while (bieuThuc[i] == ' ') {
                bieuThuc.erase(bieuThuc.begin() + i);
                --sizeBieuThuc;
            }
        }
        if (bieuThuc[i] < '1' || bieuThuc[i] > '9') {
            if (bieuThuc[i] == '/' || bieuThuc[i] == '*'|| bieuThuc[i] == '('|| bieuThuc[i] == ')') {
                nhoTam1.push_back(bieuThuc[i]);
                bieuThuc_trungTo.push_back(nhoTam1);
                nhoTam1.clear();
            }
            else if (bieuThuc[i] == '+' || bieuThuc[i] == '-') {
                if (i == 0 || bieuThuc[i - 1] == '(' || bieuThuc[i - 1] == '*' || bieuThuc[i - 1] == '/' || bieuThuc[i - 1] == '+' || bieuThuc[i - 1] == '-') {
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
        else if (bieuThuc[i] >= '1' && bieuThuc[i] <= '9') {
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

//Buoc2: Tu dang hau to chuyen thanh dang cay

/* Khai bao cau truc du lieu cay nhi phan */
struct Node {
    string Data;
    struct Node *Left, *Right; //tro trai, tro phai
    float ketqua;
};

/* Tao Node */
Node* GetNode(string x) {
    Node* p = new Node;
    if (p == NULL) {
        return NULL;
    }
    p->Data = x;
    p->Left = p->Right = NULL;
    
    return p;
}

/* Tao cay */
Node* ChuyenHauToThanhCay(vector<string> bieuThuc_hauto) {
    int size = bieuThuc_hauto.size();
    stack<Node *> nganXep;
    for (int i = 0; i < size; ++i) {
        cout << bieuThuc_hauto[i] << " ";
        
        Node *n = GetNode(bieuThuc_hauto[i]);
        if (KiemTraToanTu(bieuThuc_hauto[i]) == true) {
            Node *y = nganXep.top();
            nganXep.pop();
            
            Node *x = nganXep.top();
            nganXep.pop();
            
            n->Left = x;
            n->Right = y;
        }

        nganXep.push(n);
    }
    
    return nganXep.top();
}

//Buoc3: Tinh toan
void TinhGiaTriBieuThuc(Node *Root)    // Left-Right-Node
{
    if (Root != NULL) {
        TinhGiaTriBieuThuc(Root->Left);
        TinhGiaTriBieuThuc(Root->Right);
        
        if (KiemTraToanTu(Root->Data) == true) {
            float x = Root->Left->ketqua;
            float y = Root->Right->ketqua;
            
            char z = Root->Data[0];
            
            switch (z) {
                case '+':
                    Root->ketqua = y + x;
                    break;
                case '-':
                    Root->ketqua = x - y;
                    break;
                case '*':
                    Root->ketqua = y * x;
                    break;
                case '/':
                    Root->ketqua = x / y;
                    break;
                }
        }
        else {
            Root->ketqua = stof(Root->Data);
        }
    }
}

#endif /* Tinh_Bieu_Thuc_hpp */
