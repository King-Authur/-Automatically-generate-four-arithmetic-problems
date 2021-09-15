
#include <iostream>
#include "topic.h"
	
var result[MAX_LENGTH];
var *expression[MAX_LENGTH];//表达式
int save[MAX_LENGTH];

int main()
{
	int amount; //表达式数量
	int size = 10;	//计算数的取值范围
	int n;
	char instructions[300];//存储指令
	srand((int)time(0));
	cout << "注：运算数大小默认为小于10的正自然数，可使用指令更改为任意大于0小于2147483647的整数！\n" ;
	cout << "    可同时生成的运算式子最大值为" << MAX_LENGTH<< "!\n";
	cout << "    输入指令长度最大值为300！\n";
	while (1)
	{
		cout << "Myapp.exe ";
		cin.get(instructions, 300);
		getchar();
		if (instructions[0] == '-')
		{
			int i, j;
			switch (instructions[1])
			{
				case 'n'://控制生成题目的个数
					n = 2;
					while (instructions[n] == ' ' && n < 300) n++;
					if (n == 2 || n == 300)
					{
						cout << "指令输入有误，请重新输入！\n";
						break;
					}
					i = 10;
					amount = 0;
					while (instructions[n] != '\0' && instructions[n] >= '0' && instructions[n] <= '9' && n < 300)
					{
						j = instructions[n] - '0';
						amount =  j + amount * i;
						n++;
					}
					if (amount < 1 && n == 300 && amount > MAX_LENGTH)
					{
						cout << "数据输入有误，请重新输入！\n";
						break;
					}
					remove(EXERCISEFILE);
					remove(ANSWERFILE);
					M_instructions(expression, amount, size, result);
					Destrory(expression, result, amount);
					break;
				case 'r'://控制题目中数值（自然数、真分数和真分数分母）的范围
					n = 2;
					while (instructions[n] == ' ' && n < 300) n++;
					size = 0;
					if (n == 2 || n == 300)
					{
						cout << "指令输入有误，请重新输入！\n";
						break;
					}
					while (instructions[n] != '\0' && instructions[n] >= '0' && instructions[n] <= '9' && n < 300)
					{
						size = instructions[n] - '0' + size * 10;
						n++;
					}
					if (size <= 0 || n == 300)
					{
						size = 10;
						cout << "数据输入有误，请重新输入！\n";
					}
					break;
				case 'e':
					char exercisefile[100];
					char answerfile[100];
					n = 2;
					while (instructions[n] == ' ' && n < 300) n++;
					if (n == 2)
					{
						cout << "指令输入有误，请重新输入！\n";
						break;
					}
					i = n;
					while (instructions[n] != ' ' && n - i < 100 && n < 300 && instructions[n] != '\0')
					{
						exercisefile[n - i] = instructions[n];
						n++;
					}
					exercisefile[n - i] = '\0';
					while (instructions[n] == ' ' && n < 300) n++;
					if(instructions[n] != '-' || instructions[n + 1] != 'a')
					{
						cout << "指令输入有误，请重新输入！\n";
						break;
					}
					n = n + 2;
					i = n;
					while (instructions[n] == ' ' && n < 300) n++;
					if(i == n)
					{
						cout << "指令输入有误，请重新输入！\n";
						break;
					}
					i = n;
					while (instructions[n] != ' ' && n - i < 100 && n < 300 && instructions[n] != '\0')
					{
						answerfile[n - i] = instructions[n];
						n++;
					}
					answerfile[n - i] = '\0';
					if (n == 300)
					{
						cout << "指令输入过长，请重新输入！\n";
						break;
					}
					Correction(save, answerfile, exercisefile);
					break;
				default:
					cout << "指令输入有误，请重新输入！\n";
					break;
			}
		}
		else
		{
			cout << "指令输入有误，请重新输入！\n";
		}
	}
	return 0;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件

