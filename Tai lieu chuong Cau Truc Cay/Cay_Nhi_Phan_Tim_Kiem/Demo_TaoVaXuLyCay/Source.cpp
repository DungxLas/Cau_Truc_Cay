﻿#include <stdio.h>
#include <conio.h>
#include <malloc.h>
#include <time.h>
#include <queue>
#include <stack>
#include <Windows.h>
using namespace std;


/* 1/ Khai báo cấu trúc dữ liệu cây nhị phân tìm kiếm */

struct Node
{
	int Data; // cây nhị phân tìm kiếm chứa các số nguyên
	struct Node *Left, *Right; // Trỏ tới các Node cây con trái và cây con phải
	bool TinhTrangDuyet;
	int ThuTuDuyet;
	struct Node *Cha;
};
typedef struct Node NODE;
// typedef NODE* Tree; // Tree t; => t là 1 Node (NODE *)

/* End 1 */

// Không được để lên đầu tiên vì chương trình không biết NODE là gì khi chưa biên dịch đến struct Node => LỖI
NODE* TimKiemNode_KhuDeQuy(NODE *Root, int x);
NODE* TimKiemNode_DeQuy(NODE *Root, int x, NODE *NodeTruocNull);

/* 2/ Khởi tạo cây */

void INit(NODE *&Root)
{
	Root = NULL;
}

/* End 2 */

/* 3/ Tạo node */

// Tạo 1 Node mới chứa dữ liệu x và trả về địa chỉ của Node đó sau khi tạo xong
NODE* GetNode(int x) // x là dữ liệu mà sẽ đưa nó vào trong Node
{
	//NODE *p = new NODE; // cấp phát con trỏ Node kiểu của bên C++
	NODE *p = (NODE *)malloc(sizeof(NODE)); // cấp phát con trỏ Node kiểu của bên C
	if(p == NULL)
		return NULL; // Không tạo thành công do thiếu vùng nhớ để cấp phát tạo ra Node

	// Nếu vẫn còn chạy được xuống đây tức là không thỏa cái if => Node được tạo thành công
	p->Data = x; // đưa dữ liệu x vào trong Node p
	p->Left = p->Right = NULL; // cập nhật con trỏ Left, Right là NULL
	p->ThuTuDuyet = 0;
	p->TinhTrangDuyet = false;
	p->Cha = NULL;

	return p; // trả về Node p đã được tạo
}

/* End 3 */

// 40, 5, 35, 45, 15, 56, 48, 13, 16, 49, 47
// return 1: Thành công
// return 0: Không thành công (bị trùng)
// return -1: Không thành công (không đủ bộ nhớ để cấp phát cho Node)
int ThemNodeVaoCay_DeQuy(NODE *&Root, int x, NODE *k) // thêm giá trị x vào cây
{
	if(Root != NULL)
	{
		 // điều kiện đệ quy

		if(x > Root->Data)
			return ThemNodeVaoCay_DeQuy(Root->Right, x, Root);
		else if(x < Root->Data)
			return ThemNodeVaoCay_DeQuy(Root->Left, x, Root);
		else
		{
			//printf("\nGia tri Node nay da co ton tai trong cay roi cho nen khong tao moi nua");
			return 0; // không thành công (bị trùng)
		}
	}
	else // Root == NULL
	{
		//Root = GetNode(x); // Dừng đệ quy => Tạo Node chứa giá trị cần thêm vào
		NODE *ConMoi = GetNode(x);

		if(ConMoi == NULL)
			return -1; // Không thành công (không đủ bộ nhớ để cấp phát cho Node)

		Root = ConMoi;

		ConMoi->Cha = k;
	}
	return 1; // thành công
}

// 40, 5, 35, 45, 15, 56, 35, 35, 35, 48, 13, 16, 49, 47
// return 1: Thành công
// return 0: Không thành công (bị trùng)
// return -1: Không thành công (không đủ bộ nhớ để cấp phát cho Node)
int ThemNodeVaoCay_KhuDeQuy(NODE *&Root, int x) // thêm giá trị x vào cây
{
	// Từ ban đầu cây chưa có gì => tạo node gốc cho cây
	if(Root == NULL)
	{
		Root = GetNode(x);
	}
	else // cây đã có node gốc rồi thì tiến hành thêm lần lượt các node tiếp theo vào và so sánh để tìm vị trí thích hợp để thêm
	{
		//NODE *q = Root; // q là Node đại diện cho Root để đi qua Left, Right và cứ mỗi lần chuẩn bị thêm 1 giá trị mới vào cây thì q sẽ trỏ về Root để cập nhật lại về gốc của cây, chứ nếu để Root trực tiếp đi thì sau 1 lần thêm phải trả Root về lại ban đầu thông qua 1 Node phụ => phức tạp
		//NODE *p; // Là node trước khi q = NULL
		//while(q != NULL)
		//{
		//	p = q;
		//	if(x > q->Data)
		//		q = q->Right;
		//	else if(x < q->Data)
		//		q = q->Left;
		//	else if(x == q->Data)
		//		return; // kết thúc hàm do cây nhị phân tìm kiếm không có node trùng nhau
		//}

		// p là Node đứng trước Node NULL (nếu trong trường hợp trong cây không có node nào có giá trị trùng với giá trị đang cần thêm)
		// p là Node có giá trị trùng với giá trị đang cần thêm trong trường hợp đã có node có giá trị đó tồn tại
		
		NODE *p = TimKiemNode_DeQuy(Root, x, Root); 
		//NODE *p = TimKiemNode_KhuDeQuy(Root, x); 

		if(p->Data != x) // vì thế phải xét tiêu chí giá trị của p phải khác x => thêm mới vào chứ không bị trùng
		{
			// Thêm Node mới vào
			NODE *ConMoi = GetNode(x);

			if(ConMoi == NULL)
				return -1; // Không thành công (không đủ bộ nhớ để cấp phát cho Node)

			/*if(x > p->Data)
				p->Right = GetNode(x);
			else if(x < p->Data)
				p->Left = GetNode(x);*/

			if(x > p->Data)
				p->Right = ConMoi;
			else if(x < p->Data)
				p->Left = ConMoi;

			ConMoi->Cha = p;
		}
		else
		{
			//printf("\nGia tri Node nay da co ton tai trong cay roi cho nen khong tao moi nua");
			return 0; // Không thành công (bị trùng)
		}
	}
	return 1; // thành công
}

