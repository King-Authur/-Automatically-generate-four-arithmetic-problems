#include "topic.h"

#define random(a, b) (rand() % ((b) - (a)) + (a))

Status Create(var** exp, int size, int* length) 
{
	var* expre;
	int mark_num = random(1, 4);//计算符个数
	int pre = 0;//前括号在第pre个数字前
	int aft = 0;//后括号在第aft个数字后
	int judge = 0;//判断，0写入数字，1写入符号
	int n = 0;
	*length = mark_num + mark_num + 1;
	n = 0;
	if (mark_num > 1)//如果运算符有3个，则存在括号
	{
		pre = random(1, mark_num);
		if(pre == 1)//不让括号括住整个式子
			aft = random((pre + 1), (mark_num + 1));
		else
			aft = random((pre + 1), (mark_num + 2));
		(*length) += 2;
		expre = new var[*length + 1];
		expre[pre * 2 - 2].num_or_Symbol = 1;
		expre[pre * 2 - 2].Symbol = 4;
		expre[aft * 2].num_or_Symbol = 1;
		expre[aft * 2].Symbol = 5;
	}
	else
	{
		expre = new var[*length + 1];
	}
	n = 0;
	while (n < *length)
	{
		if (expre[n].Symbol < 4)
		{
			if (judge == 0)
			{
				expre[n].num_or_Symbol = 0;
				expre[n].Den = random(2, size);
				expre[n].numer = random(0, expre[n].Den);
				expre[n].num = random(1, size);
				judge = 1;
			}
			else
			{
				expre[n].num_or_Symbol = 1;
				expre[n].Symbol = random(0, 4);
				judge = 0;
			}
		}
		n++;
	}
	*exp = expre;
	return SUCCESS;
}

void Visit(var* expression, int length, int num)
{
	fstream exercise;
	exercise.open(EXERCISEFILE , ios::out | ios::app);
	exercise << num <<".   ";
	int n = 0;
	while (n < length)
	{
		if (expression[n].num_or_Symbol == 0)
		{
			if (expression[n].numer == 0)
			{
				cout << expression[n].num;
				exercise << expression[n].num ;
			}
			else
			{
				if (expression[n].num != 0)
				{
					cout << expression[n].num;
					cout << "`";
					exercise << expression[n].num ;
					exercise << "`" ;
				}
				cout << expression[n].numer;
				cout << "/";
				cout << expression[n].Den;
				exercise << expression[n].numer ;
				exercise << "/" ;
				exercise << expression[n].Den;
			}
		}
		else
		{
			switch (expression[n].Symbol)
			{
			case 0:
				cout << " + ";
				exercise << " + ";
				break;
			case 1:
				cout << " - ";
				exercise << " - ";
				break;
			case 2:
				cout << " × ";
				exercise << " × ";
				break;
			case 3:
				cout << " ÷ ";
				exercise << " ÷ ";
				break;
			case 4:
				cout << '(';
				exercise << '(';
				break;
			case 5:
				cout << ')';
				exercise << ')';
				break;
			default:break;
			}
		}
		n++;
	}
	
	cout << " = \n";
	exercise << " = ";
	exercise << endl;
	exercise.close();
}

