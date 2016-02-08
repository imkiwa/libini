#include "Section.h"

using namespace kiva;


Section::Section(const std::string &name)
	:name(name)
{
}


Section::Section(const std::string &name, const Section &o)
	:name(name)
{
	*this = o;
}


Section::~Section()
{
}


int Section::size() const
{
	return data.size();
}


bool Section::contains(const std::string &key) const
{
	auto it = data.find(key);
	
	return it != data.end();
}


bool Section::isEmpty() const
{
	return size() == 0;
}


void Section::set(const std::string &key, const IniValue &value)
{
	data[key] = value;
}


IniValue& Section::get(const std::string &key)
{
	static IniValue empty;
	
	if (contains(key)) {
		return data[key];
	}
	
	return empty;
}


const std::string& Section::getName() const
{
	return name;
}


void Section::setName(const std::string &name)
{
	this->name = name;
}


const std::map<std::string, IniValue>& Section::mapping() const
{
	return data;
}


Section& Section::operator=(const Section &o)
{
	if (name.empty()) {
		name = o.name;
	}
	
	data = o.data;
	
	return *this;
}


IniValue& Section::operator[](const std::string &key)
{
	return data[key];
}


bool Section::operator==(const Section &o) const
{
	return name == o.name;
}


bool Section::operator==(const std::string &name) const
{
	return this->name == name;
}

