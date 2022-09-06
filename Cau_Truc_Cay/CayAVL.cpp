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
        chieucaocontrai = TinhChieuCaoCuaCay_KhongDeQuyKhongStack(NodeDangXet->Left);

    if(NodeDangXet->Right != NULL)
        chieucaoconphai = TinhChieuCaoCuaCay_KhongDeQuyKhongStack(NodeDangXet->Right);

    if(abs(chieucaocontrai - chieucaoconphai) > 1) // mất cân bằng
    {
        Node *ChaCuaNodeBiMatCanBang = NULL;

        if(NodeDangXet->Cha != NULL)
            ChaCuaNodeBiMatCanBang = NodeDangXet->Cha;

        if(chieucaocontrai > chieucaoconphai) // Lệch trái
        {
            int chieucaocontrai_2 = 0;
            int chieucaoconphai_2 = 0;

            if(NodeDangXet->Left->Left != NULL)
                chieucaocontrai_2 = TinhChieuCaoCuaCay_KhongDeQuyKhongStack(NodeDangXet->Left->Left);

            if(NodeDangXet->Left->Right != NULL)
                chieucaoconphai_2 = TinhChieuCaoCuaCay_KhongDeQuyKhongStack(NodeDangXet->Left->Right);

            if(chieucaocontrai_2 >= chieucaoconphai_2) // Trái - Trái
            {
                quayPhai(NodeDangXet);

                // Sau khi quay xong kiểm tra nếu mới quay tại Node gốc của cây thì cập nhật lại Root là node đó
                if(NodeDangXet->Cha == NULL)
                    Root = NodeDangXet;
            }
            else // Trái - Phải
            {
                quayTrai(NodeDangXet->Left);

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
                chieucaocontrai_2 = TinhChieuCaoCuaCay_KhongDeQuyKhongStack(NodeDangXet->Right->Left);

            if(NodeDangXet->Right->Right != NULL)
                chieucaoconphai_2 = TinhChieuCaoCuaCay_KhongDeQuyKhongStack(NodeDangXet->Right->Right);

            if(chieucaoconphai_2 >= chieucaocontrai_2) // Phải - Phải
            {
                quayTrai(NodeDangXet);

                // Sau khi quay xong kiểm tra nếu mới quay tại Node gốc của cây thì cập nhật lại Root là node đó
                if(NodeDangXet->Cha == NULL)
                    Root = NodeDangXet;
            }
            else // Phải - Trái
            {
                quayPhai(NodeDangXet->Right);

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

// Trả về 1: Nếu tại Node có bị mất cân bằng và tiến hành cân bằng lại
// Trả về 0: Nếu tại Node không có mất cân bằng
int XetTinhCanBangVaCanBangLaiTai1Node_DeQuy(Node *&Root)
{
    int chieucaocontrai = 0;
    int chieucaoconphai = 0;

    if(Root->Left != NULL)
        chieucaocontrai = tinhChieuCaoCay_DeQuy(Root->Left);

    if(Root->Right != NULL)
        chieucaoconphai = tinhChieuCaoCay_DeQuy(Root->Right);

    if(abs(chieucaocontrai - chieucaoconphai) > 1) // mất cân bằng
    {
        //printf("\n=> Cay bi mat can bang tai Node %c", Root->Data);

        if(chieucaocontrai > chieucaoconphai) // Lệch trái
        {
            int chieucaocontrai_2 = 0;
            int chieucaoconphai_2 = 0;

            if(Root->Left->Left != NULL)
                chieucaocontrai_2 = tinhChieuCaoCay_DeQuy(Root->Left->Left);

            if(Root->Left->Right != NULL)
                chieucaoconphai_2 = tinhChieuCaoCay_DeQuy(Root->Left->Right);

            if(chieucaocontrai_2 >= chieucaoconphai_2) // Trái - Trái
            {
                //printf("\nMat can bang Trai - Trai");
                //printf("\n=> Quay phai tai Node %c voi Root = %c & Pivot = %c", Root->Data, Root->Data, Root->Left->Data);
                quayPhai(Root);
            }
            else // Trái - Phải
            {
                //printf("\nMat can bang Trai - Phai");
                //printf("\nBuoc 1: Quay trai tai Node %c voi Root = %c & Pivot = %c", Root->Left->Data, Root->Left->Data, Root->Left->Right->Data);
                quayTrai(Root->Left);

                //printf("\nBuoc 2: Quay phai tai Node %c voi Root = %c & Pivot = %c", Root->Data, Root->Data, Root->Left->Data);
                quayPhai(Root);
            }
        }
        else // Lệch phải
        {
            int chieucaocontrai_2 = 0;
            int chieucaoconphai_2 = 0;

            if(Root->Right->Left != NULL)
                chieucaocontrai_2 = tinhChieuCaoCay_DeQuy(Root->Right->Left);

            if(Root->Right->Right != NULL)
                chieucaoconphai_2 = tinhChieuCaoCay_DeQuy(Root->Right->Right);

            if(chieucaoconphai_2 >= chieucaocontrai_2) // Phải - Phải
            {
                //printf("\nMat can bang Phai - Phai");
                //printf("\n=> Quay trai tai Node %c voi Root = %c & Pivot = %c", Root->Data, Root->Data, Root->Right->Data);
                quayTrai(Root);
            }
            else // Phải - Trái
            {
                //printf("\nMat can bang Phai - Trai");
                //printf("\nBuoc 1: Quay phai tai Node %c voi Root = %c & Pivot = %c", Root->Right->Data, Root->Right->Data, Root->Right->Left->Data);
                quayPhai(Root->Right);

                //printf("\nBuoc 2: Quay trai tai Node %c voi Root = %c & Pivot = %c", Root->Data, Root->Data, Root->Right->Data);
                quayTrai(Root);
            }
        }
        return 1; // Node bị mất cân bằng và đã cân bằng xong
    }
    return 0; // Node không có mất cân bằng
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
            return 0; //Data can nhap da co trong cay
        }
    }
    else {
        Node *con = getNode(x);
        
        if (con == NULL) {
            return -1; //Ko them Node thanh cong do ko du bo nho
        }
        
        Root = con;
        
        return 1; //Them Node thanh cong
    }
    
    if (ketqua == 0) {
        return 0; //Data can nhap da co trong cay
    }
    else if (ketqua == -1) {
        return -1; //Ko them Node thanh cong do ko du bo nho
    }
    else if (ketqua == 1) { //Them thanh cong, quay ve cha, kiem tra can bang o node cha truoc do
        ketqua = XetTinhCanBangVaCanBangLaiTai1Node_DeQuy(Root);
        if (ketqua == 1) {
            return 2; //Node bị mất cân bằng và đã cân bằng xong
        }
        return 3; // Node không có mất cân bằng ketqua = 0
    }
    else if (ketqua == 2) {
        return 2; //Node bị mất cân bằng và đã cân bằng xong
    }
    else return 3; // Node không có mất cân bằng ketqua = 3
}

// p là Node thế mạng sẽ xóa
int TimPhanTuTheMang_DeQuy(Node *&Root, Node *&p)
{
    int ketqua;

    if(Root->Left != NULL)
        ketqua = TimPhanTuTheMang_DeQuy(Root->Left, p);
    else // Lúc này Root->Left == NULL => Root là NODE TRÁI nhất => đó là Node thế mạng
    {
        p->data = Root->data; // Gán giá trị của Node thế mạng (Root) sang giá trị của Node cần xóa (p)
        p = Root; // Cho con trỏ p trỏ tới Node thế mạng (Root) để kết thúc hàm thì sẽ free(p) chính là free(Root)
        Root = Root->Right; // Mục đích: Giữ liên kết với các Node con của Node bị xóa - Vì Root đang là Node TRÁI nhất => sẽ không có con trái nữa chỉ có thể có con phải hoặc không có con => cứ cho trỏ tới con phải

        return 1;
    }

    if(ketqua == 1)
    {
        //printf("\nXet nguoc ve Node %c", Root->Data);
        XetTinhCanBangVaCanBangLaiTai1Node_DeQuy(Root);
        return 1; // Để tiếp tục xét lùi về cho các cha tiếp theo
    }
    else return 0;
}

// return 1: Xóa thành công
// return 0: Không xóa thành công (Node cần xóa không tồn tại trong cây)
int XoaNodeTrongCay_DeQuy(Node *&Root, char x) // x là giá trị cần xóa ra khỏi cây
{
    int ketqua;

    // Điều kiện dừng
    if(Root == NULL)
        return 0; // kết thúc vì cây không có gì để xóa hoặc không tìm thấy Node cần xóa (giá trị cần xóa x không tồn tại trong cây)

    // Bước đệ quy
    if(x > Root->data)
        ketqua = XoaNodeTrongCay_DeQuy(Root->Right, x);
    else if(x < Root->data)
        ketqua = XoaNodeTrongCay_DeQuy(Root->Left, x);
    else // tìm thấy x trong cây tại Node Root => xóa
    {
        Node *p = Root; // p là Node sẽ bị xóa

        // TH1: Node cần xóa là Node lá
        // TH2: Node cần xóa là Node có 1 con

        // Giữ liên kết với phần còn lại của Node bị xóa
        if(p->Left == NULL)
        {
            Root = p->Right;
        }
        else if(p->Right == NULL)
        {
            Root = p->Left;
        }
        else // p->Left != NULL && p->Right != NULL => TH3: Node cần xóa là Node có đủ 2 con
        {
            TimPhanTuTheMang_DeQuy(Root->Right, p); // TRÁI nhất của cây con phải

            //printf("\nXet nguoc ve Node %c", Root->Data);
            XetTinhCanBangVaCanBangLaiTai1Node_DeQuy(Root);
        }

        delete p; // giải phóng p

        return 1; // xóa thành công
    }

    if(ketqua == 1)
    {
        // Bắt đầu xét tính cân bằng của Root (Root chính là lần lượt cha của Node BỊ xóa)
        XetTinhCanBangVaCanBangLaiTai1Node_DeQuy(Root);

        //printf("\nXet nguoc ve Node %c", Root->Data);

        return 1; // để tiếp tục xét lùi về các Node trước đó mới có giá trị cho biến ketqua để mà đi so sánh //Ham luon luon tra ve 1 neu cay co Node can xoa
    }
    else return 0;
}

// p là Node thế mạng sẽ xóa
void TimPhanTuTheMang_KhuDeQuy(Node *&Root, Node *&p)
{
    // q là Node thế mạng cần xóa
    Node *q = Root;
    Node *k = p; // k là Node đứng trước Node q để khi cần có thể truy xuất về cha của nó. Khởi đầu thì k = p (Node cần xóa)

    while(q->Left != NULL)
    {
        k = q; // k là node đứng trước node q nên trước khi q trỏ đi đâu khác thì k cập nhật lại là q
        q = q->Left;
    }

    // Sau vòng lặp thì q là Node trái nhất (Tức là nếu trỏ trái lần nữa thì sẽ là NULL => q là trái nhất)

    // Phải để đoạn lệnh này trước 2 đoạn lệnh sau để cập nhật liên kết cho xong rồi từ đó mới muốn cho trỏ đi đâu thì trỏ. Nếu không sẽ bị lỗi nếu để 2 đoạn lệnh dưới lên trên đoạn lệnh này
    if(q->data > k->data)
        k->Right = q->Right; // Lúc này q đã là trái nhất nên sẽ không có con trái nữa => chỉ có thể có con phải => cho giữ lại phần con phải
    else if(q->data < k->data)
        k->Left = q->Right; // Lúc này q đã là trái nhất nên sẽ không có con trái nữa => chỉ có thể có con phải => cho giữ lại phần con phải

    if(q->Right != NULL)
        q->Right->Cha = k;

    p->data = q->data; // Gán giá trị của Node thế mạng (Root) sang giá trị của Node cần xóa (p)
    p = q; // Cho con trỏ p trỏ tới Node thế mạng (q) để kết thúc hàm thì sẽ free(p) chính là free(q)
}


// return 1: Xóa thành công
// return 0: Không xóa thành công (Node cần xóa không tồn tại trong cây)
int XoaNodeTrongCay_KhuDeQuy(Node *&Root, char x) // x là giá trị cần xóa ra khỏi cây
{
    Node *q = Root;
    Node *k = NULL; // k là Node đứng trước Node q để khi cần có thể truy xuất về cha của nó
    while(q != NULL)
    {
        if(x > q->data)
        {
            k = q; // k là node đứng trước node q nên trước khi q trỏ đi đâu khác thì k cập nhật lại là q
            q = q->Right;
        }
        else if(x < q->data)
        {
            k = q; // k là node đứng trước node q nên trước khi q trỏ đi đâu khác thì k cập nhật lại là q
            q = q->Left;
        }
        else // tìm thấy x trong cây tại Node q => tiến hành xóa
        {
            Node *p = q; // p là Node sẽ bị xóa: Lý do dùng Node tạm p để xóa mà không xóa trực tiếp q bởi vì lỡ trong cùng 1 hàm sau khi xóa xong lại có nhu cầu duyệt cây tiếp thì lại duyệt dựa theo Node q nếu mà q bị xóa thì đâu còn duyệt được nữa

            // TH1: Node cần xóa là Node lá
            // TH2: Node cần xóa là Node có 1 con

            // Giữ liên kết với phần còn lại của Node bị xóa
            if(p->Left == NULL)
            {
                // k là Node cha của Node q cần xóa => k sẽ trỏ liên kết để giữ cháu của nó (giữ con của node cần xóa)
                // Làm sao biết k phải trỏ Left hay Right đến cháu của nó? => tùy thuộc q cần xóa đang là con trái hay con phải của k
                if(k != NULL) // k có tồn tại
                {
                    if(p->data > k->data)
                        k->Right = p->Right;
                    else if(p->data < k->data)
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
                    if(p->data > k->data)
                        k->Right = p->Left;
                    else if(p->data < k->data)
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
                TimPhanTuTheMang_KhuDeQuy(q->Right, p); // Tìm phần tử thế mạng: TRÁI nhất của cây con phải
            }

            // 3 dòng code này phải để trước dòng lệnh free(p) vì nếu free(p) rồi thì đâu còn giá trị để trỏ tới cha mà truyền qua Node ChaCuaNodeBiXoa
            Node *ChaCuaNodeBiXoa = NULL;
            if(p->Cha != NULL)
                ChaCuaNodeBiXoa = p->Cha;

            while(ChaCuaNodeBiXoa != NULL)
            {
                // Xét tính cân bằng của Node ChaCuaNodeBiXoa
                //printf("\nXet tinh can bang cua Node: %c", ChaCuaNodeBiXoa->Data);

                XetTinhCanBangVaCanBangLaiTai1Node_KhuDeQuy(Root, ChaCuaNodeBiXoa);

                ChaCuaNodeBiXoa = ChaCuaNodeBiXoa->Cha;
            }

            delete p; // giải phóng p
            return 1; // Xóa thành công - kết thúc hàm
        }
    }
    return 0; // Không xóa thành công (Node cần xóa không tồn tại trong cây)
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