void TaoCayTuDaySo(NODE *&Root, int a[], int n) // dãy số chứa trong mảng a và có n là số lượng phần tử của dãy
{
	INit(Root); // khởi tạo ra cây rồi từ đó mới có thể thêm các node vào trong cây
	
	for(int i = 0; i < n; ++i) // vòng lặp duyệt qua danh sách dãy số chứa trong mảng a để từ đó thêm vào cây
	{
		//printf("\nDang chuan bi them gia tri %d vao cay", a[i]);
		//ThemNodeVaoCay_DeQuy(Root, a[i], NULL);
		ThemNodeVaoCay_KhuDeQuy(Root, a[i]);
		//printf("\nNode goc cua cay la: %d", Root->Data);
	}
}

// n là số lượng
void TaoCayNhapTuBanPhimBietTruocSoLuong(NODE *&Root, int &n)
{
	INit(Root); // Phải nhớ khởi tạo cho cây để tránh bị lỗi
	do{
		printf("\nNhap vao so luong Node cua cay: ");
		scanf("%d", &n);

		if(n < 0)
			printf("\nSo luong phai la so duong. Xin kiem tra lai!");
	}while(n < 0);

	for(int i = 1; i <= n; ++i)
	{
		int x;
		printf("\nNhap vao gia tri cua Node thu %d: ", i);
		scanf("%d", &x);

		ThemNodeVaoCay_KhuDeQuy(Root, x);
	}
}

// ví dụ như gặp số âm là dừng lại
void TaoCayNhapTuBanPhimKhongBietTruocSoLuong(NODE *&Root)
{
	int i = 1;
	while(true) // lặp vô tận đến khi nào gặp điều kiện dừng thì dừng lại
	{
		int x;
		do{
			printf("\nNhap vao gia tri cua Node thu %d (Nhap so 123456 de ket thuc): ", i);
			scanf("%d", &x);

			if(x < 0)
				printf("\nGia tri nhap vao cua Node phai la so duong. Xin kiem tra lai!");
		}while(x < 0);

		if(x == 123456)
		{
			printf("\nGia tri 123456 Ban vua nhap la de ket thuc hay muon tao ra 1 Node moi co gia tri la 123456? Neu de ket thuc thi nhan phim Y, neu khong muon ket thuc thi nhan phim N");
			char c = getch();

			if(c == 'y' || c == 'Y')
				break; // thoát khỏi vòng lặp => dừng lại
		}

		int ketqua = ThemNodeVaoCay_KhuDeQuy(Root, x);
		//int ketqua = ThemNodeVaoCay_DeQuy(Root, x, NULL);

		if(ketqua == 1) // thêm Node thành công thì mới tăng biến đếm lên
			i++;
		else if(ketqua == 0)
			printf("\nLoi: Gia tri Node nay da co ton tai trong cay roi cho nen khong them vao cay duoc nua");
		else if(ketqua == -1)
			printf("\nLoi: Khong du bo nho de cap phat cho Node");
	}
}

void TaoCayTuTapTin(NODE *&Root, FILE *FileIn)
{
	//INit(Root); // Phải nhớ khởi tạo cho cây để tránh bị lỗi

	// Trường hợp dòng đầu tiên trong file tượng trưng cho số lượng data
	//int n;
	//fscanf(FileIn, "%d", &n);

	//for(int i = 1; i <= n; ++i)

	// Trường hợp không biết trước số lượng có bao nhiêu dòng data trong file => cứ đọc hết từ đầu đến cuối
	while(!feof(FileIn)) // đọc từ đầu đến cuối của file thì dừng
	{
		int x;
		if(fscanf(FileIn, "%d", &x) == 1) // Đọc giá trị từ tập tin thành công sẽ trả về 1 => dựa vào đó mà biết được x có dữ liệu không? Nếu có => thêm x vào cây
			ThemNodeVaoCay_KhuDeQuy(Root, x);
	}
}

