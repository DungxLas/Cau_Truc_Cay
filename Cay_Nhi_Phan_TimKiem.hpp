//
//  Cay_Nhi_Phan_TimKiem.hpp
//  Cau_Truc_Cay
//
//  Created by PHẠM HÙNG DŨNG on 20/07/2022.
//

#ifndef Cay_Nhi_Phan_TimKiem_hpp
#define Cay_Nhi_Phan_TimKiem_hpp

#include <iostream>
#include <string>
#include <fstream>
#include <queue>

using namespace std;

/* 1/ Khai bao cau truc du lieu cay nhi phan tim kiem */
struct Node
{
    int Data;
    Node *Cha, *Left, *Right;
    int ThuTuDuyet;
};

/* 2/ Khoi tao cay */
void iNit(Node *&Root)
{
    Root = NULL;
}

/* 3/ Tao Node */
Node* getNode(int x)
{
    Node* p = new Node;
    if (p == NULL) {
        return NULL;
    }
    p->Data = x;
    p->Left = p->Right = p->Cha = NULL;
    p->ThuTuDuyet = 0;
    return p;
}

/* 4/ Them Node */
void ThemNode_DeQuy(Node*& Root, int x, Node* k)
{
    if (Root != NULL) {
        if (x > Root->Data) {
            ThemNode_DeQuy(Root->Right, x, Root);
        }
        else if (x < Root->Data) {
            ThemNode_DeQuy(Root->Left, x, Root);
        }
    }
    else
    {
        Root = getNode(x);
        Root->Cha = k;
    }
}

void ThemNode_KhuDeQuy(Node*& Root, int x)
{
    if (Root == NULL) {
        Root = getNode(x);
    }
    else
    {
        Node* p;
        Node* q = Root;
        while (q != NULL) {
            p = q;
            if (x > q->Data) {
                q = q->Right;
            }
            else if (x < q->Data) {
                q = q->Left;
            }
            else {
                return;
            }
        }
        
        if (x > p->Data) {
            p->Right = getNode(x);
            p->Right->Cha = p;
        }
        else if (x < p->Data) {
            p->Left = getNode(x);
            p->Left->Cha = p;
        }
    }
}

void taoCayTuDaySo(Node*& Root, int a[], int n)
{
    for (int i = 0; i < n; ++i) {
        //ThemNode_DeQuy(Root, a[i], NULL);
        ThemNode_KhuDeQuy(Root, a[i]);
    }
}
void taoCayTuTapTin(Node*& Root, fstream &fileIn)
{
    
}

void preOrder(Node *Root)    // Node-Left-Right
{
    if (Root != NULL) {
        cout << Root->Data << " ";
        preOrder(Root->Left);
        preOrder(Root->Right);
    }
}

void inOrder(Node *Root)    // Left-Node-Right
{
    if (Root != NULL) {
        inOrder(Root->Left);
        cout << Root->Data << " ";
        inOrder(Root->Right);
    }
}

void postOrder(Node *Root)    // Left-Right-Node
{
    if (Root != NULL) {
        postOrder(Root->Left);
        postOrder(Root->Right);
        cout << Root->Data << " ";
    }
}

Node* timNode_DeQuy1(Node* Root, int x)
{
    if (Root != NULL) {
        if (x > Root->Data) {
            return timNode_DeQuy1(Root->Right, x);
        }
        else if (x < Root->Data) {
            return timNode_DeQuy1(Root->Left, x);
        }
        else {
            return Root;
        }
    }
    return NULL;
}

Node* timNode_DeQuy2(Node* Root, int x)
{
    if (Root == NULL) {
        return NULL;
    }

    if (Root->Data == x) {
        return Root;
    }

    Node* p;
    if (x > Root->Data) {
        p = timNode_DeQuy2(Root->Right, x);
    }
    else if (x < Root->Data) {
        p = timNode_DeQuy2(Root->Left, x);
    }
    return p;
}

