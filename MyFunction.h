#ifndef __MY_FUNCTION_H__
#define __MY_FUNCTION_H__

#include"Vector2.h"
#include"Color.h"
#include<fstream>
#include<vector>
#include<minmax.h>
#include<conio.h>
#include<Windows.h>
//------------------------------------------------------------DEFINE--------------------------------------------------------------
#define WIDTH_BOARD 10
#define HEIGHT_BOARD 6
#define RAT_COLOR 95
#define LAMP_COLOR 252
#define PAINT_COLOR 207
#define BLOCK_COLOR 224
#define BOARD_COLOR	159
//-------------------------------------------------------------ENUM--------------------------------------------------------------
enum Move{ UP, DOWN, LEFT, RIGHT, STOP };
//----------------------------------------------------------WinDOWS.H------------------------------------------------------------
void gotoXY(const int &x, const int &y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
void resizeConsole(const int &width, const int &height)
{
	HWND console = GetConsoleWindow();
	RECT rect;
	GetWindowRect(console, &rect);
	MoveWindow(console, rect.left, rect.top, width, height, TRUE);
}
void textColor(const int &x)
{
	HANDLE color;
	color = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(color, x);
}
void drawChar(const int &x, const int &y, const char &c, const Color &color)
{
	gotoXY(x, y);
	textColor(color.m_code);
	std::cout << c;
	textColor(7);
	gotoXY(WIDTH_BOARD + 1, 0);
}
//------------------------------------------------------------STRUCT-------------------------------------------------------------
class Object
{
private:
	char m_shape;
	Vector2i m_position;
	Move m_move;
	Color m_color;
public:
	Object() { m_shape = ' '; m_move = STOP; }
	Object(const char &shape, const Vector2i &position, const Move &move, const Color &color)
		: m_shape(shape), m_position(position), m_move(move), m_color(color) {}
	~Object() {}

	void setShape(const char &shape) { m_shape = shape; }
	void setPosition(const Vector2i &position) { m_position = position; }
	void setMove(const Move &move) { m_move = move; }
	void setColor(const Color &color) { m_color = color; }

	char getShape() const { return m_shape; }
	Vector2i getPosition() const { return m_position; }
	Move getMove() const { return m_move; }
	Color getColor() const { return m_color; }

	void draw() { drawChar(m_position.m_x, m_position.m_y, m_shape, m_color); }
	void erase() { drawChar(m_position.m_x, m_position.m_y, ' ', Color::Black); }
	void move()
	{
		
		switch (m_move)
		{
		case UP:
			erase();
			if (m_position.m_y > 1)
				m_position.m_y--;
			draw();
			break;
		case DOWN:
			erase();
			if (m_position.m_y < HEIGHT_BOARD - 1)
				m_position.m_y++;
			draw();
			break;
		case LEFT:
			erase();
			if (m_position.m_x > 1)
				m_position.m_x--;
			draw();
			break;
		case RIGHT:
			erase();
			if (m_position.m_x < WIDTH_BOARD - 1)
				m_position.m_x++;
			draw();
			break;
		default:
			break;
		}
		m_move = STOP;
	}
};
class GameProgramme
{
private:
	Object Paint, Rat, Lamp; // Cây vẽ, Chuột, Đèn
	std::vector<Object> Blocks; // Mảng Vật cản
	std::vector<Vector2i> TempPath; // Mảng các tọa độ tạo thành một đường đi dẫn Chuột đến Đèn
	std::vector<std::vector<Vector2i>> Paths; // Tổng hợp tất cả các cách đi từ Chuột đến Đèn
	bool MatrixSet[HEIGHT_BOARD][WIDTH_BOARD]; // Ma trận check các Vật cản đã được vẽ chưa
	bool CheckPutRat, CheckPutLamp, CheckWin; // Check Chuột, Đèn đã được vẽ chưa, check Chuột đã chạy đến Đèn chưa

	//--- Check vị trí pos có tồn tại trong đường TempPath
	bool exist(const Vector2i &pos)
	{
		int size = TempPath.size();
		while (size--)
			if (TempPath[size] == pos)
				return true;
		return false;
	}
	//--- Tìm tất cả các cách đi từ Chuột đến Đèn
	void backTrackingFindAllPath(const Vector2i &startPos, const Vector2i &endPos)
	{
		// Neo
		if (startPos == endPos)
		{
			TempPath.push_back(startPos);
			Paths.push_back(TempPath);
			TempPath.pop_back();
			return;
		}
		// Đệ quy
		TempPath.push_back(startPos);
		Vector2i bottom, under, left, right;
		bottom = Vector2i(startPos.m_x, startPos.m_y - 1);
		under = Vector2i(startPos.m_x, startPos.m_y + 1);
		left = Vector2i(startPos.m_x - 1, startPos.m_y);
		right = Vector2i(startPos.m_x + 1, startPos.m_y);
		if (bottom.m_y > 0 && MatrixSet[bottom.m_y][bottom.m_x] == false && exist(bottom) == false)
			backTrackingFindAllPath(bottom, endPos);
		if (under.m_y < HEIGHT_BOARD && MatrixSet[under.m_y][under.m_x] == false && exist(under) == false)
			backTrackingFindAllPath(under, endPos);
		if (left.m_x > 0 && MatrixSet[left.m_y][left.m_x] == false && exist(left) == false)
			backTrackingFindAllPath(left, endPos);
		if (right.m_x < WIDTH_BOARD && MatrixSet[right.m_y][right.m_x] == false && exist(right) == false)
			backTrackingFindAllPath(right, endPos);
		TempPath.pop_back();
	}
	//--- Chỉ số của đường đi ngắn nhất trong tất cả các đường
	int iShortestPath()
	{
		int size = Paths.size() - 1, iShortest = size;
		while (size--)
		{
			if (Paths[size].size() < Paths[iShortest].size())
				iShortest = size;
		}
		return iShortest;
	}
	//--- Chỉ số của đường đi dài nhất trong tất cả các đường
	int iLongestPath()
	{
		int size = Paths.size() - 1, iLongest = size;
		while (size--)
		{
			if (Paths[size].size() > Paths[iLongest].size())
				iLongest = size;
		}
		return iLongest;
	}
	//--- Hiệu ứng cho Chuột chạy tới Đèn
	void ratFindLamp(const std::vector<Vector2i> &path)
	{
		int size = path.size();
		for (int i = 0; i < size; i++)
		{
			Rat.erase();
			Rat.setPosition(path[i]);
			Rat.draw();
			Sleep(200);
		}
	}
	//--- In đường đi ngắn nhất
	void displayShortestPath()
	{
		int iShortest = iShortestPath(), size = Paths[iShortest].size();
		std::cout << "SHORTEST PATH: ";
		for (int i = 0; i < size; i++)
			std::cout << Paths[iShortest][i].m_y << "-" << Paths[iShortest][i].m_x << "\t";
		std::cout << std::endl;
	}
	//--- In đường đi dài nhất
	void displayLongestPath()
	{
		int iLongest = iLongestPath(), size = Paths[iLongest].size();
		std::cout << "LONGEST PATH: ";
		for (int i = 0; i < size; i++)
			std::cout << Paths[iLongest][i].m_y << "-" << Paths[iLongest][i].m_x << "\t";
		std::cout << std::endl;
	}
	//--- In tất cả đường đi
	void displayAllPath()
	{
		int sizeY = Paths.size(), sizeX;
		for (int i = 0; i < sizeY; i++)
		{
			sizeX = Paths[i].size();
			std::cout << "PATH " << i + 1 << ": ";
			for (int j = 0; j < sizeX; j++)
				std::cout << Paths[i][j].m_y << "-" << Paths[i][j].m_x << "\t";
			std::cout << std::endl;
		}
		std::cout << std::endl;
	}
public:
	GameProgramme()
	{
		Paint = Object(' ', Vector2i(1, 1), STOP, Color(PAINT_COLOR));
		Rat = Object('R', Vector2i(WIDTH_BOARD + 1, 0), STOP, Color(RAT_COLOR));
		Lamp = Object('L', Vector2i(WIDTH_BOARD + 1, 0), STOP, Color(LAMP_COLOR));
		CheckPutRat = CheckPutLamp = CheckWin = false;
		Paint.draw();
		for (int i = 0; i < HEIGHT_BOARD; i++)
			for (int j = 0; j < WIDTH_BOARD; j++)
				MatrixSet[i][j] = false;
		// Đường biên
		for (int i = 0; i <= HEIGHT_BOARD; i++)
			for (int j = 0; j <= WIDTH_BOARD; j++)
				if (i == HEIGHT_BOARD || j == WIDTH_BOARD || i == 0 || j == 0)
					drawChar(j, i, ' ', Color(BOARD_COLOR));
	}
	~GameProgramme() {}

	static void readFile(const char *fileName, const Color &color)
	{
		char *buff = NULL; int n = 0;
		std::ifstream inFile(fileName);
		if (!inFile)
			std::cout << "Error read file" << std::endl;
		else
		{
			while (!inFile.eof())
			{
				buff = (char*)realloc(buff, n + 1);
				buff[n++] = inFile.get();
			}
		}
		n--; // Bỏ kí tự kết thúc file
		inFile.close();
		// Xuất
		for (int i = 0; i < n; i++)
		{
			textColor(color.m_code);
			std::cout << buff[i];
			textColor(7);
		}
		free(buff);
	}
	void Run()
	{
		char key;
		bool choose = true;
		while (true)
		{
			if (_kbhit())
			{
				key = _getch();
				switch (key)
				{
				case 'W':case 'w':
					Paint.setMove(UP);
					break;
				case 'S':case 's':
					Paint.setMove(DOWN);
					break;
				case 'A':case 'a':
					Paint.setMove(LEFT);
					break;
				case 'D':case 'd':
					Paint.setMove(RIGHT);
					break;
				case 'R':case 'r':
					if (CheckPutRat == false && MatrixSet[Paint.getPosition().m_y][Paint.getPosition().m_x] == false)
					{
						Rat.setPosition(Paint.getPosition());
						CheckPutRat = true;
					}
					break;
				case 'L':case 'l':
					if (CheckPutLamp == false && MatrixSet[Paint.getPosition().m_y][Paint.getPosition().m_x] == false)
					{
						Lamp.setPosition(Paint.getPosition());
						CheckPutLamp = true;
					}
					break;
				case 'B':case 'b':
					if (Paint.getPosition() != Rat.getPosition() && Paint.getPosition() != Lamp.getPosition())
					{
						Blocks.push_back(Object(' ', Paint.getPosition(), STOP, Color(BLOCK_COLOR)));
						MatrixSet[Blocks[Blocks.size() - 1].getPosition().m_y][Blocks[Blocks.size() - 1].getPosition().m_x] = true;
					}
					break;
				case 'M':case'm':
					gotoXY(0, HEIGHT_BOARD + 1);
					for (int i = 0; i < HEIGHT_BOARD; i++)
					{
						for (int j = 0; j < WIDTH_BOARD; j++)
							std::cout << MatrixSet[i][j];
						std::cout << std::endl;
					}
					break;
				case 'E':case'e': // Xóa
					if (Paint.getPosition() == Rat.getPosition())
						Rat = Object(), CheckPutRat = false;
					if (Paint.getPosition() == Lamp.getPosition())
						Lamp = Object(), CheckPutLamp = false;
					for (auto it = Blocks.begin(); it != Blocks.end(); it++)
					{
						if (Paint.getPosition() == it->getPosition())
						{
							Blocks.erase(it);
							MatrixSet[Paint.getPosition().m_y][Paint.getPosition().m_x] = false;
							break;
						}
					}
					break;
				case 'X':case 'x':
					backTrackingFindAllPath(Rat.getPosition(), Lamp.getPosition());
					gotoXY(0, HEIGHT_BOARD + 1); displayShortestPath();
					choose = true;
					break;
				case 'Y':case 'y':
					backTrackingFindAllPath(Rat.getPosition(), Lamp.getPosition());
					gotoXY(0, HEIGHT_BOARD + 1); displayLongestPath();
					choose = false;
					break;
				case 'F':case 'f':
					if (choose)
						ratFindLamp(Paths[iShortestPath()]);
					else
						ratFindLamp(Paths[iLongestPath()]);
					system("cls");
					CheckWin = true;
					break;
				default:
					break;
				}
			}
			if (CheckWin)
				break;
			if (CheckPutRat)
				Rat.draw();
			if(CheckPutLamp)
				Lamp.draw();
			for (int i = 0; i < Blocks.size(); i++)
				Blocks[i].draw();
			Paint.move();
			Sleep(100);
		}
	}
};

#endif