void NLR(NODE *Root)
{
	if(Root != NULL)
	{
		printf("%d ", Root->Data);
		NLR(Root->Left);
		NLR(Root->Right);
	}
}

void LNR(NODE *Root)
{
	if(Root != NULL)
	{
		LNR(Root->Left);
		printf("%d ", Root->Data);
		LNR(Root->Right);
	}
}

void RNL(NODE *Root)
{
	if(Root != NULL)
	{
		RNL(Root->Right);
		printf("%d ", Root->Data);
		RNL(Root->Left);
	}
}

void LRN(NODE *Root)
{
	if(Root != NULL)
	{
		LRN(Root->Left);
		LRN(Root->Right);
		printf("%d ", Root->Data);
	}
}

// 1: left -> right, khác 1: right->left
void DuyetTheoChieuRong(NODE *Root, int thutu = 1) 
{
	queue<NODE *> q;

	// Phải có tồn tại Node gốc thì mới đưa Node gốc đó vào hàng đợi
	if(Root != NULL)
		q.push(Root);

	while(!q.empty()) // lặ[ liên tục khi hàng đợi còn phần tử
	{
		NODE *p = q.front(); // Lấy ra Node đầu hàng đợi
		printf("%d ", p->Data); 
		q.pop(); // bỏ Node ra khỏi hàng đợi

		if(thutu == 1)
		{
			if(p->Left != NULL) // có tồn tại Node con trái của p
				q.push(p->Left); // Đưa con trái vào hàng đợi

			if(p->Right != NULL) // có tồn tại Node con phải của p
				q.push(p->Right); // Đưa con phải vào hàng đợi
		}
		else
		{
			if(p->Right != NULL) // có tồn tại Node con phải của p
				q.push(p->Right); // Đưa con phải vào hàng đợi

			if(p->Left != NULL) // có tồn tại Node con trái của p
				q.push(p->Left); // Đưa con trái vào hàng đợi
		}
	}
}

// thutu = 1 (left -> right), thutu = 2 (right -> left)
void PreOrder_KhuDeQuyDungStack(NODE *Root, int thutu = 1)
{
	stack<NODE *> s;
	s.push(Root);

	//thutu == 1 ? printf("\nNLR: ") : printf("\nNRL: ");

	while(!s.empty())
	{
		NODE *p = s.top();
		s.pop();
		printf("%d ", p->Data);

		if(thutu == 1) // left -> right
		{
			if(p->Right != NULL)
				s.push(p->Right);

			if(p->Left != NULL)
				s.push(p->Left);
		}
		else // right -> left
		{
			if(p->Left != NULL)
				s.push(p->Left);

			if(p->Right != NULL)
				s.push(p->Right);
		}
	}
}

// thutu = 1 (left -> right), thutu = 2 (right -> left)
void InOrder_KhuDeQuyDungStack(NODE *Root, int thutu = 1)
{
	stack<NODE *> s;
	s.push(Root);
	Root->TinhTrangDuyet = true;

	//thutu == 1 ? printf("\nLNR: ") : printf("\nRNL: ");

	while(!s.empty())
	{
		NODE *p = s.top(); // p là Node ở đỉnh stack
		bool Check = false;

		if(thutu == 1)
		{
			if(p->Right != NULL && p->Right->TinhTrangDuyet == false) // có tồn tại con phải và con phải chưa được duyệt
			{
				s.pop(); // xóa phần tử đầu stack hiện tại
				s.push(p->Right); // đưa con phải vào stack
				p->Right->TinhTrangDuyet = true; // đánh dấu là đã được duyệt
				s.push(p); // trả lại phần tử đầu stack trước đó
				Check = true; // kiểm tra có con được thêm vào
			}

			if(p->Left != NULL && p->Left->TinhTrangDuyet == false) // có tồn tại con trái và con trái chưa được duyệt
			{
				s.push(p->Left); // đưa con trái vào stack
				p->Left->TinhTrangDuyet = true; // đánh dấu là đã được duyệt
				Check = true; // kiểm tra có con được thêm vào
			}
		}
		else
		{
			if(p->Left != NULL && p->Left->TinhTrangDuyet == false) // có tồn tại con phải và con phải chưa được duyệt
			{
				s.pop(); // xóa phần tử đầu stack hiện tại
				s.push(p->Left); // đưa con phải vào stack
				p->Left->TinhTrangDuyet = true; // đánh dấu là đã được duyệt
				s.push(p); // trả lại phần tử đầu stack trước đó
				Check = true; // kiểm tra có con được thêm vào
			}

			if(p->Right != NULL && p->Right->TinhTrangDuyet == false) // có tồn tại con trái và con trái chưa được duyệt
			{
				s.push(p->Right); // đưa con trái vào stack
				p->Right->TinhTrangDuyet = true; // đánh dấu là đã được duyệt
				Check = true; // kiểm tra có con được thêm vào
			}
		}

		// Nếu sau 1 quá trình xét mà không có con nào được thêm vào => in ra node đầu stack hiện tại và bỏ đi
		if(Check == false)
		{
			printf("%d ", p->Data);
			s.pop();
		}
	}
}

