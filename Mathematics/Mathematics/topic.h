#pragma once
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <istream> 
#include <stack>

#define EXERCISEFILE	"exercisefile.txt"
#define ANSWERFILE		"answerfile.txt"
#define GRADE			"grade.txt"
#define MAX_LENGTH		20000
using namespace std;

const int maxn = 100;

typedef enum Status
{
	ERROR = 0, SUCCESS = 1
} Status;

typedef struct variable
{
	int num_or_Symbol;		 //0是数字1是符号
	int Symbol = -1;		//    + - * % ( ) 分别表示为 0 1 2 3 4 5
	int numer;				//如果是数字此为分子
	int Den = 1;			//如果是数字此为分母
	int num;

	bool operator == (variable c){
		return num_or_Symbol == c.num_or_Symbol && Symbol == c.Symbol && numer == c.numer && Den == c.Den && num == c.num;
	}
}var;

/**
 *  @name			Status Create(var* exp, int size)
 *	@description	生成表达式函数
 *	@param			exp		表达式数组
 *					size	表达式内数值的大小
 *					length	表达式结构体的长度
 *	@return			ERROR  SUCCESS
 *  @notice			none
 */
Status Create(var** exp, int size, int *length);

/**
 *  @name			Status Calculation(var *exp, int size, var *result);
 *	@description	计算表达式函数
 *	@param			exp		表达式数组
 *					size	表达式内数值的大小，以及计算过程中数值的大小
 *					result	表达式的返回值
 *					length	表达式结构体的长度
 *	@return			ERROR  SUCCESS
 *  @notice			none
 */
Status Calculation(var* exp, int size, var* result, int length);

/**
 *  @name			void visit(var* expression, int length);
 *	@description	输出表达式
 *	@param			expression		表达式数组
 *					length			表达式结构体的长度
 *					num				题目题号
 *	@return			none
 *  @notice			none
 */
void Visit(var* expression, int length, int num);

/**
 *  @name			void M_instructions(var* expression, int amount, int size);
 *	@description	m指令的执行
 *	@param			expression		表达式数组
 *					amount			表达式数量
 *					size			计算数的取值范围
 *	@return			none
 *  @notice			none
 */
void M_instructions(var** expression, int amount, int size, var* result);

/**
 *  @name			void Destrory(var** expression, var* result, int amount);
 *	@description	销毁分配的内存
 *	@param			expression		表达式数组
 *					amount			表达式数量
 *					result			保存结果的结构体数组
 *	@return			none
 *  @notice			none
 */
void Destrory(var** expression, var* result, int amount);

/**
 *  @name			void Correction(int* save, char* instructions);
 *	@description	判断对错
 *	@param			save			保存正确或错误的数组
 *					answerfile		答案文件路径
 *					exercisefile	题目文件路径
 *	@return			none
 *  @notice			none
 */
void Correction(int* save, char* answerfile, char* exercisefile);


/**
 *  @name			Status Infix_to_Postfix(var* p, int size, var* Postfix, int length, int& postLen);
 *	@description	中缀表达式转后缀表达式
 *	@param			p		结构体数组形式的表达式
 *					size	表达式内数值的大小，以及计算过程中数值的大小
 *					Postfix	返回的后缀表达式
 *					length	表达式 p 的长度
 *					postLen	后缀表达式的长度
 *	@return			ERROR SUCCESS
 *  @notice			none
 */
Status Infix_to_Postfix(var* p, int size, var* Postfix, int length, int& postLen);

/**
 *  @name			bool priority(var p);
 *	@description	返回运算符的优先级
 *	@param			element	一个运算符
 *	@return			优先级级别 ()  +-  *÷ 分别对应 0 1 2
 *  @notice			none
 */
int prio(var element);

/**
 *  @name			void preprocess(var &a, var &b);
 *	@description	将两个分数通分
 *	@param			a	操作数
 *					b	操作数
 *	@return			ERROR SUCCESS
 *  @notice			none
 */
void preprocess(var& a, var& b);

/**
 *  @name			Status calc(var* Postfix, int length, var &ans);
 *	@description	计算后缀表达式的值
 *	@param			Postfix		后缀表达式
 *					length		后缀表达式的长度
 *					ans			表达式的计算结果
 *	@return			ERROR SUCCESS
 *  @notice			none
 */
Status calc(var* Postfix, int length, var& ans);

/**
 *  @name			void display(var* a);
 *	@description	打印单个操作数
 *	@param			a	操作数
 *	@return
 *  @notice			none
 */
void display(var* a);

/**
 *  @name			Status operate(var a, var b, var oper, var &ret);
 *	@description	执行加减乘除的操作并对结果进行化简
 *	@param			a		操作数
 *					b		操作数
 *					oper	运算符
 *					ret		结果
 *	@return			ERROR SUCCESS
 *  @notice			none
 */
Status operate(var a, var b, var oper, var& ret);

/**
 *  @name			Status get_Subexpression(var* Postfix, int length, var ans[][3], int& sta_size);
 *	@description	由后缀表达式 获取 后缀子表达式
 *	@param			Postfix		后缀表达式
 *					length		后缀表达式的长度
 *					ans			后缀子表达式
 *					sta_size	后缀子表达式的个数
 *	@return			ERROR  SUCCESS
 *  @notice			none
 */
Status get_Subexpression(var* Postfix, int length, var ans[][3], int& sta_size);

/**
 *  @name			bool cmp(var a[], var b[]);
 *	@description	判断两个后缀子表达式是否等价
 *	@param			a		后缀子表达式1
 *					b		后缀子表达式2
 *	@return			ERROR  SUCCESS
 *  @notice			none
 */
bool cmp(var a[], var b[]);

/**
 *  @name			Status is_same(var* Question, int lenQuest, var* newQuestion, int lenNewQuest, int size);
 *	@description	判断两个问题是否等价
 *	@param			Question		原题库中的一个表达式
 *					lenQuest		原题库中的一个表达式的长度
 *					newQuestion		新生成的表达式
 *					lenNewQuest		新生成的表达式的长度
 *					size			表达式内数值的大小，以及计算过程中数值的大小
 *	@return			ERROR  SUCCESS
 *  @notice			none
 */
Status is_question_same(var* Question, int lenQuest, var* newQuestion, int lenNewQuest, int size);

