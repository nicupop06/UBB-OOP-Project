#pragma once
#include <qwidget.h>
#include <qlistwidget.h>
#include <qpushbutton.h>
#include <qlineedit.h>
#include <qboxlayout.h>
#include <qdebug.h>
#include "service.h"
#include "book.h"
#include <vector>
#include <qlabel.h>
#include <qtablewidget.h>
#include "observer.h"
#include "cosReadOnlyGUI.h"
class SmallGUI : public QWidget {
private:
	QLabel* lbl = new QLabel("Nimic");
public:
	SmallGUI() {
		QHBoxLayout* ly = new QHBoxLayout;
		setLayout(ly);
		ly->addWidget(lbl);
	}

	void setPet(const book& p) {
		lbl->setText(QString::fromStdString(p.get_title()));
	}
};


class BookStoreGUI : public QWidget, public Observer {
private:
	bookService& ctr;
	Cos& cos;
	cosReadOnlyGUI& cosRO;
	QHBoxLayout* lyMain = new QHBoxLayout;
	QListWidget* lst;
	QListWidget* lstFiltrare;
	QTableWidget* table = new QTableWidget{ 10, 1 };
	QPushButton* btnFltr;
	QLineEdit* fltrType;
	QLineEdit* fltrYear;
	QLineEdit* txtAdaugaRandom;
	QListWidget* lst_cos = new QListWidget;
	QPushButton* btnSortByTitle;
	QPushButton* btnSortByYear;
	QPushButton* btnAdaugaCos;
	QPushButton* btnEmptyCos;
	QPushButton* btnExportCos;
	QPushButton* btnAdaugaRandomCos;
	QLineEdit* txtTitle;
	QLineEdit* txtAuthor;
	QLineEdit* txtType;
	QLineEdit* txtYear;
	QLineEdit* txtUpdtTitle;
	QLineEdit* txtExportFile;
	QPushButton* btnAdd;
	QPushButton* btnDel;
	QPushButton* btnUpdt;
	QPushButton* btnUndo;
	QPushButton* btnDesene;
	QPushButton* btnCos;
	QVBoxLayout* lyBtnDy = new QVBoxLayout;
	QWidget* btnDyn = new QWidget;

	void initGUICmps();
	void connectSignalsSlots();
	void reloadList(const VectorDinamic<book> books);
	void addNewBook();
	void delBook();
	void updateBook();
	void UNDO();
	void addNewBookCos();
	void empty_Cos();
	void export_Cos();
	void reloadListCos(const VectorDinamic<book> books);
	void reloadListFiltrare(const VectorDinamic<book> books);
	void adaugaButoane(const map<string, int> books_map);

public:
	BookStoreGUI(bookService& ctr, Cos& cos, cosReadOnlyGUI& cosRO) :ctr{ ctr }, cos{ cos }, cosRO{ cosRO } {
		initGUICmps();
		connectSignalsSlots();
		reloadList(ctr.get_all());
		adaugaButoane(ctr.get_raport());
	}
	void update() override {
		reloadListCos(ctr.getCos());
	}

};
