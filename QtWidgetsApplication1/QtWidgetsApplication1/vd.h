#pragma once
#include "book.h"
#include <vector>
using std::vector;

template<typename ElemIt>
class IteratorVD;

template<typename ElemType>
class VectorDinamic {
private:
	int cap;
	int lg;
	ElemType* elems;
public:
	//constructorul
	VectorDinamic() : cap{ 10 }, lg{ 0 }, elems{ new ElemType[cap] } {

	}

	//constructorul de copiere
	VectorDinamic(const VectorDinamic& ot) : cap{ ot.cap }, lg{ ot.lg }, elems{ new ElemType[ot.cap] } {
		for (int i = 0; i < lg; i++) {
			elems[i] = ot.elems[i];
		}
	}

	//suprascrierea operatorului =
	VectorDinamic& operator=(const VectorDinamic& ot)
	{
		if (this == &ot) {
			return *this;
		}
		delete[] elems;
		elems = new ElemType[ot.cap];
		for (int i = 0; i < ot.lg; i++)
			elems[i] = ot.elems[i];
		cap = ot.cap;
		lg = ot.lg;
		return *this;
	}

	~VectorDinamic()
	{
		delete[] elems;
	}

	VectorDinamic(VectorDinamic&& ot) {
		// Copy the data pointer from other
		elems = ot.elems;
		lg = ot.lg;
		cap = ot.cap;

		// Release the data pointer from the source object so that  
		// the destructor does not free the memory multiple times.  
		ot.elems = nullptr;
		ot.lg = 0;
		ot.cap = 0;
	}

	VectorDinamic& operator=(VectorDinamic&& ot) noexcept {
		if (this == &ot) {
			return *this;
		}
		delete[] elems;
		// Copy the data pointer from other
		elems = ot.elems;
		lg = ot.lg;
		cap = ot.cap;

		// Release the data pointer from the source object so that  
		// the destructor does not free the memory multiple times.  
		ot.elems = nullptr;
		ot.lg = 0;
		ot.cap = 0;
		return *this;
	}

	//suprascrierea operatorului ==
	bool operator==(const VectorDinamic& ot) const
	{
		if (ot.lg != lg)
			return false;
		for (int i = 0; i < ot.lg; i++)
		{
			if (!(ot.elems[i] == elems[i]))
				return false;
		}
		return true;
	}

	VectorDinamic(vector<ElemType> bookService) : cap{ 5 }, lg{ 0 }, elems{ new ElemType[cap] }
	{
		for (const auto& l : bookService)
		{
			push_back(l);
		}
	}

	vector<ElemType> toStdVector()
	{
		vector<ElemType> rez;
		for (int i = 0; i < lg; i++)
			rez.push_back(elems[i]);
		return rez;
	}

	int size() const noexcept
	{
		return lg;
	}

	void push_back(const ElemType& p) {
		if (cap == lg)
		{
			ElemType* aux = new ElemType[cap * 2];
			for (int i = 0; i < lg; i++)
			{
				aux[i] = elems[i];
			}
			delete[] elems;
			elems = aux;
			cap = cap * 2;
		}
		elems[lg] = p;
		lg++;
	}

	void erase(int index)
	{
		for (int i = index; i < lg - 1; i++)
			elems[i] = elems[i + 1];
		this->lg--;
	}

	ElemType& front() noexcept
	{
		return elems[0];
	}

	ElemType& back() noexcept
	{
		return elems[lg - 1];
	}

	void modify(int index, ElemType& el)
	{
		elems[index] = el;
	}

	ElemType& at(int index) const noexcept
	{
		return elems[index];
	}


	friend class IteratorVD<ElemType>;

	IteratorVD<ElemType> begin() noexcept
	{
		return IteratorVD<ElemType>(*this);
	}

	IteratorVD<ElemType> end() noexcept
	{
		return IteratorVD<ElemType>(*this, lg);
	}
};


template<typename ElemType>
class IteratorVD {
private:
	const VectorDinamic<ElemType>& v;
	int curent = 0;
public:
	IteratorVD(const VectorDinamic < ElemType>& v) noexcept : v{ v } {}

	IteratorVD(const VectorDinamic < ElemType>& v, int curent) noexcept : v{ v }, curent{ curent } {}

	bool valid() const
	{
		return curent < v.lg;
	}

	ElemType& element() const noexcept
	{
		return v.elems[curent];
	}

	void next() noexcept
	{
		curent++;
	}

	ElemType& operator*() noexcept
	{
		return element();
	}

	void operator++() noexcept
	{
		next();
	}

	bool operator==(const IteratorVD& ot) noexcept
	{
		return curent == ot.curent;
	}

	bool operator!=(const IteratorVD& ot) noexcept
	{
		return !(*this == ot);
	}
};