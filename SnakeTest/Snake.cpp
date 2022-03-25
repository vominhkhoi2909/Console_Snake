//Khai báo các thư viện cần thiết.
#include<stdio.h>
#include<conio.h>
#include<time.h>
#include<Windows.h>
#include <iostream>
#include<string.h>
using namespace std;

//Định nghĩa chiều ngang, chiều dọc của map.
#define Width 50
#define Heigh 23

//Hàm đổi màu ký tự.
void TextColor(int color)
{
	//Màu trắng: 7
	//Màu xanh lá: 10
	//Màu tím nhạt: 13
	//Màu tím đậm: 5

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

//Hàm làm mới.
void clrscr(void)
{
	CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
	HANDLE hConsoleOut;
	COORD Home = { 0,0 };
	DWORD dummy;

	hConsoleOut = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(hConsoleOut, &csbiInfo);

	FillConsoleOutputCharacter(hConsoleOut, ' ', csbiInfo.dwSize.X * csbiInfo.dwSize.Y, Home, &dummy);
	csbiInfo.dwCursorPosition.X = 0;
	csbiInfo.dwCursorPosition.Y = 0;
	SetConsoleCursorPosition(hConsoleOut, csbiInfo.dwCursorPosition);
}

//Hàm di chuyển tới tọa độ XY.
void gotoXY(short x, short y)
{
	HANDLE hConsoleOutput;
	COORD Cursor_an_Pos = { x,y };
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsoleOutput, Cursor_an_Pos);
}

//Xét tên cho hướng điều khiển.
enum Status { Up, Down, Left, Right };

//Tạo các biến giá trị.
struct Position
{
	int x, y;
};

struct Snake
{
	Position dot[50];
	int n;
	Status tt;
};

struct Item
{
	Position pos;
};

//Tạo rắn và mồi.
void Create(Snake& snake, Item& item)
{
	snake.n = 1;
	snake.dot[0].x = 1;
	snake.dot[0].y = 1;
	snake.tt = Down;
	item.pos.x = 7;
	item.pos.y = 7;
}

//Vẽ bản đồ
void Map(int map) {

	TextColor(7);

	//Basic map - ID map: 1.
	{
		//Vẽ cột ngang dưới.
		for (int i = 0; i <= Width + 1; i++)
		{
			gotoXY(i, Heigh);
			putchar(219);
		}
		// Vẽ cột ngang trên.
		for (int i = 0; i <= Width; i++)
		{
			gotoXY(i, 0);
			putchar(219);
		}
		//Vẽ cột dọc trái.
		for (int i = 0; i < Heigh; i++)
		{
			gotoXY(51, i);
			putchar(219);
		}
		//Vẽ cột dọc phải.
		for (int i = 0; i < Heigh; i++)
		{
			gotoXY(0, i);
			putchar(219);
		}
	}
	
	//Map có hcn giữa - ID map: 2.
	{
		if (map == 2)
		{
			//Vẽ chữ nhất ở giữa map.
			for (int i = 10; i < 14; i++)
			{
				for (int j = 20; j < 31; j++)
				{
					gotoXY(j, i);
					putchar(219);
				}
			}
		}
	}
	
	//Map có hcn giữa và 4 L 4 góc - ID map: 3.
	{
		if (map == 3)
		{
			//Vẽ chữ nhất ở giữa map.
			for (int h = 11; h <= 13; h++)
			{
				for (int w = 21; w <= 30; w++)
				{
					gotoXY(w, h);
					putchar(219);
				}
			}

			//Vẽ chữ L trên trái.
			for (int w = 5; w <= 9; w++)
			{
				gotoXY(w, 5);
				putchar(219);
			}
			for (int h = 6; h <= 8; h++)
			{
				gotoXY(5, h);
				putchar(219);
			}

			//Vẽ chữ L trên phải.
			for (int w = 42; w <= 46; w++)
			{
				gotoXY(w, 5);
				putchar(219);
			}
			for (int h = 6; h <= 8; h++)
			{
				gotoXY(46, h);
				putchar(219);
			}

			//Vẽ chữ L dưới trái.
			for (int w = 5; w <= 9; w++)
			{
				gotoXY(w, 19);
				putchar(219);
			}
			for (int h = 16; h <= 18; h++)
			{
				gotoXY(5, h);
				putchar(219);
			}

			//Vẽ chữ L dưới phải.
			for (int w = 42; w <= 46; w++)
			{
				gotoXY(w, 19);
				putchar(219);
			}
			for (int h = 16; h <= 18; h++)
			{
				gotoXY(46, h);
				putchar(219);
			}
		}
	}
	
}

