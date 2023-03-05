#include "bookGUI.h"
#include "book.h"
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMessageBox>
#include <qpalette.h>
#include <qbrush.h>
#include<qdebug.h>
#include <string>
#include <algorithm>
#include <qcolor.h>

void BookStoreGUI::initGUICmps() {
	setLayout(lyMain);

	//adaug lista si sub doua butoane de sort
	QWidget* widDreapta = new QWidget;
	QVBoxLayout* vl = new QVBoxLayout;
	widDreapta->setLayout(vl);
	lst = new QListWidget;
	lstFiltrare = new QListWidget;
	vl->addWidget(lst);

	QWidget* widBtnDreapta = new QWidget;
	QHBoxLayout* lyBtnsDr = new QHBoxLayout;
	widBtnDreapta->setLayout(lyBtnsDr);
	btnSortByYear = new QPushButton("Sort by year");
	btnSortByYear->setStyleSheet("color : black; border:1px solid; background-color: rgb(25, 206, 235)");
	lyBtnsDr->addWidget(btnSortByYear);

	btnSortByTitle = new QPushButton("Sort by title");
	btnSortByTitle->setStyleSheet("color : black; border:1px solid; background-color: rgb(25, 206, 235)");
	lyBtnsDr->addWidget(btnSortByTitle);
	vl->addWidget(widBtnDreapta);
	lyMain->addWidget(widDreapta);



	//fac un form pentru detalii
	QWidget* widDetalii = new QWidget;
	QFormLayout* formLDetalii = new QFormLayout;
	widDetalii->setLayout(formLDetalii);
	txtTitle = new QLineEdit;
	formLDetalii->addRow(new QLabel("Title:"), txtTitle);
	txtAuthor = new QLineEdit;
	formLDetalii->addRow(new QLabel("Author:"), txtAuthor);
	txtType = new QLineEdit;
	formLDetalii->addRow(new QLabel("Type:"), txtType);
	txtYear = new QLineEdit;
	formLDetalii->addRow(new QLabel("Year:"), txtYear);
	txtUpdtTitle = new QLineEdit;
	formLDetalii->addRow(new QLabel("New title:"), txtUpdtTitle);
	txtExportFile = new QLineEdit;
	formLDetalii->addRow(new QLabel("Export file:"), txtExportFile);
	txtAdaugaRandom = new QLineEdit;
	formLDetalii->addRow(new QLabel("Number of random inserts:"), txtAdaugaRandom);

	btnFltr = new QPushButton("Filter");
	btnFltr->setStyleSheet("color : black; border:1px solid; background-color: rgb(25, 206, 235)");
	lyBtnsDr->addWidget(btnFltr);
	vl->addWidget(widBtnDreapta);
	lyMain->addWidget(widDreapta);


	//FILTRARE
	fltrType = new QLineEdit;
	formLDetalii->addRow(new QLabel("Filter by type: "), fltrType);

	fltrYear = new QLineEdit;
	formLDetalii->addRow(new QLabel("Filter by year: "), fltrYear);

	btnAdd = new QPushButton("Add book");
	btnAdd->setStyleSheet("border:2px solid #ff0000;");
	btnDel = new QPushButton("Delete book");
	btnDel->setStyleSheet("border:2px solid #ff0000;");
	btnUpdt = new QPushButton("Update book");
	btnUpdt->setStyleSheet("border:2px solid #ff0000;");
	btnUndo = new QPushButton("Undo");
	btnUndo->setStyleSheet("border:2px solid #ff0000;");

	btnCos = new QPushButton("Cos");
	//btnCos->setStyleSheet("border:2px solid rgb(229, 210, 196)");
	btnCos->setStyleSheet("border: 2px solid rgb(139, 0, 139);");
	btnAdaugaCos = new QPushButton("Add to cart");
	btnAdaugaCos->setStyleSheet("border:2px solid rgb(139, 0, 139)");
	btnEmptyCos = new QPushButton("Delete cart");
	btnEmptyCos->setStyleSheet("border:2px solid rgb(139, 0, 139)");
	btnExportCos = new QPushButton("Export cart");
	btnExportCos->setStyleSheet("border:2px solid rgb(139, 0, 139)");
	btnAdaugaRandomCos = new QPushButton("Add random");
	btnAdaugaRandomCos->setStyleSheet("border:2px solid rgb(139, 0, 139)");
	btnDesene = new QPushButton("Watch drawings");
	btnDesene->setStyleSheet("border:2px solid rgb(139, 0, 139)");

	formLDetalii->addWidget(btnAdd);
	formLDetalii->addWidget(btnDel);
	formLDetalii->addWidget(btnUpdt);
	formLDetalii->addWidget(btnUndo);
	formLDetalii->addWidget(btnCos);
	formLDetalii->addWidget(btnAdaugaCos);
	formLDetalii->addWidget(btnEmptyCos);
	formLDetalii->addWidget(btnExportCos);
	formLDetalii->addWidget(btnAdaugaRandomCos);
	formLDetalii->addWidget(btnDesene);

	lyMain->addWidget(widDetalii);

	btnDyn->setLayout(lyBtnDy);

	lyMain->addWidget(btnDyn);

}

