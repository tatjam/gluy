#pragma once
#include <vector>
#include <unordered_map>
#include "Data.h"
#include "Function.h"
#include "Error.h"

namespace gluy
{
	// Callback typedefs
	typedef void(*user_error_handler)(std::string& error);
	typedef void(*error_handler)(Error::ErrorType error);

	class Program 
	{

	public:

		// Can be null, if it's this is a _ class
		Program* parent;

		gluy_struct data;

		std::unordered_multimap<std::string, Function> funcs;

		std::string error;

		user_error_handler usr_handler;
		error_handler err_handler;

	public:

		// Ordered arguments
		gluy_result call(std::string name, std::vector<Data> args);

		Function* get_function(std::string name, std::vector<Data::DataType> args);

		void set_user_error_callback();
		void set_error_callback();
		
		Program();

	};
}