#include "Program.h"

namespace gluy
{
	Function* Program::get_function(std::string name, std::vector<Data::DataType> args)
	{
		auto name_compat = funcs.equal_range(name);
		Function* found = NULL;

		for (auto it = name_compat.first; it != name_compat.second; ++it)
		{
			// Check signature
			int i = 0;
			bool sigmatch = true;
			for (auto tmatch : it->second.args)
			{
				if (tmatch.second != args[i])
				{
					sigmatch = false;
				}
				i++;
			}

			if (sigmatch)
			{
				found = &it->second;
			}
		}

		if (found == NULL)
		{
			if (parent != NULL)
			{
				// Search in parent
				return parent->get_function(name, args);
			}
			else
			{
				return NULL;
			}
		}
		else
		{
			return found;
		}
	}

	gluy_result Program::call(std::string name, std::vector<Data> args)
	{
		std::vector<Data::DataType> argsTypes;
		for (auto arg : args)
		{
			argsTypes.push_back(arg.type);
		}

		Function* f = get_function(name, argsTypes);

		if (f != NULL)
		{
			error.clear();

			// Add the caller program
			args.insert(args.begin(), Data(this));

			f->locals.clear();
			auto result = f->call(args, &error);
			if (error != "")
			{
				if (usr_handler != NULL)
				{
					usr_handler(error);
				}
				else
				{
					std::cout << "USER ERROR " << error << std::endl;
				}
			}

			if (result.second != Error::NONE)
			{
				if (err_handler != NULL)
				{
					err_handler(result.second);
				}
				else
				{
					std::cout << "ERROR: " << result.second << std::endl;
				}
			}
		}
		
		return std::make_pair(Data(), Error::FUNCTION_NOT_FOUND);
	}

	Program::Program()
	{
		usr_handler = NULL;
		err_handler = NULL;
		data = gluy_struct();
	}
}