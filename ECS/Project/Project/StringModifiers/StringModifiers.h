#pragma once

#include <algorithm> 
#include <functional> 
#include <cctype>
#include <locale>
#include <vector>
#include <string>


namespace StringModifiers {

	// Trim from start (in place).
	inline void ltrim(std::string &s) {
		s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
	}

	// Trim from end (in place).
	inline void rtrim(std::string &s) {
		s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
	}

	// Trim from both ends (in place).
	inline void trim(std::string &s) {
		ltrim(s);
		rtrim(s);
	}

	// Trim from start (copying).
	inline std::string ltrimmed(std::string s) {
		ltrim(s);
		return s;
	}

	// Trim from end (copying).
	inline std::string rtrimmed(std::string s) {
		rtrim(s);
		return s;
	}

	// Trim from both ends (copying).
	inline std::string trimmed(std::string s) {
		trim(s);
		return s;
	}

	/**
	Create a wchar_t string from the provided string, (given by a char *) and return a pointer to the new one.
	Calling function is responsible for deallocating returned string.
	*/
	inline wchar_t * convertToWChar_T(const char * filename)
	{
		size_t newsize = strlen(filename) + 1;
		wchar_t * wfilename = new wchar_t[newsize];
		size_t convertedChars = 0;
		mbstowcs_s(&convertedChars, wfilename, newsize, filename, _TRUNCATE);
		return wfilename;
	}

	//	Return a vector of strings, created by splitting the string according to the given delimiter.
	inline std::vector<std::string> split_string(const std::string& str, const std::string& delimiter)
	{
		std::vector<std::string> strings;

		std::string::size_type pos = 0;
		std::string::size_type prev = 0;
		while ((pos = str.find(delimiter, prev)) != std::string::npos)
		{
			strings.push_back(str.substr(prev, pos - prev));
			prev = pos + delimiter.size();
		}

		// To get the last substring (or only, if delimiter is not found)
		strings.push_back(str.substr(prev));

		return strings;
	}
}