#pragma once

#include "book.h"
#include <vector>
#include <string>
using std::string;
using std::vector;

class ValidationException {
	vector<string> errorMsg;
public:
	ValidationException(vector<string> errorMessages) :errorMsg{ errorMessages } {};
	string getErrorMsg()
	{
		string fullMsg = "";
		for (const string e : errorMsg)
		{
			fullMsg += e + '\n';
		}
		return fullMsg;
	}
};

class bookValidator {
public:
	void validate(const book& l)
	{
		vector<string> errors;
		if (l.get_title().length() == 0)
			throw RepoExceptions("Invalid book title!");
		if (l.get_author().length() == 0)
			throw RepoExceptions("Invalid book author!");
		if (l.get_type().length() == 0)
			throw RepoExceptions("Invalid book type!");
		if (l.get_year() < 1000)
			throw RepoExceptions("Invalid year");
		if (errors.size() > 0)
			throw ValidationException(errors);
	}
};