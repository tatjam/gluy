#pragma once
#include <string>
#include <vector>
#include "Data.h"
#include "Error.h"

namespace gluy
{

	class Program;

	struct CodeChunk;

	struct CodeLine
	{
		enum CodeChunkCond
		{				// Representation in debug:
			NONE,		// (nothing)
			TRUE,		// T: 
			FALSE		// F: 
		};

		enum OpCode
		{
			MAKE,		// (VARNAME) (TYPE)
			SET,		// (VARNAME) (VARNAME/NUMBER/STRING/ARG)

			JMP,		// (LOC: NUMBER/VARNAME)
			JMP_OFF,	// (OFF: NUMBER/VARNAME)

			// For Numbers:
			ADD,		// (VARNAME) (VARNAME/NUMBER/ARG)
			SUB,		// (VARNAME) (VARNAME/NUMBER/ARG)
			MUL,		// (VARNAME) (VARNAME/NUMBER/ARG)
			DIV,		// (VARNAME) (VARNAME/NUMBER/ARG)
			MOD,		// (VARNAME) (VARNAME/NUMBER/ARG)
			// For Arrays/Maps:
			INSERT,		// (VARNAME) (INDEX: VARNAME/NUMBER/ARG/STRING) (VAL: VARNAME/NUMBER/ARG/STRING)
			PUSH,		// (VARNAME) (VAL: VARNAME/NUMBER/ARG/STRING)
			GET,		// (VARNAME) (INDEX: VARNAME/NUMBER/ARG/STRING) (TO: VARNAME)
			POP,		// (VARNAME) (TO: VARNAME)

		};

		CodeChunkCond cond;
		OpCode code;

		std::vector<CodeChunk> chunks;

	};

	struct CodeChunk
	{
		enum CodeChunkType
		{				// Representation in debug:
			VARNAME,	//	"out"
			TYPE,		//	[char]
			INT,		//	5, 10, -20
			FLOAT,		//	0.5, 11000.0, -500.0
			STRING,		//	$"Hello, World!" (aka [char])
			ARG,		//	ARG0, ARG10
		};

		CodeChunkType type;

		std::string data;

		union
		{
			float as_float;
			int as_int;
		};
	};

	class Function 
	{
		friend class Program;

	public:

		gluy_arglist args;

		std::vector<CodeLine> code;

		gluy_struct locals;
		CodeLine::CodeChunkCond flags;

	public:

		// If it returns something we must halt!
		optional<gluy_result> do_opcode(CodeLine::OpCode code, std::vector<CodeChunk>& chunks, 
			std::vector<Data>& args, Program* super, std::string* error, size_t* pc, bool* halt_pc);

		// Resolves a variable, first checking locals
		// and then checking this.[x]. Args are resolved
		// separately
		Data* resolve(std::string name, Program* super);

		// The first arg is ALWAYS the owner program
		// and it's named "this" (ALWAYS!)
		gluy_result call(std::vector<Data> args, std::string* error);

	};
}