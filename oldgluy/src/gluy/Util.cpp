#include "gluy.h"

namespace gluy
{

	BaseType getType(std::string name)
	{
		if (name == "i64" || name == "long")
		{
			return I64;
		}
		else if (name == "i32" || name == "int")
		{
			return I32;
		}
		else if(name == "i16" || name == "short")
		{
			return I16;
		}
		else if (name == "i8" || name == "char")
		{
			return I8;
		}
		else if (name == "u64" || name == "ulong")
		{
			return U64;
		}
		else if (name == "u32" || name == "uint")
		{
			return U32;
		}
		else if (name == "u16" || name == "ushort")
		{
			return U16;
		}
		else if (name == "u8" || name == "byte")
		{
			return U8;
		}
		else if (name == "f64" || name == "double")
		{
			return F64;
		}
		else if (name == "f32" || name == "float")
		{
			return F32;
		}

		return UNKNOWN;
	}

}