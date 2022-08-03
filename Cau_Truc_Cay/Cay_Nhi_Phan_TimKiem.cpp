//
//  Cay_Nhi_Phan_TimKiem.cpp
//  Cau_Truc_Cay
//
//  Created by PHẠM HÙNG DŨNG on 20/07/2022.
//

#include <iostream>

#include "Cay_Nhi_Phan_TimKiem.hpp"

using namespace std;

int main() {
    int a[] = {40, 5, 35, 45, 15, 56, 48, 13, 16, 49, 47};
    int n = sizeof(a)/sizeof(a[0]);
    
    Node* Root;
    taoCayTuDaySo(Root, a, n);
    inOrder(Root);

    cout << "\n";
    
    int x = 5;
    timVaXoaNode_DeQuy(Root, x);
    inOrder(Root);
    
    system("pause");
    return 0;
}
