//
//  convertString.h
//  Cau_Truc_Cay
//
//  Created by PHẠM HÙNG DŨNG on 25/08/2022.
//

#ifndef convertString_h
#define convertString_h

#include <iostream>
#include <string>

using namespace std;

string strlwr(string data) {
    for (int i = 0; i < data.length(); ++i) {
        if (data[i] >= 'A' && data[i] <= 'Z') {
            data[i] += 32;
        }
    }
    return data;
}

string strupr(string data) {
    for (int i = 0; i < data.length(); ++i) {
        if (data[i] >= 'a' && data[i] <= 'z') {
            data[i] -= 32;
        }
    }
    return data;
}

#endif /* convertString_h */
