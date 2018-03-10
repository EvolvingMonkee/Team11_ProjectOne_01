#include "InfixEvaluator.h"

enum UNARY_OPERATOR_FLAG :unsigned int
{
	NONE = 0,
	NEGATIVE = 1,
	INCREMENT = 2,
	DECREMENT = 3,
	LOGICAL_NEGATION = 4
};



enum BINARY_OPERATOR_FLAG : unsigned int
{
	NO_FLAG = 0,
	LOGICAL_OR = 1,
	LOGICAL_AND = 2,
	EQUAL_TO = 3,
	NOT_EQUAL = 4,
	GREATER_OR_EQUAL = 5,
	LESS_OR_EQUAL = 6,

};

BINARY_OPERATOR_FLAG operandDecoder(string& s)
{
	BINARY_OPERATOR_FLAG result = NO_FLAG;
	if (s == "||") result = LOGICAL_OR;
	else if (s == "&&") result = LOGICAL_AND;
	else if (s == "==") result = EQUAL_TO;
	else if (s == "!=") result = NOT_EQUAL;
	else if (s == ">=") result = GREATER_OR_EQUAL;
	else if (s == "<=") result = LESS_OR_EQUAL;

	return result;
}

int unaryOperation(int& i, UNARY_OPERATOR_FLAG& flag)
{
	switch (flag)
	{
	case NEGATIVE:
		i = 0 - i;
		break;
	case INCREMENT:
		i+=1;
		break;
	case DECREMENT:
		i -= 1;
		break;
	case LOGICAL_NEGATION:
		if (i != 0)
			i = 1;
		break;

	}
	return i;

}


void InfixEvaluator:: runOperation()
{
	int rhs = operand_stack.top();
	operand_stack.pop();
	int lhs = operand_stack.top();
	operand_stack.pop();
	operand_stack.push(applyOperation(operator_stack.top(), lhs, rhs));
	operator_stack.pop();

}



int InfixEvaluator::applyOperation(char op, int lhs, int rhs)
{
	/* TODO: Complete all operations */
	switch (op)
	{
	case '+':
		return lhs + rhs;

		/*TODO: finish*/




	case 'G':
		if (lhs >= rhs) return 1;
		else return 0;
	case 'L':
		if (lhs <= rhs) return 1;
		else return 0;



	}

	return 0;

}


/** 
	Replaces Negatives with 'M' to differentiate negatives from minus operator
	@param string for parsing
*/
string InfixEvaluator::findNegatives(string& s)
{
	string::iterator itr = s.begin();
	if (*itr == '-' && isdigit(*(itr + 1)))
		*itr = 'M';

	int previousOperatorFlag = 0;

	while (itr != s.end())
	{
		if (isOperator(*(itr)) && *(itr) != '-')
		{
			previousOperatorFlag = 1;
		}
		else if (*itr >= '0' && *itr <= '9')
		{
			previousOperatorFlag = 0;
		}

		if (*itr == '-')
		{
			if ( previousOperatorFlag != 0 )
			{
				*itr = 'M';
			}
		}


		++itr;
	}

	return s;

}

/** Evaluates an infix expression.
@param expression The expression to be evaluated
@return The value of the expression
@throws Syntax_Error if a syntax error is detected
*/
int InfixEvaluator::eval(const std::string& expression)
{
	// Be sure the operand_stack is empty
	while (!operand_stack.empty())
		operand_stack.pop();
	// Be sure the operator_stack is empty
	while (!operator_stack.empty())
		operator_stack.pop();

	/* Result */
	int result = 0;
	/* String to parse through, add a buffer char*/
	string expr = expression + " ";
	/* Iterator for string parsing */
	size_t position = 0;
	/* String for operators and operands */
	string next_chars = "";
	UNARY_OPERATOR_FLAG unaryOperatorFlag = NONE;

	expr = findNegatives(expr);

	/* Loop through string */
	while (position < expr.size() - 1)
	{
		string nextTwo = expr.substr(position, 2);

		/* Ignore whitespace */
		if (expr.at(position) == ' ')
		{
			/* Do nothing */
		}
		else if (isdigit(expr.at(position)))
		{
			int op = strtol(&expr.at(position), NULL, 10);
			if (unaryOperatorFlag != NONE)
			{
				op = unaryOperation(op, unaryOperatorFlag);
				unaryOperatorFlag = NONE;
			}
			while (isdigit(expr.at(position + 1)) && position < expr.size() - 1)
				position++;
			operand_stack.push(op);
		}

		/* Handle Negative Unary Operator */
		else if (expr.at(position) == 'M')
		{
			unaryOperatorFlag = NEGATIVE;
		}



		/* Handle unary operators*/
		else if (expr.at(position) == '!')
			unaryOperatorFlag = LOGICAL_NEGATION;
		else if (nextTwo == "--")
		{
			unaryOperatorFlag = DECREMENT;
			position++;
		}
		else if (nextTwo == "++")
		{
			unaryOperatorFlag = INCREMENT;
			position++;
		}



		/* Handle Binary two digit unary operators*/
		else if ( TWO_DIGIT_BINARY_OP.find(nextTwo) != std::string::npos)
		{
			string optr = expr.substr(position, 2);
			BINARY_OPERATOR_FLAG fl = operandDecoder(optr);
			if (fl == NO_FLAG)
			{
				/* todo: Error */
			}
			else
			{
				operator_stack.push(BINARY_OPERATOR[fl]);
			}
			/* Increment once to get past the second char */
			position++;

		}

		/* Handle opening brace*/
		else if (expr.at(position) == '(')
			operator_stack.push('(');

		/* Handle closing brace*/
		else if (expr.at(position) == ')')
		{
			/* todo: check for error*/
			{
			
			}

			/* operator*/
			while (operator_stack.top() != '(')
			{
				runOperation();
			}
			operator_stack.pop();

		}

		/* Handle all other operators */
		else if (isOperator(expr.at(position)))
		{
			while (!operator_stack.empty() && precedence(operator_stack.top()) >= precedence(expr.at(position)))
			{
				runOperation();
			}

			operator_stack.push(expr.at(position));

		
		}




		++position;
	}

	while (!operator_stack.empty())
	{
		runOperation();
	}

	result = operand_stack.top();



	return result;

}
