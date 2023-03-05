#include "QtWidgetsApplication1.h"
#include <QtWidgets/QApplication>

#include "service.h"
#include "book.h"
#include "bookGUI.h"
#include "cosReadOnlyGUI.h"

void runGUI(int argc, char* argv[])
{
    QApplication a(argc, argv);
    BookRepoFile rep{ "books.txt" };
    bookValidator val;
    CosCVS cos;
    cosReadOnlyGUI cosRO{cos};
    bookService ctr{ rep,val,cos };

    BookStoreGUI gui{ ctr, cos, cosRO };
    gui.setGeometry(0, 0, 750, 500);
    gui.setStyleSheet("color: red; background-color: black");
    gui.show();
    a.exec();

}

int main(int argc, char* argv[]) {
    runGUI(argc, argv);
}
