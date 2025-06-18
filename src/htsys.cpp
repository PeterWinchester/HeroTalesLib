/* htsys.cpp
   Created - 2025/2/6
*/

#include "htsys.h"

int restricted_input_int(int arg_l, int arg_r) {
	int x = input_int_safely();
	while (x < arg_l || x > arg_r) {
		printf("输入的数字超出了范围！\n");
		x = input_int_safely();
	}
	return x;
}

int input_int_safely() {
	std::string str_input;  // 输入的字符串
	int res = 0;            // 返回的数值

	while (1) {
		getline(std::cin, str_input); // 读取一整行字符串并存储到 str_input 中

		bool str_is_valid = true; // 检查是否通过
		for (int i = 0; i < str_input.length(); i++) {
			if (str_input[i] >= '0' && str_input[i] <= '9') continue;
			str_is_valid = false; // 发现非数字字符，则检查不通过
			break;
		}
		
		if (str_is_valid) break;             // 检查通过则退出循环
		else printf("输入不规范，请重新输入："); // 检查不通过继续输入
	}

	for (int i = 0; i < str_input.length(); i++) res = res * 10 + str_input[i] - '0'; // 计算数值
	return res;
}

#ifdef __linux__
int _getch() {
	termios tm, tm_old;
	int fd = 0, ch;

	// 保存现在的终端设置
	if (tcgetattr(fd, &tm) < 0) return -1;
	tm_old = tm;
	
	cfmakeraw(&tm); // 更改终端设置为原始模式，该模式下所有的输入数据以字节为单位被处理
	if (tcsetattr(fd, TCSANOW, &tm) < 0) return -1; // 使用更改之后的设置

	ch = getchar();

	if (tcsetattr(fd, TCSANOW, &tm_old) < 0) return -1; // 更改设置为最初的样子
	
	return ch;
}
#endif // __linux__

void ClearScreen() {
#ifdef _WIN32
	system("cls");
#endif // _WIN32
	
#ifdef __linux__
	system("clear");
#endif // __linux__
}

void SetColor(int arg_color) {
#ifdef _WIN32
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), arg_color);
#endif // _WIN32

#ifdef __linux__
	int background_color = arg_color / 16 * 16, foreground_color = arg_color % 16;
	if (background_color == HT_BCOLOR_BLACK) std::cout << "\033[40m";
	switch (foreground_color) {
	case HT_FCOLOR_PURPLE:
		std::cout << "\033[35m";
	case HT_FCOLOR_RED:
		std::cout << "\033[31m";
		break;
	case HT_FCOLOR_WHITE:
		std::cout << "\033[37m";
		break;
	case HT_FCOLOR_YELLOW:
		std::cout << "\033[33m";
		break;
	}
#endif // __linux__
}

void Pause() {
	printf("Press any key to continue...");
	_getch();
	printf("\n");
}