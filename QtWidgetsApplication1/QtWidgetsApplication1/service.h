#pragma once
#include <string>
#include "book.h"
#include "repo.h"
#include "vd.h"
#include "cos.h"
#include "validator.h"
#include "undo.h"
using std::string;
using std::unique_ptr;
class bookService
{
private:
	Repo& rep;
	bookValidator& val;
	std::vector<unique_ptr<ActiuneUndo>> undoActions;
	Cos& cos;

public:
	bookService(Repo& rep, bookValidator& val, Cos& cos) noexcept : rep{ rep }, val{ val }, cos{ cos } {};
	//bookService(const bookService& ot) = delete;
	//bookService() = default;
	void add(string title, string author, string type, int year);

	void delete_book(string title);

	void update(string title, string new_title);

	book find(string title);

	VectorDinamic<book> filter_by_type(string t);

	VectorDinamic<book> filter_by_year(int year);

	void undo();

	vector<book> get_all();

	VectorDinamic<book> sort_by_title();

	VectorDinamic<book> sort_by_year();

	VectorDinamic<book> sort_combined();

	void addToCos(string title);

	void addRandomToCos(int nr);

	void emptyCos() noexcept;

	void exportCos(string file_name);

	const vector<book>& getCos() noexcept;

	map<string, int> get_raport();


};


void test_add();

void test_delete_book();

void test_update();

void test_find();

void test_filter_by_type();

void test_filter_by_year();

void test_sort_by_title();

void test_sort_by_year();

void test_sort_combined();

void test_addToCos();

void test_addRandomToCos();

void test_emptyCos();

void test_undo();