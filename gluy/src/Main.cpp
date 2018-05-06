#include <iostream>
#include <string>
#include <fstream>
#include <streambuf>

#include "gluy/Program.h"

int main(void)
{
	std::ifstream t("res/fizzbuzz.gls");
	std::string str((std::istreambuf_iterator<char>(t)),
		std::istreambuf_iterator<char>());

	gluy::Program proga;
	gluy::Program progb;

	gluy::Function a = gluy::Function();
	a.args.push_back(std::make_pair("int0", gluy::Data::INT));
	a.args.push_back(std::make_pair("int1", gluy::Data::INT));

	gluy::Function b = gluy::Function();
	b.args.push_back(std::make_pair("int0", gluy::Data::INT));
	b.args.push_back(std::make_pair("int1", gluy::Data::INT));
	b.args.push_back(std::make_pair("int2", gluy::Data::INT));

	proga.funcs.emplace("a", a);
	progb.funcs.emplace("b", b);
	progb.parent = &proga;

	progb.call("a", {gluy::Data(0), gluy::Data(1)});

	std::cin.get();

	return 0;
}