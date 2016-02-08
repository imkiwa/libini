#pragma once

#include <map>

#include "IniValue.h"

namespace kiva {

class Section
{
private:
	std::string name;
	std::map<std::string, IniValue> data;

public:
	Section(const std::string &name);
	Section(const std::string &name, const Section &o);
	~Section();
	
	int size() const;
	
	bool contains(const std::string &key) const;
	bool isEmpty() const;
	
	void set(const std::string &key, const IniValue &value);
	IniValue& get(const std::string &key);
	
	const std::string& getName() const;
	void setName(const std::string &name);
	
	const std::map<std::string, IniValue>& mapping() const;
	
	Section& operator=(const Section &o);
	
	IniValue& operator[](const std::string &key);
	
	bool operator==(const Section &o) const;
	bool operator==(const std::string &name) const;
};

}