//Hiển thị map, rắn và item.
void Show(Snake snake, Item item, int map)
{
	clrscr();	
	Map(map);
	TextColor(10);
	gotoXY(item.pos.x, item.pos.y);
	putchar('O');
	TextColor(13);
	gotoXY(snake.dot[0].x, snake.dot[0].y);
	putchar(2);
	for (int i = 1; i < snake.n; i++)
	{
		gotoXY(snake.dot[i].x, snake.dot[i].y);
		putchar('O');
	}
}

//Điều khiển di chuyển rắn.
void Control(Snake& snake)
{
	//trang thai cua tung dot
	for (int i = snake.n - 1; i > 0; i--)
		snake.dot[i] = snake.dot[i - 1];
	if (_kbhit())
	{
		int key = _getch();
		//dieu khien cai dau snake
		if (key == 'a' || key == 'A')
			snake.tt = Left;
		else
			if (key == 'w' || key == 'W')
				snake.tt = Up;
			else
				if (key == 'S' || key == 's')
					snake.tt = Down;
				else
					if (key == 'd' || key == 'D')
						snake.tt = Right;
	}
	if (snake.tt == Up)
		snake.dot[0].y--;
	else if (snake.tt == Down)
		snake.dot[0].y++;
	else if (snake.tt == Left)
		snake.dot[0].x--;
	else if (snake.tt == Right)
		snake.dot[0].x++;
}

//Xử lý rắn và item.
int Action(Snake& snake, Item& item, int& thoigian, int map)
{	
	//Biến lưu tọa độ tường dựa theo map.
	Position map2[30], map3[32];

	//Kiểm tra map và lưu tọa độ các tường.
	if (map >= 2)
	{
		int i = 0;
		for (int h = 11; h <= 13; h++)
		{
			for (int w = 21; w <= 30; w++)
			{
				map2[i].x = w;
				map2[i].y = h;
			}
			i++;
		}
	}

	if (map == 3)
	{
		//Biến đếm thứ tự mảng.
		int i = 0;

		//Tọa độ L trên trái.
		for (int h = 6; h <= 8; h++)
		{
			for (int w = 5; w <= 9; w++)
			{
				map2[i].x = w;
				map2[i].y = h;
			}
			i++;
		}

		//Tọa độ L trên phải.
		for (int h = 6; h <= 8; h++)
		{
			for (int w = 42; w <= 46; w++)
			{
				map2[i].x = w;
				map2[i].y = h;
			}
			i++;
		}

		//Tọa độ L dưới trái.
		for (int h = 16; h <= 18; h++)
		{
			for (int w = 5; w <= 9; w++)
			{
				map2[i].x = w;
				map2[i].y = h;
			}
			i++;
		}

		//Tọa độ L dưới phải.
		for (int h = 16; h <= 18; h++)
		{
			for (int w = 42; w <= 46; w++)
			{
				map2[i].x = w;
				map2[i].y = h;
			}
			i++;
		}
	}

	//Xử lý khi va chạm map.
	if (snake.dot[0].x <= 0 || //Va chạm trục ngang trên.
		snake.dot[0].x >= Width + 1 || //Va chạm trục ngang dưới.
		snake.dot[0].y <= 0 || //Va chạm trục học trái.
		snake.dot[0].y >= Heigh) //Va chạm trục dọc phải.
				return -1;

	if (map >= 2) 
	{
		//Xét dựa theo mảng.
		/*for (int i = 0; i < 11; i++)
		{
			if (map2[i].x == snake.dot[0].x && map2[i].y == snake.dot[0].y)
			{
				return -1;
			}
		}
		for (int i = 19; i < 30; i++)
		{
			if (map2[i].x == snake.dot[0].x && map2[i].y == snake.dot[0].y)
			{
				return -1;
			}
		}*/
		
		if ((snake.dot[0].x >=20 && snake.dot[0].x <= 30 && snake.dot[0].y == 10) || //Va chạm trục ngang dưới.
			((snake.dot[0].x == 20 || snake.dot[0].x == 30) && snake.dot[0].y == 11) ||
			((snake.dot[0].x == 20 || snake.dot[0].x == 30) && snake.dot[0].y == 12) ||
			(snake.dot[0].x >= 20 && snake.dot[0].x <= 30 && snake.dot[0].y == 13)) //Va chạm trục dọc phải.
			return -1;
	}

	if (map == 3)
	{
		for (int i = 0; i < 32; i++)
		{
			if (map3[i].x == snake.dot[0].x && map3[i].y == snake.dot[0].y)
			{
				return -1;
			}
		}
	}

	//Vòng lặp dùng để kiểm tra xem rắn có cắn phải đốt của bản thân không.
	for (int i = 1;i < snake.n;i++)
		if (snake.dot[0].x == snake.dot[i].x && snake.dot[0].y == snake.dot[i].y)
			return -1;

	//Kiểm tra rắn va chạm item.
	if (snake.dot[0].x == item.pos.x && snake.dot[0].y == item.pos.y)
	{
		for (int i = snake.n; i > 0; i--)
			snake.dot[i] = snake.dot[i - 1];

		snake.n++;
		if (snake.tt == Up)
			snake.dot[0].y--;
		else if (snake.tt == Down)
			snake.dot[0].y++;
		else if (snake.tt == Left)
			snake.dot[0].x--;
		else if (snake.tt == Right)
			snake.dot[0].x++;

		//Nếu item trùng vị trí tường sẽ quay lại bước này.
		reset_item:

		//Tạo tọa độ mới cho item.
		item.pos.x = 1 + rand() % Width;
		item.pos.y = 1 + rand() % (Heigh - 1);

		//Kiểm tra tọa độ item với tường.
		if (map >= 2) 
		{
			for (int i = 0; i < 30; i++) 
			{
				if (map2[i].x == item.pos.x && map2[i].y == item.pos.y) 
				{
					goto reset_item;
				}
			}
		}

		if (map == 3)
		{
			for (int i = 0; i < 32; i++)
			{
				if (map3[i].x == item.pos.x && map3[i].y == item.pos.y)
				{
					goto reset_item;
				}
			}
		}

		if (thoigian > 50)
			thoigian -= 5;
	}

}

