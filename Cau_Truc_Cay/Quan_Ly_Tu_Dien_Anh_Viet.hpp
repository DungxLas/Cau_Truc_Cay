//
//  Quan_Ly_Tu_Dien_Anh_Viet.hpp
//  Cau_Truc_Cay
//
//  Created by PHẠM HÙNG DŨNG on 25/08/2022.
//

#ifndef Quan_Ly_Tu_Dien_Anh_Viet_hpp
#define Quan_Ly_Tu_Dien_Anh_Viet_hpp

#include <iostream>
#include <string>
#include <fstream>
#include <queue>
#include <cstdlib>


#include "convertString.h"

using namespace std;

/* 1/ Khai bao cau truc du lieu cay nhi phan tim kiem */
struct TU
{
    string Vie, Eng;
};

struct NODE
{
    TU Data;
    NODE *Cha, *Left, *Right;
    int ThuTuDuyet;
};

    //Xay dung phep toan operator
bool operator >(TU A, TU B)
{
    return A.Eng > B.Eng;
}
bool operator >=(TU A, TU B)
{
    return A.Eng >= B.Eng;
}
bool operator <(TU A, TU B)
{
    return A.Eng < B.Eng;
}
bool operator <=(TU A, TU B)
{
    return A.Eng <= B.Eng;
}
bool operator ==(TU A, TU B)
{
    return A.Eng == B.Eng;
}
bool operator !=(TU A, TU B)
{
    return A.Eng != B.Eng;
}

/* 2/ Khoi tao cay */
void iNit(NODE *&Root)
{
    Root = NULL;
}

/* 3/ Tao Node */
NODE* getNode(TU x)
{
    NODE* p = new NODE;
    if (p == NULL) {
        return NULL;
    }
    p->Data = x;
    p->Left = p->Right = p->Cha = NULL;
    p->ThuTuDuyet = 0;
    return p;
}

/* 4/ Them Node */
NODE* timNode_KhuDeQuy(NODE* Root, TU x)
{
    NODE* p = Root;
    NODE* q = p;
    while (p != NULL) {
        q = p;
        
        if (x > p->Data) {
            p = p->Right;
        }
        else if (x < p->Data) {
            p = p->Left;
        }
        else {
            return p;
        }
    }
    return q; //Tra ve node cuoi cung truoc khi den NULL
}

int ThemNode_KhuDeQuy(NODE*& Root, TU x)
{
    if (Root == NULL) {
        Root = getNode(x);
    }
    else
    {
        NODE* p = timNode_KhuDeQuy(Root, x);
        
        if (p->Data != x) {
            NODE* conMoi = getNode(x);
            
            if (conMoi == NULL) {
                return -1;
            }
            if (x > p->Data) {
                p->Right = conMoi;
            }
            else if (x < p->Data) {
                p->Left = conMoi;
            }
            conMoi->Cha = p;
        }
        else {
            return 0;
        }
    }
    return 1;
}

/* 5/ Giai phong cay*/
void GiaiPhongCay_KhuDeQuy(NODE *&Root)
{
    char s[] = "NLR";

    if(Root != NULL)
    {
        NODE *cha = Root->Cha;
        Root->Cha = NULL; // quy ước Root chính là gốc của cây đang xét (nó có thể là cây nhỏ cho nên phải cho điều kiện dừng là Root->Cha = NULL)
        while(true)
        {
            if(Root->ThuTuDuyet <= 2)
            {
                if(s[Root->ThuTuDuyet] == 'N' || s[Root->ThuTuDuyet] == 'n')
                {

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

                    delete Root;
                    Root = NULL;
                    break; // ĐIỀU KIỆN DỪNG => TỪ GỐC TRỎ VỀ CHA SẼ LÀ NULL => DỪNG LẠI
                }
                else
                {
                    NODE *q = Root;
                    Root = Root->Cha;
                    delete q;
                    q = NULL;
                }
            }
        }
    }
}


/* 6/ Thao tac voi tu dien*/

void nhapMotTu(TU &a){
    fflush(stdin);
    cout << "\nNhap vao tu tieng anh: ";
    getline(cin, a.Eng);
    a.Eng = strlwr(a.Eng);
    
    fflush(stdin);
    cout << "\nNhap nghia tieng viet tuong ung: ";
    getline(cin, a.Vie);
    a.Vie = strlwr(a.Vie);
}

