#include <crtdbg.h>
#define _CRTDBG_MAP_ALLOC
#include "repo.h"
#include "book.h"
#include "service.h"
#include "vd.h"
#include <assert.h>
#include <vector>
#include <algorithm>
#include <functional>
#include <map>
#include <fstream>
using std::sort;
using std::copy_if;
using namespace std;


void BookRepoFile::loadFromFile() {
	std::ifstream in(fName);
	if (!in.is_open()) { //verify if the stream is opened		
		throw RepoExceptions("Unable to open file:" + fName);
	}
	while (!in.eof()) {
		std::string title;
		in >> title;
		std::string author;
		in >> author;
		std::string type;
		in >> type;
		int year;
		in >> year;


		if (in.eof()) {	//nu am reusit sa citesc numarul
			break;
		}
		book b{ title.c_str(), author.c_str(), type.c_str(), year };
		Repo::store(b);
	}
	in.close();
}

void BookRepoFile::writeToFile() {
	std::ofstream out(fName);
	if (!out.is_open()) { //verify if the stream is opened
		std::string msg("Unable to open file:");
		throw RepoExceptions(msg);
	}
	for (auto& p : this->get_all()) {
		out << p.get_title();
		out << std::endl;
		out << p.get_author();
		out << std::endl;
		out << p.get_type();
		out << std::endl;
		out << p.get_year();
		out << std::endl;
	}
	out.close();
}




void Repo::store(const book& bookk)
{
	for (const auto& b : books)
	{
		if (b.get_title() == bookk.get_title())
		{
			throw RepoExceptions("The book has already been added");
		}
	}
	books.push_back(bookk);
}


void Repo::del(string title)
{
	bool ok = false;
	int i = -1, index = 0;
	for (const auto& b : books)
	{
		i++;
		if (b.get_title() == title)
		{
			ok = true;
			index = i;
		}
	}
	if (!ok)
		throw RepoExceptions("The book doesn't exist");
	books.erase(index);

}


void Repo::update(string title, string new_title)
{
	bool ok = false;
	for (int i = 0; i < books.size(); i++)
	{
		if (books.at(i).get_title() == title)
		{
			ok = true;
			book b = book(new_title, books.at(i).get_author(), books.at(i).get_type(), books.at(i).get_year());
			books.modify(i, b);
		}
	}
	if (!ok)
		throw RepoExceptions("The book doesn't exist");
}


const book& Repo::find(string title)
{
	for (const auto& b : books)
	{
		if (b.get_title() == title)
		{
			return b;
		}
	}
	throw RepoExceptions("The book doesn't exist");
}


VectorDinamic<book> Repo::filter_by_type(string t)
{
	vector<book> filtered_list{};
	vector<book> all = get_all();
	copy_if(all.begin(), all.end(), back_inserter(filtered_list),
		[t](const book& b) {
			return b.get_type() == t;
		});
	return VectorDinamic<book>(filtered_list);

}

VectorDinamic<book> Repo::filter_by_year(int year)
{
	vector<book> filtered_list{};
	vector<book> all = get_all();
	copy_if(all.begin(), all.end(), back_inserter(filtered_list),
		[year](const book& b) noexcept {
			return b.get_year() == year;
		});
	return VectorDinamic<book>(filtered_list);
}

const vector<book> Repo::get_all() {
	vector<book> v = books.toStdVector();
	return v;
}

bool cmp_name(book l1, book l2)
{
	return (l1.get_title().compare(l2.get_title()) < 0);
}

VectorDinamic<book> Repo::sort_by_title()
{
	vector<book> v = books.toStdVector();
	sort(v.begin(), v.end(), cmp_name);
	return VectorDinamic<book>(v);
}

bool cmp_surface(book b1, book b2) noexcept
{
	return (b1.get_year() < b2.get_year());
}

VectorDinamic<book> Repo::sort_by_year()
{
	vector<book> v = books.toStdVector();
	sort(v.begin(), v.end(), cmp_surface);
	return VectorDinamic<book>(v);
}

bool cmp_type(book b1, book b2)
{
	return (b1.get_type().compare(b2.get_type()) < 0);
}

VectorDinamic<book> Repo::sort_combined()
{
	vector<book> v = books.toStdVector();
	sort_by_year();
	sort(v.begin(), v.end(), cmp_type);
	return VectorDinamic<book>(v);
}



void test_repo()
{
	VectorDinamic<int> v;
	for (int i = 1; i <= 11; i++)
		v.push_back(5);

	Repo rep;
	book b{ "Baltagul", "Ioan Slavici", "Drama", 2001 };
	rep.store(b);
	const auto& books = rep.get_all();
	assert(books.size() == 1);
	try
	{
		rep.store(b);
	}
	catch (RepoExceptions& e)
	{
		assert(e.get_message() == "The book has already been added");
		assert(true);
	}
	book b1{ "Ion", "Andrei Dan", "Comedie", 2001 };
	rep.store(b1);


}
