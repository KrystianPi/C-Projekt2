#pragma once
#include <vector>


class produkt {
public:
	produkt(std::string n, double c, double r, int i) : name(n), cena(c), rozmiar(r), ilosc(i) {};
	std::string get_Name() { return name; }
	int get_Ilosc() { return ilosc; }
	double get_Rozmiar() { return rozmiar; }
	double get_Cena() { return cena; }
	void set_Ilosc(int i) { ilosc = i; }
	void zwieksz_Ilosc(int i) { ilosc = ilosc + i; }
	void zmniejsz_Ilosc(int i) { ilosc = ilosc - i; }
private:
	std::string name;
	double cena;
	double rozmiar;
	int ilosc;
};
