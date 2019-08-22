#include"MyFunction.h"

int main()
{
	resizeConsole(1600, 800);
	//=============================================================KHAI BÁO BIẾN======================================================================
	char exit;
	//==========================================================BẮT ĐẦU CHƯƠNG TRÌNH==================================================================
	do
	{
		system("cls");
		exit = 'N';
		GameProgramme::readFile("Guide.dat", Color(10));
		GameProgramme GP;
		GP.Run();
		std::cout << "Press Y to continue or others key to exit" << std::endl;
		std::cin >> exit;
	} while (exit == 'Y' || exit == 'y');

	_getch();
	return 0;
}