void timNodeVaThemNode_DeQuy(Node*& Root, int x)
{
    if (Root != NULL) {
        if (x > Root->Data) {
            timNodeVaThemNode_DeQuy(Root->Right, x);
        }
        else if (x < Root->Data) {
            timNodeVaThemNode_DeQuy(Root->Left, x);
        }
        else {
            cout << "Node can tim co trong cay!" << endl;
            return;
        }
    }
    else
    {
        Root = getNode(x);
        cout << "Node can tim ko co trong cay. Da tu dong them vao cay!" << endl;
    }
}

Node* timNode_KhuDeQuy(Node* Root, int x)
{
    while (Root != NULL) {
        if (x > Root->Data) {
            Root = Root->Right;
        }
        else if (x < Root->Data) {
            Root = Root->Left;
        }
        else {
            return Root;
        }
    }
    return NULL;
}

Node* timNodeVaThemNode_KhuDeQuy(Node*& Root, int x)
{
    Node* p;
    Node* q = Root;
    if (q == NULL) {
        return Root = getNode(x);
    }
    else
    {
        while (q != NULL) {
            p = q;
            if (x > q->Data) {
                q = q->Right;
            }
            else if (x < q->Data) {
                q = q->Left;
            }
            else if (x == q->Data) {
                cout << "Node can tim co trong cay!" << endl;
                return q;
            }
        }
    }
    
    cout << "Node can tim ko co trong cay. Da tu dong them vao cay!" << endl;
    if (x > p->Data) {
        p->Right = getNode(x);
        p = p->Right;
    }
    else if (x < p->Data) {
        p->Left = getNode(x);
        p = p->Left;
    }
    return p;
}

/* 5/ Xoa Node */
void timPhanTuTheMang(Node*& Root, Node*& p)
{
    if (Root->Right != NULL) {
        timPhanTuTheMang(Root->Right, p);
    }
    else {
        p->Data = Root->Data;
        p = Root;
        Root = Root->Left;
    }
}

void timVaXoaNode_DeQuy(Node*& Root, int x)
{
    if (Root == NULL) {
        return;
    }
    
    if (Root->Data < x) {
        timVaXoaNode_DeQuy(Root->Right, x);
    }
    else if (Root->Data > x) {
        timVaXoaNode_DeQuy(Root->Left, x);
    }
    else {
        Node *p = Root;
        
        if (p->Left == NULL) {
            Root = p->Right;
        }
        else if (p->Right == NULL) {
            Root = p->Left;
        }
        else {
            timPhanTuTheMang(Root->Left, p);
        }
        
        delete p;
    }
}

/* 6/ Thao tac */
int DemSoNode_DeQuyThuong(Node *Root)
{
    // Dieu kien dung
    if (Root == NULL) {
        return 0;
    }
    // Buoc de quy
    return 1 + DemSoNode_DeQuyThuong(Root->Left) + DemSoNode_DeQuyThuong(Root->Right);
}

int DemSoNode_KhuDeQuy(Node *Root)
{
    queue<Node *> q;
    q.push(Root);
    
    int dem = 0;
    while (!q.empty()) {
        Node *p = q.front();
        dem++;
        q.pop();
        
        if (p->Left != NULL) {
            q.push(p->Left);
        }
        if (p->Right != NULL) {
            q.push(p->Right);
        }
    }
    
    return dem;
}

Node* timMinTrongCay_DeQuy(Node* Root)
{
    if (Root != NULL) {
        if (Root->Left != NULL) {
            return timMinTrongCay_DeQuy(Root->Left);
        }
        return Root;
    }
    return NULL;
}

Node* timMinTrongCay_KoDeQuy(Node* Root)
{
    while (Root != NULL) {
        if (Root->Left != NULL) {
            Root = Root->Left;
            continue;
        }
        break;
    }
    return Root;
}

Node* timMaxTrongCay_DeQuy(Node* Root)
{
    if (Root != NULL) {
        if (Root->Right != NULL) {
            return timMaxTrongCay_DeQuy(Root->Right);
        }
        return Root;
    }
    return NULL;
}

