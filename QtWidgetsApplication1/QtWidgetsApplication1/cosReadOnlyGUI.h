#pragma once
#include <qwidget.h>
#include "observer.h"
#include "cos.h"
#include <QPainter>

class cosReadOnlyGUI : public QWidget, public Observer {
	Cos& cos;

public:
	cosReadOnlyGUI(Cos& cos) : cos{ cos } {
		cos.addObserver(this);
		update();
	}

    void paintEvent(QPaintEvent* ev) override {
        QPainter p{ this };
        for (int i = 0; i < cos.getAllCos().size(); i++) {
            int x = rand() % width();
            int y = rand() % height();
            p.setBrush(QBrush(Qt::magenta));
            p.drawEllipse(x, y, 100, 100);

        }
    }

    void update() override {
        this->repaint();
    }

};