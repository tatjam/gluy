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

	gluy::Function a = gluy::Function();
	a.args.push_back(std::make_pair("int0", gluy::Data::INT));
	a.args.push_back(std::make_pair("int1", gluy::Data::INT));

	gluy::CodeLine line;
	gluy::CodeChunk chunk;

	line.cond = gluy::CodeLine::NONE;
	line.code = gluy::CodeLine::MAKE;
	chunk.type = gluy::CodeChunk::VARNAME;
	chunk.data = "var0";
	line.chunks.push_back(chunk);
	chunk.type = gluy::CodeChunk::TYPE;
	chunk.data = "int";
	line.chunks.push_back(chunk);
	a.code.push_back(line);

	line.chunks.clear();

	line.code = gluy::CodeLine::MAKE;
	chunk.type = gluy::CodeChunk::VARNAME;
	chunk.data = "var1";
	line.chunks.push_back(chunk);
	chunk.type = gluy::CodeChunk::TYPE;
	chunk.data = "int";
	line.chunks.push_back(chunk);
	a.code.push_back(line);

	line.chunks.clear();

	line.code = gluy::CodeLine::SET;
	chunk.type = gluy::CodeChunk::VARNAME;
	chunk.data = "var1";
	line.chunks.push_back(chunk);
	chunk.type = gluy::CodeChunk::INT;
	chunk.as_int = 4;
	line.chunks.push_back(chunk);
	a.code.push_back(line);

	proga.funcs.emplace("a", a);

	proga.call("a", {gluy::Data(0), gluy::Data(1)});

	std::cin.get();

	return 0;
}