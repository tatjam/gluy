#include "Function.h"
#include "Program.h"

namespace gluy
{
	optional<gluy_result> Function::do_opcode(CodeLine::OpCode code, std::vector<CodeChunk>& chunks,
		std::vector<Data>& args, Program* super, std::string* error, size_t* pc, bool* halt_pc)
	{
		if (code == CodeLine::OpCode::MAKE)
		{
			if (chunks[0].type == CodeChunk::VARNAME && chunks[1].type == CodeChunk::TYPE)
			{
				locals[chunks[0].data] = Data::from_typename(chunks[1].data);
			}
			else
			{
				return gluy_result(Data(), Error::INVALID_ARGUMENTS);
			}
		}
		else if (code == CodeLine::OpCode::SET)
		{
			if (chunks[0].type == CodeChunk::VARNAME && (chunks[1].type == CodeChunk::VARNAME
				|| chunks[1].type == CodeChunk::INT || chunks[1].type == CodeChunk::STRING 
				|| chunks[1].type == CodeChunk::FLOAT || chunks[1].type == CodeChunk::ARG))
			{
				Data* target = resolve(chunks[0].data, super);
				if (target == NULL)
				{
					return gluy_result(Data(), Error::INVALID_VARIABLE);
				}
				else
				{
					Data* data2 = NULL;
					bool must_delete = false;
					if (chunks[1].type == CodeChunk::VARNAME)
					{
						data2 = resolve(chunks[1].data, super);
					}
					else if (chunks[1].type == CodeChunk::INT)
					{
						data2 = new Data(chunks[1].as_int);
						must_delete = true;
					}
					else if (chunks[1].type == CodeChunk::FLOAT)
					{
						data2 = new Data(chunks[1].as_float);
						must_delete = true;
					}
					else if (chunks[1].type == CodeChunk::STRING)
					{
						data2 = new Data(chunks[1].data);
						must_delete = true;
					}
					else if (chunks[1].type == CodeChunk::ARG)
					{
						if (chunks[1].as_int >= args.size())
						{
							return gluy_result(Data(), Error::ARG_OUT_OF_BOUNDS);
						}

						data2 = &args[chunks[1].as_int];
					}
					if (data2 == NULL)
					{
						return gluy_result(Data(), Error::INVALID_VARIABLE);
					}
					else
					{
						if (target->type != data2->type)
						{
							return gluy_result(Data(), Error::INVALID_TYPES);
						}
						else
						{
							*target = *data2;
						}

						if (must_delete)
						{
							delete data2;
						}
					}
				}
			}
			else
			{
				return gluy_result(Data(), Error::INVALID_ARGUMENTS);
			}
		}

		return nullopt;
	}

	gluy_result Function::call(std::vector<Data> args, std::string* error)
	{
		auto superopt = args[0].as_program();
		if (!superopt.has_value())
		{
			return gluy_result(Data(), Error::FUNCTION_THIS_NOT_PASSED);
		}
		Program* prog = superopt.value();

		size_t pc = 0;
		bool halt_pc = false;

		for (pc = 0; pc < code.size();)
		{
			CodeLine line = code[pc];
			// Check for conditionals
			if (line.cond == flags || line.cond == CodeLine::NONE)
			{
				auto res = do_opcode(line.code, line.chunks, args, prog, error, &pc, &halt_pc);
				if (res.has_value())
				{
					return res.value();
				}
			}

			if (halt_pc)
			{
				halt_pc = false;
			}
			else
			{
				pc++;
			}
		}

		return gluy_result(Data(), Error::NONE);
	}

	Data* Function::resolve(std::string name, Program* super)
	{
		// Check locals
		auto it = locals.find(name);
		if (it == locals.end())
		{
			// Check this.[name]
			auto it2 = super->data.find(name);
			if (it2 == super->data.end())
			{
				return NULL;
			}
			else
			{
				return &it2->second;
			}
		}
		else
		{
			return &it->second;
		}
	}
}