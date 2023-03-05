#pragma once
#include "book.h"
#include "repo.h"

class ActiuneUndo {
public:
	virtual void doUndo() = 0;
	virtual ~ActiuneUndo() = default;
};

class UndoAdauga : public ActiuneUndo {
	book bookAdaugat;
	Repo& rep;

public:
	UndoAdauga(Repo& rep, const book& b) : rep{ rep }, bookAdaugat{ b }{}

	void doUndo() override {
		rep.del(bookAdaugat.get_title());
	}
};

class UndoSterge : public ActiuneUndo {
	book bookSters;
	Repo& rep;

public:
	UndoSterge(Repo& rep, const book& b) : rep{ rep }, bookSters{ b }{}
	void doUndo() override {
		rep.store(bookSters);
	}
};

class UndoModifica : public ActiuneUndo {
	book bookModificat;
	Repo& rep;

public:
	UndoModifica(Repo& rep, const book& b) : rep{ rep }, bookModificat{ b }{}
	void doUndo() override {
		rep.update(bookModificat.get_author(), bookModificat.get_title());
	}
};


