#pragma once

namespace gluy
{
	struct Error
	{
		enum ErrorType
		{
			NONE,
			FUNCTION_NOT_FOUND,
			FUNCTION_NOT_IMPLEMENTED,
			FUNCTION_THIS_NOT_PASSED,
			ARG_OUT_OF_BOUNDS,
			INVALID_ARGUMENTS,
			INVALID_VARIABLE,
			INVALID_TYPES,
		};
	};

	typedef std::pair<Data, Error::ErrorType> gluy_result;
}