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

	Data::Data(Function* data) : stData()
	{
		this->set(data);
	}


	Data::Data(Program* data) : stData()
	{
		this->set(data);
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
	}


	Data::~Data()
	{
		if (this->type == STRUCT)
		{
			stData.~vector();
		}
	}

}