// thutu = 1 (left -> right); thutu = 2 (right -> left)
void PostOrder_KhuDeQuyDungStack(NODE *Root, int thutu = 1)
{
	stack<NODE *> s;
	s.push(Root);

	while(!s.empty())
	{
		NODE *p = s.top();
		bool Check = false; // biến cờ hiệu mục đích để biết xem từ node hiện tại đầu stack có node con nào của nó hợp lệ để được thêm vào tiếp. Nếu trải qua 2 cái if mà Check vẫn là false tức là không có node con nào của node đang xét được thêm vào stack => lấy node đó ra khỏi stack và in ra

		if(thutu == 1)
		{
			if(p->Right != NULL && p->Right->TinhTrangDuyet == false) // xét có con phải và chưa được thêm vào stack
			{
				s.push(p->Right); // tiến hành thêm vào
				p->Right->TinhTrangDuyet = true; // cập nhật tình trạng thêm
				Check = true;
			}

			if(p->Left != NULL && p->Left->TinhTrangDuyet == false) // xét có con trái và chưa được thêm vào stack
			{
				s.push(p->Left); // tiến hành thêm vào
				p->Left->TinhTrangDuyet = true; // cập nhật tình trạng thêm
				Check = true;
			}
		}
		else
		{
			if(p->Left != NULL && p->Left->TinhTrangDuyet == false) // xét có con trái và chưa được thêm vào stack
			{
				s.push(p->Left); // tiến hành thêm vào
				p->Left->TinhTrangDuyet = true; // cập nhật tình trạng thêm
				Check = true;
			}

			if(p->Right != NULL && p->Right->TinhTrangDuyet == false) // xét có con phải và chưa được thêm vào stack
			{
				s.push(p->Right); // tiến hành thêm vào
				p->Right->TinhTrangDuyet = true; // cập nhật tình trạng thêm
				Check = true;
			}
		}

		if(Check == false)
		{
			printf("%d ", p->Data);
			s.pop(); // bỏ ra khỏi stack
		}
	}
}

void DuyetCayKhongDeQuyKhongStack(NODE *Root, char *s) // s = "NLR" hoặc "LNR" hoặc "LRN" hoặc "NRL" hoặc "RNL" hoặc "RLN"
{
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
					printf("%d ", Root->Data);
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
}

// tìm giá trị x xem có tồn tại ở node nào đó trong cây không? Nếu có thì trả về node đó, nếu không có thì trả về node đứng trước node đó để phục vụ cho mục đích thêm node vào cây
NODE* TimKiemNode_DeQuy(NODE *Root, int x, NODE *NodeTruocNull) 
{
	// Điều kiện dừng: Khi không tìm thấy
	if(Root == NULL)
		return NodeTruocNull;

	// Điều kiện đệ quy
	//if(Root != NULL) // Cũng không cần viết điều kiện này bởi vì chúng ta đã xét nếu Root == NULL ở đầu tiên của hàm nên nếu nó còn chạy được xuống dưới này tức là Root != NULL
	//{
		if(x > Root->Data)
			return TimKiemNode_DeQuy(Root->Right, x, Root);
		else if(x < Root->Data)
			return TimKiemNode_DeQuy(Root->Left, x, Root);
		else // x == Root->Data
			return Root; // Điều kiện dừng: Khi đã tìm thấy
	//}
}

// tìm giá trị x xem có tồn tại ở node nào đó trong cây không? Nếu có thì trả về node đó, nếu không có thì trả về node đứng trước node đó để phục vụ cho mục đích thêm node vào cây
NODE* TimKiemNode_KhuDeQuy(NODE *Root, int x) 
{
	NODE *p = Root;
	NODE *q = p; // q là Node cuối cùng trước khi đến NULL => mục đích: Để có thể từ đó tạo liên kết thêm node mới vào
	while(p != NULL)
	{
		q = p;

		if(x > p->Data)
			p = p->Right;
		else if(x < p->Data)
			p = p->Left;
		else // x == p->Data
			return p; // Điều kiện dừng đã tìm thấy
	}

	// Chạy xuống đây tức là Root đã = NULL => không tìm thấy
	return q; // Trả về Node cuối cùng trước khi đến NULL
}

// p là Node thế mạng sẽ xóa
void TimPhanTuTheMang_DeQuy(NODE *&Root, NODE *&p, NODE *cha) 
{
	if(Root->Right != NULL)
		TimPhanTuTheMang_DeQuy(Root->Right, p, Root);
	else // Lúc này Root->Right == NULL => Root là NODE phải nhất => đó là Node thế mạng
	{
		p->Data = Root->Data; // Gán giá trị của Node thế mạng (Root) sang giá trị của Node cần xóa (p)
		p = Root; // Cho con trỏ p trỏ tới Node thế mạng (Root) để kết thúc hàm thì sẽ free(p) chính là free(Root)
		Root = Root->Left; // Mục đích: Giữ liên kết với các Node con của Node bị xóa - Vì Root đang là Node phải nhất => sẽ không có con phải chỉ có thể có con trái hoặc không có con => cứ cho trỏ tới con trái
	
		if(Root != NULL && Root->Left != NULL)
			Root->Left->Cha = cha;
	}
}

