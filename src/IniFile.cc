#include <string.h>
#include <stdio.h>

#include <fstream>

#include "IniFile.h"

using namespace kiva;


IniFile::IniFile()
{
}


IniFile::IniFile(const std::string &path)
{
	load(path);
}


IniFile::~IniFile()
{
}


void IniFile::load(const std::string &path)
{
	this->file = path;
	parseFile(path);
}


void IniFile::parseFile(const std::string &path)
{
	std::ifstream in(path);

	if(!in.is_open()) {
		return;
	}

	std::string buf;

	do {
		std::getline(in, buf);

		if (!buf.empty()) {
			parseLine(buf);
		}
	} while (in);

	in.close();
}


void IniFile::parseLine(const std::string &line)
{
	static std::string name;
	
	if (line[0] == '[') { /* is section */
		int pos = line.find_first_of(']');
		if (pos == std::string::npos || pos == 1) {
			return;
		}
		
		name = std::move(line.substr(1, pos-1));
		if (name.empty()) {
			return;
		}
		
		addSection(name);
	
	} else { /* is property */
		if (name.empty()) {
			name = "global";
		}
		
		int pos = line.find(" = ");
		if (pos == std::string::npos || pos == 0) {
			return;
		}
		
		const std::string &k = line.substr(0, pos);
		const std::string &v = line.substr(pos+3);
		
		Section &s = (*this)[name];
		s.set(k, v);
	}
}


bool IniFile::isEmpty() const
{
	return sections.empty();
}


bool IniFile::contains(const std::string &name) const
{
	const auto &it = std::find(sections.begin(), sections.end(), name);
	
	return it != sections.end();
}


Section& IniFile::get(const std::string &name)
{
	static Section empty("");
	
	auto it = std::find(sections.begin(), sections.end(), name);
	if (it != sections.end()) {
		return *it;
	}
	
	return empty;
}


void IniFile::addSection(const std::string &name)
{
	addSection(Section(name));
}


void IniFile::addSection(const Section &s)
{
	if (contains(s.getName())) {
		return;
	}
	
	sections.push_back(s);
}


void IniFile::save() const
{
	FILE *fp = fopen(file.c_str(), "w");
	
	if (!fp) {
		return;
	}
	
	for (const Section &s : sections) {
		fprintf(fp, "[%s]\n", s.getName().c_str());
		
		const auto &map = s.mapping();
		
		for (const auto &e : map) {
			if (!e.second.isValid()) {
				continue;
			}
			
			fprintf(fp, "%s = ", e.first.c_str());
			
			switch(e.second.getType()) {
			case INT:
				fprintf(fp, "%d\n", e.second.asInt());
				break;
			
			case BOOL:
				fprintf(fp, "%s\n", e.second.asBool() ? "true" : "false");
				break;
			
			case STRING:
				fprintf(fp, "%s\n", e.second.asString().c_str());
				break;
			}
		}
		
		fprintf(fp, "\n");
	}
	
	fclose(fp);
}


Section& IniFile::operator[](const std::string &name)
{
	addSection(name);
	return get(name);
}