void M_instructions(var **expression, int amount, int size, var* result)
{
	fstream answer;
	answer.open(ANSWERFILE, ios::out | ios::app);
	var results[maxn];//后缀表达式
	int length;
	int i = 0;
	int j = 0;
	int k = 0;
	while (i < amount)
	{
		Create(&expression[i], size, &length);
		result[i].Symbol = length;
		if (Calculation(expression[i], size, results, length) == ERROR || results[0].num >= size || results[0].numer >= size || results[0].Den >= size)
		{
			continue;
		}
		result[i].Den = results[0].Den;
		result[i].num = results[0].num;
		result[i].numer = results[0].numer;
		result[i].num_or_Symbol = 0;
		result[i].Symbol = length;
		j = 0;
		while (j < i)
		{
			//结果一样，表达式可能一样
			if (result[j].Den == result[i].Den && result[j].numer == result[i].numer && result[j].num == result[i].num)
			{
				if (is_question_same(expression[i], result[i].Symbol, expression[j], result[j].Symbol, size))
				{
					break;
				}
			}
			j++;
		}
		if (i != j)
		{
			if(k ++ < 20)//连续20次重复答案表明给的size太小，而amount太大，表达式多样性不足
				continue;
		}
		Visit(expression[i], length, i + 1);

		answer << i + 1 << ".   ";
		if (result[i].numer == 0)
		{
			answer << result[i].num;
		}
		else
		{
			if (result[i].num != 0)
			{
				answer << result[i].num;
				answer << "`";
			}
			answer << result[i].numer;
			answer << "/";
			answer << result[i].Den;
		}
		answer << endl;
		i++;
		k = 0;
	}
	answer.close();
}

void Correction(int *save,char * answerfile, char *exercisefile)// -e exercisefile.txt -a answerfile.txt
{
	fstream answer;
	fstream exercise;
	fstream grade;
	answer.open(answerfile, ios::in);
	if (!answer)
	{
		cout << "答案文件不存在!\n";
		return;
	}
	exercise.open(exercisefile, ios::in);
	if (!exercise)
	{
		cout << "题目文件不存在!\n";
		return;
	}
	grade.open(GRADE, ios::out | ios::app);
	char answ[100];
	char exer[100];
	int i,j;
	int n, m;
	int correct = 0;
	int wrong = 0;
	while (!answer.eof() && !exercise.eof())
	{
		answer.getline(answ, 100);
		exercise.getline(exer, 100);
		i = 0, j = 0, n = 0, m = 0;
		while (answ[i] >= '0' && answ[i] <= '9')
			n = answ[i++] - '0' + n * 10;
		while (exer[j] >= '0' && exer[j] <= '9')
			m = exer[j++] - '0' + m * 10;
		if (n == m)
		{
			if (n != 0 && n <= MAX_LENGTH)
			{
				i = 0;
				j = 0;
				while (exer[j++] != '=' && j < 100);
				while (exer[j++] == ' ' && j < 100);
				while (answ[i++] != '.' && i < 100);
				while (answ[i++] == ' ' && i < 100);
				j -= 1;
				i -= 1;
				while (exer[j] != ' ' && exer[j] != '\t' && exer[j] != '\0' && i < 100 && j < 100)
				{
					if (answ[i++] != exer[j++])
						break;
				}
				if (answ[i - 1] == exer[j - 1] && exer[j - 1] != ' ' && answ[i] == '\0')
				{
					save[n] = 1;
					save[n + 1] = -1;
					correct++;
				}
				else
				{
					save[n] = 0;
					save[n + 1] = -1;
					wrong++;
				}
			}	
		}
		else
		{
			if (n == 0 && m != 0)
				n = m;
			if (m == 0 && n != 0)
				m = n;
			cout << "操作失败！文件" << ANSWERFILE << "第" << n << "题或" << EXERCISEFILE << "第" << m << "题发生错误！\n";
			return;
		}
	}
	i = 1,j = 0;
	grade << "Correct: " << correct << " (";
	while (save[i] >= 0)
	{
		if (save[i] == 1)
		{
			if (j != 0)
				grade << ',';
			else
				j = 1;
			grade << i;
		}
		i++;
	}
	grade << ")" << endl;
	i = 1, j = 0;
	grade << "Wrong: " << wrong << " (";
	while (save[i] >= 0)
	{
		if (save[i] == 0)
		{
			if (j != 0)
				grade << ',';
			else
				j = 1;
			grade << i;
		}
		i++;
	}
	grade << ")" << endl;
	cout << "数据已录入" << GRADE << "!\n";
	answer.close();
	exercise.close();
	grade.close();
}

void Destrory(var** expression, var* result, int amount)
{
	int i = 0;
	while (i < amount)
		free(expression[i++]);
}