void BookStoreGUI::reloadListFiltrare(const VectorDinamic<book> book_list) {
	lstFiltrare->clear();
	for (int i = 0; i < book_list.size(); i++) {
		QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(book_list.at(i).get_title()));
		item->setData(Qt::UserRole, QString::fromStdString(book_list.at(i).get_type()));
		lstFiltrare->addItem(item);
	}
}

void BookStoreGUI::connectSignalsSlots() {
	cos.addObserver(this);
	//cand se emite semnalul clicked de pe buton reincarc lista
	QObject::connect(btnSortByYear, &QPushButton::clicked, [&]() {
		qDebug() << "am ajuns aici!!!";
		reloadList(ctr.sort_by_year());
		});
	//cand se emite semnalul clicked de pe buton reincarc lista
	QObject::connect(btnSortByTitle, &QPushButton::clicked, [&]() {
		reloadList(ctr.sort_by_title());
		});
	QObject::connect(btnAdd, &QPushButton::clicked, this, &BookStoreGUI::addNewBook);
	QObject::connect(btnDel, &QPushButton::clicked, this, &BookStoreGUI::delBook);
	QObject::connect(btnUpdt, &QPushButton::clicked, this, &BookStoreGUI::updateBook);
	QObject::connect(btnUndo, &QPushButton::clicked, this, &BookStoreGUI::UNDO);
	QObject::connect(btnAdaugaCos, &QPushButton::clicked, this, &BookStoreGUI::addNewBookCos);
	QObject::connect(btnEmptyCos, &QPushButton::clicked, this, &BookStoreGUI::empty_Cos);
	QObject::connect(btnExportCos, &QPushButton::clicked, this, &BookStoreGUI::export_Cos);

	QObject::connect(btnDesene, &QPushButton::clicked, [&]() {
		cosRO.show();
		});

	QObject::connect(btnCos, &QPushButton::clicked, [&]() {
		QWidget* wdg = new QWidget;
		
		QVBoxLayout* vll = new QVBoxLayout;
		wdg->setGeometry(QRect(500, 500, 400, 400));
		wdg->setStyleSheet("color: red; background-color: black");
		wdg->setLayout(vll);
		vll->addWidget(table);



		QWidget* widBtnDreapta = new QWidget;
		QHBoxLayout* lyBtnsDr = new QHBoxLayout;
		widBtnDreapta->setLayout(lyBtnsDr);

		wdg->show();
		});

	QObject::connect(btnAdaugaRandomCos, &QPushButton::clicked, [&]()
		{
			ctr.addRandomToCos(txtAdaugaRandom->text().toDouble());
			
		});

	QObject::connect(btnFltr, &QPushButton::clicked, [&]()
		{
			// creez noul widget;
			QWidget* wdgg = new QWidget;
			// lista
			QVBoxLayout* vlll = new QVBoxLayout;
			//aici adaug imaginea + dimensiuni

			if (fltrType->text().toStdString() == "")
				reloadListFiltrare(ctr.filter_by_year(fltrYear->text().toDouble()));
			else
				reloadListFiltrare(ctr.filter_by_type(fltrType->text().toStdString()));
			wdgg->setLayout(vlll);
			vlll->addWidget(lstFiltrare);

			QWidget* widBtnDreapta = new QWidget;
			QHBoxLayout* lyBtnsDr = new QHBoxLayout;
			widBtnDreapta->setLayout(lyBtnsDr);

			wdgg->show();
		});



	QObject::connect(lst, &QListWidget::itemSelectionChanged, [&]() {
		auto sel = lst->selectedItems();
		if (sel.isEmpty()) {
			txtTitle->setText("");
			txtAuthor->setText("");
			txtType->setText("");
			txtYear->setText("");


		}
		else {
			auto selItem = sel.at(0);
			auto title = selItem->text();
			auto type = selItem->data(Qt::UserRole).toString();
			txtTitle->setText(title);
			txtType->setText(type);
			auto p = ctr.find(title.toStdString());
			txtYear->setText(QString::number(p.get_year()));
			txtAuthor->setText(QString::fromStdString(p.get_author()));

		}
		});
}

