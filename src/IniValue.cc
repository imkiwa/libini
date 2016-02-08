#include <stdio.h>

#include "IniValue.h"

using namespace kiva;


IniValue::IniValue()
{
	type = NONE;
}


IniValue::IniValue(int i)
{
	*this = i;
}


IniValue::IniValue(bool b)
{
	*this = b;
}


IniValue::IniValue(const std::string &str)
{
	*this = str;
}


IniValue::~IniValue()
{
}
	

IniValue& IniValue::operator=(int i)
{
	type = INT;
	value.intValue = i;
}


IniValue& IniValue::operator=(bool b)
{
	type = BOOL;
	value.boolValue = b;
}


IniValue& IniValue::operator=(const std::string &str)
{
	type = STRING;
	this->str = str;
}
	

bool IniValue::isValid() const
{
	return type != NONE;
}
	

bool IniValue::asBool() const
{
	if (!isValid()) {
		return false;
	}
	
	switch(type) {
	case INT:
		return value.intValue == 1;
	case BOOL:
		return value.boolValue;
	case STRING:
		return str == "true";
	}
}


int IniValue::asInt() const
{
	if (!isValid()) {
		return 0;
	}
	
	switch(type) {
	case INT:
		return value.intValue;
	case BOOL:
		return value.boolValue ? 1 : 0;
	case STRING:
		if (str.empty()) {
			return 0;
		}
		
		int i;
		sscanf(str.c_str(), "%d", &i);
		return i;
	}
}


const std::string& IniValue::asString() const
{
	static std::string empty;
	
	if (!isValid() && type != STRING) {
		return empty;
	}
	
	return str;
}


ValueType IniValue::getType() const
{
	return type;
}