Status Infix_to_Postfix(var* p, int size, var* Postfix, int length, int& postLen)
{
	//传入的postfix要记得为空
	var stack[maxn];
	int top = 0;
	for (int i = 0; i < length; i++)
	{
		if (p[i].num_or_Symbol == 0)//是数字
		{
			Postfix[postLen++] = p[i];//放入输出串中
		}
		if (p[i].num_or_Symbol == 1 && p[i].Symbol == 4)//左括号
		{
			++top;
			stack[top] = p[i];
		}
		while (p[i].num_or_Symbol == 1 && p[i].Symbol != 4 && p[i].Symbol != 5)
		{
			if (top == 0 || stack[top].Symbol == 4 || prio(p[i]) > prio(stack[top]))
			{
				++top;
				stack[top] = p[i];
				break;
			}
			else
			{
				Postfix[postLen++] = stack[top];
				top--;
			}
		}
		if (p[i].num_or_Symbol == 1 && p[i].Symbol == 5)//右括号
		{
			while (stack[top].Symbol != 4)
			{
				Postfix[postLen++] = stack[top];
				top--;
			}
			top--;
		}
	}
	while (top != 0)
	{
		Postfix[postLen++] = stack[top--];
	}
	return SUCCESS;
}

int prio(var element)
{
	if (element.Symbol == 0 || element.Symbol == 1)
		return 1;
	if (element.Symbol == 2 || element.Symbol == 3)
		return 2;
	return 0;
}

void preprocess(var& a, var& b)
{
	//将前面的系数加进分母
	if (a.num != 0)
	{
		a.numer += a.num * a.Den;
		a.num = 0;
	}
	if (b.num != 0)
	{
		b.numer += b.num * b.Den;
		b.num = 0;
	}
	//分母通分
	a.numer *= b.Den;
	b.numer *= a.Den;
	a.Den = b.Den = a.Den * b.Den;
}

int get_gcd(int a, int b) {
	return b == 0 ? a : get_gcd(b, a % b);
}

Status calc(var* Postfix, int length, var& ans)
{
	var stack[maxn];//存放操作数
	int top = 0;
	for (int i = 0; i < length; i++)//遍历后缀表达式
	{
		if (Postfix[i].num_or_Symbol == 0)//是操作数
		{
			stack[top++] = Postfix[i];
		}
		else if (Postfix[i].num_or_Symbol == 1)//是运算符
		{
			if (top < 2)//判断一下操作数是否足够两个，不足够则报错
			{
				printf("发生错误，操作数不足，无法完成运算\n");
				exit(-1);
			}
			var ret;
			if (!operate(stack[top - 2], stack[top - 1], Postfix[i], ret))//计算过程有负数 || 计算过程中出现了除 0 的非法操作
			{
				return ERROR;
			}
			top -= 2;
			stack[top++] = ret;
		}
	}
	if (top == 1)//最后肯定只剩一个数字
	{
		ans = stack[0];
		return SUCCESS;
	}
	//printf("计算到最后，栈中剩余的操作数不为一个\n");
	return ERROR;
}

Status operate(var a, var b, var oper, var& ret)
{
	//先通分
	preprocess(a, b);
	//判断执行的操作
	if (oper.Symbol == 0)//+
	{
		a.numer += b.numer;
	}
	else if (oper.Symbol == 1)//-
	{
		a.numer -= b.numer;
	}
	else if (oper.Symbol == 2)// *
	{
		a.numer *= b.numer;
		a.Den *= b.Den;
	}
	else if (oper.Symbol == 3)// ÷
	{
		a.numer *= b.Den;
		a.Den *= b.numer;
	}
	if (a.numer < 0 || a.Den == 0)//计算过程中出现了负数 || 计算过程中出现了除 0 的非法操作
	{
		return ERROR;
	}
	//化简
	ret = a;
	int gcd = get_gcd(ret.numer, ret.Den);
	ret.numer /= gcd, ret.Den /= gcd;
	ret.num = ret.numer / ret.Den;
	ret.numer %= ret.Den;
	return SUCCESS;
}

