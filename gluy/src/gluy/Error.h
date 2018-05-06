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
		};
	};

	typedef std::pair<Data, Error::ErrorType> gluy_result;
}