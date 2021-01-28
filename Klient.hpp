#pragma once

#include <iostream>
#include <vector>
#include "Sklep.hpp"

class klient {
public:
	klient(std::string i, bool s) : imie{ i }, staly_klient{ s }, portfel{ 2000 }, ilosc{ 0 } { if (s == true) { rabat = 0.9; } else { rabat = 1; } } //klient dostaje do portfela 2000 zl, by ulatwic testowanie programu
	void dodaj_do_koszyka(std::string n, double c, double r, int liczba, sklep& sk) {
			int new_liczba = sprawdz_ilosc_koszyk(n, r, liczba);
			if (sk.sprawdz_ilosc(new_liczba, n, r) == true) {
				koszyk_zagli.emplace_back(produkt(n, c, r, liczba));
				ilosc = ilosc + liczba;
			}
			else { std::cout << " " << std::endl;	std::cout << "Nie ma takiej ilosci, zmniejsz ilosc" << std::endl; }
		}
	void dodaj_do_portfela(double Wplata) { portfel = Wplata + get_portfel(); }
	void id() {
		if (get_staly() == true) {
			std::cout << " " << std::endl;
			double rabat_w = 100 - rabat * 100;
			std::cout << "Klient o imieniu: " << get_imie() << " Staly klient, Twoj rabat to: " << rabat_w << "%" << " Stan portfela: " << get_portfel() << " zlotych" << " Ilosc produktow w koszyku: " << get_ilosc() << std::endl;
		} else {std::cout << "Klient o imieniu: " << get_imie()  << " Stan portfela: " << get_portfel() << " zlotych"<< " Ilosc produktow w koszyku: " << get_ilosc() << std::endl;}
	}
	void wyswietl_koszyk() const {
		std::cout << "Twoj koszyk zawiera: " << std::endl;
		if (koszyk_zagli.empty()) {
			std::cout << " " << std::endl;
			std::cout << "Twoj koszyk jest pusty" << std::endl;
		} else { for (auto x : koszyk_zagli) { std::cout << " " << std::endl; std::cout << "Nazwa produktu: " << x.get_Name() << " Rozmiar: " << x.get_Rozmiar() << " Ilosc: " << x.get_Ilosc() << std::endl;}}
	}
	int sprawdz_ilosc_koszyk(std::string s, double r, int i) {
		auto result = std::find_if(koszyk_zagli.begin(), koszyk_zagli.end(), [&s, &r](produkt p) { return p.get_Name() == s && p.get_Rozmiar() == r; });
		if (result != koszyk_zagli.end()) {return result->get_Ilosc() + i;}
		else {return i;}
	}
	void set_Ilosc(int i) { ilosc = i; }
	double get_portfel() const { return portfel; }
	bool get_staly() const { return staly_klient; }
	void set_staly(bool w) { staly_klient = w; }
	std::string get_imie() const { return imie; }
	int get_ilosc() const { return ilosc; }
	std::vector<produkt>& get_koszyk(){ return koszyk_zagli; }
	double get_rabat() const { return rabat; }
	void set_rabat(double r) { rabat = r; }
private:
	std::vector<produkt> koszyk_zagli;
	bool staly_klient;
	int ilosc;
	double portfel;
	std::string imie;
	double rabat;
};