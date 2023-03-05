#include "cos.h"
#include<fstream>
using std::shuffle;
using namespace std;

void Cos::addApToCos(const book& b)
{
	cosList.push_back(b);
	notify();
}

void Cos::emptyCos() noexcept
{
	cosList.clear();
	notify();
}

void Cos::addRandomBooks(vector <book> v, int nr)
{
	shuffle(v.begin(), v.end(), std::default_random_engine(std::random_device{}()));
	while (cosList.size() < nr && v.size() > 0)
	{
		cosList.push_back(v.back());
		v.pop_back();
	}
	notify();
}

const vector<book>& Cos::getAllCos() noexcept
{
	return cosList;
	
}

void Cos::exportCos(string file) {
	string fisier = file + ".html";
	std::ofstream filename(fisier);
	for (auto& n : this->getAllCos())
	{
		filename << n.get_title() << ',' << n.get_author() << ',' << n.get_type() << ',' << n.get_year() << "<br/>";
	}
	filename.close();
}

void CosCVS::exportCos(string file) {
	string fisier = file + ".cvs";
	std::ofstream filename(fisier);
	for (auto& n : this->getAllCos())
	{
		filename << n.get_title() << ',' << n.get_author() << ',' << n.get_type() << ',' << n.get_year()<<endl;
	}
	filename.close();
}
