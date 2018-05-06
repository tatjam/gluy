#include "gluy.h"
// This file is dedicated to build the token list / function list


namespace gluy
{
	std::string trimComments(std::string program)
	{
		std::string out;
		out.reserve(program.size());

		enum Comment
		{
			NONE,
			LINE,
			LONG
		};

		Comment comm = NONE;
		bool inStr = false;
		for (size_t i = 0; i < program.size(); i++)
		{
			if (comm == NONE)
			{
				char prev = 0;
				if (i != 0)
				{
					prev = program[i - 1];
				}

				if (prev != '\\')
				{
					if (program[i] == '"' || program[i] == '\'')
					{
						inStr = !inStr;
					}

					if (program[i] == '/')
					{
						char next;
						if (program.size() > i + 2)
						{
							next = program[i + 1];
						}

						if (next == '/')
						{
							comm = LINE;
						}
						else if (next == '*')
						{
							comm = LONG;
						}
					}

					if (comm == NONE)
					{
						out.push_back(program[i]);
					}
				}
			}
			else if (comm == LINE)
			{
				if (program[i] == '\n')
				{
					comm = NONE;
				}
			}
			else if (comm == LONG)
			{
				if (program[i] == '*')
				{
					char next = 0;
					if (program.size() > i + 2)
					{
						next = program[i];
					}

					if (next == '/')
					{
						comm = NONE;
					}
				}
			}
		}

		out.shrink_to_fit();

		return out;
	}

	std::string preprocess(std::string program)
	{
		std::string prog = program;
		prog = trimComments(program);

		return prog;
	}

	std::vector<TokenFunction> extractFunctions(std::vector<Token> tokens)
	{
		std::vector<TokenFunction> out;
		TokenFunction acc;

		int level = 0;
		
		for (size_t i = 0; i < tokens.size(); i++)
		{
			if (level == 0)
			{
				// Begin new function
				acc.data.rettype = tokens[i].inside;
				acc.data.name = tokens[i + 1].inside;
				for (size_t j = i + 3; j < tokens.size(); j+=3)
				{
					std::pair<std::string, std::string> pair;

					if (tokens[j + 1].type == OP)
					{
						pair = std::make_pair(tokens[j].inside + tokens[j + 1].inside, tokens[j + 2].inside);
						j++;
					}
					else
					{
						pair = std::make_pair(tokens[j].inside, tokens[j + 1].inside);
					}
					
					acc.data.inputs.push_back(pair);
					if (tokens[j + 2].type == RPAR)
					{
						level++;
						i = j + 3;
						break;
					}
				}
			}
			else
			{
				if (tokens[i].type == LBRACE)
				{
					level++;
				}
				else if (tokens[i].type == RBRACE)
				{
					level--;
				}

				acc.inside.push_back(tokens[i]);

				if (level == 0)
				{
					out.push_back(acc);
					acc.inside.clear();
					acc.data.inputs.clear();
					acc.data.name.clear();
					acc.data.rettype.clear();
				}
			}

		}

		return out;
	}

	std::vector<Token> tokenize(std::string program)
	{
		std::vector<std::string> prog = separate(program);
		// Categorize each token
		std::vector<Token> out;

		for (std::string str : prog)
		{
			if (isalpha(str[0]))
			{
				if (str == "if")
				{
					out.push_back({ TokenType::KEYWORD, str });
				}
				else
				{
					out.push_back({ TokenType::NAME, str });
				}
			}
			else
			{
				if (isdigit(str[0]))
				{
					out.push_back({ TokenType::NUMBER, str });
				}
				else if (str[0] == '\'')
				{
					out.push_back({ TokenType::NUMBER, str.substr(1, str.size() - 2) });
				}
				else if (str[0] == '"')
				{
					out.push_back({ TokenType::STRING, str.substr(1, str.size() - 2) });
				}
				else if (str[0] == '(')
				{
					out.push_back({ TokenType::LPAR, "" });
				}
				else if (str[0] == ')')
				{
					out.push_back({ TokenType::RPAR, "" });
				}
				else if (str[0] == '{')
				{
					out.push_back({ TokenType::LBRACE, "" });
				}
				else if (str[0] == '}')
				{
					out.push_back({ TokenType::RBRACE, "" });
				}
				else if (str[0] == '[')
				{
					out.push_back({ TokenType::LBRACKET, "" });
				}
				else if (str[0] == ']')
				{
					out.push_back({ TokenType::RBRACKET, "" });
				}
				else if (str[0] == ';')
				{
					out.push_back({ TokenType::SEMICOLON, "" });
				}
				else if (str[0] == ',')
				{
					out.push_back({ TokenType::COMMA, "" });
				}
				else if (str[0] == '.')
				{
					out.push_back({ TokenType::OP, str });
				}
				else if (ispunct(str[0]))
				{
					out.push_back({ TokenType::OP, str });
				}


				
			}
		}

		return out;
	}

	std::vector<std::string> separate(std::string program)
	{
		std::vector<std::string> out;

		bool inStr = false;
		std::string data;
		for (size_t i = 0; i < program.size(); i++)
		{
			char prev = 0;
			if (i != 0)
			{
				prev = program[i - 1];
			}

			if (prev != '\\')
			{
				if (program[i] == '"' || program[i] == '\'')
				{
					inStr = !inStr;
				}
			}

			if (!inStr)
			{
				if (isblank(program[i]) || iscntrl(program[i]))
				{
					if (!data.empty())
					{
						out.push_back(data);
						data.clear();
					}
					continue;
				}
				else if ((isalnum(program[i]) && !isalnum(program[i + 1]))
					|| (!isalnum(program[i]) && isalnum(program[i + 1])))
				{
					data.push_back(program[i]);
					out.push_back(data);
					data.clear();
					continue;
				}
			}

			data.push_back(program[i]);
		}

		return out;
	}
}