int main()
{
	//Tạo các biến lưu lựa chọn.
	int lc, lcl, lcm;

	new_Game:

	TextColor(7);
	system("cls");
	//Thoại thông báo chơi game.
	{
		cout << "\nChoi Game Vui Ve Khong Quao :))\n";
		cout << "\n1. Choi game.\n";
		cout << "2. Out.\n";
		cout << "\nP/S: Nhap 1 hoac 2 sau do Enter.";
		cout << "\nLua chon : ";
	}
	
	cin >> lc;

	if (lc == 1) {
		system("cls");
		int ma;
		int thoigian;

		//Thoại thông báo chọn độ khó của game.
		{
			cout << "\nChoose Map.\n";
			cout << "\n1. Map 1 - Basic.";
			cout << "\n2. Map 2 - HCN.";
			cout << "\n1. Map 3 - .... (Map dang lo^i~)\n";
			cout << "\nP/S: Nhap 1, 2 hoac 3 sau do Enter.";
			cout << "\nLua chon : ";
		}
		cin >> lcm;

		//Thoại thông báo chọn độ khó của game.
		{
			cout << "\nChoose Level.\n";
			cout << "\n1. Ez game.";
			cout << "\n2. Normal.";
			cout << "\n3. Try hard game.\n";
			cout << "\nP/S: Nhap 1, 2 hoac 3 sau do Enter.";
			cout << "\nLua chon : ";
		}
		cin >> lcl;

		//Kiểm tra lựa chọn level từ người chơi để xét thời gian làm mới tương ứng.
		switch (lcl)
		{
			case 1:
				thoigian = 300;
				break;
			case 2:
				thoigian = 180;
				break;
			default: thoigian = 50;
				break;
		}

		//Khởi tạo bộ số ngẫu nhiên.
		srand(time(NULL));

		//Khới tạo các đối tượng.
		Item item;
		Snake snake;
		Create(snake, item);

		//Vòng lặp để làm mới các đối tượng, vòng lặp dừng khi rắn xảy ra va chạm map.
		while (1)
		{
			//Gọi hàm để hiển thị map, rắn và item.
			Show(snake, item, lcm);

			//Thông tin trò chơi.
			{
				TextColor(10);
				gotoXY(Width + 3, 2);
				cout << ("Control = WASD / wasd.");
				gotoXY(Width + 3, 4);
				cout << ("Khi thua an phim bat ky");
				gotoXY(Width + 3, 5);
				cout << ("de quay tro lai.");
				gotoXY(Width + 3, 7);
				cout << ("Created/Updated by V.M.K");
			}			

			//Gọi hàm điều khiển rắn.
			Control(snake);

			//Gọi hàm xử lý rắn khi di chuyển.
			ma = Action(snake, item, thoigian, lcm);

			//Kiểm tra va chạm rắn map sau action.
			if (ma == -1) //thua
			{
				//Thông báo thua.
				{
					gotoXY(Width / 2 - 1, (Heigh / 2) + 1);
					cout << ("LOSE");
					while (_getch() != 13);
					break;
				}				
			}

			//Độ làm mới game.
			Sleep(thoigian);
		}

		//Xuất thông báo thua.
		{
			system("cls");
			cout << "\nCon non va xanh lam :)) \n";
			_getch();
		}
	}

	//Quay về màn hình new game.
	goto new_Game;

	//Out game.
	{
		system("cls");
		cout << "\nLOL Chua choi da xoan ;p \n";
		_getch();
		return 0;
	}	
}