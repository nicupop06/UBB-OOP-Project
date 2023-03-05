#pragma once
#include "book.h"
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
#include "observer.h"

using std::vector;

class Cos : public Observable {
private:
	vector<book> cosList;
public:
	Cos() = default;
	void addApToCos(const book& l);
	void emptyCos() noexcept;
	void addRandomBooks(vector<book> l, int nr);
	virtual void exportCos(string file_name);
	const vector<book>& getAllCos() noexcept;
};

class CosCVS : public Cos {
public:
	void exportCos(string file_name) override;
};