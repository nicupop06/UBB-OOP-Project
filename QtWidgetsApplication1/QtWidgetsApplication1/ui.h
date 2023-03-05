#pragma once
#include "service.h"
#include "cos.h"

class UI
{
private:
	bookService& serv;
public:
	UI(bookService& serv) noexcept :serv{ serv } {

	}

	void principal_menu();
	void menu_notif();
	void populeaza_lista();
};