Node* timMaxTrongCay_KoDeQuy(Node* Root)
{
    while (Root != NULL) {
        if (Root->Right != NULL) {
            Root = Root->Right;
            continue;
        }
        break;
    }
    return Root;
}

int demNodeAmTrongCay_DeQuy(Node* Root)
{
    if (Root == NULL) {
        return 0;
    }
    else {
        if (Root->Data >= 0) {
            return demNodeAmTrongCay_DeQuy(Root->Left);
        }
        else {
            if (Root->Data == -1) {
                return 1 + DemSoNode_DeQuyThuong(Root->Left);
            }
            else {
                return 1 + DemSoNode_DeQuyThuong(Root->Left) + demNodeAmTrongCay_DeQuy(Root->Right);
            }
        }
    }
}

void demNodeAmTrongCay_DeQuy_CaiTien(Node *Root, int &count)
{
    if (Root != NULL) {
        demNodeAmTrongCay_DeQuy_CaiTien(Root->Left, count);
        if (Root->Data < 0) {
            ++count;
        }
        else {
            return;
        }
        demNodeAmTrongCay_DeQuy_CaiTien(Root->Right, count);
    }
}

int demNodeAmTrongCay_KoDeQuy(Node* Root)
{
    int dem = 0;
    
xetCayPhai:
    if (Root == NULL) {
        return dem;
    }
    else {
        if (Root->Data >= 0) {
            Root = Root->Left;
            goto xetCayPhai;
        }
        
        ++dem;
        if (Root->Left != NULL) {
            dem += DemSoNode_KhuDeQuy(Root->Left);
        }
        if (Root->Data != 1) {
            Root = Root->Right;
            goto xetCayPhai;
        }
        
        return dem;
    }
}

//Dem so Node trong khoang [x, y] //
void buoc1_TaoMangChuaCacNodeVaXY_KhuDeQuy(Node *Root, vector<int> &a, int x, int y)
{
    char *s = "LNR";
    bool xCheck = false;
    bool yCheck = false;
    
    if(Root != NULL)
    {
        Node *cha = Root->Cha;
        Root->Cha = NULL; // quy ước Root chính là gốc của cây đang xét (nó có thể là cây nhỏ cho nên phải cho điều kiện dừng là Root->Cha = NULL)
        
        while(true)
        {

            if(Root->ThuTuDuyet <= 2)
            {
                if(s[Root->ThuTuDuyet] == 'N' || s[Root->ThuTuDuyet] == 'n')
                {
                    if(Root->Data > x && xCheck == false)
                    {
                        a.push_back(x);
                        xCheck = true;
                    }

                    if(Root->Data > y && yCheck == false)
                    {
                        a.push_back(y);
                        yCheck = true;
                    }

                    a.push_back(Root->Data);
                    Root->ThuTuDuyet++;
                }
                else if(s[Root->ThuTuDuyet] == 'L' || s[Root->ThuTuDuyet] == 'l')
                {
                    Root->ThuTuDuyet++;

                    if(Root->Left != NULL)
                        Root = Root->Left;
                }
                else if(s[Root->ThuTuDuyet] == 'R' || s[Root->ThuTuDuyet] == 'r')
                {
                    Root->ThuTuDuyet++;

                    if(Root->Right != NULL)
                        Root = Root->Right;
                }
            }
            else // khi đi vào đây tức là 1 node đã đi hết thang thứ tự duyệt rồi, lúc này không đi tới được nữa mà phải lùi về cha của nó để xét theo hướng khác
            {
                Root->ThuTuDuyet = 0; // trước khi trở về cha thì sẽ reset lại thứ tự duyệt của node đó về 0 để có thể sau hàm này còn nhu cầu duyệt tiếp kiểu khác nữa

                if(Root->Cha == NULL)
                {
                    Root->Cha = cha; // trả lại cha ban đầu của Root;

                    if(xCheck == false)
                        a.push_back(x);

                    if(yCheck == false)
                        a.push_back(y);

                    break; // ĐIỀU KIỆN DỪNG => TỪ GỐC TRỎ VỀ CHA SẼ LÀ NULL => DỪNG LẠI
                }
                else
                    Root = Root->Cha;
            }
        }
    }
}