void BookStoreGUI::addNewBookCos()
{
	try {
		ctr.addToCos(txtTitle->text().toStdString());
		
	}
	catch (RepoExceptions& ex) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(ex.get_message()));
	}
}

void BookStoreGUI::empty_Cos() {
	try {
		ctr.emptyCos();
		
	}
	catch (RepoExceptions& ex) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(ex.get_message()));
	}
}

void BookStoreGUI::export_Cos() {
	try {
		ctr.exportCos(txtExportFile->text().toStdString());
		reloadListCos(ctr.getCos());
	}
	catch (RepoExceptions& ex) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(ex.get_message()));
	}
}
void BookStoreGUI::addNewBook() {
	try {
		ctr.add(txtTitle->text().toStdString(), txtAuthor->text().toStdString(), txtType->text().toStdString(), txtYear->text().toDouble());
		reloadList(ctr.get_all());
	}
	catch (RepoExceptions& ex) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(ex.get_message()));
	}
}

void BookStoreGUI::delBook() {
	try {
		ctr.delete_book(txtTitle->text().toStdString());
		reloadList(ctr.get_all());
	}
	catch (RepoExceptions& ex) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(ex.get_message()));
	}
}

void BookStoreGUI::updateBook() {
	try {
		ctr.update(txtTitle->text().toStdString(), txtUpdtTitle->text().toStdString());
		reloadList(ctr.get_all());
	}
	catch (RepoExceptions& ex) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(ex.get_message()));
	}
}

void BookStoreGUI::UNDO() {
	try {
		ctr.undo();
		reloadList(ctr.get_all());
	}
	catch (RepoExceptions& ex) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(ex.get_message()));
	}
}

void BookStoreGUI::reloadListCos(const VectorDinamic<book> books)
{
	table->clearContents();
	table->setRowCount(books.size());

	int lineNumber = 0;

	for (const auto& b : ctr.getCos()) {
		table->setItem(lineNumber, 0, new QTableWidgetItem(QString::fromStdString(b.get_title())));
		lineNumber++;
	}

	/*lst_cos->clear();
	for (int i = 0; i < books.size(); i++) {
		QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(books.at(i).get_title()));
		item->setData(Qt::UserRole, QString::fromStdString(books.at(i).get_type()));
		lst_cos->addItem(item);

	}*/
}
void BookStoreGUI::reloadList(const VectorDinamic<book> boooks) {
	lst->clear();
	for (int i = 0; i < boooks.size(); i++) {
		QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(boooks.at(i).get_title()));
		item->setData(Qt::UserRole, QString::fromStdString(boooks.at(i).get_type()));
		if (boooks.at(i).get_year() > 2050) {
			item->setData(Qt::BackgroundRole, QBrush{ Qt::red, Qt::SolidPattern });
		}
		lst->addItem(item);

	}
}
void BookStoreGUI::adaugaButoane(const map<string, int> books_map) {
	for (const auto& p : books_map) {

		auto btn = new QPushButton{ QString::fromStdString(p.first) };
		btn->setStyleSheet("border:2px solid yellow");
		lyBtnDy->addWidget(btn);
		QObject::connect(btn, &QPushButton::clicked, [&, p]() {
			QMessageBox::information(this, QString::fromStdString(p.first), QString::number(p.second));
			}
		);


	}
}