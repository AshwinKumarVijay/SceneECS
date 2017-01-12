#pragma once

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <map>

#include "../StringModifiers/StringModifiers.h"
#include "ResourceDescription.h"


class RDFP
{

public:

	//	Default Resource Description File Parser Constructor.
	RDFP();

	//	Default Resource Description File Parser Destructor.
	virtual ~RDFP();

	//	Parse the specified Resource Description File.
	virtual bool parseResourceDescriptionFile(const std::string & RDF, std::map<std::string, ResourceDescription> & RDM);

	//	Parse the Resource Description File
	virtual bool parseResourceDescription(const std::vector<std::string> & RD, std::map<std::string, ResourceDescription> & RDM);

	//	Parse a Resource.
	virtual bool parseResource(const std::vector<std::string> & RD, int lineIndex, std::map<std::string, ResourceDescription> & RDM);

private:

	//	Check if we should ignore the line in the creation of the Resource Description.
	virtual bool shouldIgnoreLine(const std::string & line);

};
