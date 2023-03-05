#include <crtdbg.h>
#define _CRTDBG_MAP_ALLOC
#include "ui.h"
#include "vd.h"
#include <iostream>
using std::cin;
using std::cout;

void populeaza_lista();

void UI::principal_menu()
{
	while (true)
	{
		cout << "0.Exit\n1.Add\n2.Delete\n3.Update\n4.Show all\n5.Search for book\n6.Filter\n7.Sort\n8.Show Notification Menu\n9.Freq\n10.Populeaza\n11.Undo\n";
		int cmd = 0;
		string title, author, type;
		int year = 0;
		cout << "Your option is:";
		cin >> cmd;
		if (cmd == 0)
		{
			break;
		}
		if (cmd == 1)
		{
			cout << "Introduce the book's title:";
			cin.ignore();
			getline(cin, title);
			cout << "Introduce the book's author:";
			getline(cin, author);
			cout << "Introduce the book's type:";
			getline(cin, type);
			cout << "Introduce the book's year:";
			cin >> year;
			try {
				serv.add(title, author, type, year);
				cout << "book succesfully added\n";
			}
			catch (ValidationException& ex) {
				cout << ex.getErrorMsg();
			}
		}
		if (cmd == 2)
		{
			cout << "Introduce the book title to delete:";
			cin >> title;
			try {
				serv.delete_book(title);
				cout << "book succesfully deleted\n";
			}
			catch (RepoExceptions& ex) {
				cout << ex.get_message();

			}
		}
		if (cmd == 3)
		{
			string new_title;
			cout << "Introduce the book title to update:";
			cin.ignore();
			getline(cin, title);
			cout << "Introduce the new book's title:";
			getline(cin, new_title);
			try {
				serv.update(title, new_title);
				cout << "book succesfully updated\n";
			}
			catch (RepoExceptions& ex) {
				cout << ex.get_message();
			}
		}
		if (cmd == 4)
		{
			VectorDinamic<book> books = serv.get_all();
			for (const auto& b : books)
			{
				cout << "Title: " << b.get_title() << " | Author: " << b.get_author() << " | Type: " << b.get_type() << " | Year: " << b.get_year() << '\n';
			}

		}
		if (cmd == 5)
		{
			cout << "Introduce the book title to search:";
			cin.ignore();
			getline(cin, title);
			book l = serv.find(title);
			cout << "Title: " << l.get_title() << " | Author: " << l.get_author() << " | Type: " << l.get_type() << " | Year: " << l.get_type() << '\n';
		}
		if (cmd == 6)
		{

			cout << "You want to filter by type(1) or year(2):";
			int op;
			cin >> op;
			VectorDinamic<book> lista_filtrata;
			if (op == 1)
			{
				cout << "Introduce the type to filter:";
				cin >> type;
				lista_filtrata = serv.filter_by_type(type);
				if (lista_filtrata.size() == 0)
					cout << "It doesn't exist books with that type\n";
				else
				{
					for (const auto& b : lista_filtrata)
					{
						cout << "Title: " << b.get_title() << " | Author: " << b.get_author() << " | Type: " << b.get_type() << " | Year: " << b.get_year() << '\n';
					}
				}


			}
			if (op == 2)
			{
				cout << "Introduce the year to filter:";
				cin >> year;
				lista_filtrata = serv.filter_by_year(year);
				if (lista_filtrata.size() == 0)
					cout << "It doesn't exist books with that year\n";
				else
				{
					for (int i = 0; i < lista_filtrata.size(); i++)
					{
						cout << "Title: " << lista_filtrata.at(i).get_title() << " | Author: " << lista_filtrata.at(i).get_author() << " | Type: " << lista_filtrata.at(i).get_type() << " | Year: " << lista_filtrata.at(i).get_year() << '\n';
					}
				}
			}
		}
		if (cmd == 7)
		{
			VectorDinamic<book> lista_sortata;
			cout << "You want to sort by book's title(1), year(2) or type+year(3):";
			int op;
			cin >> op;
			if (op == 1)
			{
				lista_sortata = serv.sort_by_title();

			}
			if (op == 2)
			{
				lista_sortata = serv.sort_by_year();
			}
			if (op == 3)
			{
				lista_sortata = serv.sort_combined(); //tip+year
			}
			for (int i = 0; i < lista_sortata.size(); i++)
			{
				cout << "Title: " << lista_sortata.at(i).get_title() << " | Author: " << lista_sortata.at(i).get_author() << " | Type: " << lista_sortata.at(i).get_type() << " | Year: " << lista_sortata.at(i).get_year() << '\n';
			}
		}
		if (cmd == 8)
		{
			menu_notif();
		}
		if (cmd == 9)
		{
			//serv.frecventa_an();
		}
		if (cmd == 10) {
			populeaza_lista();
		}
		if (cmd == 11) {
			serv.undo();
		}
	}

}

void UI::menu_notif()
{
	while (true)
	{
		int cmd = 0, nr = 0;
		vector<book> n = serv.getCos();
		cout << "0.Exit\n1.Clear\n2.Add book\n3.Random generate\n4.Export\n";
		cout << "Your option is:";
		cin >> cmd;
		if (cmd == 0)
			return;
		if (cmd == 1)
		{
			serv.emptyCos();
			n = serv.getCos();
			cout << "Actual capacity=" << n.size() << "\n";
		}
		if (cmd == 2)
		{
			string title;
			cout << "Introduce the book's title you want in Cos List:";
			cin >> title;
			serv.addToCos(title);
			n = serv.getCos();
			cout << "Actual capacity=" << n.size() << "\n";
		}
		if (cmd == 3)
		{
			cout << "Introduce the number of books you want to randomly add:";
			cin >> nr;
			serv.addRandomToCos(nr);
			n = serv.getCos();
			cout << "Actual capacity=" << n.size() << "\n";
		}
		if (cmd == 4)
		{

			string file;
			cout << "Introduce the name of the file you eant to export to: ";
			cin >> file;
			serv.exportCos(file);
			cout << "The cos list was succesfully exported\n";
			n = serv.getCos();
			cout << "Actual capacity=" << n.size() << "\n";
		}
	}
}


void UI::populeaza_lista() {
	serv.add("Baltagul", "Ioan Slavici", "Drama", 2001);
	serv.add("Ion", "Nicu Pop", "Drama", 2001);
	serv.add("Mara", "Cosmin Popa", "Comedie", 2002);
	serv.add("Joker", "Andrei Dan", "Comedie", 1998);
	serv.add("O scrisoare pierduta", "Perta Rares", "Drama", 2003);
	serv.add("Vara", "Roxana Dop", "Comedie", 2004);
	serv.add("Iarna", "Emil Prodan", "Drama", 2003);
}