void taoCayTuBanPhimKoBietTruocSoLuong(NODE *&Root){
    TU x;
    char select;
    do {
        nhapMotTu(x);
        
        int ketqua = ThemNode_KhuDeQuy(Root, x);
        if (ketqua == 0) {
            cout << "\nLoi: Gia tri Node nay da ton tai trong cay roi cho nen khong them vao cay duoc nua!!!";
        }
        else if (ketqua == -1) {
            cout << "\nLoi: Khong du bo nho de cap nhap cho Node!!!";
        }
        else if (ketqua == 1) {
            cout << "\nThem thanh cong vao tu dien.";
        }
        
        cout << "\nBan co muon nhap nua ko? nha phim c de nhap tiep / nhan phim bat ki de ket thuc: ";
        cin >> select;
    } while (select == 'c' || select == 'C');
}

void preOrder(NODE *Root)    // Node-Left-Right
{
    if (Root != NULL) {
        cout << Root->Data.Eng << ": " << Root->Data.Vie << endl;
        preOrder(Root->Left);
        preOrder(Root->Right);
    }
}

void inOrder(NODE *Root)    // Left-Node-Right
{
    if (Root != NULL) {
        inOrder(Root->Left);
        cout << Root->Data.Eng << ": " << Root->Data.Vie << endl;
        inOrder(Root->Right);
    }
}

// p là Node phải nhất của cây con trái (lớn nhất của cây con trái) thế mạng sẽ xóa
// Root la cay con trai cua Node can xoa
void TimPhanTuTheMang_KhuDeQuy(NODE *&Root, NODE *&p)
{
    // q là Node thế mạng cần xóa
    NODE *q = Root;
    NODE *k = p; // k là Node đứng trước Node q để khi cần có thể truy xuất về cha của nó. Khởi đầu thì k = p (Node cần xóa)
    
    while(q->Right != NULL)
    {
        k = q; // k là node đứng trước node q nên trước khi q trỏ đi đâu khác thì k cập nhật lại là q
        q = q->Right;
    }

    // Sau vòng lặp thì q là Node phải nhất (Tức là nếu trỏ phải lần nữa thì sẽ là NULL => q là phải nhất)

    // Phải để đoạn lệnh này trước 2 đoạn lệnh sau để cập nhật liên kết cho xong rồi từ đó mới muốn cho trỏ đi đâu thì trỏ. Nếu không sẽ bị lỗi nếu để 2 đoạn lệnh dưới lên trên đoạn lệnh này
    if(q->Data > k->Data)
        k->Right = q->Left;
//    else if(q->Data < k->Data)
//        k->Left = q->Left;

    if(q->Left != NULL)
        q->Left->Cha = k;

    p->Data = q->Data; // Gán giá trị của Node thế mạng (Root) sang giá trị của Node cần xóa (p)
    p = q; // Cho con trỏ p trỏ tới Node thế mạng (q) để kết thúc hàm thì sẽ free(p) chính là free(q)
}


