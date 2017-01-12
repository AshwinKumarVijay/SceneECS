#include "RDFP.h"

//	Default Resource Description File Parser Contructor.
RDFP::RDFP()
{

}

//	Default Resource Description File Parser Destructor.
RDFP::~RDFP()
{

}

//	Parse the specified Resource Description File.
bool RDFP::parseResourceDescriptionFile(const std::string & RDF, std::map<std::string, ResourceDescription> & RDM)
{

	//	The Actual Description.
	std::vector<std::string> resourceDescription;

	//	Open the file.
	std::ifstream filestream(RDF);

	//	The temporary line.
	std::string currentLine;

	//	Read in the file, one line at a time.
	while (std::getline(filestream, currentLine))
	{
		//	Add it to the actual description.
		resourceDescription.push_back(StringModifiers::trimmed(currentLine));
	}

	//	Parse the description.
	std::cout << "Parsing " << RDF << " " << std::endl;;

	//	
	if (parseResourceDescription(resourceDescription, RDM))
	{
		std::cout << "Parsing Successful! " << std::endl;;
		return true;
	}
	else
	{
		std::cout << "Parsing Failed! " << std::endl;;
		return false;
	}
}

//	Parse the specified Resource Description.
bool RDFP::parseResourceDescription(const std::vector<std::string>& RD, std::map<std::string, ResourceDescription> & RDM)
{
	//	Check if the provided description really is a resource description.
	if (RD[0] != "#Resource Description File")
		std::cerr << "Error! Not A Resource Description File!" << std::endl;

	//	
	for (int i = 1; i < RD.size(); i++)
	{
		//	Check if we should ignore the current line.
		if (shouldIgnoreLine(RD[i]))
		{
			continue;
		}

		//	Check if we are at the start of the Resource.
		if (RD[i] == "#define Resource")
		{
			bool successfullyParsed = parseResource(RD, i, RDM);
			if (!successfullyParsed)
			{		
				std::cerr << "Error ! Failed to Parse Resource State at line : " << i << std::endl;
				return false;
			}

		}
	}

	return true;
}

//	Parse a single resource from the file, starting at the specified line.
bool RDFP::parseResource(const std::vector<std::string>& RD, int lineIndex, std::map<std::string, ResourceDescription>& RDM)
{
	//	Locate the End of the State Type Description.
	auto resourceDescriptionEnd = std::find(RD.begin() + lineIndex, RD.end(), "#end Resource");

	//	Check if we reached the end of the file before the end of the description.
	if (resourceDescriptionEnd > RD.end())
	{
		std::cerr << "Error! Resource not completed before End of File. Resource starts at : " << lineIndex << std::endl;
		return false;
	}

	//	Compute the number of lines between the start and the end of the resource.
	int linesNumber = (int)std::distance(RD.begin() + lineIndex, resourceDescriptionEnd);

	//	Check if we have the minimum number of lines.
	if (linesNumber < 2)
	{
		std::cerr << "Error! Resource is incomplete! Resource starts at : " << lineIndex << std::endl;
		return false;
	}

	std::string resourceNameLine = RD[lineIndex + 1];
	std::string resourceTypeLine = RD[lineIndex + 2];


	//	The State Name and Type.
	std::string resourceName = StringModifiers::split_string(resourceNameLine, "=")[1];
	std::string resourceType = StringModifiers::split_string(resourceTypeLine, "=")[1];
	
	(RDM[resourceName].getProperties())["Resource Name"] = StringModifiers::trimmed(resourceName);
	(RDM[resourceName].getProperties())["Resource Type"] = StringModifiers::trimmed(resourceType);

	
	//	Iterate over all the remaining resources.
	for (int i = lineIndex + 3; i < (lineIndex + linesNumber); i++)
	{
		//	Check if we should ignore the specified line.
		if (shouldIgnoreLine(RD[i]))
			continue;
		
		//	Get the current property and the value.
		std::string currentProperty = StringModifiers::trimmed(StringModifiers::split_string(RD[i], "=")[0]);
		std::string currentValue = StringModifiers::trimmed(StringModifiers::split_string(RD[i], "=")[1]);

		//	Add it to the current map.
		(RDM[resourceName].getProperties())[currentProperty] = currentValue;
	}

	return true;
}

//	Check if we should ingore the current line.
bool RDFP::shouldIgnoreLine(const std::string & line)
{
	//	Check for empty line.
	if (line == "")
		return true;

	//	Check for commented out line.
	if (line.size() >= 2)
		if (line.at(0) == '/' && line.at(1) == '/')
			return true;

	//	Add additional lines to check for and ignore.


	//	Return false if none of the ignore checks match.
	return false;
}