void XoaNodeTrongCay_DeQuy(NODE *&Root, int x, NODE *cha = NULL) // x là giá trị cần xóa ra khỏi cây
{
	// Điều kiện dừng
	if(Root == NULL)
		return; // kết thúc vì cây không có gì để xóa hoặc không tìm thấy Node cần xóa (giá trị cần xóa x không tồn tại trong cây)

	// Bước đệ quy
	if(x > Root->Data)
		XoaNodeTrongCay_DeQuy(Root->Right, x, Root);
	else if(x < Root->Data)
		XoaNodeTrongCay_DeQuy(Root->Left, x, Root);
	else // tìm thấy x trong cây tại Node Root => xóa
	{
		NODE *p = Root; // p là Node sẽ bị xóa

		// TH1: Node cần xóa là Node lá
		// TH2: Node cần xóa là Node có 1 con

		// Giữ liên kết với phần còn lại của Node bị xóa
		if(p->Left == NULL)
		{
			Root = p->Right;

			if(p->Right != NULL)
				p->Right->Cha = cha;
		}
		else if(p->Right == NULL)
		{
			Root = p->Left;

			if(p->Left != NULL)
				p->Left->Cha = cha;
		}
		else // p->Left != NULL && p->Right != NULL => TH3: Node cần xóa là Node có đủ 2 con
		{
			TimPhanTuTheMang_DeQuy(Root->Left, p, Root);
		}

		// Viết đầy đủ thì sẽ thế này
		//if(p->Left == NULL && p->Right == NULL) // TH1: Node cần xóa là Node lá
		//	Root = NULL;
		//else if((p->Left == NULL && p->Right != NULL) || (p->Left != NULL && p->Right == NULL)) // TH2: Node cần xóa là Node có 1 con
		//{
		//	if(p->Left == NULL)
		//		Root = p->Right;
		//	else
		//		Root->Left;
		//}
		//else // TH3: Node cần xóa là Node có đủ 2 con
		//{
		//	TimPhanTuTheMang_DeQuy(Root->Left, p);
		//}


		free(p); // giải phóng p
	}
}

// p là Node thế mạng sẽ xóa
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
	else if(q->Data < k->Data)
		k->Left = q->Left;

	if(q->Left != NULL)
		q->Left->Cha = k;

	p->Data = q->Data; // Gán giá trị của Node thế mạng (Root) sang giá trị của Node cần xóa (p)
	p = q; // Cho con trỏ p trỏ tới Node thế mạng (q) để kết thúc hàm thì sẽ free(p) chính là free(q)
}


// return 1: Xóa thành công
// return 0: Không xóa thành công (Node cần xóa không tồn tại trong cây)
int XoaNodeTrongCay_KhuDeQuy(NODE *&Root, int x) // x là giá trị cần xóa ra khỏi cây
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

			free(p); // giải phóng p
			return 1; // Xóa thành công - kết thúc hàm
		}
	}
	return 0; // Không xóa thành công (Node cần xóa không tồn tại trong cây)
}

// p là Node thế mạng sẽ xóa
void TimPhanTuTheMang_KhuDeQuy_Ver2DungNodeCha(NODE *&Root, NODE *&p) 
{
	// q là Node thế mạng cần xóa
	NODE *q = Root;
	//printf("\nq = %d", q->Data);
	while(q->Right != NULL)
		q = q->Right;

	// Sau vòng lặp thì q là Node phải nhất (Tức là nếu trỏ phải lần nữa thì sẽ là NULL => q là phải nhất)

	// Phải để đoạn lệnh này trước 2 đoạn lệnh sau để cập nhật liên kết cho xong rồi từ đó mới muốn cho trỏ đi đâu thì trỏ. Nếu không sẽ bị lỗi nếu để 2 đoạn lệnh dưới lên trên đoạn lệnh này
	if(q->Data > q->Cha->Data)
		q->Cha->Right = q->Left;
	else if(q->Data < q->Cha->Data)
		q->Cha->Left = q->Left;

	if(q->Left != NULL)
		q->Left->Cha = q->Cha;
	

	p->Data = q->Data; // Gán giá trị của Node thế mạng (Root) sang giá trị của Node cần xóa (p)
	p = q; // Cho con trỏ p trỏ tới Node thế mạng (q) để kết thúc hàm thì sẽ free(p) chính là free(q)

	
}

