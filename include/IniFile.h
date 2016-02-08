#pragma once

#include <algorithm>
#include <string>
#include <vector>

#include "IniValue.h"
#include "Section.h"

namespace kiva {

class IniFile
{
private:
	std::vector<Section> sections;
	std::string file;
	
	void parseFile(const std::string &path);
	void parseLine(const std::string &line);

public:
	IniFile();
	IniFile(const std::string &path);
	~IniFile();
	
	void load(const std::string &path);
	
	bool isEmpty() const;
	bool contains(const std::string &name) const;
	
	Section& get(const std::string &name);
	void addSection(const std::string &name);
	void addSection(const Section &s);
	
	void save() const;
	
	Section& operator[](const std::string &name);
};

}