// return 1: Xóa thành công
// return 0: Không xóa thành công (Node cần xóa không tồn tại trong cây)
int XoaNodeTrongCay_KhuDeQuy(NODE *&Root, TU x) // x là giá trị cần xóa ra khỏi cây
{
    NODE *q = Root;
    NODE *k = NULL; // k là Node đứng trước Node q để khi cần có thể truy xuất về cha của nó
    while(q != NULL)
    {
        if(x > q->Data)
        {
            k = q; // k là node đứng trước node q nên trước khi q trỏ đi đâu khác thì k cập nhật lại là q
            q = q->Right;
        }
        else if(x < q->Data)
        {
            k = q; // k là node đứng trước node q nên trước khi q trỏ đi đâu khác thì k cập nhật lại là q
            q = q->Left;
        }
        else // tìm thấy x trong cây tại Node q => tiến hành xóa
        {
            NODE *p = q; // p là Node sẽ bị xóa: Lý do dùng Node tạm p để xóa mà không xóa trực tiếp q bởi vì lỡ trong cùng 1 hàm sau khi xóa xong lại có nhu cầu duyệt cây tiếp thì lại duyệt dựa theo Node q nếu mà q bị xóa thì đâu còn duyệt được nữa

            // TH1: Node cần xóa là Node lá
            // TH2: Node cần xóa là Node có 1 con

            // Giữ liên kết với phần còn lại của Node bị xóa
            if(p->Left == NULL)
            {
                // k là Node cha của Node q cần xóa => k sẽ trỏ liên kết để giữ cháu của nó (giữ con của node cần xóa)
                // Làm sao biết k phải trỏ Left hay Right đến cháu của nó? => tùy thuộc q cần xóa đang là con trái hay con phải của k
                if(k != NULL) // k có tồn tại
                {
                    if(p->Data > k->Data)
                        k->Right = p->Right;
                    else if(p->Data < k->Data)
                        k->Left = p->Right;

                    if(p->Right != NULL)
                        p->Right->Cha = k;
                }
                else // Nếu ngay từ đầu k rỗng (tức là Node p cần xóa chính là Node gốc của cây
                {
                    Root = Root->Right; // Cập nhật trực tiếp Node gốc của cây sẽ trỏ sang con của nó
                    
                    if(Root != NULL)
                        Root->Cha = NULL;
                }
            }
            else if(p->Right == NULL)
            {
                if(k != NULL) // k có tồn tại
                {
                    // k là Node cha của Node q cần xóa => k sẽ trỏ liên kết để giữ cháu của nó (giữ con của node cần xóa)
                    // Làm sao biết k phải trỏ Left hay Right đến cháu của nó? => tùy thuộc q cần xóa đang là con trái hay con phải của k
                    if(p->Data > k->Data)
                        k->Right = p->Left;
                    else if(p->Data < k->Data)
                        k->Left = p->Left;

                    if(p->Left != NULL)
                        p->Left->Cha = k;
                }
                else // Nếu ngay từ đầu k rỗng (tức là Node p cần xóa chính là Node gốc của cây
                {
                    Root = Root->Left; // Cập nhật trực tiếp Node gốc của cây sẽ trỏ sang con của nó
                    
                    if(Root != NULL)
                        Root->Cha = NULL;
                }
            }
            else // p->Left != NULL && p->Right != NULL => TH3: Node cần xóa là Node có đủ 2 con
            {
                TimPhanTuTheMang_KhuDeQuy(q->Left, p); // Tìm phần tử thế mạng: Phải nhất của cây con trái
            }
            delete p; // giải phóng p
            return 1; // Xóa thành công - kết thúc hàm
        }
    }
    return 0; // Không xóa thành công (Node cần xóa không tồn tại trong cây)
}

void DocFileTuDien(NODE *&Root)
{
    ifstream FileIn;
    FileIn.open("tudien.txt", ios_base::in);

    if(!FileIn)
    {
        cout << "\nKhong tim thay tap tin tudien.txt nen cay ban dau se khoi tao rong (khong co du lieu san trong cay)";
        FileIn.close();
        return;
    }

    // Nếu vẫn chạy được xuống dưới đây tức là có tồn tại tập tin => đọc dữ liệu vào cây
    cout << "\nDu lieu tu dien trong tap tin tudien.txt da duoc doc vao cay thanh cong";

    while(!FileIn.eof())
    {
        TU x;
        getline(FileIn, x.Eng, ':');
        getline(FileIn, x.Vie);

        if(x.Eng != "")
        {
            ThemNode_KhuDeQuy(Root, x);
        }
        
    }

    FileIn.close();
}

void GhiFileTuDien(NODE *Root)
{
    ofstream FileOut;
    FileOut.open("tudien.txt", ios_base::out);
    
    if(Root != NULL)
    {
        char *s = "NLR";
        NODE *cha = Root->Cha;
        Root->Cha = NULL; // quy ước Root chính là gốc của cây đang xét (nó có thể là cây nhỏ cho nên phải cho điều kiện dừng là Root->Cha = NULL)
        
        while(true)
        {
            if(Root->ThuTuDuyet <= 2)
            {
                if(s[Root->ThuTuDuyet] == 'N' || s[Root->ThuTuDuyet] == 'n')
                {
                    FileOut << Root->Data.Eng << ":" << Root->Data.Vie << endl;

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
    
    FileOut.close();
}

#endif /* Quan_Ly_Tu_Dien_Anh_Viet_hpp */
