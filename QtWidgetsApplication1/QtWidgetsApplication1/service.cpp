#include <crtdbg.h>
#define _CRTDBG_MAP_ALLOC
#include "service.h"
#include <assert.h>
#include<fstream>

void bookService::add(string title, string author, string type, int year)
{
	book b{ title, author, type, year };
	val.validate(b);
	rep.store(b);
	undoActions.push_back(std::make_unique<UndoAdauga>(rep, b));
}

void bookService::delete_book(string title)
{
	book b = rep.find(title);
	undoActions.push_back(std::make_unique<UndoSterge>(rep, b));
	rep.del(title);

}

void bookService::update(string title, string new_title)
{
	book b{ title, new_title,"default", 2001 };
	undoActions.push_back(std::make_unique<UndoModifica>(rep, b));
	rep.update(title, new_title);
}

book bookService::find(string title)
{
	return rep.find(title);
}

VectorDinamic<book> bookService::filter_by_type(string t)
{
	return rep.filter_by_type(t);
}

VectorDinamic<book> bookService::filter_by_year(int year)
{
	return rep.filter_by_year(year);
}

VectorDinamic<book> bookService::sort_by_title()
{
	return rep.sort_by_title();
}

VectorDinamic<book> bookService::sort_by_year()
{
	return rep.sort_by_year();
}

VectorDinamic<book> bookService::sort_combined()
{
	return rep.sort_combined();
}

void bookService::undo() {
	if (undoActions.empty()) {
		cout << "Undo indisponibil!\n";
	}
	else {

		undoActions.back()->doUndo();
		undoActions.pop_back();
	}
}

vector<book> bookService::get_all()
{
	return rep.get_all();
}

void bookService::addToCos(string title)
{
	const auto& l = rep.find(title);
	cos.addApToCos(l);
}

void bookService::addRandomToCos(int nr)
{
	cos.addRandomBooks(get_all(), nr);
}

void bookService::emptyCos() noexcept
{
	cos.emptyCos();
}

void bookService::exportCos(string file_name) {
	cos.exportCos(file_name);
}

const vector<book>& bookService::getCos() noexcept
{
	return cos.getAllCos();
}

map<string, int> bookService::get_raport()
{
	/// <summary> 
	/// Realizeaza raportul dupa tip al listei de activitati
	/// </summary>
	/// <returns></returns>
	map<string, int> frecventa;
	for (const auto& activitate : get_all())
	{
		if (frecventa.find(activitate.get_type()) == frecventa.end())
		{
			frecventa[activitate.get_type()] = 1;
		}
		else
		{
			frecventa[activitate.get_type()] += 1;
		}
	}
	return frecventa;


}



void test_add()
{
	Repo rep;
	bookValidator val;
	Cos cos;
	bookService srv{ rep, val, cos };
	srv.add("Baltagul", "Ioan Slavici", "Drama", 2001);
	auto books = srv.get_all();
	assert(books.size() == 1);
	srv.add("Colt Alb", "Mikel Dijkstra", "Comedie", 2002);
	books = srv.get_all();
	assert(books.size() == 2);
	try {
		srv.add("", "Ioan Slavici", "Drama", 2001);
	}
	catch (ValidationException& e) {
		assert(true);
		assert(e.getErrorMsg() == "Invalid book title!\n");
	}
	try {
		srv.add("Baltagul", "", "Comedie", 2002);
	}
	catch (ValidationException& e) {
		assert(true);
		assert(e.getErrorMsg() == "Invalid book author!\n");
	}
	try {
		srv.add("Baltagul", "Daria Groza", "", 2001);
	}
	catch (ValidationException& e) {
		assert(true);
		assert(e.getErrorMsg() == "Invalid book type!\n");
	}
}

void test_delete_book()
{
	Repo rep;
	bookValidator val;
	Cos cos;
	bookService srv{ rep, val, cos };
	srv.add("Baltagul", "Ioan Slavici", "Drama", 2001);
	srv.add("Colt Alb", "Mikel Dijkstra", "Comedie", 2002);
	auto books = srv.get_all();
	assert(books.size() == 2);
	srv.delete_book("Baltagul");
	books = srv.get_all();
	assert(books.size() == 1);
	assert(books.front().get_title() == "Colt Alb");
	try
	{
		srv.delete_book("Avion");
	}
	catch (RepoExceptions& e)
	{
		assert(e.get_message() == "The book doesn't exist");
		assert(true);
	}
	Cos cos2;
	srv.add("Nicu", "Nicu", "Nicu", 2002);
	books = srv.get_all();
	cos2.addRandomBooks(books, 2);
	srv.exportCos("nicu.html");
}

void test_update()
{
	Repo rep;
	bookValidator val;
	Cos cos;
	bookService srv{ rep, val, cos };
	srv.add("Baltagul", "Ioan Slavici", "Drama", 2001);
	srv.add("Colt Alb", "Mikel Dijkstra", "Comedie", 2002);
	srv.update("Baltagul", "Carmen Dan");
	auto books = srv.get_all();
	assert(books.front().get_title() == "Carmen Dan");
	try
	{
		srv.update("Avion", "Victor Pop");
	}
	catch (RepoExceptions& e)
	{
		assert(e.get_message() == "The book doesn't exist");
		assert(true);
	}
}

void test_find()
{
	Repo rep;
	bookValidator val;
	Cos cos;
	bookService srv{ rep, val, cos };
	srv.add("Baltagul", "Ioan Slavici", "Drama", 2001);
	srv.add("Colt Alb", "Mikel Dijkstra", "Comedie", 2002);
	auto l = srv.find("Colt Alb");
	assert(l.get_title() == "Colt Alb");
	assert(l.get_author() == "Mikel Dijkstra");
	assert(l.get_type() == "Comedie");
	assert(l.get_year() == 2002);
	try
	{
		l = srv.find("Avion");
	}
	catch (RepoExceptions& e)
	{
		assert(e.get_message() == "The book doesn't exist");
		assert(true);
	}

}

