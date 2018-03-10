#include "infixEvaluator.h"
#include <iostream>

using namespace std;


int main()
{
	string s("(-4 + -5) +++25");
	string t("(4 >= -5) + 25");
	string u("4 <= -5 + 25");

	InfixEvaluator i;

	cout << i.eval(s) << endl;
	cout << i.eval(t) << endl;
	cout << i.eval(u) << endl;


	char wait = getchar();
}
