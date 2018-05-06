#pragma once
#include <string>
#include <vector>
#include "Data.h"
#include "Error.h"

namespace gluy
{

	struct CodeChunk
	{
		enum CodeChunkType
		{				// Representation in debug:
			OPCODE,		//	MAKE
			VARNAME,	//	"out"
			TYPE,		//	[char]
			NUMBER,		//	5, 5.3, 0.0004	(Bit-size is deduced later on)
			STRING,		//	$"Hello, World!"
		};

		enum CodeChunkCond
		{				// Representation in debug:
			NONE,		// (nothing)
			TRUE,		// T: 
			FALSE		// F: 
		};

		std::string data;
	};

	class Function 
	{
		friend class Program;

	public:

		gluy_arglist args;

		std::vector<std::vector<CodeChunk>> code;

	public:

		// The first arg is ALWAYS the owner program
		gluy_result call(std::vector<Data> args, std::string* error)
		{
			return std::make_pair(gluy::Data(), Error::NONE);
		}

	};
}