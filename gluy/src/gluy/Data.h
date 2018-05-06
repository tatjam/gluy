#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include "optional.h"


using nonstd::optional;
using nonstd::nullopt;

namespace gluy
{
	class Data;
	class Program;
	class Function;

	typedef std::unordered_map<std::string, Data> gluy_struct;
	typedef std::vector<Data> gluy_vector;

	class Data
	{

	private:

		union
		{
			uint64_t reserve;
			float reservef;
			gluy_struct stData;
			gluy_vector vcData;
			void* reserveptr;
		};

	public:

		enum DataType
		{
			INT,
			FLOAT,
			STRUCT,
			VECTOR,
			PROGRAM,
			FUNCTOR,
			VOID
		};

		DataType type;

		Data();
		Data(int data);
		Data(float data);
		Data(gluy_struct data);
		Data(gluy_vector data);
		Data(const Data& b);
		Data(Function* data);
		Data(Program* data);
		Data(std::string str);

		~Data();

		// Returns nulloptr if invalid type, otherwise
		// returns the value packed in an optional
		inline optional<int> as_int() const
		{
			return (this->type == DataType::INT) ? optional<int>((int)this->reserve) : nullopt;
		}
		inline optional<float> as_float() const
		{
			return (this->type == DataType::FLOAT) ? optional<float>((float)this->reservef) : nullopt;
		}
		inline optional<gluy_struct> as_struct() const
		{
			return (this->type == DataType::STRUCT) ? optional<gluy_struct>(this->stData) : nullopt;
		}
		inline optional<gluy_vector> as_vector() const
		{
			return (this->type == DataType::VECTOR) ? optional<gluy_vector>(this->vcData) : nullopt;
		}
		inline optional<Program*> as_program() const
		{
			return (this->type == DataType::PROGRAM) ? optional<Program*>((Program*)this->reserveptr) : nullopt;
		}
		inline optional<Function*> as_function() const
		{
			return (this->type == DataType::FUNCTOR) ? optional<Function*>((Function*)this->reserveptr) : nullopt;
		}

		inline void set(int d)
		{
			this->type = INT; this->reserve = d;
		}
		inline void set(float d)
		{
			this->type = FLOAT; this->reservef = d;
		}
		inline void set(gluy_struct d)
		{
			this->type = STRUCT; this->stData = d;
		}
		inline void set(gluy_vector d)
		{
			this->type = VECTOR; this->vcData = d;
		}
		inline void set(Function* func)
		{
			this->type = FUNCTOR; this->reserveptr = (void*)func;
		}
		inline void set(Program* prog)
		{
			this->type = PROGRAM; this->reserveptr = (void*)prog;
		}
		inline void set_void()
		{
			this->type = VOID;
		}

		operator std::string() const;
		Data& operator=(const gluy::Data& b);

		static Data from_typename(std::string tname);

	};

	typedef std::vector<std::pair<std::string, Data::DataType>> gluy_arglist;



}