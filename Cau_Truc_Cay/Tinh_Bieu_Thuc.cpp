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
    string bieuThuc = "90-(5*8/(4+6)-3/(2+1)*23)/100";
    vector<string> bieuThuc_hauTo = TrungToThanhHauTo(bieuThuc);
    
    cout << "Bieu thuc da cho: " << bieuThuc << endl;
    
    cout << "Bieu thuc hau to: ";
    for (int i = 0; i < bieuThuc_hauTo.size(); ++i) {
        cout << bieuThuc_hauTo[i] << " ";
    }
    
    system("pause");
    return 0;
}
