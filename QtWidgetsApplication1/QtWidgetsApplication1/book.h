#pragma once
#include <crtdbg.h>
#define _CRTDBG_MAP_ALLOC
#include <string>
#include <iostream>
using std::cout;
using std::string;

class book
{
private:
	string title;
	string author;
	string type;
	int year;
public:
	string get_title() const noexcept
	{
		return title;
	}
	string get_author() const
	{
		return author;
	}
	string get_type() const noexcept
	{
		return type;
	}
	int get_year() const
	{
		return year;
	}

	void set_title(string new_title)
	{
		title = new_title;
	}

	bool operator==(const book& ot) const noexcept
	{
		return ot.title == title;
	}

	book(const book& ot) :title{ ot.title }, author{ ot.author }, type{ ot.type }, year{ ot.year } {

	}

	book()
	{
		title = "";
		author = "";
		type = "";
		year = 0;
	};

	book(string title, string author, string type, int year) :title{ title }, author{ author }, type{ type }, year{ year }{

	}
};