int buoc2_TimKiemNhiPhanXY_KhuDeQuy(vector<int> a, int phantutimkiem)
{
    int left = 0;
    int right = a.size() - 1;
    
    while (left <= right) {
        int mid = (left + right) / 2;
        
        if (phantutimkiem > a[mid]) {
            left = mid + 1;
        }
        else if (phantutimkiem < a[mid]) {
            right = mid - 1;
        }
        else {
            return mid;
        }
    }
    return -1;
}

int DemCacNodeCuaCayNamTrongDoanXY_KhuDeQuy(Node *Root, int x, int y)
{
    vector<int> arr;
    buoc1_TaoMangChuaCacNodeVaXY_KhuDeQuy(Root, arr, x, y);

    int index_X = buoc2_TimKiemNhiPhanXY_KhuDeQuy(arr, x);
    int index_Y = buoc2_TimKiemNhiPhanXY_KhuDeQuy(arr, y);

    // Để đề phòng trường hợp là cây có những Node có giá trị trùng với x, y nên phải lấy x đầu tiên và y cuối cùng để đảm bảo
    if(index_X - 1 >= 0 && index_X - 1 < arr.size()) // Xét điều kiện ràng buộc rồi mới xử lý để tránh truy xuất đến 1 vị trí index không hợp lệ của mảng
    {
        if(arr[index_X - 1] == x)
            index_X--;
    }
    
    if(index_Y + 1 >= 0 && index_Y + 1 < arr.size()) // Xét điều kiện ràng buộc rồi mới xử lý để tránh truy xuất đến 1 vị trí index không hợp lệ của mảng
    {
        if(arr[index_Y + 1] == y)
            index_Y++;
    }

    printf("\nDanh sach cac Node thoa dieu kien nam trong doan [%d, %d] la: ", x, y);
    // Không bắt đầu chạy từ index_x được vì chính index_x là giá trị x mình chủ động thêm vào
    // Không chạy đến index_Y được vì chính index_Y là giá trị y mình chủ động thêm vào => chạy đến index_Y - 1
    for(int i = index_X + 1; i < index_Y; ++i)
        printf("%d ", arr[i]);

    return index_Y - index_X + 1 - 2;
}

//Tinh tong cac Node trong khoang [x, y] //
int tongCacNodeCuaCayNamTrongDoanXY_KhuDeQuy(Node *Root, int x, int y)
{
    vector<int> arr;
    buoc1_TaoMangChuaCacNodeVaXY_KhuDeQuy(Root, arr, x, y);

    int index_X = buoc2_TimKiemNhiPhanXY_KhuDeQuy(arr, x);
    int index_Y = buoc2_TimKiemNhiPhanXY_KhuDeQuy(arr, y);

    // Để đề phòng trường hợp là cây có những Node có giá trị trùng với x, y nên phải lấy x đầu tiên và y cuối cùng để đảm bảo
    if(index_X - 1 >= 0 && index_X - 1 < arr.size()) // Xét điều kiện ràng buộc rồi mới xử lý để tránh truy xuất đến 1 vị trí index không hợp lệ của mảng
    {
        if(arr[index_X - 1] == x)
            index_X--;
    }
    
    if(index_Y + 1 >= 0 && index_Y + 1 < arr.size()) // Xét điều kiện ràng buộc rồi mới xử lý để tránh truy xuất đến 1 vị trí index không hợp lệ của mảng
    {
        if(arr[index_Y + 1] == y)
            index_Y++;
    }

    printf("\nDanh sach cac Node thoa dieu kien nam trong doan [%d, %d] la: ", x, y);
    // Không bắt đầu chạy từ index_x được vì chính index_x là giá trị x mình chủ động thêm vào
    // Không chạy đến index_Y được vì chính index_Y là giá trị y mình chủ động thêm vào => chạy đến index_Y - 1
    int tong = 0;
    for(int i = index_X + 1; i <= index_Y--; ++i)
        tong += arr[i];

    return tong;
}

