#include "Data.h"


namespace gluy
{

	Data::operator std::string() const
	{
		std::string out = "";
		if (type == INT) { out.append("INT -> "); out.append(std::to_string((int)reserve)); }
		if (type == FLOAT) { out.append("FLOAT -> "); out.append(std::to_string(reservef)); };
		if (type == STRUCT) { out.append("STRUCT"); }
		if (type == VOID) { out.append("VOID"); }

		return out;
	}

	Data& Data::operator=(const gluy::Data& b)
	{
		if (this != &b)
		{
			this->type = b.type;
			this->reserve = b.reserve;
			this->stData = b.stData;
		}

		return *this;
	}

	Data::Data(int data) : stData()
	{
		this->set(data);
	}

	Data::Data(float data) : stData()
	{
		this->set(data);
	}

	Data::Data(gluy_struct data) : stData()
	{
		this->set(data);
	}

	Data::Data(gluy_vector data) : stData()
	{
		this->set(data);
	}

	Data::Data(Function* data) : stData()
	{
		this->set(data);
	}


	Data::Data(Program* data) : stData()
	{
		this->set(data);
	}

	Data::Data(std::string str) : stData()
	{
		gluy_vector vec = gluy_vector();
		for (size_t i = 0; i < str.size(); i++)
		{
			vec.push_back(Data(str[i]));
		}
		this->set(vec);
	}


	Data::Data() : stData()
	{
		this->set_void();
	}

	Data::Data(const Data& b)
	{
		this->type = b.type;
		if (this->type == INT)
		{
			this->reserve = b.reserve;
		}
		else if (this->type == FLOAT)
		{
			this->reservef = b.reservef;
		}
		else if (this->type == STRUCT)
		{
			this->stData = b.stData;
		}
		else if (this->type == VECTOR)
		{
			this->vcData = b.vcData;
		}
	}


	Data::~Data()
	{
		/*if (this->type == STRUCT)
		{
			stData.~_Hash();
		}*/
	}

	Data Data::from_typename(std::string tname)
	{
		if (tname == "int")
		{
			return Data(0);
		}
		else if (tname == "float")
		{
			return Data(0.0f);
		}
		else if (tname == "struct")
		{
			return Data(gluy_struct());
		}
		else if (tname == "vector")
		{
			return Data(gluy_vector());
		}
		else if (tname == "prog" || tname == "program")
		{
			return Data((Program*)NULL);
		}
		else if (tname == "func" || tname == "function")
		{
			return Data((Function*)NULL);
		}
		else
		{
			return Data();
		}
	}

}