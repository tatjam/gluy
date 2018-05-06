#pragma once
#include <vector>
#include <string>

//#include "Type.h"

#include "Util.h"


namespace gluy
{
	enum TokenType
	{
		// Basic data types
		NUMBER,		// 5, 2, 'A'
		STRING,		// "Hello!"
		NAME,		// a b jl fizzbuzz int
		KEYWORD,	// if while else
		OP,			// += + - * .call
		COMMA,		// ,
		LPAR,		// (
		RPAR,		// )
		LBRACE,		// {
		RBRACE,		// }
		LBRACKET,	// [
		RBRACKET,	// ]
		SEMICOLON,	// ;
	};

	enum BaseType
	{
		I64,	// i64, long
		I32,	// i32, int
		I16,	// i16, short
		I8,		// i8, char
		U8,		// u8, byte, bool
		U16,	// u16, ushort
		U32,	// u32, uint
		U64,	// u64 ulong
		F32,	// f32, float
		F64,	// f64, double
		UNKNOWN,
	};


	struct Token
	{
		TokenType type;
		std::string inside;
	};

	struct FunctionData
	{
		std::string name;
		std::string rettype;
		// (type, name) pairs, (int, a)
		std::vector<std::pair<std::string, std::string>> inputs;
	};

	struct TokenFunction
	{
		FunctionData data;
		std::vector<Token> inside;
	};

	struct ASTFunction
	{
		FunctionData data;
	};

	struct Type
	{
		bool isStruct = false;
		BaseType asBase;
		union numeric
		{
			int64_t i64;
			int32_t i32;
			int16_t i16;
			int8_t i8;
			uint64_t u64;
			uint32_t u32;
			uint16_t u16;
			uint8_t u8;
			float f32;
			double f64;
		};

	};

	std::string preprocess(std::string program);
	std::string trimComments(std::string program);

	std::vector<TokenFunction> extractFunctions(std::vector<Token> tokens);
	std::vector<Token> tokenize(std::string program);
	std::vector<std::string> separate(std::string program);

	BaseType getType(std::string name);

	template<typename T>
	T get(Type t)
	{

	}

}