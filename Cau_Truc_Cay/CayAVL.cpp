//
//  CayAVL.cpp
//  Cau_Truc_Cay
//
//  Created by PHẠM HÙNG DŨNG on 30/08/2022.
//

#include <iostream>

using namespace std;

struct Node
{
    char data;
    struct Node *Left, *Right, *Cha;
    int thuTuDuyet;
};

void iNit(Node *&Root)
{
    Root = NULL;
}


Node* getNode(char x)
{
    Node *p = new Node;
    
    if (p == NULL) {
        return NULL;
    }
    
    p->data = x;
    p->Left = p->Right = p->Cha = NULL;
    p->thuTuDuyet = 0;
    
    return p;
}

int tinhChieuCaoCay_DeQuy(Node *Root)
{
    if (Root != NULL) {
        int left = tinhChieuCaoCay_DeQuy(Root->Left);
        int right = tinhChieuCaoCay_DeQuy(Root->Right);
        return left > right ? left + 1 : right + 1;
    }
    return 0;
}

// Tính tầng mà node đó đang đứng
int TinhDoSauCuaNodeBatKy_KhongDeQuyKhongStack(Node *X)
{
    int dem = 0;

    while(true)
    {
        X = X->Cha;

        if(X == NULL)
            break;

        dem++;
    }
    return dem + 1;
}