void XoaNodeTrongCay_KhuDeQuy_Ver2DungNodeCha(NODE *&Root, int x) // x là giá trị cần xóa ra khỏi cây
{
	NODE *q = Root;
	while(q != NULL)
	{
		if(x > q->Data)
			q = q->Right;
		else if(x < q->Data)
			q = q->Left;
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
				if(p->Cha != NULL) // có tồn tại Node cha của Node cần xóa
				{
					if(p->Data > p->Cha->Data)
						p->Cha->Right = p->Right;
					else if(p->Data < p->Cha->Data)
						p->Cha->Left = p->Right;

					if(p->Right != NULL)
						p->Right->Cha = p->Cha;
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
				if(p->Cha != NULL) // k có tồn tại
				{
					// k là Node cha của Node q cần xóa => k sẽ trỏ liên kết để giữ cháu của nó (giữ con của node cần xóa)
					// Làm sao biết k phải trỏ Left hay Right đến cháu của nó? => tùy thuộc q cần xóa đang là con trái hay con phải của k
					if(p->Data > p->Cha->Data)
						p->Cha->Right = p->Left;
					else if(p->Data < p->Cha->Data)
						p->Cha->Left = p->Left;

					if(p->Left != NULL)
						p->Left->Cha = p->Cha;
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
				TimPhanTuTheMang_KhuDeQuy_Ver2DungNodeCha(q->Left, p);
			}

			free(p); // giải phóng p
			return; // kết thúc hàm
		}
	}
}

void XoaTatCaCacNodeGiaiPhongCay_KhuDeQuy(NODE *&Root)
{
	while(Root != NULL)
	{
		//printf("\nXoa Node: %d", Root->Data);
		//if(Root->Cha != NULL)
			//printf(" co cha la: %d", Root->Cha->Data);
		//XoaNodeTrongCay_KhuDeQuy_Ver2DungNodeCha(Root, Root->Data);
		XoaNodeTrongCay_KhuDeQuy(Root, Root->Data);
	}
}

void XoaTatCaCacNodeGiaiPhongCay_DeQuy(NODE *&Root)
{
	/*while(Root != NULL)
	{
		XoaNodeTrongCay_DeQuy(Root, Root->Data);
	}*/

	if(Root == NULL)
		return;

	XoaNodeTrongCay_DeQuy(Root, Root->Data);
	
	XoaTatCaCacNodeGiaiPhongCay_DeQuy(Root);
}

void GiaiPhongCay_DeQuy(NODE *&Root)
{
	if(Root != NULL)
	{
		GiaiPhongCay_DeQuy(Root->Left);
		GiaiPhongCay_DeQuy(Root->Right);

		free(Root);
		Root = NULL; // Để sau hàm giải phóng nếu người dùng có thao tác gì đó với cây thì Root = NULL nên ko làm gì được nữa, tránh xảy ra lỗi ngang
	}
}

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
					free(Root);
					Root = NULL;
					break; // ĐIỀU KIỆN DỪNG => TỪ GỐC TRỎ VỀ CHA SẼ LÀ NULL => DỪNG LẠI
				}
				else
				{
					NODE *q = Root;
					Root = Root->Cha;
					free(q);
					q = NULL;
				}
			}
		}
	}

}

