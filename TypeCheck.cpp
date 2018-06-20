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

	GT,
	LT,
	EQU,
	AND,
	OR,
	NOT,
	BOOL,

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
	INBOOL,
	DONE
};

// 语法树的结点类型
enum NodeType
{
	OPERATOR,
	NUMBER,
	BOOLEAN
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

bool isBool;
bool isError;

string currentToken;
TokenType currentTokenType;

// 操作符映射器
// Notice: c++11 新特性(unordered_map)，旧版本编译器编译报错，请使用支持C++11标准的编译器。
unordered_map<string, TokenType> mapper =
{
	{ "add", ADD },
	{ "sub", SUB },

	{ "gt", GT },
	{ "lt", LT },
	{ "equ", EQU },
	{ "and", AND },
	{ "or", OR },
	{ "not", NOT } };

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

			// 在已有程序基础上加上T/F的判断
			// 先判断是否是T/F
			else if (c == 'T' || c == 'F')
			{
				currentNodeType = BOOLEAN;
				status = INBOOL;
			}

			// 再判断是否是其他字母
			else if (isalpha(c))
			{
				currentNodeType = OPERATOR;
				status = INID;
			}

			// 此break跳出的是switch
			break;

		case INNUM:
		case INID:
			// 新增
		case INBOOL:
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

		// 设置当前token类型
		if (status == DONE)
		{
			currentTokenType = currentNodeType == OPERATOR ? mapping(currentToken) : (currentNodeType == BOOLEAN ? BOOL : NUM);
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
		if (currentTokenType == NUM || currentTokenType == ERROR || currentTokenType == BOOL) //新增bool
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

// 类型检测
void checkType(TreeNode *tree)
{
	isDigit = tree->nodeType == NUM ? true : isDigit;
	isBool = tree->nodeType == BOOL ? true : isBool;

	
	if (tree->nodeType != NUM && tree->nodeType != BOOL)
	{
		// 到这，说明 tree->nodeType 为 ADD SUB AND 等
		if (tree->lchild != NULL)
		{
			checkType(tree->lchild);
		}
		if (tree->rchild != NULL)
		{
			checkType(tree->rchild);
		}

		switch (tree->nodeType)
		{
		case ADD:
		case SUB:
			// 对于+、-，孩子出现bool/error，那么isError为true
			isError = (isBool || isError) ? true : isError;
			isDigit = !isError;
			break;

		case GT:
		case LT:
		case EQU:
			// 对于>、<、=，孩子出现bool/error，那么isError为true
			isError = (isBool || isError) ? true : isError;
			isBool = !isError;
			break;

		case AND:
		case OR:
		case NOT:
			// 对于and、or、not，孩子出现digit/error，那么isError为true
			isError = (isDigit || isError) ? true : isError;
			isBool = !isError;
			break;
		}
	}
}

int main()
{
	while (1)
	{
		/*  检测以下Lisp表达式：

		(add 5 3)					int
		(add 5 T)					error

		(gt (add 5 3) (sub 5 3))	bool
		(gt (add 5 3) (lt 5 3))		error

		(and T F)					bool
		(or (add 5 3) T)			error

		(not F)						bool
		(not 5)						error

		*/
		getline(cin, str);
		if (str == "quit")
		{
			return 0;
		}

		pos = 0;
		// 获取解析到的词
		getToken();

		// 构建语法树syntaxTree，对输入的语言进行分析
		TreeNode *syntaxTree;
		syntaxTree = buildTree();
		isDigit = false;
		isBool = false;
		isError = false;

		checkType(syntaxTree);
		string res = isError ? "error" : (isBool ? "bool" : (isDigit ? "int" : ""));
		cout << res << endl;
	}

	return 0;
}
