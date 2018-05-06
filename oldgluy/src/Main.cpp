#include <iostream>
#include <string>
#include <fstream>
#include <streambuf>

#include "gluy/gluy.h"

int main(void)
{
	std::ifstream t("res/fizzbuzz.gls");
	std::string str((std::istreambuf_iterator<char>(t)),
		std::istreambuf_iterator<char>());

	std::string prog = gluy::preprocess(str);
	std::cout << prog << std::endl;
	
	std::vector<gluy::Token> tokens = gluy::tokenize(prog);
	auto list = gluy::extractFunctions(tokens);

	std::cin.get();

	return 0;
}