//int main()
//{
//	int a[] = {40, 5, 35, 45, 15, 56, 35, 35, 35, 48, 13, 16, 49, 47};
//	//int a[] = {50, 100, 30, 20, 40, 35, 45, 37};
//	int n = sizeof(a) / sizeof(a[0]);
//
//	NODE *Root;
//	INit(Root);
//	TaoCayTuDaySo(Root, a, n);
//	//TaoCayNhapTuBanPhimBietTruocSoLuong(Root, n);
//	//TaoCayNhapTuBanPhimKhongBietTruocSoLuong(Root);
//	//TaoCayTuTapTin(Root);
//
//	printf("\nNLR: ");
//	NLR(Root);
//
//	printf("\nLNR: ");
//	LNR(Root);
//
//	printf("\nLRN: ");
//	LRN(Root);
//
//	////XoaNodeTrongCay_KhuDeQuy(Root, 40);
//	////XoaNodeTrongCay_KhuDeQuy_Ver2DungNodeCha(Root, 40);
//	//XoaNodeTrongCay_DeQuy(Root, 40);
//	//XoaTatCaCacNodeGiaiPhongCay_DeQuy(Root);
//
//	//XoaTatCaCacNodeGiaiPhongCay_DeQuy(Root);
//
//	//printf("\nInOrder: ");
//	//DuyetCayKhongDeQuyKhongStack(Root, "LNR");
//
//	//DuyetTheoChieuRong(Root, 2);
//
//	/*printf("\nNLR: ");
//	NLR(Root);
//
//	printf("\nPreOrder: ");
//	DuyetCayKhongDeQuyKhongStack(Root, "NLR");
//
//	printf("\nLNR: ");
//	LNR(Root);
//
//	printf("\nInOrder: ");
//	DuyetCayKhongDeQuyKhongStack(Root, "LNR");
//
//	printf("\nLRN: ");
//	LRN(Root);
//
//	printf("\nPostOrder: ");
//	DuyetCayKhongDeQuyKhongStack(Root, "LRN");*/
//
//	/*printf("\nLNR: ");
//	LNR(Root);
//
//	int y = 40;
//	printf("\nXoa node co gia tri la: %d", y);
//	XoaNodeTrongCay_KhuDeQuy_Ver2DungNodeCha(Root, y);
//
//	printf("\nLNR: ");
//	LNR(Root);*/
//
//	
//	//printf("\nXoa tat ca cac Node => giai phong cay");
//	//XoaTatCaCacNodeGiaiPhongCay_DeQuy(Root);
//
//	//int x = 17;
//
//	// p có thể là node có giá trị cần tìm trong trường hợp tìm thấy hoặc node đứng trước node NULL trong trường hợp không tìm thấy
//	//NODE *p = TimKiemNode_DeQuy(Root, x, Root);
//
//	//// Tức là trong 2 trường hợp lúc nào cũng trả về 1 Node có tồn tại nên không thể dựa theo tiêu chí NULL để biết có tìm ra node có giá trị x không?
//	//// vì thế cần phải xét Data của Node trả về nếu trùng với x thì nghĩa là tìm thấy, nếu không trùng với x thì nghĩa là không tìm thấy
//	//if(p->Data != x)
//	//	printf("\nKhong tim thay node trong cay co gia tri la: %d", x);
//	//else
//	//	printf("\nDa tim thay node trong cay co gia tri la: %d", p->Data);
//
//	//printf("\nLNR: ");
//	//LNR(Root);
//
//	/*
//	clock_t start1 = clock();
//
//	for(int k = 1; k <= 1000000; ++k)
//	{
//		NODE *Root1;
//		INit(Root1);
//		TaoCayTuDaySo(Root1, a, n);
//
//		GiaiPhongCay_DeQuy(Root1);
//	}
//	
//	clock_t end1 = clock();
//
//	clock_t start2 = clock();
//
//	for(int k = 1; k <= 1000000; ++k)
//	{
//		NODE *Root2;
//		INit(Root2);
//		TaoCayTuDaySo(Root2, a, n);
//
//		GiaiPhongCay_KhuDeQuy(Root2);
//	}
//	
//	clock_t end2 = clock();
//
//	printf("\nGiai phong cay dung de quy chay mat %lf giay", (double)(end1 - start1) / CLOCKS_PER_SEC);
//	printf("\nGiai phong cay dung khu de quy chay mat %lf giay", (double)(end2 - start2) / CLOCKS_PER_SEC); */
//
//	getch();
//	return 0;
//}

