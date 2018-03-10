
#pragma once

#ifndef INFIX_EVALUATOR_H
#define INFIX_EVALUATOR_H

#include <stack>
#include <string>

using namespace std;


class InfixEvaluator
{
	// Private member functions
private:
	/** Evaluates the current operator.
	This function pops the two operands off the operand
	stack and applies the operator.
	@param op A character representing the operator
	@throws Syntax_Error if top is attempted on an empty stack
	*/
//	int eval_op(char op);

	/** Determines whether a character is an operator.
	@param ch The character to be tested
	@return true if the character is an operator
	*/
	bool isOperator(const char& c)
	{
		return (OPERATOR_LIST.find(c) != std::string::npos);
	}


	// Data fields



	const string InfixEvaluator::OPERATOR_LIST = "+-*/<>%^()";
	const char BINARY_OPERATOR[7] = { 'x','O','A','E','N','G','L' };
	const string OPERATORS = "OAENG>L<+-*/%^()";
	const int PRECEDENCE[16] = { 1, 2, 3, 3, 4, 4, 4, 4, 5, 5, 6, 6, 6, 7, -1, -1 };
	const string TWO_DIGIT_BINARY_OP = {"||&&==!=>=<="};


	std::stack<int> operand_stack;
	std::stack<char> operator_stack;

	int precedence(char op) const {
		return PRECEDENCE[OPERATORS.find(op)];
	}

	string findNegatives(string& s);

public:
	/** Evaluates a postfix expression.
	@param expression The expression to be evaluated
	@return The value of the expression
	@throws Syntax_Error if a syntax error is detected
	*/
	int eval(const std::string& expression);

	/*  */
	void InfixEvaluator::runOperation();

	/*  */
	int InfixEvaluator::applyOperation(char op, int lhs, int rhs);
	
};










#endif
