#pragma once
#include <vector>
#include <map>
#include "vd.h"
#include "book.h"
using std::vector;
using std::map;
class RepoExceptions
{
private:
	string msg;
public:
	RepoExceptions(string m) :msg{ m } {

	}
	string get_message()
	{
		return msg;
	}
};
class Repo //: public RepoAbstract
{
private:
	VectorDinamic<book > books;
public:
	//Repo(const Repo& ot) = delete;

	Repo() = default;

	virtual void store(const book& loc);

	virtual void del(const string title);

	virtual void update(string title, string new_title);

	const book& find(string title);

	VectorDinamic<book> filter_by_type(string t);

	VectorDinamic<book> filter_by_year(int year);

	VectorDinamic<book> sort_by_title();

	VectorDinamic<book> sort_by_year();

	VectorDinamic<book> sort_combined();

	const vector<book> get_all();

};

class BookRepoFile :public Repo {
private:
	std::string fName;
	void loadFromFile();
	void writeToFile();
public:
	BookRepoFile(std::string fName) :Repo(), fName{ fName } {
		loadFromFile();//incarcam datele din fisier
	}
	void store(const book& p) override {
		Repo::store(p);//apelam metoda din clasa de baza
		writeToFile();
	}
	void del(const string title) override {
		Repo::del(title);//apelam metoda din clasa de baza
		writeToFile();
	}
	void update(string title, string new_title) {
		Repo::update(title, new_title);
		writeToFile();
	}
};



void test_repo();