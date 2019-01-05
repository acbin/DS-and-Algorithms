#include <iostream>
#include <cstdlib>
#include <string>
#include <unordered_map>

using namespace std;

// token类型
enum TokenType
{
	ADD,
	SUB,
	MUL,
	DIV,
	MOD,

	ENDFILE,
	ERROR,
	NUM
};

// 有限状态机的状态类型
enum Status
{
	START,
	INNUM,
	INID,
	DONE
};

// 语法树的结点类型
enum NodeType
{
	OPERATOR,
	NUMBER
};

// 语法树的结点结构
struct TreeNode
{
	int value;
	string str;
	TokenType nodeType;
	TreeNode *lchild, *rchild;
};

// 全局变量，用于记录当前表达式解析的状态
string str;
int pos;
bool isDigit;
string currentToken;
TokenType currentTokenType;

// 操作符映射器
// Notice: c++11 新特性(unordered_map)，旧版本编译器编译报错，请使用支持C++11标准的编译器。
unordered_map<string, TokenType> mapper =
{
	{ "add", ADD },
	{ "sub", SUB },
	{ "mul", MUL },
	{ "div", DIV },
	{ "mod", MOD }
};

// 查找s(小写)对应的tokenType(大写)
TokenType mapping(string s)
{
	return mapper.count(s) == 1 ? mapper[s] : ERROR;
}

// 产生一个可解释的词(用于构建语法树)
void getToken()
{
	NodeType currentNodeType;
	// 每次解释前，状态标记为START
	Status status = START;

	// 标记是否要保存该字符
	bool save;
	currentToken = "";

	// 只要状态不是DONE,就循环解释
	while (status != DONE)
	{
		// 到达字符串末尾
		if (pos == str.length())
		{
			// 标记状态并跳出循环
			currentTokenType = ENDFILE;
			break;
		}

		// 获取一个字符
		// 40是左括号的ASCII码
		int c = str[pos++];
		save = true;

		switch (status)
		{
		case START:
			if (c == ' ' || c == '(' || c == ')')
			{
				// 开始while的下一次循环
				continue;
			}
			if (isdigit(c))
			{
				currentNodeType = NUMBER;
				status = INNUM;
			}
			else if (isalpha(c))
			{
				currentNodeType = OPERATOR;
				status = INID;
			}
			// 此break跳出的是switch
			break;

		case INNUM:
		case INID:
			if (c == ' ' || c == ')')
			{
				status = DONE;
				save = false;
			}
			break;
		case DONE:
		default:
			break;
		}
		if (save)
		{
			currentToken += (char)c;
		}
		if (status == DONE)
		{
			currentTokenType = currentNodeType == OPERATOR ? mapping(currentToken) : NUM;
		}
	}
}

TreeNode *buildTree();

TreeNode *getChildNode()
{
	getToken();
	TreeNode *p = NULL;
	if (currentTokenType != ENDFILE)
	{
		if (currentTokenType == NUM || currentTokenType == ERROR)
		{
			p = new TreeNode();
			p->nodeType = currentTokenType;
			if (currentTokenType == NUM)
			{
				// 把字符串(数字)转为整型
				p->value = atoi(currentToken.c_str());
			}
			else
			{
				p->str = currentToken;
			}
		}
		else
		{
			// 是一些操作符(eg. ADD MUL)
			// 说明是一棵子树，继续递归
			p = buildTree();
		}
	}
	return p;
}

// 构建语法树
TreeNode *buildTree()
{
	TreeNode *t = NULL;
	if (currentTokenType == ENDFILE)
	{
		return t;
	}

	t = new TreeNode();
	t->nodeType = currentTokenType;
	t->str = currentToken;

	t->lchild = getChildNode();
	t->rchild = getChildNode();

	return t;
}

/*
打印二叉树:
1. 结点类型为NUM，直接输出值
2. 结点类型为ERROR，输出该结点str值
3. 结点类型为操作符，输入str(
*/
void printTree(TreeNode *tree)
{
	string out = tree->nodeType == NUM ?
		to_string(tree->value) : (tree->nodeType == ERROR ? tree->str : tree->str + "(");
	
	cout << out;
	if (tree->lchild != NULL)
	{
		// 递归调用
		printTree(tree->lchild);
		cout << ", ";
	}
	if (tree->rchild != NULL)
	{
		// 递归调用
		printTree(tree->rchild);
		cout << ")";
	}
}

// 表达式的结果计算
int calc(TreeNode *tree)
{
	if (tree->nodeType == NUM)
	{
		return tree->value;
	}
	else if (tree->nodeType == ERROR)
	{
		isDigit = false;
		return 0;
	}
	else
	{
		int a, b, c;
		a = calc(tree->lchild);
		b = calc(tree->rchild);
		switch (tree->nodeType)
		{
			// 此处自定义语义计算规则
		case ADD:
			c = a - b;
			break;
		case SUB:
			c = a + b;
			break;
		case MUL:
			if (b == 0)
			{
				isDigit = false;
				return 0;
			}
			c = a / b;
			break;
		case DIV:
			c = a * b;
			break;
		case MOD:
			if (b == 0)
			{
				isDigit = false;
				return 0;
			}
			c = a % b;
			break;
		}
		return c;
	}
}

int main()
{
	while (1)
	{
		// 获取一行输入
		// eg. (mul (add 3 4) 5)
		getline(cin, str);
		if (str == "quit")
		{
			return 0;
		}

		pos = 0;
		// 获取解析到的词
		getToken();

		// 构建语法树syntaxTree，对输入的语言进行分析
		TreeNode *syntaxTree = buildTree();

		// 格式化输出
		printTree(syntaxTree);
		cout << endl;

		// 计算表达式结果
		isDigit = true;
		int num = calc(syntaxTree);

		string res = isDigit ? to_string(num) : "e";
		cout << res << endl;
	}

	return 0;
}