int TinhChieuCaoCuaCay_KhongDeQuyKhongStack(Node *Root)
{
    char s[] = "NLR"; // quy ước thao tác duyệt

    int DoSauMax = 1;

    if(Root != NULL)
    {
        Node *cha = Root->Cha;
        Root->Cha = NULL; // quy ước Root chính là gốc của cây đang xét (nó có thể là cây nhỏ cho nên phải cho điều kiện dừng là Root->Cha = NULL)

        while(true)
        {
            if(Root->thuTuDuyet <= 2)
            {
                if(s[Root->thuTuDuyet] == 'N' || s[Root->thuTuDuyet] == 'n')
                {
                    int DoSauNode = TinhDoSauCuaNodeBatKy_KhongDeQuyKhongStack(Root);
                    if(DoSauNode > DoSauMax)
                        DoSauMax = DoSauNode;

                    Root->thuTuDuyet++;
                }
                else if(s[Root->thuTuDuyet] == 'L' || s[Root->thuTuDuyet] == 'l')
                {
                    Root->thuTuDuyet++;

                    if(Root->Left != NULL)
                    {
                        Root = Root->Left;
                    }
                }
                else if(s[Root->thuTuDuyet] == 'R' || s[Root->thuTuDuyet] == 'r')
                {
                    Root->thuTuDuyet++;

                    if(Root->Right != NULL)
                    {
                        Root = Root->Right;
                    }
                }
            }
            else // khi đi vào đây tức là 1 node đã đi hết thang thứ tự duyệt rồi, lúc này không đi tới được nữa mà phải lùi về cha của nó để xét theo hướng khác
            {
                Root->thuTuDuyet = 0; // trước khi trở về cha thì sẽ reset lại thứ tự duyệt của node đó về 0 để có thể sau hàm này còn nhu cầu duyệt tiếp kiểu khác nữa

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

    return DoSauMax; // CHIỀU CAO Cây
}

void quayTrai(Node *&Root)
{
    Node *Pivot = Root->Right;
    Node *cha = Root->Cha;
    
    Root->Right = Pivot->Left;
    if (Pivot->Left != NULL) {
        Pivot->Left->Cha = Root;
    }
    
    Pivot->Left = Root;
    Root->Cha = Pivot;
    
    Pivot->Cha = cha;
    Root = Pivot;
}

void quayPhai(Node *&Root)
{
    Node *Pivot = Root->Left;
    Node *cha = Root->Cha;
    
    Root->Left = Pivot->Right;
    if (Pivot->Right != NULL) {
        Pivot->Right->Cha = Root;
    }
    
    Pivot->Right = Root;
    Root->Cha = Pivot;
    
    Pivot->Cha = cha;
    Root = Pivot;
}

Node* timKiemNode_KhuDeQuy(Node *Root, char x)
{
    Node *p = Root;
    Node *q = p; // q là Node cuối cùng trước khi đến NULL => mục đích: Để có thể từ đó tạo liên kết thêm node mới vào
    while(p != NULL)
    {
        q = p;

        if(x > p->data)
            p = p->Right;
        else if(x < p->data)
            p = p->Left;
        else // x == p->Data // Điều kiện dừng đã tìm thấy
        {
            return p;
        }
    }

    // Chạy xuống đây tức là Root đã = NULL => không tìm thấy
    return q; // Trả về Node cuối cùng trước khi đến NULL
}

// Trả về 1: Nếu tại Node có bị mất cân bằng và tiến hành cân bằng lại
// Trả về 0: Nếu tại Node không có mất cân bằng
int XetTinhCanBangVaCanBangLaiTai1Node_KhuDeQuy(Node *&Root, Node *&NodeDangXet)
{
    int chieucaocontrai = 0;
    int chieucaoconphai = 0;

    if(NodeDangXet->Left != NULL)
        //chieucaocontrai = TinhChieuCaoCay_DeQuy(ConMoi->Left);
            chieucaocontrai = TinhChieuCaoCuaCay_KhongDeQuyKhongStack(NodeDangXet->Left);

    if(NodeDangXet->Right != NULL)
        //chieucaoconphai = TinhChieuCaoCay_DeQuy(ConMoi->Right);
            chieucaoconphai = TinhChieuCaoCuaCay_KhongDeQuyKhongStack(NodeDangXet->Right);

    if(abs(chieucaocontrai - chieucaoconphai) > 1) // mất cân bằng
    {
        //printf("\n=> Cay bi mat can bang tai Node %c", NodeDangXet->Data);

        Node *ChaCuaNodeBiMatCanBang = NULL;

        if(NodeDangXet->Cha != NULL)
            ChaCuaNodeBiMatCanBang = NodeDangXet->Cha;

        if(chieucaocontrai > chieucaoconphai) // Lệch trái
        {
            int chieucaocontrai_2 = 0;
            int chieucaoconphai_2 = 0;

            if(NodeDangXet->Left->Left != NULL)
                //chieucaocontrai_2 = TinhChieuCaoCay_DeQuy(ConMoi->Left->Left);
                    chieucaocontrai_2 = TinhChieuCaoCuaCay_KhongDeQuyKhongStack(NodeDangXet->Left->Left);

            if(NodeDangXet->Left->Right != NULL)
                //chieucaoconphai_2 = TinhChieuCaoCay_DeQuy(ConMoi->Left->Right);
                    chieucaoconphai_2 = TinhChieuCaoCuaCay_KhongDeQuyKhongStack(NodeDangXet->Left->Right);

            if(chieucaocontrai_2 >= chieucaoconphai_2) // Trái - Trái
            {
                //printf("\nMat can bang Trai - Trai");
                //printf("\n=> Quay phai tai Node %c voi Root = %c & Pivot = %c", NodeDangXet->Data, NodeDangXet->Data, NodeDangXet->Left->Data);
                quayPhai(NodeDangXet);

                // Sau khi quay xong kiểm tra nếu mới quay tại Node gốc của cây thì cập nhật lại Root là node đó
                if(NodeDangXet->Cha == NULL)
                    Root = NodeDangXet;
            }
            else // Trái - Phải
            {
                //printf("\nMat can bang Trai - Phai");
                //printf("\nBuoc 1: Quay trai tai Node %c voi Root = %c & Pivot = %c", NodeDangXet->Left->Data, NodeDangXet->Left->Data, NodeDangXet->Left->Right->Data);
                quayTrai(NodeDangXet->Left);

                //printf("\nBuoc 2: Quay phai tai Node %c voi Root = %c & Pivot = %c", NodeDangXet->Data, NodeDangXet->Data, NodeDangXet->Left->Data);
                quayPhai(NodeDangXet);

                // Sau khi quay xong kiểm tra nếu mới quay tại Node gốc của cây thì cập nhật lại Root là node đó
                if(NodeDangXet->Cha == NULL)
                    Root = NodeDangXet;
            }
        }
        else // Lệch phải
        {
            int chieucaocontrai_2 = 0;
            int chieucaoconphai_2 = 0;

            if(NodeDangXet->Right->Left != NULL)
                //chieucaocontrai_2 = TinhChieuCaoCay_DeQuy(ConMoi->Right->Left);
                    chieucaocontrai_2 = TinhChieuCaoCuaCay_KhongDeQuyKhongStack(NodeDangXet->Right->Left);

            if(NodeDangXet->Right->Right != NULL)
                //chieucaoconphai_2 = TinhChieuCaoCay_DeQuy(ConMoi->Right->Right);
                    chieucaoconphai_2 = TinhChieuCaoCuaCay_KhongDeQuyKhongStack(NodeDangXet->Right->Right);

            if(chieucaoconphai_2 >= chieucaocontrai_2) // Phải - Phải
            {
                //printf("\nMat can bang Phai - Phai");
                //printf("\n=> Quay trai tai Node %c voi Root = %c & Pivot = %c", NodeDangXet->Data, NodeDangXet->Data, NodeDangXet->Right->Data);
                quayTrai(NodeDangXet);

                // Sau khi quay xong kiểm tra nếu mới quay tại Node gốc của cây thì cập nhật lại Root là node đó
                if(NodeDangXet->Cha == NULL)
                    Root = NodeDangXet;
            }
            else // Phải - Trái
            {
                //printf("\nMat can bang Phai - Trai");
                //printf("\nBuoc 1: Quay phai tai Node %c voi Root = %c & Pivot = %c", NodeDangXet->Right->Data, NodeDangXet->Right->Data, NodeDangXet->Right->Left->Data);
                quayPhai(NodeDangXet->Right);

                //printf("\nBuoc 2: Quay trai tai Node %c voi Root = %c & Pivot = %c", NodeDangXet->Data, NodeDangXet->Data, NodeDangXet->Right->Data);
                quayTrai(NodeDangXet);

                // Sau khi quay xong kiểm tra nếu mới quay tại Node gốc của cây thì cập nhật lại Root là node đó
                if(NodeDangXet->Cha == NULL)
                    Root = NodeDangXet;
            }
        }

        if(ChaCuaNodeBiMatCanBang != NULL)
        {
            if(NodeDangXet->data > ChaCuaNodeBiMatCanBang->data)
                ChaCuaNodeBiMatCanBang->Right = NodeDangXet;
            else if(NodeDangXet->data < ChaCuaNodeBiMatCanBang->data)
                ChaCuaNodeBiMatCanBang->Left = NodeDangXet;
        }

        return 1;
    }
    return 0;
}


// return 1: Thành công
// return 0: Không thành công (bị trùng)
// return -1: Không thành công (không đủ bộ nhớ để cấp phát cho Node)
int ThemNodeVaoCay_KhuDeQuy(Node *&Root, char x) // thêm giá trị x vào cây
{
    // Từ ban đầu cây chưa có gì => tạo node gốc cho cây
    if(Root == NULL)
    {
        Root = getNode(x);
    }
    else // cây đã có node gốc rồi thì tiến hành thêm lần lượt các node tiếp theo vào và so sánh để tìm vị trí thích hợp để thêm
    {
        // p là Node đứng trước Node NULL (nếu trong trường hợp trong cây không có node nào có giá trị trùng với giá trị đang cần thêm)
        // p là Node có giá trị trùng với giá trị đang cần thêm trong trường hợp đã có node có giá trị đó tồn tại


        Node *p = timKiemNode_KhuDeQuy(Root, x);
        //NODE *p = TimKiemNode_DeQuy(Root, x, NULL);

        if(p->data != x) // vì thế phải xét tiêu chí giá trị của p phải khác x => thêm mới vào chứ không bị trùng
        {
            // Thêm Node mới vào
            Node *ConMoi = getNode(x);

            if(ConMoi == NULL)
                return -1; // Không thành công (không đủ bộ nhớ để cấp phát cho Node)

            if(x > p->data)
                p->Right = ConMoi;
            else if(x < p->data)
                p->Left = ConMoi;

            ConMoi->Cha = p;

            // Bắt đầu kiểm tra tính cân bằng của cây để xem cây có bị mất cân bằng tại Node nào thì tiến hành cân bằng lại
            while(ConMoi->Cha != NULL)
            {
                ConMoi = ConMoi->Cha;

                // Bắt đầu kiểm tra tính cân bằng của ConMoi (chính là cha của Node mới thêm liên tục trỏ về Cha)

                int kq = XetTinhCanBangVaCanBangLaiTai1Node_KhuDeQuy(Root, ConMoi);

                if(kq == 1)
                    break;
            }
        }
    }
    return 1; // thành công
}

//// Trả về 1: Nếu tại Node có bị mất cân bằng và tiến hành cân bằng lại
//// Trả về 0: Nếu tại Node không có mất cân bằng
//int XetTinhCanBangVaCanBangLaiTai1Node_DeQuy(NODE *&Root)
//{
//    int chieucaocontrai = 0;
//    int chieucaoconphai = 0;
//
//    if(Root->Left != NULL)
//        chieucaocontrai = TinhChieuCaoCay_DeQuy(Root->Left);
//
//    if(Root->Right != NULL)
//        chieucaoconphai = TinhChieuCaoCay_DeQuy(Root->Right);
//
//    if(abs(chieucaocontrai - chieucaoconphai) > 1) // mất cân bằng
//    {
//        //printf("\n=> Cay bi mat can bang tai Node %c", Root->Data);
//
//        if(chieucaocontrai > chieucaoconphai) // Lệch trái
//        {
//            int chieucaocontrai_2 = 0;
//            int chieucaoconphai_2 = 0;
//
//            if(Root->Left->Left != NULL)
//                chieucaocontrai_2 = TinhChieuCaoCay_DeQuy(Root->Left->Left);
//
//            if(Root->Left->Right != NULL)
//                chieucaoconphai_2 = TinhChieuCaoCay_DeQuy(Root->Left->Right);
//
//            if(chieucaocontrai_2 >= chieucaoconphai_2) // Trái - Trái
//            {
//                //printf("\nMat can bang Trai - Trai");
//                //printf("\n=> Quay phai tai Node %c voi Root = %c & Pivot = %c", Root->Data, Root->Data, Root->Left->Data);
//                QuayPhai(Root);
//            }
//            else // Trái - Phải
//            {
//                //printf("\nMat can bang Trai - Phai");
//                //printf("\nBuoc 1: Quay trai tai Node %c voi Root = %c & Pivot = %c", Root->Left->Data, Root->Left->Data, Root->Left->Right->Data);
//                QuayTrai(Root->Left);
//
//                //printf("\nBuoc 2: Quay phai tai Node %c voi Root = %c & Pivot = %c", Root->Data, Root->Data, Root->Left->Data);
//                QuayPhai(Root);
//            }
//        }
//        else // Lệch phải
//        {
//            int chieucaocontrai_2 = 0;
//            int chieucaoconphai_2 = 0;
//
//            if(Root->Right->Left != NULL)
//                chieucaocontrai_2 = TinhChieuCaoCay_DeQuy(Root->Right->Left);
//
//            if(Root->Right->Right != NULL)
//                chieucaoconphai_2 = TinhChieuCaoCay_DeQuy(Root->Right->Right);
//
//            if(chieucaoconphai_2 >= chieucaocontrai_2) // Phải - Phải
//            {
//                //printf("\nMat can bang Phai - Phai");
//                //printf("\n=> Quay trai tai Node %c voi Root = %c & Pivot = %c", Root->Data, Root->Data, Root->Right->Data);
//                QuayTrai(Root);
//            }
//            else // Phải - Trái
//            {
//                //printf("\nMat can bang Phai - Trai");
//                //printf("\nBuoc 1: Quay phai tai Node %c voi Root = %c & Pivot = %c", Root->Right->Data, Root->Right->Data, Root->Right->Left->Data);
//                QuayPhai(Root->Right);
//
//                //printf("\nBuoc 2: Quay trai tai Node %c voi Root = %c & Pivot = %c", Root->Data, Root->Data, Root->Right->Data);
//                QuayTrai(Root);
//            }
//        }
//        return 1; // Node bị mất cân bằng và đã cân bằng xong
//    }
//    return 0; // Node không có mất cân bằng
//}

int themNodeVaoCay_DeQuy(Node *&Root, char x)
{
    int ketqua;
    if (Root != NULL) {
        if (x > Root->data) {
            ketqua = themNodeVaoCay_DeQuy(Root->Right, x);
        }
        else if (x < Root->data) {
            ketqua = themNodeVaoCay_DeQuy(Root->Left, x);
        }
        else {
            return 0;
        }
    }
    else {
        Node *con = getNode(x);
        
        if (con == NULL) {
            return -1;
        }
        
        Root = con;
        
        return 1;
    }
    
    if (ketqua == 0) {
        return 0;
    }
    else if (ketqua == -1) {
        return -1;
    }
    else if (ketqua == 1) { //Them thanh cong, quay ve cha, kiem tra can bang o node cha truoc do
        int heightLeft = 0;
        int heightRight = 0;
        
        if (Root->Left != NULL) {
            heightLeft = tinhChieuCaoCay_DeQuy(Root->Left);
        }
        if (Root->Right != NULL) {
            heightRight = tinhChieuCaoCay_DeQuy(Root->Right);
        }
        if (abs(heightLeft - heightRight) > 1) {
            cout << "\n=> Cay bi mat can bang tai Node " << Root->data;
            if (heightLeft > heightRight) {
                //lech trai
                int heightLeftLeft = 0;
                int heightLeftRight = 0;
                
                if (Root->Left->Left != NULL) {
                    heightLeftLeft = tinhChieuCaoCay_DeQuy(Root->Left->Left);
                }
                if (Root->Left->Right != NULL) {
                    heightLeftRight = tinhChieuCaoCay_DeQuy(Root->Left->Right);
                }
                
                if (heightLeftLeft >= heightLeftRight) { // Trai - Trai
                    cout << "\nMat can bang Trai - Trai";
                    cout << "\nQuay phai tai Node " << Root->data;
                    quayPhai(Root);
                }
                else { // Trai - Phai
                    cout << "\nMat can bang Trai - Phai";
                    cout << "\nQuay trai tai Node " << Root->Left->data << " va Quay phai tai Node " << Root->data;
                    quayTrai(Root->Left);
                    quayPhai(Root);
                }
            }
            else {
                //lech phai
                int heightRightLeft = 0;
                int heightRightRight = 0;
                
                if (Root->Right->Left != NULL) {
                    heightRightLeft = tinhChieuCaoCay_DeQuy(Root->Right->Left);
                }
                if (Root->Right->Right != NULL) {
                    heightRightRight = tinhChieuCaoCay_DeQuy(Root->Right->Right);
                }
                
                if (heightRightRight >= heightRightLeft) { // Phai - Phai
                    cout << "\nMat can bang Phai - Phai";
                    cout << "\nQuay trai tai Node " << Root->data;
                    quayTrai(Root);
                }
                else { // Phai - Trai
                    cout << "\nMat can bang Phai - Trai";
                    cout << "\nQuay phai tai Node " << Root->Right->data << " va Quay trai tai Node " << Root->data;
                    quayPhai(Root->Right);
                    quayTrai(Root);
                }
            }
        }
        return 2;
    }
    else {
        return 2;
    }
}

void NLR(Node *Root)
{
    if (Root != NULL) {
        cout << Root->data << " ";
        NLR(Root->Left);
        NLR(Root->Right);
    }
}

void giaiPhongCay(Node *&Root)
{
    if (Root != NULL) {
        giaiPhongCay(Root->Left);
        giaiPhongCay(Root->Right);
        delete Root;
        Root = NULL;
    }
}

int main()
{
    Node *Root;
    iNit(Root);
    
    char x;
    do {
        cout << "\nNhap vao gia tri can them(Nhap '.' de ket thuc qua trinh them): ";
        fflush(stdin);
        cin >> x;
        
        int kq = themNodeVaoCay_DeQuy(Root, x);
        if (kq == 0) {
            cout << "\nKhong them duoc do da bi trung!!!";
        }
        else if (kq == -1) {
            cout << "\nKhong them duoc do khong du bo nho!!!";
        }
        else {
            cout << "\nThem thanh cong vao cay.";
            cout << "\nCay sau khi them: ";
            NLR(Root);
            cout << "\nChieu cao cay: " << tinhChieuCaoCay_DeQuy(Root);
        }
    } while (x != '.');
    
    giaiPhongCay(Root);
    
    //system("pause");
    return 0;
}
