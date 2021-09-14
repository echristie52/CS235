#include "ExpressionManager.h"

bool ExpressionManager::isBalanced(string expression){
	stack<char> openHalf;

	for(int i = 0; i < expression.length(); i++){
		//checking open brackets to push onto stack
		if(expression.at(i) == '('){	
			openHalf.push(expression.at(i));
		}
		else if(expression.at(i) == '['){
			openHalf.push(expression.at(i));
		}
		else if(expression.at(i) == '{'){
			openHalf.push(expression.at(i));
		}

		//checking for matching closing brackets
		else if(expression.at(i) == ')'){
			if(openHalf.empty()){
				return false;
			}
			else if(openHalf.top() == '('){
				
				openHalf.pop();
			}
			else return false;
		}
		else if(expression.at(i) == ']'){
			if(openHalf.empty()){
				return false;
			}
			else if(openHalf.top() == '['){
				openHalf.pop();
		}
			else return false;
		}
		else if(expression.at(i) == '}'){
			if(openHalf.empty()){
				return false;
			}
			else if(openHalf.top() == '{'){
				openHalf.pop();
			}
			else return false;
			
		}
		//else continues on to next char
	}
	
	//no unmatched closing brackets, checking for extra opening
	if(!openHalf.empty()){
		return false;
	}
	//else
	cout << "isBalanced: " << expression << endl;
	return true;
}

string ExpressionManager::postfixToInfix(string postfixExpression){
	vector<string> tokens = parseTokens(postfixExpression);
	stack<string> bits;
	string expr;
	string num2;
	string operation;

	for(int i = 0; i < tokens.size(); i++){
		if(isNum(tokens.at(i))){ //pulls numbers
			bits.push(tokens.at(i));
		}
		else if(isOperator(tokens.at(i))){ //pulls operators
			char opChar = tokens.at(i).at(0);

			if(bits.size() > 1){
				num2 = bits.top();
				bits.pop();
				expr = bits.top();
				bits.pop();

				expr = "( " + expr + " " + opChar + " " + num2 + " )";
				bits.push(expr);
			}
			else return "invalid"; //not enough numbers
		}
	}

	if(bits.size() == 1){
		return bits.top();
	}
	else return "invalid";
}

string ExpressionManager::postfixEvaluate(string postfixExpression){
	stack<int> nums;
	vector<string> tokens = parseTokens(postfixExpression);

	for(int i = 0; i < tokens.size(); i++){
		//load any numbers
		if(isNum(tokens.at(i))){ //convert string to int
			nums.push(stoi(tokens.at(i)));

		}

		//check for operators and evaluate if needed
		else if(isOperator(tokens.at(i))){
			char opChar = tokens.at(i).at(0);
			if(nums.size() > 1){	//sufficient size
				int second = nums.top();
				nums.pop();
				int first = nums.top();
				nums.pop();

				if(opChar == '+'){ //addition
					nums.push(first + second);
				}
				else if(opChar == '-'){
					nums.push(first - second);
				}
				else if(opChar == '*'){
					nums.push(first * second);
				}
				else if(opChar == '/'){
					if(second == 0){ //protects against divide by 0
						return "invalid";
					}
					nums.push(first / second);
				}
				else if (opChar == '%'){
					nums.push(first % second);
				}
			}
			else{ //error message
				return "invalid";
			}
		}
		else{
			return "invalid";
		}
	}

	if(nums.size() == 1){
		return to_string(nums.top());
	}
	else return "invalid";
}

string ExpressionManager::infixToPostfix(string infixExpression){
	string postfix;
	vector<string> tokens = parseTokens(infixExpression);
	stack<string> opStack;
	string opChar;
	int tokenPriority;
	int stackPriority;

	for(int i = 0; i < tokens.size(); i++){

		if(isNum(tokens.at(i))){
			postfix += tokens.at(i) + " ";
		}

		else if(isOperator(tokens.at(i))){
			opChar = tokens.at(i);
			tokenPriority = operatorPriority(opChar);

			if(opStack.empty()){ //auto-pushes onto stack if empty or open bracket
				opStack.push(opChar);
			}

			else if(!opStack.empty()){
				stackPriority = operatorPriority(opStack.top());

				if(stackPriority < tokenPriority){ //higher precedence
					opStack.push(opChar);
				}

				else if(stackPriority >= tokenPriority){ //lower/equal precedence
					while(!opStack.empty() && stackPriority >=tokenPriority){
						postfix += opStack.top() + " ";
						opStack.pop();

						if(!opStack.empty()){
							stackPriority = operatorPriority(opStack.top());
						}
					}
				}
			}
		}

		else if(isBracket(tokens.at(i))){
			opChar = tokens.at(i);
			tokenPriority = operatorPriority(opChar);

			if(tokenPriority == 0){
				opStack.push(opChar);
			}

			if(tokenPriority == 3){
				stackPriority = operatorPriority(opChar);				
				while(!opStack.empty() && stackPriority != 0){
					postfix += opStack.top() + " ";
					opStack.pop();
					
					
					if(!opStack.empty()){
						stackPriority = operatorPriority(opStack.top());

						if(stackPriority == 0){
							opStack.pop();
						}
					}
				}				
			}
		}
		else return "invalid";
	}
	while(!opStack.empty()){
		postfix += opStack.top() + " ";
		opStack.pop();
	}

	return postfix;
}

vector<string> ExpressionManager::parseTokens(string expression)
{
  stringstream ss(expression);
  string token;
  vector<string> tokens;
  while(getline(ss, token, ' '))
  {
    tokens.push_back(token);
  }
  return tokens;
}

bool ExpressionManager::isNum(string token){
	bool isNum = false;
	for(int i = 0; i < token.length(); i++){
		if(isdigit(token.at(i))){
			isNum = true;
		}
		else return false;
	}
	return isNum;
}

bool ExpressionManager::isOperator(string token){
	bool theOperator = false;
	for (int i = 0; i < token.length(); i++){
		if(token.at(i) == '+' || token.at(i) == '-' || token.at(i) == '*' || token.at(i) == '/' || token.at(i) == '%'){
			theOperator = true;
		}
		else{
			return false;
		}
	}
	return theOperator;
}

int ExpressionManager::operatorPriority(string operation){
	if(operation == "(" || operation == "[" || operation == "{"){
		return 0;
	}
	else if(operation == "+" || operation == "-"){
		return 1;
	}
	else if(operation == "*" || operation == "/" || operation == "%"){
		return 2;
	}
	else if(operation == ")" || operation == "]" || operation == "}"){
		return 3;
	}
	else{
		return -1;
	}
}

bool ExpressionManager::isBracket(string token){
	char bracket;
	if(token.length() == 1){
		bracket = token.at(0);

		if(bracket == '(' || bracket == ')' || bracket == '[' || bracket == ']' || bracket == '{' || bracket == '}')
		{
			return true;
		}
		else return false;
	}
	else return false;
}