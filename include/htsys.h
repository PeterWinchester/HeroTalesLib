/* htsys.h
   Created - 2025/2/6
*/

#ifndef HTSYS_H
#define HTSYS_H

#define HT_BCOLOR_BLACK  0x00 // 背景黑色
#define HT_FCOLOR_RED    0x0c // 前景红色
#define HT_FCOLOR_PURPLE 0x0d // 前景紫色
#define HT_FCOLOR_YELLOW 0x0e // 前景黄色
#define HT_FCOLOR_WHITE  0x0f // 前景白色

#include <iostream>
#include <string>
#include <cstdio>

// 此头文件为 linux 专用
#ifdef __linux__
#include <termio.h>
#endif // __linux__

// 此头文件为 Windows 专用
#ifdef _WIN32
#include <windows.h>
#include <conio.h>
#endif // _WIN32

// 此函数保证输入的整数在 arg_l ~ arg_r 范围内
int restricted_input_int(int, int);

/* input_int_safely 函数用于安全地输入 int 型的整数。
   由于 scanf 函数读取整数时，如果读到数字和加减号以外的可见字符会导致程序崩溃，所以重新写一个函数用于安全地读取非负
   整数。（非负整数能够满足 Hero Tales 的功能需求。）
   input_int_safely 函数先读取一行字符串，然后检查读入的字符串是否全为数字字符，若存在数字字符以外的字符，则检查不通
   过，需要重新输入。最后从将输入的规范字符串转换成数字返回。
   注意：input_int_safely 函数只支持一行输入一个数字。
*/
int input_int_safely();

// linux 系统没有 _getch 函数，需要自己定义
#ifdef __linux__
int _getch();
#endif // __linux__

// 清空屏幕
void ClearScreen();

// 设置显示文字的颜色
// 参数 arg_color 取值用 htsys.h 中定义好的宏
void SetColor(int arg_color);

// 暂停
void Pause();

#endif // HTSYS_H
