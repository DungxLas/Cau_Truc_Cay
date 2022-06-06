//
//  main.cpp
//  Cau_Truc_Cay
//
//  Created by PHẠM HÙNG DŨNG on 05/06/2022.
//

#include <iostream>

#include "/Users/phamhungdung/CoDe/C:C++/Cau_Truc_Cay/Cay_Nhi_Phan_Linked.h"

using namespace std;

int main() {
    Node *A = GetNode('A');
    Node *B = GetNode('B');
    Node *C = GetNode('C');
    Node *D = GetNode('D');
    Node *E = GetNode('E');
    Node *F = GetNode('F');
    Node *G = GetNode('G');
    Node *H = GetNode('H');
    Node *I = GetNode('I');
    Node *J = GetNode('J');
    Node *K = GetNode('K');
    Node *L = GetNode('L');
    
    A->Left = B;
    A->Right = C;
    B->Left = D;
    B->Right = E;
    C->Left = F;
    C->Right = G;
    D->Left = H;
    D->Right = I;
//    E->Left
    E->Right = J;
    F->Left = K;
//    F->Right
//    G->Left
    G->Right = L;

    cout << A->Left->Left->Data << endl;
    
    return 0;
}