void kiemTraCayNhiPhanTimKiem_DeQuy(Node *Root, int &temp, bool &KiemTra)
{
    if (Root != NULL && KiemTra == true) {
        kiemTraCayNhiPhanTimKiem_DeQuy(Root->Left, temp, KiemTra);
        
        if (Root->Data > temp) {
            temp = Root->Data;
        }
        else {
            KiemTra = false;
            return;
        }
        
        kiemTraCayNhiPhanTimKiem_DeQuy(Root->Right, temp, KiemTra);
    }
}

bool kiemTraCayNhiPhanTimKiem_KhuDeQuy(Node *Root)
{
    char *s = "LNR";
    int temp = INT_MIN;
    
    if(Root != NULL)
    {
        Node *cha = Root->Cha;
        Root->Cha = NULL; // quy ước Root chính là gốc của cây đang xét (nó có thể là cây nhỏ cho nên phải cho điều kiện dừng là Root->Cha = NULL)
        
        while(true)
        {

            if(Root->ThuTuDuyet <= 2)
            {
                if(s[Root->ThuTuDuyet] == 'N' || s[Root->ThuTuDuyet] == 'n')
                {
                    if(Root->Data > temp)
                    {
                        temp = Root->Data;
                    }
                    else
                    {
                        Root->ThuTuDuyet = 0; // trước khi trở về cha thì sẽ reset lại thứ tự duyệt của node đó về 0 để có thể sau hàm này còn nhu cầu duyệt tiếp kiểu khác nữa

                        while (Root->Cha != NULL) {
                            Root = Root->Cha;
                            Root->ThuTuDuyet = 0;
                        }
                        
                        Root->Cha = cha;
                        return false;
                    }
                    
                    Root->ThuTuDuyet++;
                }
                else if(s[Root->ThuTuDuyet] == 'L' || s[Root->ThuTuDuyet] == 'l')
                {
                    Root->ThuTuDuyet++;

                    if(Root->Left != NULL)
                        Root = Root->Left;
                }
                else if(s[Root->ThuTuDuyet] == 'R' || s[Root->ThuTuDuyet] == 'r')
                {
                    Root->ThuTuDuyet++;

                    if(Root->Right != NULL)
                        Root = Root->Right;
                }
            }
            else // khi đi vào đây tức là 1 node đã đi hết thang thứ tự duyệt rồi, lúc này không đi tới được nữa mà phải lùi về cha của nó để xét theo hướng khác
            {
                Root->ThuTuDuyet = 0; // trước khi trở về cha thì sẽ reset lại thứ tự duyệt của node đó về 0 để có thể sau hàm này còn nhu cầu duyệt tiếp kiểu khác nữa

                if(Root->Cha == NULL)
                {
                    Root->Cha = cha; // trả lại cha ban đầu của Root;
                    break; // ĐIỀU KIỆN DỪNG => TỪ GỐC TRỎ VỀ CHA SẼ LÀ NULL => DỪNG LẠI
                }
                else
                    Root = Root->Cha;
            }
        }
    }
    
    return true;
}

void kiemTraCayNhiPhanTimKiem(Node *Root)
{
    int temp = INT_MIN;
    bool kiemtra = true;
    
    //kiemTraCayNhiPhanTimKiem_DeQuy(Root, temp, kiemtra);
    kiemtra = kiemTraCayNhiPhanTimKiem_KhuDeQuy(Root);
    
    if (kiemtra == true) {
        cout << "\nDay la cay nhi phan tim kiem";
    }
    else {
        cout << "\nDay khong phai la cay nhi phan tim kiem";
    }
}

#endif /* Cay_Nhi_Phan_TimKiem_hpp */