void display(var* a) {
	if (a->num == 0)
	{
		if (a->Den == 1)
		{
			printf("%d\n", a->numer);
		}
		else {
			printf("%d/%d\n", a->numer, a->Den);
		}
	}
	else {
		if (a->Den == 1)
		{
			printf("%d\n", a->numer + a->num);
		}
		else {
			printf("%d'%d/%d\n", a->num, a->numer, a->Den);
		}
	}
}

void crerat_info(var* expression, int i, int num_or_Symbol, int numer, int den, int Symbol, int num)
{
	expression[i].num_or_Symbol = num_or_Symbol;
	expression[i].Den = den;
	expression[i].numer = numer;
	expression[i].Symbol = Symbol;
	expression[i].num = num;
}

void print(var* result, int len)
{
	for (int i = 0; i < len; i++)
	{
		if (result[i].num_or_Symbol == 0)
		{
			printf("%d", result[i].numer);
		}else{
			if (result[i].Symbol == 0)
			{
				printf("+");
			}
			else if (result[i].Symbol == 1)
			{
				printf("-");
			}
			else if (result[i].Symbol == 2)
			{
				printf("*");
			}
			else if (result[i].Symbol == 3)
			{
				printf("÷");
			}
		}
	}
	puts("");
}

Status Calculation(var* exp, int size, var* result, int length)
{
	int postLen = 0;
	Infix_to_Postfix(exp, size, result, length, postLen);
	var ans;
	if (!calc(result, postLen, ans))
	{
		return ERROR;
	}
	*result = ans;
	return SUCCESS;
}

Status get_Subexpression(var* Postfix, int length, var ans[][3], int& sta_size)
{
	var stack[maxn];//存放操作数
	int top = 0;
	for (int i = 0; i < length; i++)//遍历后缀表达式
	{
		if (Postfix[i].num_or_Symbol == 0)//是操作数
		{
			stack[top++] = Postfix[i];
		}
		else if (Postfix[i].num_or_Symbol == 1)//是运算符
		{
			var ret;
			
			ans[sta_size][0] = stack[top - 2];
			ans[sta_size][1] = stack[top - 1];
			ans[sta_size++][2] = Postfix[i];

			operate(stack[top - 2], stack[top - 1], Postfix[i], ret);
			top -= 2;
			stack[top++] = ret;
		}
	}
	return SUCCESS;
}

bool cmp(var a[], var b[])
{
	//判断子表达式是否等价
	if (a[2] == b[2])//运算符
	{
		if (a[0] == b[1] && a[1] == b[0] || (a[0] == b[0] && a[1] == b[1]))//操作数
		{
			return true;
		}
	}
	return false;
}

Status is_question_same(var* Question, int lenQuest, var* newQuestion, int lenNewQuest, int size)
{
	var Postfix1[maxn], Postfix2[maxn];
	var stack1[3][3], stack2[3][3];
	int len1 = 0, len2 = 0, sta_size1 = 0, sta_size2 = 0;

	//获取后缀表达式
	Infix_to_Postfix(Question, size, Postfix1, lenQuest , len1);
	Infix_to_Postfix(newQuestion, size, Postfix2, lenNewQuest, len2);

	//获取子表达式
	get_Subexpression(Postfix1, len1, stack1, sta_size1);
	get_Subexpression(Postfix2, len2, stack2, sta_size2);

	bool flag;
	for (int i = 0; i < sta_size1; i++)
	{
		flag = false;
		for (int j = 0; j < sta_size2; j++)
		{
			//短式等价
			if (cmp(stack1[i], stack2[j]))
			{
				flag = true;
				stack2[j][2].Symbol = -1;//将表达式的运算符删掉
				break;
			}
		}
		if (!flag)//如果存在不一样的，返回not same
		{
			return ERROR;
		}
	}
	return SUCCESS;
}