void Menu()
{
	NODE *Root;
	INit(Root); // Phải nhớ khởi tạo cho cây để tránh bị lỗi
	int menu1;

menucha:

	do{
		printf("\n===============> Menu <===============\n");
		printf("\n1. Doc du lieu tu tap tin vao cay");
		printf("\n2. Them Node vao cay (du lieu nhap vao tu ban phim)");
		printf("\n3. Tim kiem Node");
		printf("\n4. Xoa Node");
		printf("\n5. Duyet cay");
		printf("\n6. Giai phong cay");
		printf("\n0. Thoat chuong trinh");
		printf("\n======================================\n");

		printf("\nNhap vao lua chon (0 -> 6): ");
		scanf("%d", &menu1);

		if(menu1 < 0 || menu1 > 6)
		{
			printf("\nLua chon chi duoc trong khoang 0 -> 6. Nhan enter nhap lai!");
			getch();
			system("cls");
		}
	}while(menu1 < 0 || menu1 > 6);

	if(menu1 == 1) // Doc du lieu tu tap tin vao cay
	{
		char s[50];
		fflush(stdin);
		printf("\nHay nhap vao duong dan den tap tin can doc: ");
		gets(s);

		FILE *FileIn = fopen(s, "r");

		if(FileIn == NULL)
		{
			printf("\nKhong tim thay tap tin co duong dan la: %s. Nhan enter de tro ve Menu chinh", s);
			getch();
		}
		else
		{
			TaoCayTuTapTin(Root, FileIn);

			if(Root != NULL)
				printf("\nCay da duoc tao thanh cong. Nhan enter de tro ve Menu chinh", Root->Data);
			else
				printf("\nCay khong duoc tao do tap tin khong co du lieu. Nhan enter de tro ve Menu chinh");

			getch();

			fclose(FileIn); // chỉ giải phóng tập tin khi tập tin có tồn tại
		}

		system("cls"); // xóa hết màn hình đi
		goto menucha;
	}
	else if(menu1 == 2) // Them Node vao cay (du lieu nhap vao tu ban phim)
	{
		TaoCayNhapTuBanPhimKhongBietTruocSoLuong(Root);
		system("cls"); // xóa hết màn hình đi
		goto menucha;
	}
	else if(menu1 == 3) // Tim kiem Node
	{
		int x;
		printf("\nNhap vao gia tri can tim kiem: ");
		scanf("%d", &x);

		NODE *p = TimKiemNode_KhuDeQuy(Root, x);

		if(p != NULL)
		{
			if(p->Data == x)
				printf("\nTim thay Node co chua gia tri %d trong cay. Nhan enter de tro ve Menu chinh", x);
			else
				printf("\nCay khong ton tai Node co chua gia tri %d. Nhan enter de tro ve Menu chinh", x);
		}
		else
			printf("\nCay khong ton tai thi lay gi ma tim kiem. Nhan enter de tro ve Menu chinh");

		getch();
		system("cls"); // xóa hết màn hình đi
		goto menucha;
	}
	else if(menu1 == 4) // Xoa Node
	{
		int x;
		printf("\nNhap vao gia tri can xoa khoi cay: ");
		scanf("%d", &x);

		int ketqua = XoaNodeTrongCay_KhuDeQuy(Root, x);

		if(ketqua == 1)
			printf("\nDa xoa thanh cong Node co gia tri %d. Nhan enter de tro ve Menu chinh", x);
		else if(ketqua == 0)
			printf("\nKhong xoa duoc do khong tim thay Node co gia tri %d o trong cay. Nhan enter de tro ve Menu chinh", x);

		getch();
		system("cls"); // xóa hết màn hình đi
		goto menucha;
	}
	else if(menu1 == 5) // Duyet cay
	{
		int menu2;

menucon:
		do{
			printf("\n===============> Menu <===============\n");
			printf("\n1. Duyet Node - Left - Right (NLR)");
			printf("\n2. Duyet Node - Right - Left (NRL)");
			printf("\n3. Duyet Left - Node - Right (LNR)");
			printf("\n4. Duyet Right - Node - Left (RNL)");
			printf("\n5. Duyet Left - - Right - Node (LRN)");
			printf("\n6. Duyet Right - Left - Node (RLN)");
			printf("\n7. Duyet theo chieu rong (Left -> Right)");
			printf("\n8. Duyet theo chieu rong (Right -> Left)");
			printf("\n0. Tro ve lai Menu chinh ban dau");
			printf("\n======================================\n");

			printf("\nNhap vao lua chon (0 -> 8): ");
			scanf("%d", &menu2);

			if(menu2 < 0 || menu2 > 8)
			{
				printf("\nLua chon chi duoc trong khoang 0 -> 8. Nhan enter nhap lai!");
				getch();
				system("cls");
			}
		}while(menu2 < 0 || menu2 > 8);

		if(menu2 == 1) // Duyet Node - Left - Right (NLR)
		{
			printf("\nDuyet Node - Left - Right (NLR): ");
			DuyetCayKhongDeQuyKhongStack(Root, "NLR");
		}
		else if(menu2 == 2) // Duyet Node - Right - Left (NRL)
		{
			printf("\nDuyet Node - Right - Left (NRL): ");
			DuyetCayKhongDeQuyKhongStack(Root, "NRL");
		}
		else if(menu2 == 3) // Duyet Left - Node - Right (LNR)
		{
			printf("\nDuyet Left - Node - Right (LNR): ");
			DuyetCayKhongDeQuyKhongStack(Root, "LNR");
		}
		else if(menu2 == 4) // Duyet Right - Node - Left (RNL)
		{
			printf("\nDuyet Right - Node - Left (RNL): ");
			DuyetCayKhongDeQuyKhongStack(Root, "RNL");
		}
		else if(menu2 == 5) // Duyet Left - - Right - Node (LRN)
		{
			printf("\nDuyet Left - - Right - Node (LRN): ");
			DuyetCayKhongDeQuyKhongStack(Root, "LRN");
		}
		else if(menu2 == 6) // Duyet Right - Left - Node (RLN)
		{
			printf("\nDuyet Right - Left - Node (RLN): ");
			DuyetCayKhongDeQuyKhongStack(Root, "RLN");
		}
		else if(menu2 == 7) // Duyet theo chieu rong (Left -> Right)
		{
			printf("\nDuyet theo chieu rong (Left -> Right): ");
			DuyetTheoChieuRong(Root);
		}
		else if(menu2 == 8) // Duyet theo chieu rong (Right -> Left)
		{
			printf("\nDuyet theo chieu rong (Right -> Left): ");
			DuyetTheoChieuRong(Root, 2);
		}
		else if(menu2 == 0)
		{
			system("cls"); // xóa hết màn hình đi
			goto menucha;
		}

		printf("\nNhan enter de quay tro lai Menu phep duyet");
		getch();
		system("cls"); // xóa hết màn hình đi
		goto menucon;
	}
	else if(menu1 == 6) // Giai phong cay
	{
		GiaiPhongCay_KhuDeQuy(Root);

		if(Root == NULL)
			printf("\nCay duoc giai phong thanh cong. Nhan enter de tro ve Menu chinh");
		else
			printf("\nCay chua duoc giai phong vi ly do gi do. Nhan enter de tro ve Menu chinh");

		getch();
		system("cls"); // xóa hết màn hình đi
		goto menucha;
	}
	else if(menu1 == 0) // Thoat chuong trinh => phải giải phóng cây
	{
		GiaiPhongCay_KhuDeQuy(Root);

		if(Root == NULL)
			printf("\nCay duoc giai phong thanh cong truoc khi thoat chuong trinh");
		else
			printf("\nCay chua duoc giai phong truoc khi thoat chuong trinh vi ly do gi do");
	}
}

int main()
{
	Menu();

	getch();
	return 0;
}