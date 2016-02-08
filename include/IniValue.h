#pragma once

#include <string>

namespace kiva {

enum ValueType
{
	INT, STRING, BOOL, NONE
};

class IniValue
{
private:
	ValueType type;
	std::string str;
	union {
		int intValue;
		bool boolValue;
	} value;
	
public:
	IniValue();
	IniValue(int i);
	IniValue(bool b);
	IniValue(const std::string &str);
	~IniValue();
	
	IniValue& operator=(int i);
	IniValue& operator=(bool b);
	IniValue& operator=(const std::string &str);
	
	bool isValid() const;
	ValueType getType() const;
	
	bool asBool() const;
	int asInt() const;
	const std::string& asString() const;
};

}

