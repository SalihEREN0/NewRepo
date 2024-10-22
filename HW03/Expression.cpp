#include <string>
#include <stack>
#include <iostream>
using namespace std;


int priority(char c)
{
	if (c == '+' || c == '-')
		return 1;
	else if (c == '*' || c == '/')
		return 2;
}

///----------------------------------------------------------------------------------
/// Given an expression in infix-notation, converts it to a string in post-fix notation 
/// 
string Infix2Postfix(string &s) {
	// Fill this in
	string result;
	stack<char> stack;
	int i = 0;
	int num;

	while (s[i] != '\0')
	{
		while (s[i] == ' ')
		{
			i++;
		}

		if (s[i] >= '0' && s[i] <= '9')
		{
			result += s[i];
		}

		else if (s[i] == '/' || s[i] == '*' || s[i] == '-' || s[i] == '+')
		{
			while (!stack.empty() && priority(stack.top()) >= priority(s[i]))
			{
				result += stack.top();
				stack.pop();
			}
			stack.push(s[i]);
		}

		while(!stack.empty())
		{
			result += stack.top();
			stack.pop();
		}

	}
	return result;
} // end-Infix2Postfix

///----------------------------------------------------------------------------------
/// Given a string in post-fix notation, evaluates it and returns the result
/// 
int EvaluatePostfixExpression(string& s) {
	int result;
	int i = 0;
	stack<int> stack;
	int temp ;

	while (s[i] != '\0')
	{
		temp = 0;
		
		if (s[i] == '+')
		{
			temp = stack.top();
			stack.pop();
			temp = temp + stack.top();
			stack.pop();
			stack.push(temp);
			temp = 0;
			i++;
			continue;
		}
		else if (s[i] == '-')
		{
			temp = stack.top();
			stack.pop();
			temp = stack.top() - temp;
			stack.pop();
			stack.push(temp);
			temp = 0;
			i++;
			continue;
		}
		else if (s[i] == '*')
		{
			temp = stack.top();
			stack.pop();
			temp = temp * stack.top();
			stack.pop();
			stack.push(temp);
			temp = 0;
			i++;
			continue;
		}
		else if (s[i] == '/')
		{
			temp = stack.top();
			stack.pop();
			temp = stack.top() / temp;
			stack.pop();
			stack.push(temp);
			temp = 0;
			i++;
			continue;
		}
		else if (s[i] == ' ')
		{
			i++;
			continue;
		}
		while (s[i] >= '0' && s[i] <= '9')
		{
			temp = temp * 10 + (s[i] - '0');
			i++;
		}
		stack.push(temp);
	}
	result = stack.top();
	cout << result << endl;
	return result;
} // end-EvaluatePostfixExpression