void test_filter_by_type()
{
	Repo rep;
	bookValidator val;
	Cos cos;
	bookService srv{ rep, val, cos };
	srv.add("Baltagul", "Ioan Slavici", "Drama", 2001);
	srv.add("Colt Alb", "Mikel Dijkstra", "Comedie", 2002);
	srv.add("Mara", "Andrei Mircea", "Drama", 2005);
	auto filtered_list = srv.filter_by_type("Drama");
	assert(filtered_list.size() == 2);
	filtered_list = srv.filter_by_type("Tip_inexistent");
	assert(filtered_list.size() == 0);
}

void test_filter_by_year()
{
	Repo rep;
	bookValidator val;
	Cos cos;
	bookService srv{ rep, val, cos };
	srv.add("Baltagul", "Ioan Slavici", "Drama", 2001);
	srv.add("Colt Alb", "Mikel Dijkstra", "Comedie", 2002);
	srv.add("Mara", "Andrei Mircea", "Drama", 2005);
	auto filtered_list = srv.filter_by_year(2001);
	assert(filtered_list.size() == 1);
	filtered_list = srv.filter_by_year(2002);
	assert(filtered_list.size() == 1);
}

void test_sort_by_title()
{
	Repo rep;
	bookValidator val;
	Cos cos;
	bookService srv{ rep, val, cos };
	srv.add("Colt Alb", "Mikel Dijkstra", "Comedie", 2002);
	srv.add("Baltagul", "Ioan Slavici", "Drama", 2001);
	srv.add("Mara", "Andrei Mircea", "Drama", 2005);
	VectorDinamic<book> books = srv.sort_by_title();
	assert(books.front().get_title() == "Baltagul");
	assert(books.back().get_title() == "Mara");
}

void test_sort_by_year()
{
	Repo rep;
	bookValidator val;
	Cos cos;
	bookService srv{ rep, val, cos };
	srv.add("Colt Alb", "Mikel Dijkstra", "Comedie", 2002);
	srv.add("Baltagul", "Ioan Slavici", "Drama", 2001);
	srv.add("Mara", "Andrei Mircea", "Drama", 2005);
	VectorDinamic<book> books = srv.sort_by_year();
	assert(books.front().get_year() == 2001);
	assert(books.back().get_year() == 2005);
}

void test_sort_combined()
{
	Repo rep;
	bookValidator val;
	Cos cos;
	bookService srv{ rep, val, cos };
	srv.add("Colt Alb", "Mikel Dijkstra", "Comedie", 2002);
	srv.add("Baltagul", "Ioan Slavici", "Drama", 2001);
	srv.add("Mara", "Andrei Mircea", "Drama", 2005);
	VectorDinamic<book> books = srv.sort_combined();
	assert(books.front().get_year() == 2002);
	assert(books.back().get_year() == 2005);
}

void test_addToCos()
{
	Repo rep;
	bookValidator val;
	Cos cos;
	bookService srv{ rep, val, cos };
	srv.add("Baltagul", "Ioan Slavici", "Drama", 2001);
	srv.add("Colt Alb", "Mikel Dijkstra", "Comedie", 2002);
	srv.addToCos("Baltagul");
	vector<book> n = srv.getCos();
	assert(n.size() == 1);
}

void test_addRandomToCos()
{
	Repo rep;
	bookValidator val;
	Cos cos;
	bookService srv{ rep, val, cos };
	srv.add("Colt Alb", "Mikel Dijkstra", "Comedie", 2002);
	srv.add("Baltagul", "Ioan Slavici", "Drama", 2001);
	srv.add("Mara", "Andrei Mircea", "Drama", 2005);
	srv.add("Batman", "Jony Dep", "Comedie", 2003);
	srv.add("Cartea Junglei", "Mircea Petrescu", "Romantism", 1992);
	srv.addToCos("Colt Alb");
	srv.addRandomToCos(5);
	vector<book> n = srv.getCos();
	assert(n.size() == 5);
}

void test_emptyCos()
{
	Repo rep;
	bookValidator val;
	Cos cos;
	bookService srv{ rep, val, cos };
	srv.add("Colt Alb", "Mikel Dijkstra", "Comedie", 2002);
	srv.add("Baltagul", "Ioan Slavici", "Drama", 2001);
	srv.add("Mara", "Andrei Mircea", "Drama", 2005);
	srv.add("Batman", "Jony Dep", "Comedie", 2003);
	srv.add("Cartea Junglei", "Mircea Petrescu", "Romantism", 1992);
	srv.addRandomToCos(5);
	vector<book> n = srv.getCos();
	assert(n.size() == 5);
	srv.emptyCos();
	n = srv.getCos();
	assert(n.size() == 0);
}

void test_undo() {
	Repo rep;
	bookValidator val;
	Cos cos;
	bookService srv{ rep, val, cos };
	srv.add("Colt Alb", "Mikel Dijkstra", "Comedie", 2002);
	vector<book> books = srv.get_all();
	assert(books.size() == 1);
	srv.undo();
	books = srv.get_all();
	assert(books.size() == 0);
	srv.undo();

	srv.add("Baltagul", "Ioan Slavici", "Drama", 2001);
	srv.delete_book("Baltagul");
	srv.undo();
	books = srv.get_all();
	assert(books.size() == 1);

	srv.update("Baltagul", "Baltagul 2.0");
	books = srv.get_all();
	assert(books[0].get_title() == "Baltagul 2.0");
	srv.undo();
	books = srv.get_all();
	assert(books[0].get_title() == "Baltagul");


}